#include "pch.h"
#include "../uint2hexstr/hexstr_uint32.h"
#include "../uint2hexstr/hexstr_uint64.h"
#include "../uint2hexstr/hexstr_m128.h"

std::string sprintf_str32( uint32_t x )
{
  char buffer[ sizeof( uint32_t ) * 2 + 1 ];
	sprintf( buffer, "%08X", x );
	return std::string( buffer, sizeof( uint32_t ) * 2 );
}

std::string sprintf_str64( uint64_t x )
{
  char buffer[ sizeof( uint64_t ) * 2 + 1 ];
	sprintf( buffer, "%016llX", x );
	return std::string( buffer, sizeof( uint64_t ) * 2 );
}

std::string sprintf_str128( __m128i x )
{
  char buffer[ sizeof( __m128i ) * 2 + 1 ];
  uint64_t u64[2];
  memcpy( &u64, &x, sizeof(__m128i) );
  
	sprintf( buffer, "%016llX%016llX", u64[1], u64[0] );
  
	return std::string( buffer, sizeof( __m128i ) * 2 );
}

TEST(TestCaseUint32, TestUint32Eq) {
  EXPECT_EQ( sprintf_str32( 0 ), hexstr_uint32( 0 ) );
  EXPECT_EQ( sprintf_str32( 1 ), hexstr_uint32( 1 ) );
  EXPECT_EQ( sprintf_str32( 2 ), hexstr_uint32( 2 ) );
  EXPECT_EQ( sprintf_str32( 0x0F ), hexstr_uint32( 0x0F ) );
  EXPECT_EQ( sprintf_str32( 0x8000'0000 ), hexstr_uint32( 0x8000'0000 ) );
  EXPECT_EQ( sprintf_str32( 0xF000'0000 ), hexstr_uint32( 0xF000'0000 ) );
  EXPECT_EQ( sprintf_str32( 0x1234'5678 ), hexstr_uint32( 0x1234'5678 ) );
  EXPECT_EQ( sprintf_str32( 0xFEDC'BA98 ), hexstr_uint32( 0xFEDC'BA98 ) );
  EXPECT_EQ( sprintf_str32( 0xA531'1230 ), hexstr_uint32( 0xA531'1230 ) );
  EXPECT_EQ( sprintf_str32( 0xC000'8901 ), hexstr_uint32( 0xC000'8901 ) );
  EXPECT_EQ( sprintf_str32( 0x0123'FED0 ), hexstr_uint32( 0x0123'FED0 ) );
  EXPECT_EQ( sprintf_str32( 0x8000'0001 ), hexstr_uint32( 0x8000'0001 ) );
  EXPECT_EQ( sprintf_str32( 0xFFFF'FFFF ), hexstr_uint32( 0xFFFF'FFFF ) );
  EXPECT_EQ( sprintf_str32( 0xFFFF'FFFE ), hexstr_uint32( 0xFFFF'FFFE ) );
  EXPECT_EQ( sprintf_str32( 0x8001'8001 ), hexstr_uint32( 0x8001'8001 ) );
}

TEST(TestCaseUint64, TestUint64Eq) {
  EXPECT_EQ( sprintf_str64( 0 ), hexstr_uint64( 0 ) );
  EXPECT_EQ( sprintf_str64( 1 ), hexstr_uint64( 1 ) );
  EXPECT_EQ( sprintf_str64( 2 ), hexstr_uint64( 2 ) );
  EXPECT_EQ( sprintf_str64( 0x0F ), hexstr_uint64( 0x0F ) );
  EXPECT_EQ( sprintf_str64( 0x8000'0000'0000'0000 ), hexstr_uint64( 0x8000'0000'0000'0000 ) );
  EXPECT_EQ( sprintf_str64( 0xF000'0000'0000'0000 ), hexstr_uint64( 0xF000'0000'0000'0000 ) );
  EXPECT_EQ( sprintf_str64( 0x1234'5678'9ABC'DEF0 ), hexstr_uint64( 0x1234'5678'9ABC'DEF0 ) );
  EXPECT_EQ( sprintf_str64( 0xFEDC'BA98'7654'3210 ), hexstr_uint64( 0xFEDC'BA98'7654'3210 ) );
  EXPECT_EQ( sprintf_str64( 0xA531'1230'0321'135A ), hexstr_uint64( 0xA531'1230'0321'135A ) );
  EXPECT_EQ( sprintf_str64( 0xC000'8901'0FF0'FFFF ), hexstr_uint64( 0xC000'8901'0FF0'FFFF ) );
  EXPECT_EQ( sprintf_str64( 0x0123'4567'89AB'CDEF ), hexstr_uint64( 0x0123'4567'89AB'CDEF ) );
  EXPECT_EQ( sprintf_str64( 0x8000'0000'0000'0001 ), hexstr_uint64( 0x8000'0000'0000'0001 ) );
  EXPECT_EQ( sprintf_str64( 0xFFFF'FFFF'FFFF'FFFF ), hexstr_uint64( 0xFFFF'FFFF'FFFF'FFFF ) );
  EXPECT_EQ( sprintf_str64( 0xFFFF'FFFF'FFFF'FFFE ), hexstr_uint64( 0xFFFF'FFFF'FFFF'FFFE ) );
  EXPECT_EQ( sprintf_str64( 0x8001'8001'8001'8001 ), hexstr_uint64( 0x8001'8001'8001'8001 ) );
}

TEST(TestCaseM128, TestM128) {
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x0000000000000000, 0x0000000000000000 ) ), hexstr_m128( _mm_set_epi64x( 0x0000000000000000, 0x0000000000000000 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x0000000000000000, 0x0000000000000001 ) ), hexstr_m128( _mm_set_epi64x( 0x0000000000000000, 0x0000000000000001 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x0000000000000000, 0x0000000000000002 ) ), hexstr_m128( _mm_set_epi64x( 0x0000000000000000, 0x0000000000000002 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x0000000000000000, 0x000000000000000F ) ), hexstr_m128( _mm_set_epi64x( 0x0000000000000000, 0x000000000000000F ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x8000000000000000, 0x0000000000000000 ) ), hexstr_m128( _mm_set_epi64x( 0x8000000000000000, 0x0000000000000000 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x8000000000000000, 0x0000000000000001 ) ), hexstr_m128( _mm_set_epi64x( 0x8000000000000000, 0x0000000000000001 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x0000000000000001, 0x0000000000000000 ) ), hexstr_m128( _mm_set_epi64x( 0x0000000000000001, 0x0000000000000000 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x0000000000000001, 0x8000000000000000 ) ), hexstr_m128( _mm_set_epi64x( 0x0000000000000001, 0x8000000000000000 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0xF000000000000000, 0x0000000000000000 ) ), hexstr_m128( _mm_set_epi64x( 0xF000000000000000, 0x0000000000000000 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0xFDB97531ECA86420, 0x1234FEDC5678BA98 ) ), hexstr_m128( _mm_set_epi64x( 0xFDB97531ECA86420, 0x1234FEDC5678BA98 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0xFEDCBA9876543210, 0x123456789ABCDEF0 ) ), hexstr_m128( _mm_set_epi64x( 0xFEDCBA9876543210, 0x123456789ABCDEF0 ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF ) ), hexstr_m128( _mm_set_epi64x( 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF ) ) );
  EXPECT_EQ( sprintf_str128( _mm_set_epi64x( 0x1111111111111111, 0x1111111111111111 ) ), hexstr_m128( _mm_set_epi64x( 0x1111111111111111, 0x1111111111111111 ) ) );

  
}