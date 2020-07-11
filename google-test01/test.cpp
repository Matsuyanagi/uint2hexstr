#include "pch.h"
#include "../uint2hexstr/hexstr_uint32.h"

std::string sprintf_str( uint32_t x )
{
    char buffer[ sizeof( uint32_t ) * 2 + 1 ];
	sprintf( buffer, "%08X", x );
	return std::string( buffer, sizeof( uint32_t ) * 2 );
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ( sprintf_str( 0 ), hexstr_uint32( 0 ) );
  EXPECT_EQ( sprintf_str( 1 ), hexstr_uint32( 1 ) );
  EXPECT_EQ( sprintf_str( 2 ), hexstr_uint32( 2 ) );
  EXPECT_EQ( sprintf_str( 0x0F ), hexstr_uint32( 0x0F ) );
  EXPECT_EQ( sprintf_str( 0x8000'0000 ), hexstr_uint32( 0x8000'0000 ) );
  EXPECT_EQ( sprintf_str( 0xF000'0000 ), hexstr_uint32( 0xF000'0000 ) );
  EXPECT_EQ( sprintf_str( 0x1234'5678 ), hexstr_uint32( 0x1234'5678 ) );
  EXPECT_EQ( sprintf_str( 0xFEDC'BA98 ), hexstr_uint32( 0xFEDC'BA98 ) );
  EXPECT_EQ( sprintf_str( 0xA531'1230 ), hexstr_uint32( 0xA531'1230 ) );
  EXPECT_EQ( sprintf_str( 0xC000'8901 ), hexstr_uint32( 0xC000'8901 ) );
  EXPECT_EQ( sprintf_str( 0x0123'FED0 ), hexstr_uint32( 0x0123'FED0 ) );
  EXPECT_EQ( sprintf_str( 0x8000'0001 ), hexstr_uint32( 0x8000'0001 ) );
  EXPECT_EQ( sprintf_str( 0xFFFF'FFFF ), hexstr_uint32( 0xFFFF'FFFF ) );
  EXPECT_EQ( sprintf_str( 0xFFFF'FFFE ), hexstr_uint32( 0xFFFF'FFFE ) );
  EXPECT_EQ( sprintf_str( 0x8001'8001 ), hexstr_uint32( 0x8001'8001 ) );
}