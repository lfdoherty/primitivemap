
#include <v8.h>
#include <node.h>
#include <string>
#include <map>

#include "sparsehash/dense_hash_map"

/*

= V8 recap =

More detailed info at http://code.google.com/apis/v8/embed.html

== Context ==

A context is an execution environment that allows separate, unrelated, JavaScript applications to run in a single instance of V8.
Must be explicitly declared.

== Handles ==

Defines the lifetime of an object.

Local (deleted when scope deleted),
Persistent (deleted manually),
Handle (parent class)

== Handle scope ==

A container that holds lots of handles.
When handle scope's destructor is called (implicitly called when ~ called) all handles created within that scope are removed

== Templates ==

A template is a blueprint for JavaScript functions and objects in a context. You can use a template to wrap C++ functions and data structures within JavaScript objects so that they can be manipulated by JavaScript scripts. (i.e. a browser's DOM aka 'document')

Function template: A function template is the blueprint for a single function.
Object templates: Each function template has an associated object template. accessors/interceptor C++ callbacks

*/

using namespace v8;

v8::Handle<v8::Value> ErrorException(const char *msg);
v8::Handle<v8::Value> VException(const char *msg);

Handle<Value> ErrorException(const char *msg)
{
    HandleScope scope;
    return Exception::Error(String::New(msg));
}

Handle<Value> VException(const char *msg) {
    HandleScope scope;
    return ThrowException(ErrorException(msg));
}

class IntIntMap : node::ObjectWrap {
  private:
  public:
	google::dense_hash_map<int32_t,int32_t> data;

    IntIntMap(){
	   data.set_empty_key(-214783648);
	   data.set_deleted_key(-214783647);
    }
    ~IntIntMap() {}
    
    static v8::Persistent<FunctionTemplate> constructor_template;

    static Handle<Value> New(const Arguments& args) {
		HandleScope scope;
		IntIntMap* instance = new IntIntMap();
		instance->Wrap(args.This());
		return args.This();
    }
	static v8::Handle<Value> GetSize(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
		HandleScope scope;
		IntIntMap* instance = node::ObjectWrap::Unwrap<IntIntMap>(info.Holder());
		return scope.Close(Integer::New(instance->data.size()));
	}
    static v8::Handle<Value> get(const Arguments& args) {
	    HandleScope scope;
		IntIntMap* instance = node::ObjectWrap::Unwrap<IntIntMap>(args.This());
    	int index = args[0]->Int32Value();
		google::dense_hash_map<int32_t,int32_t>::const_iterator it = instance->data.find(index);
		if(it == instance->data.end()){
			return scope.Close(Null());
		}else{
	    	return scope.Close(Int32::New(it->second));
		}
    }
    static v8::Handle<Value> put(const Arguments& args) {
	    HandleScope scope;
		IntIntMap* instance = node::ObjectWrap::Unwrap<IntIntMap>(args.This());
    	int32_t key = args[0]->Int32Value();
    	int32_t value = args[1]->Int32Value();
		instance->data[key] = value;
		return scope.Close(Null());
    }
    static v8::Handle<Value> remove(const Arguments& args) {
	    HandleScope scope;
		IntIntMap* instance = node::ObjectWrap::Unwrap<IntIntMap>(args.This());
    	int key = args[0]->Int32Value();
		google::dense_hash_map<int32_t,int32_t>::iterator it = instance->data.find(key);
		if(it != instance->data.end()){
			instance->data.erase(it);
		}
		return scope.Close(Null());
    }
    static v8::Handle<Value> clear(const Arguments& args) {
	    HandleScope scope;
		IntIntMap* instance = node::ObjectWrap::Unwrap<IntIntMap>(args.This());
		instance->data.clear();
		return scope.Close(Null());
    }
};


class IntDoubleMap : node::ObjectWrap {
  private:
  public:
	google::dense_hash_map<int32_t,double> data;

    IntDoubleMap(){
	   data.set_empty_key(-214783648);
	   data.set_deleted_key(-214783647);
    }
    ~IntDoubleMap() {}
    
    static v8::Persistent<FunctionTemplate> constructor_template;

    static Handle<Value> New(const Arguments& args) {
		HandleScope scope;

		IntDoubleMap* instance = new IntDoubleMap();

		instance->Wrap(args.This());
		return args.This();
    }
	static v8::Handle<Value> GetSize(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
		HandleScope scope;
		IntDoubleMap* instance = node::ObjectWrap::Unwrap<IntDoubleMap>(info.Holder());
		return scope.Close(Integer::New(instance->data.size()));
	}

    static v8::Handle<Value> get(const Arguments& args) {
	    HandleScope scope;
		IntDoubleMap* instance = node::ObjectWrap::Unwrap<IntDoubleMap>(args.This());

    	int index = args[0]->Int32Value();

		google::dense_hash_map<int,double>::const_iterator it = instance->data.find(index);
		if(it == instance->data.end()){
			return scope.Close(Null());
		}else{
	    	return scope.Close(Number::New(it->second));
		}
    }
    static v8::Handle<Value> put(const Arguments& args) {
	    HandleScope scope;
		IntDoubleMap* instance = node::ObjectWrap::Unwrap<IntDoubleMap>(args.This());

    	int key = args[0]->Int32Value();
    	double value = args[1]->NumberValue();

		instance->data[key] = value;
		
		return scope.Close(Null());
    }
    static v8::Handle<Value> remove(const Arguments& args) {
	    HandleScope scope;
		IntDoubleMap* instance = node::ObjectWrap::Unwrap<IntDoubleMap>(args.This());

    	int key = args[0]->Int32Value();

		google::dense_hash_map<int,double>::iterator it = instance->data.find(key);
		if(it != instance->data.end()){
			instance->data.erase(it);
		}
		return scope.Close(Null());
    }
    static v8::Handle<Value> clear(const Arguments& args) {
	    HandleScope scope;
		IntDoubleMap* instance = node::ObjectWrap::Unwrap<IntDoubleMap>(args.This());

		instance->data.clear();
		return scope.Close(Null());
    }
};


class StringStringMap : node::ObjectWrap {
  private:
  public:
	std::string empty_key;
	std::string deleted_key;
	google::dense_hash_map<std::string,std::string> data;

    StringStringMap(){
    	empty_key = "";
    	deleted_key = "cbb47b9d-d565-455a-b60f-3dc97df836b4";
		data.set_empty_key(empty_key);
		data.set_deleted_key(deleted_key);
    }
    ~StringStringMap() {}
    
    static v8::Persistent<FunctionTemplate> constructor_template;

    static Handle<Value> New(const Arguments& args) {
		HandleScope scope;
		StringStringMap* instance = new StringStringMap();
		instance->Wrap(args.This());
		return args.This();
    }
	static v8::Handle<Value> GetSize(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
		HandleScope scope;
		StringStringMap* instance = node::ObjectWrap::Unwrap<StringStringMap>(info.Holder());
		return scope.Close(Integer::New(instance->data.size()));
	}

    static v8::Handle<Value> get(const Arguments& args) {
	    HandleScope scope;
		StringStringMap* instance = node::ObjectWrap::Unwrap<StringStringMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		google::dense_hash_map<std::string,std::string>::const_iterator it = instance->data.find(key);
		if(it == instance->data.end()){
			return scope.Close(Null());
		}else{
	    	return scope.Close(String::New(it->second.c_str(),it->second.size()));
		}
    }
	static v8::Handle<Value> remove(const Arguments& args) {
	    HandleScope scope;
		StringStringMap* instance = node::ObjectWrap::Unwrap<StringStringMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		google::dense_hash_map<std::string,std::string>::iterator it = instance->data.find(key);
		if(it != instance->data.end()){
			instance->data.erase(it);
		}
		return scope.Close(Null());
    }
    static v8::Handle<Value> put(const Arguments& args) {
	    HandleScope scope;
		StringStringMap* instance = node::ObjectWrap::Unwrap<StringStringMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		std::string value = *v8::String::Utf8Value(args[1]->ToString());
		instance->data[key] = value;
		return scope.Close(Null());
    }
     static v8::Handle<Value> clear(const Arguments& args) {
	    HandleScope scope;
		StringStringMap* instance = node::ObjectWrap::Unwrap<StringStringMap>(args.This());
		instance->data.clear();
		return scope.Close(Null());
    }
};


class IntStringMap : node::ObjectWrap {
  private:
  public:
	google::dense_hash_map<int32_t,std::string> data;

    IntStringMap(){
		data.set_empty_key(-214783648);
		data.set_deleted_key(-214783647);
    }
    ~IntStringMap() {}
    
    static v8::Persistent<FunctionTemplate> constructor_template;

    static Handle<Value> New(const Arguments& args) {
		HandleScope scope;
		IntStringMap* instance = new IntStringMap();
		instance->Wrap(args.This());
		return args.This();
    }
	static v8::Handle<Value> GetSize(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
		HandleScope scope;
		IntStringMap* instance = node::ObjectWrap::Unwrap<IntStringMap>(info.Holder());
		return scope.Close(Integer::New(instance->data.size()));
	}

    static v8::Handle<Value> get(const Arguments& args) {
	    HandleScope scope;
		IntStringMap* instance = node::ObjectWrap::Unwrap<IntStringMap>(args.This());
    	int key = args[0]->Int32Value();
		google::dense_hash_map<int32_t,std::string>::const_iterator it = instance->data.find(key);
		if(it == instance->data.end()){
			return scope.Close(Null());
		}else{
	    	return scope.Close(String::New(it->second.c_str(),it->second.size()));
		}
    }
	static v8::Handle<Value> remove(const Arguments& args) {
	    HandleScope scope;
		IntStringMap* instance = node::ObjectWrap::Unwrap<IntStringMap>(args.This());
    	int key = args[0]->Int32Value();
		google::dense_hash_map<int32_t,std::string>::iterator it = instance->data.find(key);
		if(it != instance->data.end()){
			instance->data.erase(it);
		}
		return scope.Close(Null());
    }
    static v8::Handle<Value> put(const Arguments& args) {
	    HandleScope scope;
		IntStringMap* instance = node::ObjectWrap::Unwrap<IntStringMap>(args.This());
    	int key = args[0]->Int32Value();
		std::string value = *v8::String::Utf8Value(args[1]->ToString());
		instance->data[key] = value;
		return scope.Close(Null());
    }
     static v8::Handle<Value> clear(const Arguments& args) {
	    HandleScope scope;
		IntStringMap* instance = node::ObjectWrap::Unwrap<IntStringMap>(args.This());
		instance->data.clear();
		return scope.Close(Null());
    }
};

class StringIntMap : node::ObjectWrap {
  private:
  public:
	std::string empty_key;
	std::string deleted_key;
	google::dense_hash_map<std::string,int32_t> data;

    StringIntMap(){
    	empty_key = "";
    	deleted_key = "cbb47b9d-d565-455a-b60f-3dc97df836b4";
		data.set_empty_key(empty_key);
		data.set_deleted_key(deleted_key);
    }
    ~StringIntMap() {}
    
    static v8::Persistent<FunctionTemplate> constructor_template;

    static Handle<Value> New(const Arguments& args) {
		HandleScope scope;
		StringIntMap* instance = new StringIntMap();
		instance->Wrap(args.This());
		return args.This();
    }
	static v8::Handle<Value> GetSize(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
		HandleScope scope;
		StringIntMap* instance = node::ObjectWrap::Unwrap<StringIntMap>(info.Holder());
		return scope.Close(Integer::New(instance->data.size()));
	}

    static v8::Handle<Value> get(const Arguments& args) {
	    HandleScope scope;
		StringIntMap* instance = node::ObjectWrap::Unwrap<StringIntMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		google::dense_hash_map<std::string,int32_t>::const_iterator it = instance->data.find(key);
		if(it == instance->data.end()){
			return scope.Close(Null());
		}else{
	    	return scope.Close(Int32::New(it->second));
		}
    }
	static v8::Handle<Value> remove(const Arguments& args) {
	    HandleScope scope;
		StringIntMap* instance = node::ObjectWrap::Unwrap<StringIntMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		google::dense_hash_map<std::string,int32_t>::iterator it = instance->data.find(key);
		if(it != instance->data.end()){
			instance->data.erase(it);
		}
		return scope.Close(Null());
    }
    static v8::Handle<Value> put(const Arguments& args) {
	    HandleScope scope;
		StringIntMap* instance = node::ObjectWrap::Unwrap<StringIntMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		int value = args[1]->Int32Value();
		instance->data[key] = value;
		return scope.Close(Null());
    }
    static v8::Handle<Value> clear(const Arguments& args) {
	    HandleScope scope;
		IntStringMap* instance = node::ObjectWrap::Unwrap<IntStringMap>(args.This());

		instance->data.clear();
		return scope.Close(Null());
    }
};

class StringDoubleMap : node::ObjectWrap {
  private:
  public:
	std::string empty_key;
	std::string deleted_key;
	google::dense_hash_map<std::string,double> data;

    StringDoubleMap(){
    	empty_key = "";
    	deleted_key = "cbb47b9d-d565-455a-b60f-3dc97df836b4";
		data.set_empty_key(empty_key);
		data.set_deleted_key(deleted_key);
    }
    ~StringDoubleMap() {}
    
    static v8::Persistent<FunctionTemplate> constructor_template;

    static Handle<Value> New(const Arguments& args) {
		HandleScope scope;
		StringDoubleMap* instance = new StringDoubleMap();
		instance->Wrap(args.This());
		return args.This();
    }
	static v8::Handle<Value> GetSize(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
		HandleScope scope;
		StringDoubleMap* instance = node::ObjectWrap::Unwrap<StringDoubleMap>(info.Holder());
		return scope.Close(Integer::New(instance->data.size()));
	}

    static v8::Handle<Value> get(const Arguments& args) {
	    HandleScope scope;
		StringDoubleMap* instance = node::ObjectWrap::Unwrap<StringDoubleMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		google::dense_hash_map<std::string,double>::const_iterator it = instance->data.find(key);
		if(it == instance->data.end()){
			return scope.Close(Null());
		}else{
	    	return scope.Close(Number::New(it->second));
		}
    }
	static v8::Handle<Value> remove(const Arguments& args) {
	    HandleScope scope;
		StringDoubleMap* instance = node::ObjectWrap::Unwrap<StringDoubleMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		google::dense_hash_map<std::string,double>::iterator it = instance->data.find(key);
		if(it != instance->data.end()){
			instance->data.erase(it);
		}
		return scope.Close(Null());
    }
    static v8::Handle<Value> put(const Arguments& args) {
	    HandleScope scope;
		StringDoubleMap* instance = node::ObjectWrap::Unwrap<StringDoubleMap>(args.This());
    	std::string key = *v8::String::Utf8Value(args[0]->ToString());
		double value = args[1]->NumberValue();
		instance->data[key] = value;
		return scope.Close(Null());
    }
     static v8::Handle<Value> clear(const Arguments& args) {
	    HandleScope scope;
		StringDoubleMap* instance = node::ObjectWrap::Unwrap<StringDoubleMap>(args.This());
		instance->data.clear();
		return scope.Close(Null());
    }
};
// @Node.js calls Init() when you load the extension through require()
// Init() defines our constructor function and prototype methods
// It then binds our constructor function as a property of the target object
// Target is the "target" onto which an extension is loaded. For example:
// var notify = require("../build/default/gtknotify.node"); will bind our constructor function to notify.Notification
// so that we can call "new notify.Notification();"
static void Init(Handle<Object> target) {
	// We need to declare a V8 scope so that our local handles are eligible for garbage collection.
	// once the Init() returns.
	v8::HandleScope scope;

	{//set up Batch
		v8::Local<FunctionTemplate> lftIntInt = v8::FunctionTemplate::New(IntIntMap::New);
		IntIntMap::constructor_template = v8::Persistent<FunctionTemplate>::New(lftIntInt);
		IntIntMap::constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
		IntIntMap::constructor_template->SetClassName(v8::String::NewSymbol("IntIntMap"));

		v8::Local<FunctionTemplate> lftIntDouble = v8::FunctionTemplate::New(IntDoubleMap::New);
		IntDoubleMap::constructor_template = v8::Persistent<FunctionTemplate>::New(lftIntDouble);
		IntDoubleMap::constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
		IntDoubleMap::constructor_template->SetClassName(v8::String::NewSymbol("IntDoubleMap"));

		v8::Local<FunctionTemplate> lftIntString = v8::FunctionTemplate::New(IntStringMap::New);
		IntStringMap::constructor_template = v8::Persistent<FunctionTemplate>::New(lftIntString);
		IntStringMap::constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
		IntStringMap::constructor_template->SetClassName(v8::String::NewSymbol("IntStringMap"));

		v8::Local<FunctionTemplate> lftStringString = v8::FunctionTemplate::New(StringStringMap::New);
		StringStringMap::constructor_template = v8::Persistent<FunctionTemplate>::New(lftStringString);
		StringStringMap::constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
		StringStringMap::constructor_template->SetClassName(v8::String::NewSymbol("StringStringMap"));

		v8::Local<FunctionTemplate> lftStringInt = v8::FunctionTemplate::New(StringIntMap::New);
		StringIntMap::constructor_template = v8::Persistent<FunctionTemplate>::New(lftStringInt);
		StringIntMap::constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
		StringIntMap::constructor_template->SetClassName(v8::String::NewSymbol("StringIntMap"));

		v8::Local<FunctionTemplate> lftStringDouble = v8::FunctionTemplate::New(StringDoubleMap::New);
		StringDoubleMap::constructor_template = v8::Persistent<FunctionTemplate>::New(lftStringDouble);
		StringDoubleMap::constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
		StringDoubleMap::constructor_template->SetClassName(v8::String::NewSymbol("StringDoubleMap"));

		// Set property accessors
		IntIntMap::constructor_template->InstanceTemplate()->SetAccessor(String::New("size"), IntIntMap::GetSize);
		IntDoubleMap::constructor_template->InstanceTemplate()->SetAccessor(String::New("size"), IntDoubleMap::GetSize);
		IntStringMap::constructor_template->InstanceTemplate()->SetAccessor(String::New("size"), IntStringMap::GetSize);
		StringStringMap::constructor_template->InstanceTemplate()->SetAccessor(String::New("size"), StringStringMap::GetSize);
		StringIntMap::constructor_template->InstanceTemplate()->SetAccessor(String::New("size"), StringIntMap::GetSize);

		NODE_SET_PROTOTYPE_METHOD(IntIntMap::constructor_template, "get", IntIntMap::get);
		NODE_SET_PROTOTYPE_METHOD(IntIntMap::constructor_template, "put", IntIntMap::put);
		NODE_SET_PROTOTYPE_METHOD(IntIntMap::constructor_template, "rm", IntIntMap::remove);
		NODE_SET_PROTOTYPE_METHOD(IntIntMap::constructor_template, "clear", IntIntMap::clear);

		NODE_SET_PROTOTYPE_METHOD(IntDoubleMap::constructor_template, "get", IntDoubleMap::get);
		NODE_SET_PROTOTYPE_METHOD(IntDoubleMap::constructor_template, "put", IntDoubleMap::put);
		NODE_SET_PROTOTYPE_METHOD(IntDoubleMap::constructor_template, "rm", IntDoubleMap::remove);
		NODE_SET_PROTOTYPE_METHOD(IntDoubleMap::constructor_template, "clear", IntDoubleMap::clear);

		NODE_SET_PROTOTYPE_METHOD(IntStringMap::constructor_template, "get", IntStringMap::get);
		NODE_SET_PROTOTYPE_METHOD(IntStringMap::constructor_template, "put", IntStringMap::put);
		NODE_SET_PROTOTYPE_METHOD(IntStringMap::constructor_template, "rm", IntStringMap::remove);
		NODE_SET_PROTOTYPE_METHOD(IntStringMap::constructor_template, "clear", IntStringMap::clear);

		NODE_SET_PROTOTYPE_METHOD(StringStringMap::constructor_template, "get", StringStringMap::get);
		NODE_SET_PROTOTYPE_METHOD(StringStringMap::constructor_template, "put", StringStringMap::put);
		NODE_SET_PROTOTYPE_METHOD(StringStringMap::constructor_template, "rm", StringStringMap::remove);
		NODE_SET_PROTOTYPE_METHOD(StringStringMap::constructor_template, "clear", StringStringMap::clear);

		NODE_SET_PROTOTYPE_METHOD(StringIntMap::constructor_template, "get", StringIntMap::get);
		NODE_SET_PROTOTYPE_METHOD(StringIntMap::constructor_template, "put", StringIntMap::put);
		NODE_SET_PROTOTYPE_METHOD(StringIntMap::constructor_template, "rm", StringIntMap::remove);
		NODE_SET_PROTOTYPE_METHOD(StringIntMap::constructor_template, "clear", StringIntMap::clear);

		NODE_SET_PROTOTYPE_METHOD(StringDoubleMap::constructor_template, "get", StringDoubleMap::get);
		NODE_SET_PROTOTYPE_METHOD(StringDoubleMap::constructor_template, "put", StringDoubleMap::put);
		NODE_SET_PROTOTYPE_METHOD(StringDoubleMap::constructor_template, "rm", StringDoubleMap::remove);
		NODE_SET_PROTOTYPE_METHOD(StringDoubleMap::constructor_template, "clear", StringDoubleMap::clear);
	}

	target->Set(String::NewSymbol("IntIntMap"), IntIntMap::constructor_template->GetFunction());
	target->Set(String::NewSymbol("IntDoubleMap"), IntDoubleMap::constructor_template->GetFunction());
	target->Set(String::NewSymbol("IntStringMap"), IntStringMap::constructor_template->GetFunction());
	target->Set(String::NewSymbol("StringStringMap"), StringStringMap::constructor_template->GetFunction());
	target->Set(String::NewSymbol("StringIntMap"), StringIntMap::constructor_template->GetFunction());
	target->Set(String::NewSymbol("StringDoubleMap"), StringDoubleMap::constructor_template->GetFunction());
}

// What follows is boilerplate code:

/* Thats it for actual interfacing with v8, finally we need to let Node.js know how to dynamically load our code.
Because a Node.js extension can be loaded at runtime from a shared object, we need a symbol that the dlsym function can find,
so we do the following: */
// See https://www.cloudkick.com/blog/2010/aug/23/writing-nodejs-native-extensions/ & http://www.freebsd.org/cgi/man.cgi?query=dlsym
// Cause of name mangling in C++, we use extern C here

v8::Persistent<FunctionTemplate> IntIntMap::constructor_template;
v8::Persistent<FunctionTemplate> IntDoubleMap::constructor_template;
v8::Persistent<FunctionTemplate> IntStringMap::constructor_template;
v8::Persistent<FunctionTemplate> StringStringMap::constructor_template;
v8::Persistent<FunctionTemplate> StringIntMap::constructor_template;
v8::Persistent<FunctionTemplate> StringDoubleMap::constructor_template;

extern "C"
void init(Handle<Object> target) {
	HandleScope scope;
    Init(target);
}

NODE_MODULE(primitivemap, init);

