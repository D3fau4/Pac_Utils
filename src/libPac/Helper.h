//
// Created by raul2 on 23/03/2022.
//

#ifndef PAC_UTILS_HELPER_H
#define PAC_UTILS_HELPER_H
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "defines.h"
#include "membuf.h"
#include "pac.h"
#include "systemfilesource.h"
#include "defines.h"
#include "compressor.h"

EXPORTS void testlib(const char* s);
EXPORTS void patch_archive(const char* s);
EXPORTS void extract_archive(const char *s);
#endif //PAC_UTILS_HELPER_H
