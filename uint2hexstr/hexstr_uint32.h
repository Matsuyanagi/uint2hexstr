#pragma once

#include <intrin.h>
#include <stdint.h>

#include <string>

extern int32_t hexstr_uint32( char *buffer, size_t buffer_size, uint32_t x );
extern std::string hexstr_uint32( uint32_t x );
