cmake_minimum_required (VERSION 3.14)

project(CorProfiler)

if (WIN32)
    set(BASE_SOURCES src/windows/CorProfiler.def)
endif(WIN32)

set(SOURCES
    ${BASE_SOURCES}
    src/ClassFactory.cpp
    src/CorProfiler.cpp
    src/dllmain.cpp
    src/corprof.h)

#add_compile_definitions(PRINT_REMOTING_CALLBACKS)

add_library(CorProfiler SHARED ${SOURCES})
