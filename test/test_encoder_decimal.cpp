#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_decimal.h"

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

BOOST_AUTO_TEST_CASE(test_encoder_bcd)
{
	fast_simple_codec::Encoder encoder;
	const unsigned char sTestDecimalEtalon[] =
	{
		0xfb, 0x01,	0x6b, 0x5d, 0x0d, 0x39, 0x60, 0x85
	};

	fast_simple_codec::Decimal val{ -5, 8099531223045 };
	uint8_t bcd_val[sizeof(uint16_t) + BCD_SIZEOF(BCD_MAKE_TYPE(16, 5))];
	val.ToBCD<16, 5>(bcd_val);

	encode_bcd(encoder, bcd_val);
	Check(encoder, sTestDecimalEtalon);
	encoder.Reset();
}

BOOST_AUTO_TEST_CASE(perf_test_encoder_bcd)
{
#ifdef NDEBUG
	#define cCycleCount 1000000
#else
	#define cCycleCount 10
#endif

	fast_simple_codec::Encoder encoder;
	encoder.data_.reserve(10*cCycleCount);

	fast_simple_codec::BCD<16, 5>* bcd = new fast_simple_codec::BCD<16, 5>[cCycleCount];
	for(int i = 0; i < cCycleCount; ++i)
		bcd[i] = fast_simple_codec::BCD<16, 5>(8099531223045 + i, 5);
	
	{
		TimeCounterGuard t("encode_bcd", cCycleCount);
		for(int i = 0; i < cCycleCount; ++i)
			encode_bcd(encoder, reinterpret_cast<const uint8_t*>(&bcd[i]));
	}

	delete[] bcd;
}
