#pragma once

#include <intrin.h>
#include <stdint.h>

#include <string>

extern int32_t hexstr_m256( char *buffer, size_t buffer_size, __m256i x );
extern std::string hexstr_m256( __m256i x );
