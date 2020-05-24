@echo off
setlocal

set CORECLR_ENABLE_PROFILING=1
set CORECLR_PROFILER={cf0d821e-299b-5307-a3d8-b283c03916dd}
set CORECLR_PROFILER_PATH=%~dp0\CorProfiler.dll

:: set COMPLUS_EnableEventPipe=1
:: set COMPLUS_EventPipeConfig=ArrayTypesEventSource
:: set COMPLUS_EventPipeOutputPath=%~dp0\
:: set COMPLUS_EventPipeRundown=0

if not exist %~dp0\runtime\corerun.exe (
    echo runtime\CoreRun.exe does not exist, you have to copy it from your local coreclr build!
    goto :EOF
)

:: C:\dbg\x64\windbg
%~dp0\runtime\corerun.exe %~dp0\arraytypesapp.dll