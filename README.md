# WebAssemblyTests

This is a small repository with some WebAssembly tests.

* **copy**: Testing the performance of copying JavaScript objects into the emscripten heap vs allocating memory on the emscripten heap and manipulate there directly
* **memory**: Just to show the behaviour between objects created within emscripten and objects passed from JavaScript.
* **DynamicLinking**: One example shows dynamic linking using the Module.loadDynamicLibraries which loads the modules at initialisation time
* **DynamicLinking**: Another example using the dlopen mechanism.
