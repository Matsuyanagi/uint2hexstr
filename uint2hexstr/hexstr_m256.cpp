#include "hexstr_m256.h"

/**
 * 分岐なしに __m256i を16進文字列に変換する
 * __m256i は 256bit = 32byte -> 64文字 = 64byte : 32byte(_m256i) x 2
 * 	FF -> 0F0F に分けてから '0' か 'A'-10 を足す
 */
int32_t hexstr_m256( char *buffer, size_t buffer_size, __m256i x ) {
	if ( !buffer ) {
		return -1;
	}
	if ( buffer_size < sizeof( __m256i ) * 2 ) {
		return -1;
	}

	const __m256i v0 = _mm256_set1_epi8( '0' );
	const __m256i vA = _mm256_set1_epi8( 'A' - 10 );
	const __m256i v9 = _mm256_set1_epi8( 9 );

	//	x 32byte を 64文字64byte文字列に変換する
	//		32文字 32byte x 2 に分けて処理する
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

	// 上位128bit を ニブル->バイト 256bit に展開、上下をスワップ
	__m256i high_nibbled = _mm256_set_epi64x( _pdep_u64( _mm256_extract_epi32( x, 5 ), expand_nibble_mask ),
	                                          _pdep_u64( _mm256_extract_epi32( x, 4 ), expand_nibble_mask ),
	                                          _pdep_u64( _mm256_extract_epi32( x, 7 ), expand_nibble_mask ),
	                                          _pdep_u64( _mm256_extract_epi32( x, 6 ), expand_nibble_mask ) );

	//	バイト順を逆転
	high_nibbled = _mm256_shuffle_epi8( high_nibbled, shuffle_index );

	// 1バイトずつ 9 と比較する。10以上なら 0xFF
	__m256i ans_compare = _mm256_cmpgt_epi8( high_nibbled, v9 );

	// 0x00 のバイトは v0 , 0xFF のバイトは vA, が入る
	// https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=AVX2&expand=339,453
	__m256i hex_base = _mm256_blendv_epi8( v0, vA, ans_compare );

	// 0～9 + '0' / 10～15 + 'A'-10
	__m256i hex_string_high = _mm256_add_epi16( hex_base, high_nibbled );

	memcpy( buffer, &hex_string_high, sizeof( hex_string_high ) );

	// // ここから下位
	// 下位128bit を 256bit に展開、上下をスワップ
	__m256i low_nibbled = _mm256_set_epi64x( _pdep_u64( _mm256_extract_epi32( x, 1 ), expand_nibble_mask ),
	                                         _pdep_u64( _mm256_extract_epi32( x, 0 ), expand_nibble_mask ),
	                                         _pdep_u64( _mm256_extract_epi32( x, 3 ), expand_nibble_mask ),
	                                         _pdep_u64( _mm256_extract_epi32( x, 2 ), expand_nibble_mask ) );

	//	バイト順を逆転
	low_nibbled = _mm256_shuffle_epi8( low_nibbled, shuffle_index );

	// 1バイトずつ 9 と比較する。10以上なら 0xFF
	ans_compare = _mm256_cmpgt_epi8( low_nibbled, v9 );

	// 0x00 のバイトは v0 , 0xFF のバイトは vA, が入る
	// https://software.intel.com/sites/landingpage/IntrinsicsGuide/#techs=AVX2&expand=339,453
	hex_base = _mm256_blendv_epi8( v0, vA, ans_compare );

	// 0～9 + '0' / 10～15 + 'A'-10
	__m256i hex_string_low = _mm256_add_epi16( hex_base, low_nibbled );

	memcpy( buffer + sizeof( __m256i ), &hex_string_low, sizeof( hex_string_low ) );

	return 0;
}

std::string hexstr_m256( __m256i x ) {
	char buffer[ sizeof( __m256i ) * 2 + 1 ];
	hexstr_m256( buffer, sizeof( buffer ), x );
	return std::string( buffer, sizeof( __m256i ) * 2 );
}
