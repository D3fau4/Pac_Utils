//
// Created by raul2 on 23/03/2022.
//

#ifndef PAC_UTILS_HELPER_H
#define PAC_UTILS_HELPER_H
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "defines.h"
#include "membuf.h"
#include "pac.h"
#include "systemfilesource.h"
#include "defines.h"
#include "compressor.h"

EXPORTS void testlib(const char* s);
EXPORTS void testpath(const char *s);
EXPORTS void patch_archive(const char* pac, const char* folder);
EXPORTS void extract_archive(const char* pac, const char* folder);
EXPORTS void extract_archive_withlist(const char* pac, char** ListFiles, int numoffiles, const char* folder);
#endif //PAC_UTILS_HELPER_H
