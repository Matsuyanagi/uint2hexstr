#include "hexstr_m128.h"

/*
hexstr_m128()

Converts __m128i to a hexadecimal string without looping.

 */
int32_t hexstr_m128( char *buffer, size_t buffer_size, __m128i x ) {
	if ( !buffer ) {
		return -1;
	}
	if ( buffer_size < sizeof( __m128i ) * 2 ) {
		return -1;
	}

	// char hex_str_buffer[ sizeof(__m128i) * 2 ];
	const __m256i v0 = _mm256_set1_epi8( '0' );
	const __m256i vA = _mm256_set1_epi8( 'A' - 10 );
	const __m256i v9 = _mm256_set1_epi8( 9 );

	__m256i xx = _mm256_set_m128i( x, x );

	//	x 16byte を 32文字32byte文字列に変換する
	//		上位から変換して、出力時に逆転させる必要があるが、2文字単位で
	//		0x123456789ABCDEF0_1122334455667788_99AABBCCDDEEFF00_FDB9753102468ACE
	//		'123456789ABCDEF0112233445566778899AABBCCDDEEFF00FDB9753102468ACE'
	//		0x31,32,34,44,... 0x41,43,45

	const __m256i shuffle_index = _mm256_set_epi8( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4,
	                                               5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 );

	// ニブルをバイトに展開する
	// 	ABCD
	// 	0A0B0C0D
	const uint64_t expand_nibble_mask = 0x0F0F0F0F0F0F0F0F;

	// 下位128bit を ニブル->バイト 256bit に展開、上下をスワップ
	__m256i nibbled = _mm256_set_epi64x( _pdep_u64( _mm256_extract_epi32( xx, 1 ), expand_nibble_mask ),
	                                     _pdep_u64( _mm256_extract_epi32( xx, 0 ), expand_nibble_mask ),
	                                     _pdep_u64( _mm256_extract_epi32( xx, 3 ), expand_nibble_mask ),
	                                     _pdep_u64( _mm256_extract_epi32( xx, 2 ), expand_nibble_mask ) );

	//	バイト順を逆転
	nibbled = _mm256_shuffle_epi8( nibbled, shuffle_index );

	// 1バイトずつ 9 と比較する。10以上なら 0xFF
	__m256i ans_compare = _mm256_cmpgt_epi8( nibbled, v9 );

	// 0x00 のバイトは v0 , 0xFF のバイトは vA, が入る
	// https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=AVX2&expand=339,453
	__m256i hex_base = _mm256_blendv_epi8( v0, vA, ans_compare );

	// 0～9 + '0' / 10～15 + 'A'-10
	__m256i hex_string = _mm256_add_epi16( hex_base, nibbled );

	memcpy( buffer, &hex_string, sizeof( hex_string ) );

	return 0;
}

std::string hexstr_m128( __m128i x ) {
	char buffer[ sizeof( __m128i ) * 2 + 1 ];
	hexstr_m128( buffer, sizeof( buffer ), x );
	return std::string( buffer, sizeof( __m128i ) * 2 );
}