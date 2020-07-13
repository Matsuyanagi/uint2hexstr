#pragma once

#include <intrin.h>
#include <stdint.h>

#include <string>

extern int32_t hexstr_m128( char *buffer, size_t buffer_size, __m128i x );
extern std::string hexstr_m128( __m128i x );
