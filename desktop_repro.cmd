@echo off
setlocal

set COR_ENABLE_PROFILING=1
set COR_PROFILER={cf0d821e-299b-5307-a3d8-b283c03916dd}
set COR_PROFILER_PATH=C:\work\arraytypes_test\CorProfiler.dll

C:\dbg\x64\windbg C:\Users\dave\source\repos\DesktopConsoleApp\DesktopConsoleApp\bin\x64\Release\DesktopConsoleApp.exe
