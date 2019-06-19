self.importScripts('emscripten_fetch.js')

var Module = typeof Module !== 'undefined' ? Module : {};

self.onmessage = (data) => {
  console.log(data.data)
  Module.DoSyncFetch(data.data);
}

Module['onRuntimeInitialized'] = () => {
  console.log('wasm loaded')
}
