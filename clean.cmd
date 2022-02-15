@echo off
setlocal

echo Deleting bin\
if exist bin\ (
    rmdir /s /q bin\
)

echo Deleting build32\
if exist build32\ (
    rmdir /s /q build32\
)

echo Deleting build64\
if exist build64\ (
    rmdir /s /q build64\
)

echo Done!
