
var primitivemap = require('./primitivemap')

var m = new primitivemap.StringStringMap()

m.put('hello', 'world')
console.log('hello ' + m.get('hello'))

m.put(undefined,undefined)

var lookup = {}
for(var i=0;i<100000;++i){
	var k = 'key_'+i
	var v = 'value_'+i+'_'+Math.random()
	lookup[k] = v
	m.put(k,v)
}

Object.keys(lookup).forEach(function(key){
	var mv = m.get(key)
	var lv = lookup[key]
	if(mv !== lv){
		throw new Error('mismatch ' + mv + '|'+lv)
	}
})

console.log('ok')
