cmake_minimum_required(VERSION 3.16)
project(Pac_Utils)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/libPac)

add_library(Nep SHARED
        src/libPac/bitstream.cpp
        src/libPac/bitstream.h
        src/libPac/compressor.cpp
        src/libPac/compressor.h
        src/libPac/defines.h
        src/libPac/filesourcebase.h
        src/libPac/huffman.cpp
        src/libPac/huffman.h
        src/libPac/logcfg.cpp
        src/libPac/membuf.cpp
        src/libPac/membuf.h
        src/libPac/pac.cpp
        src/libPac/pac.h
        src/libPac/pacfilesource.cpp
        src/libPac/pacfilesource.h
        src/libPac/semaphore.cpp
        src/libPac/semaphore.h
        src/libPac/structs.h
        src/libPac/systemfilesource.cpp
        src/libPac/systemfilesource.h
        src/libPac/Helper.cpp
        src/libPac/Helper.h)

target_compile_definitions(Nep PUBLIC LIBPACK)
