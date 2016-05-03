#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_decimal.h"
#include "codec/decoder.h"
#include "codec/decoder_decimal.h"

BOOST_AUTO_TEST_CASE(test_decoder_decimal)
{
	fast_codec::Decoder decoder;
	fast_codec::Decimal d;
	decoder.data_ =
	{
		0x80, 0x80,
		0x00, 0xc0, 0x05, 0x71, 0x3d, 0xa8,
		0xc0, 0x7a, 0x0e, 0x42, 0xd8
	};
	BOOST_REQUIRE_EQUAL(decode_decimal(0, decoder, d), 0);
	BOOST_REQUIRE_EQUAL(d.exponent_, 0);
	BOOST_REQUIRE_EQUAL(d.mantissa_, 0);
	BOOST_REQUIRE_EQUAL(decode_decimal(0, decoder, d), 0);
	BOOST_REQUIRE_EQUAL(d.exponent_, fast_codec::exponent_t(64));
	BOOST_REQUIRE_EQUAL(d.mantissa_, 12345000);
	BOOST_REQUIRE_EQUAL(decode_decimal(0, decoder, d), 0);
	BOOST_REQUIRE_EQUAL(d.exponent_, fast_codec::exponent_t(-64));
	BOOST_REQUIRE_EQUAL(d.mantissa_, -12345000);
}

BOOST_AUTO_TEST_CASE(perf_test_decoder_decimal)
{
#ifdef NDEBUG
	const int cCycleCount = 1000000;
#else
	const int cCycleCount = 10;
#endif

	fast_codec::Encoder encoder;
	fast_codec::Decoder decoder;
	encoder.data_.reserve(6 * cCycleCount);
	for (uint32_t i = 0; i < cCycleCount; ++i)
	{
		fast_codec::Decimal d(5, 8099531223045 + i);
		encode_decimal(0, encoder, d);
	}
	decoder.data_ = encoder.data_;
	{
		TimeCounterGuard t("decode_decimal", cCycleCount);
		fast_codec::Decimal d;
		for (int i = 0; i < cCycleCount; ++i)
			encode_decimal(0, encoder, d);
	}
}
