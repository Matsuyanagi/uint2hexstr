#include <intrin.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

#include "./hexstr_m128.h"
#include "./hexstr_m256.h"
#include "./hexstr_uint32.h"
#include "./hexstr_uint64.h"

/*
hexstr_uint32()

Converts uint32_t to a hexadecimal string without looping.

 */

std::string sprintf_str( uint32_t x ) {
	char buffer[ sizeof( uint32_t ) * 2 + 1 ];
	sprintf( buffer, "%08X", x );
	return std::string( buffer, sizeof( uint32_t ) * 2 );
}

std::string hex_array_str( uint32_t x ) {
	const char byte_str[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	char buffer[ sizeof( uint32_t ) * 2 + 1 ];

	char* p = buffer + sizeof( uint32_t ) * 2 - 1;
	for ( int i = 0; i < 8; i++ ) {
		*p-- = byte_str[ x & 0xF ];
		x >>= 4;
	}
	return std::string( buffer, sizeof( uint32_t ) * 2 );
}

int main() {
	uint64_t x = 0x1234'5678;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0xFEDC'BA98;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;

	std::cout << hexstr_uint64( 0x1234'5678'9ABC'DEF0 ).c_str() << std::endl;
	std::cout << hexstr_sse_uint64( 0x1234'5678'9ABC'DEF0 ).c_str() << std::endl;

	std::cout << hexstr_m128( _mm_set_epi64x( 0xFEDCBA9876543210, 0x123456789ABCDEF0 ) ).c_str() << std::endl;

	std::cout << hexstr_m256(
	    _mm256_set_epi64x( 0xFEDCBA9876543210, 0x123456789ABCDEF0, 0x76543210FEDCBA98, 0xFDB97531ECA86420 ) ).c_str() << std::endl;
}
