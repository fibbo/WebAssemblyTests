/* 
  Fetch API Range Request PoC

  C++ implementation of a function that creates a fetch call with a range header.
  In order for this to work, the hosting server has to accept the "Range" keyword
  as allowed method name ('Access-Control-Allowe-Headers'). Otherwise the preflight
  request will be denied.

  The flag EMSCRIPTEN_FETCH_REPLACE needs to be set in order for the synchronous
  request to work. Otherwise the JavaScript call will be synchronous and the code
  fails: https://github.com/emscripten-core/emscripten/issues/8749

  TODO: As it is, there doesn't seem to be a way to retrieve the total file size
  with a HEAD request, since the totalBytes member contains the bytes of the response
  body - which is 0 in a HEAD request - instead of the Content-Length.
 */

#include <cstdio>
#include <cstring>
#include <emscripten/fetch.h>
#include <emscripten/bind.h>

void downloadSucceeded(emscripten_fetch_t *fetch) {
  printf("Async: Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
  // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
  emscripten_fetch_close(fetch); // Free data associated with the fetch.
}

void downloadFailed(emscripten_fetch_t *fetch) {
  printf("Async: Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
  emscripten_fetch_close(fetch); // Also free data on failure.
}

uint64_t GetContentLength(std::string url)
{
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "HEAD");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_REPLACE | EMSCRIPTEN_FETCH_SYNCHRONOUS ;
  emscripten_fetch_t *fetch = emscripten_fetch(&attr, url.c_str());
  if (fetch->status == 200)
  {
    printf("HEAD request successful: %llu\n", fetch->totalBytes);
    return fetch->totalBytes;
  }
  else {
    printf("Failed HEAD request: %d\n", fetch->status);
    return fetch->totalBytes;
  }
}

void DoRangeRequests(std::string url)
{
  printf("Content Length: %llu\n", GetContentLength(url));
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "GET");
  const char* headers[] = {"Range", "bytes=0-1000",\
                            0 };
  attr.requestHeaders = headers;
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_REPLACE | EMSCRIPTEN_FETCH_SYNCHRONOUS ;
  emscripten_fetch_t *fetch = emscripten_fetch(&attr, url.c_str());
  if (fetch->status == 200) {
    printf("Range request successful: %llu - DataOffset: %llu\n", fetch->numBytes, fetch->dataOffset);
  }
  else if (fetch->status == 206) {
    printf("Partial file downloaded: %llu of a total of: %llu bytes\n", fetch->numBytes, fetch->totalBytes);
  }
  else {
    printf("Downloading %s failed, HTTP failure status code: %d: %s\n", fetch->url, fetch->status, fetch->statusText);
  }
  emscripten_fetch_close(fetch);
}

void downloadProgress(emscripten_fetch_t *fetch) {
  if (fetch->totalBytes) {
    printf("Downloading %s.. %.2f%% complete.\n", fetch->url, fetch->dataOffset * 100.0 / fetch->totalBytes);
  } else {
    printf("Downloading %s.. %lld bytes complete.\n", fetch->url, fetch->dataOffset + fetch->numBytes);
  }
}

void DoSyncFetch(std::string url) {
  emscripten_fetch_attr_t attr;
  emscripten_fetch_attr_init(&attr);
  strcpy(attr.requestMethod, "GET");
  attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS | EMSCRIPTEN_FETCH_REPLACE ;
  attr.onprogress = downloadProgress;
  emscripten_fetch_t *fetch = emscripten_fetch(&attr, url.c_str()); // Blocks here until the operation is complete.
  if (fetch->status == 200) {
    printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
    // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
  } else {
    printf("Downloading %s failed, HTTP failure status code: %d: %s\n", fetch->url, fetch->status, fetch->statusText);
  }
  emscripten_fetch_close(fetch);
}

EMSCRIPTEN_BINDINGS() {
  emscripten::function("DoSyncFetch", &DoSyncFetch);
  emscripten::function("DoRangeRequests", &DoRangeRequests);
}
