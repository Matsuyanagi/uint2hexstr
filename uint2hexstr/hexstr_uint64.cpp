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

int64_t hexstr_sse_uint64( char *buffer, size_t buffer_size, uint64_t x )
{
	if ( ! buffer ){
		return -1;
	}
	if ( buffer_size < sizeof( uint64_t ) * 2 ){
		return -1;
	}

	//	ニブル→バイト展開して、バイト順を逆転
	uint64_t x_low_expand =  _byteswap_uint64( _pdep_u64( x, 0x0F0F0F0F0F0F0F0F ) );
	uint64_t x_high_expand = _byteswap_uint64(_pdep_u64( x >> 32, 0x0F0F0F0F0F0F0F0F ) );

	__m128i nibbled = _mm_set_epi64x( x_low_expand, x_high_expand );
	
	const __m128i v0 = _mm_set1_epi8( '0' );
	const __m128i vA = _mm_set1_epi8( 'A'-10 );
	const __m128i v9 = _mm_set1_epi8( 9 );
	
	// 1バイトずつ 9 と比較する。10以上なら 0xFF
	__m128i ans_compare = _mm_cmpgt_epi8( nibbled, v9 );

	// 0x00 のバイトは v0 , 0xFF のバイトは vA, が入る
	// https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=AVX2&expand=339,453
	__m128i hex_base = _mm_blendv_epi8( v0, vA, ans_compare );

	// 0～9 + '0' / 10～15 + 'A'-10
	__m128i hex_string = _mm_add_epi16( hex_base, nibbled );

	memcpy( buffer, &hex_string, sizeof( hex_string ) );

	return 0;
}

std::string hexstr_sse_uint64( uint64_t x )
{
    char buffer[ sizeof( uint64_t ) * 2 + 1 ];
	hexstr_sse_uint64( buffer, sizeof( buffer ), x );
	return std::string( buffer, sizeof( uint64_t ) * 2 );
}
