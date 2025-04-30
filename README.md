# Wasm64Demo

This is stripped down version of an existing Blazor application, with a simple modification to test memory allocation. No attempt has been made to tidy this other than remove some references to proprietary files, other than the allocation test.

It will attempt to allocate 1GB of space every time the WebView is refreshed until it fails.

The intention is to test the dotnet runtime compiled with wasm64 support.

It has been built with emscripten 4.0.5, as has the dotnet runtime.

- Builds into WebViewer/builds

- Debug directly from Visual Studio 17.14.0 Preview 2.0

or 

- `dotnet run` from `Was64Demo\WebViewer`

