#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_decimal.h"

/*
#define P2SYSTYPES_OLDBCD
#include "..\..\..\cgate\trunk\share\p2\src\Plaza-II\P2SysTypes\Include\P2SysBCDII.hpp"

#ifdef NDEBUG
	#pragma comment(lib, "../../cgate/trunk/share/p2/lib/P2Sys.lib")
#else
	#pragma comment(lib, "../../cgate/trunk/share/p2/lib/P2SysD.lib")
#endif
*/

BOOST_AUTO_TEST_CASE(test_encoder_decimal)
{
	fast_simple_codec::Encoder encoder;

	const unsigned char sTestDecimalEtalon[] =
	{
		0x80, 0x80,
		0x00, 0xc0, 0x05, 0x71, 0x3d, 0xa8,
		0xc0, 0x7a, 0x0e, 0x42, 0xd8
	};
	fast_simple_codec::encode_decimal(encoder, fast_simple_codec::Decimal{ 0, 0 });
	fast_simple_codec::encode_decimal(encoder, fast_simple_codec::Decimal{ 64, 12345000 });
	fast_simple_codec::encode_decimal(encoder, fast_simple_codec::Decimal{ -64, -12345000 });
	Check(encoder, sTestDecimalEtalon);
	encoder.Reset();
}
/*
BOOST_AUTO_TEST_CASE(test_encoder_bcd)
{
	fix_fast::Encoder encoder;

	const unsigned char sTestDecimalEtalon[] =
	{
		0xfb, 0x01,	0x6b, 0x5d, 0x0d, 0x39, 0x60, 0x85
	};

	BCD(16, 5) val(80995312.23045);
	encode_bcd(encoder, &val);
	Check(encoder, sTestDecimalEtalon);
	encoder.Reset();
}
*/
/*
BOOST_AUTO_TEST_CASE(perf_test_encoder_bcd)
{
#ifdef NDEBUG
	#define cCycleCount 1000000
#else
	#define cCycleCount 10
#endif

	fix_fast::Encoder encoder;
	encoder.data_.reserve(10*cCycleCount);

	BCD(16, 5)* bcd = new BCD(16, 5)[cCycleCount];
	for(int i = 0; i < cCycleCount; ++i)
		bcd[i] = 80995312.23045 + i;
	
	{
		TimeCounterGuard t("encode_bcd", cCycleCount);
		for(int i = 0; i < cCycleCount; ++i)
			encode_bcd(encoder, &bcd[i]);		
	}

	delete[] bcd;
}
*/
