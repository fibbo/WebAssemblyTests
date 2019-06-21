self.importScripts('emscripten_fetch.js')

var Module = typeof Module !== 'undefined' ? Module : {};

self.onmessage = (data) => {
  console.log('SyncFetchRanges')
  Module.DoRangeRequests(data.data);
  console.log('SyncFetchComplete')
  Module.DoSyncFetch(data.data);
}

Module['onRuntimeInitialized'] = () => {
  console.log('wasm loaded')
}
