
/*

Grow your node.js process to 3.3GB without special configuration or GC unhappiness.

*/


var primitivemap = require('./../primitivemap')

var m = new primitivemap.StringStringMap()

m.put('hello', 'world')
console.log('hello ' + m.get('hello'))

m.put(undefined,undefined)

var lookup = {}
for(var i=0;i<1000*1000*20;++i){
	var k = 'key_'+i
	var v = 'value_'+i+'_'+Math.random()
	if(Math.random() < .01) lookup[k] = v
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
