@echo off
setlocal

set COMPLUS_TieredCompilation=0

C:\dbg\x64\windbg -g C:\dbg\x64\windbg.exe repro\runtime\CoreRun.exe repro\arraytypesapp.dll inlining