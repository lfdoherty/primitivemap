
var primitivemap = require('./primitivemap')

function FakeIntIntMap(){
	this.data = {}
}
FakeIntIntMap.prototype.get = function(key){
	return this.data[key]
}
FakeIntIntMap.prototype.put = function(key, value){
	this.data[key] = value
}

var m = new FakeIntIntMap()

//var m = new primitivemap.IntIntMap()

var v = m.get(10)

console.log('nonexistent:' + v)

m.put(10,20)
v = m.get(10)
console.log('put:' + v)

var start = Date.now()

var N = 50*1000*1000


for(var i=0;i<N;++i){
	m.put(i,i+1)
}

console.log('*write finished in ' + (Date.now()-start))
var start = Date.now()

var sum = 0
for(var i=0;i<N;++i){
	sum += m.get(i)
}

console.log('*read finished in ' + (Date.now()-start))


var k = {}

setTimeout(function(){
	
	//global.gc();
	console.log(require('util').inspect(process.memoryUsage()));

	var start = Date.now()

	for(var i=0;i<N;++i){
		k[i] = i+1
	}

	console.log('write finished in ' + (Date.now()-start))

	var sum = 0
	for(var i=0;i<N;++i){
		sum += k[i]
	}

	console.log('read finished in ' + (Date.now()-start))

	//global.gc();
	setTimeout(function(){
		//global.gc();
		console.log(require('util').inspect(process.memoryUsage()));
	},100)
},100)

setInterval(function(){},1000)
