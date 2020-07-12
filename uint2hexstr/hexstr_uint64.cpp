#include "hexstr_uint64.h"

/*
hexstr_uint64()

Converts uint64_t to a hexadecimal string without looping.

 */
int64_t hexstr_uint64( char *buffer, size_t buffer_size, uint64_t x )
{
	if ( ! buffer ){
		return -1;
	}
	if ( buffer_size < sizeof( uint64_t ) * 2 ){
		return -1;
	}
	uint64_t x_expand = _pdep_u64( x >> 32, 0x0F0F0F0F0F0F0F0F );

	uint64_t mask = 0x19191919'19191919 - x_expand;
	mask &= 0x10101010'10101010;
	mask ^= 0x10101010'10101010;
	mask >>= 4;
	mask *= 7;
	x_expand += mask;
	x_expand += 0x30303030'30303030;
	x_expand = _byteswap_uint64( x_expand );

	memcpy( buffer, reinterpret_cast<char*>( &x_expand ), sizeof( uint64_t ) );

	x_expand = _pdep_u64( x, 0x0F0F0F0F0F0F0F0F );

	mask = 0x19191919'19191919 - x_expand;
	mask &= 0x10101010'10101010;
	mask ^= 0x10101010'10101010;
	mask >>= 4;
	mask *= 7;
	x_expand += mask;
	x_expand += 0x30303030'30303030;
	x_expand = _byteswap_uint64( x_expand );

	memcpy( buffer + sizeof( uint64_t ), reinterpret_cast<char*>( &x_expand ), sizeof( uint64_t ) );

	return 0;
}

std::string hexstr_uint64( uint64_t x )
{
    char buffer[ sizeof( uint64_t ) * 2 + 1 ];
	hexstr_uint64( buffer, sizeof( buffer ), x );
	return std::string( buffer, sizeof( uint64_t ) * 2 );
}