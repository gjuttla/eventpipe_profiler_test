# remoting_profiler

## Build requirements
* [Visual Studio 2022](https://visualstudio.microsoft.com/vs/)
* [CMake](https://cmake.org/download/)

## Usage
Build with `build.cmd`. This will copy the built profiler library (`CorProfiler.dll`) to `bin/x86` and `bin/x64`.

Set the following environment variables to run a .NET Framework application with the profiler.
```
COR_ENABLE_PROFILING=0x01
COR_PROFILER={cf0d821e-299b-5307-a3d8-b283c03916dd}
COR_PROFILER_PATH_32=<path to 32-bit CorProfiler.dll>
COR_PROFILER_PATH_64=<path to 64-bit CorProfiler.dll>
```

## Acknowledgements
* This is a fork of [eventpipe_profiler_test](https://github.com/davmason/eventpipe_profiler_test) which is licensed under the MIT license.
* [.NET runtime](https://github.com/dotnet/runtime) is licensed under the [MIT license](https://github.com/dotnet/runtime/blob/main/LICENSE.TXT).<br>(Using the prebuilt [corprof.h](src/corprof.h).)

## License
This project is licensed under the [MIT license](LICENSE.txt).
