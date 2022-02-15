@echo off
setlocal

if not defined BuildConfig (
    set BuildConfig=Release
)

echo   BuildConfig  : %BuildConfig%

echo   Building

if not exist bin\ (
    mkdir bin
)

if not exist bin\x86 (
    mkdir bin\x86
)

if not exist bin\x64 (
    mkdir bin\x64
)

cmake -G "Visual Studio 17 2022" -A Win32 -S . -B "build32"
cmake -G "Visual Studio 17 2022" -A x64 -S . -B "build64"
cmake --build build32 --config %BuildConfig%
cmake --build build64 --config %BuildConfig%

echo.
echo.
echo.
echo Done building

echo Copying binaries to bin
copy /y  build32\%BuildConfig%\CorProfiler.dll bin\x86
copy /y  build64\%BuildConfig%\CorProfiler.dll bin\x64
