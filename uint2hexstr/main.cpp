#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <intrin.h>
#include <string>
#include <vector>

#include "./hexstr_uint32.h"
#include "./hexstr_uint64.h"
#include "./hexstr_m128.h"

/*
hexstr_uint32()

Converts uint32_t to a hexadecimal string without looping.

 */

std::string sprintf_str( uint32_t x )
{
    char buffer[ sizeof( uint32_t ) * 2 + 1 ];
	sprintf( buffer, "%08X", x );
	return std::string( buffer, sizeof( uint32_t ) * 2 );
}

std::string hex_array_str( uint32_t x )
{
	const char byte_str[] = { '0', '1', '2', '3', '4', '5', '6', '7',
									'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	char buffer[ sizeof( uint32_t ) * 2 + 1 ];


	char* p = buffer + sizeof( uint32_t ) * 2 -1;
	for ( int i = 0; i < 8; i++ ) {
		*p-- = byte_str[ x & 0xF ];
		x >>= 4;
	}
	return std::string( buffer, sizeof( uint32_t ) * 2 );
}


int main() {

    uint64_t x = 0;
    std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 1;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0x8000'0000;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0xF000'0000;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0x1234'5678;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0xFEDC'BA98;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0x0000'000F;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0xA531'1230;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0xC000'8901;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;
	x = 0x0123'FED0;
	std::cout << sprintf_str( x ).c_str() << std::endl;
	std::cout << hex_array_str( x ).c_str() << std::endl;
	std::cout << hexstr_uint32( x ).c_str() << std::endl;

	std::cout << hexstr_m128( _mm_set_epi64x( 0xFEDCBA9876543210, 0x123456789ABCDEF0 ) ).c_str() << std::endl;

}
