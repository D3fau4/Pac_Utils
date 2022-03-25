cmake_minimum_required(VERSION 3.16)
project(Pac_Utils)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/libNep)

add_library(Nep SHARED
        src/libNep/bitstream.cpp
        src/libNep/bitstream.h
        src/libNep/compressor.cpp
        src/libNep/compressor.h
        src/libNep/defines.h
        src/libNep/filesourcebase.h
        src/libNep/huffman.cpp
        src/libNep/huffman.h
        src/libNep/membuf.cpp
        src/libNep/membuf.h
        src/libNep/pac.cpp
        src/libNep/pac.h
        src/libNep/pacfilesource.cpp
        src/libNep/pacfilesource.h
        src/libNep/semaphore.cpp
        src/libNep/semaphore.h
        src/libNep/structs.h
        src/libNep/systemfilesource.cpp
        src/libNep/systemfilesource.h
        src/libNep/Helper.cpp
        src/libNep/Helper.h)

target_compile_definitions(Nep PUBLIC LIBPACK)
