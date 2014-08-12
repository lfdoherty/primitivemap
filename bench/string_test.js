
var primitivemap = require('./../primitivemap')

var m = new primitivemap.StringStringMap()

m.put('hello', 'world')
console.log('hello ' + m.get('hello'))

m.put(undefined,undefined)

var lookup = {}
var deleted = {}
for(var i=0;i<100000;++i){
	var k = 'key_'+i
	var v = 'value_'+i+'_'+Math.random()
	lookup[k] = v
	m.put(k,v)
	if(Math.random() < .2){
		deleted[k] = true
		m.rm(k)
	}
}

Object.keys(lookup).forEach(function(key){
	var mv = m.get(key)
	var lv = lookup[key]
	if(deleted[key]){
		if(mv != null) throw new Error('not deleted properly: ' + key)
	}else{
		if(mv !== lv){
			throw new Error('mismatch ' + mv + '|'+lv)
		}
	}
})

console.log('ok')
