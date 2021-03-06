#pragma once

#include <intrin.h>
#include <stdint.h>

#include <string>

extern int64_t hexstr_uint64( char *buffer, size_t buffer_size, uint64_t x );
extern std::string hexstr_uint64( uint64_t x );

extern int64_t hexstr_sse_uint64( char *buffer, size_t buffer_size, uint64_t x );
extern std::string hexstr_sse_uint64( uint64_t x );
