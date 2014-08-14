
var primitivemap = require('./../primitivemap')

var m = new primitivemap.StringDoubleMap()

var now = Date.now()
var next = now+1
var prev = now-1
var big = 9007199254740000
m.put('now', now)
m.put('prev',prev)
m.put('next',next)
m.put('big', big)
if(m.get('now') !== now) throw new Error('inexact timestamp storage')
if(m.get('prev') !== prev) throw new Error('inexact timestamp storage')
if(m.get('next') !== next) throw new Error('inexact timestamp storage')
if(m.get('big') !== big) throw new Error('inexact timestamp storage')

console.log('timestamps stored correctly')