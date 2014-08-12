
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
};


class IntLongMap : node::ObjectWrap {
  private:
  public:
	google::dense_hash_map<int32_t,int64_t> data;

    IntLongMap(){
	   data.set_empty_key(-214783648);
    }
    ~IntLongMap() {}
    
    static v8::Persistent<FunctionTemplate> constructor_template;

    static Handle<Value> New(const Arguments& args) {
		HandleScope scope;

		IntLongMap* instance = new IntLongMap();

		instance->Wrap(args.This());
		return args.This();
    }
	static v8::Handle<Value> GetSize(v8::Local<v8::String> property, const v8::AccessorInfo& info) {
		HandleScope scope;
		IntLongMap* instance = node::ObjectWrap::Unwrap<IntLongMap>(info.Holder());
		return scope.Close(Integer::New(instance->data.size()));
	}

    static v8::Handle<Value> get(const Arguments& args) {
	    HandleScope scope;
		IntLongMap* instance = node::ObjectWrap::Unwrap<IntLongMap>(args.This());

    	int index = args[0]->Int32Value();

		google::dense_hash_map<int,int64_t>::const_iterator it = instance->data.find(index);
		if(it == instance->data.end()){
			return scope.Close(Null());
		}else{
	    	return scope.Close(Integer::New(it->second));
		}
    }
    static v8::Handle<Value> put(const Arguments& args) {
	    HandleScope scope;
		IntLongMap* instance = node::ObjectWrap::Unwrap<IntLongMap>(args.This());

    	int key = args[0]->Int32Value();
    	int64_t value = args[1]->IntegerValue();

		instance->data[key] = value;
		
		return scope.Close(Null());
    }
    static v8::Handle<Value> remove(const Arguments& args) {
	    HandleScope scope;
		IntLongMap* instance = node::ObjectWrap::Unwrap<IntLongMap>(args.This());

    	int key = args[0]->Int32Value();

		google::dense_hash_map<int,int64_t>::iterator it = instance->data.find(key);
		if(it != instance->data.end()){
			instance->data.erase(it);
		}
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

		v8::Local<FunctionTemplate> lftIntLong = v8::FunctionTemplate::New(IntLongMap::New);
		IntLongMap::constructor_template = v8::Persistent<FunctionTemplate>::New(lftIntLong);
		IntLongMap::constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
		IntLongMap::constructor_template->SetClassName(v8::String::NewSymbol("IntLongMap"));

		v8::Local<FunctionTemplate> lftStringString = v8::FunctionTemplate::New(StringStringMap::New);
		StringStringMap::constructor_template = v8::Persistent<FunctionTemplate>::New(lftStringString);
		StringStringMap::constructor_template->InstanceTemplate()->SetInternalFieldCount(1);
		StringStringMap::constructor_template->SetClassName(v8::String::NewSymbol("StringStringMap"));

		// Set property accessors
		IntIntMap::constructor_template->InstanceTemplate()->SetAccessor(String::New("size"), IntIntMap::GetSize);
		IntLongMap::constructor_template->InstanceTemplate()->SetAccessor(String::New("size"), IntLongMap::GetSize);
		StringStringMap::constructor_template->InstanceTemplate()->SetAccessor(String::New("size"), StringStringMap::GetSize);

		NODE_SET_PROTOTYPE_METHOD(IntIntMap::constructor_template, "get", IntIntMap::get);
		NODE_SET_PROTOTYPE_METHOD(IntIntMap::constructor_template, "put", IntIntMap::put);
		NODE_SET_PROTOTYPE_METHOD(IntIntMap::constructor_template, "rm", IntIntMap::remove);

		NODE_SET_PROTOTYPE_METHOD(IntLongMap::constructor_template, "get", IntLongMap::get);
		NODE_SET_PROTOTYPE_METHOD(IntLongMap::constructor_template, "put", IntLongMap::put);
		NODE_SET_PROTOTYPE_METHOD(IntLongMap::constructor_template, "rm", IntLongMap::remove);

		NODE_SET_PROTOTYPE_METHOD(StringStringMap::constructor_template, "get", StringStringMap::get);
		NODE_SET_PROTOTYPE_METHOD(StringStringMap::constructor_template, "put", StringStringMap::put);
		NODE_SET_PROTOTYPE_METHOD(StringStringMap::constructor_template, "rm", StringStringMap::remove);
	}

	target->Set(String::NewSymbol("IntIntMap"), IntIntMap::constructor_template->GetFunction());
	target->Set(String::NewSymbol("IntLongMap"), IntLongMap::constructor_template->GetFunction());
	target->Set(String::NewSymbol("StringStringMap"), StringStringMap::constructor_template->GetFunction());
}

// What follows is boilerplate code:

/* Thats it for actual interfacing with v8, finally we need to let Node.js know how to dynamically load our code.
Because a Node.js extension can be loaded at runtime from a shared object, we need a symbol that the dlsym function can find,
so we do the following: */
// See https://www.cloudkick.com/blog/2010/aug/23/writing-nodejs-native-extensions/ & http://www.freebsd.org/cgi/man.cgi?query=dlsym
// Cause of name mangling in C++, we use extern C here

v8::Persistent<FunctionTemplate> IntIntMap::constructor_template;
v8::Persistent<FunctionTemplate> IntLongMap::constructor_template;
v8::Persistent<FunctionTemplate> StringStringMap::constructor_template;

extern "C"
void init(Handle<Object> target) {
	HandleScope scope;
    Init(target);
}

NODE_MODULE(primitivemap, init);

