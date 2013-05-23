{
  "targets": [
    {
      "target_name": "primitivemap",
      "sources": [ "src/node_primitivemap.cc" ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ]
    }
  ]
}
