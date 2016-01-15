#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_int.h"
#include "codec/decoder.h"
#include "codec/decoder_int.h"

BOOST_AUTO_TEST_CASE(test_decoder_int)
{
	fast_codec::Decoder decoder;

	// uInt32 test
	std::uint32_t v = 0;
	decoder.data_ = { 0x00, 0x00, 0x00 };
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), FC_UNEXPECTED_END_OF_BUFFER_END);
	decoder.Reset();
	decoder.data_ =
	{
		0x80,
		0x39, 0x45, 0xa3,
		0x01, 0x80,
		0x01, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x80,
		0x0f, 0x7f, 0x7f, 0x7f, 0xff,
		0x10, 0x7f, 0x7f, 0x7f, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), 0);
	BOOST_REQUIRE_EQUAL(v, 0);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), 0);
	BOOST_REQUIRE_EQUAL(v, 942755);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), 0);
	BOOST_REQUIRE_EQUAL(v, 128);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), 0);
	BOOST_REQUIRE_EQUAL(v, 16384);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), 0);
	BOOST_REQUIRE_EQUAL(v, 2097152);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), 0);
	BOOST_REQUIRE_EQUAL(v, 268435456);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), 0);
	BOOST_REQUIRE_EQUAL(v, 4294967295);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), FC_INTEGER_OVERFLOW);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), FC_INTEGER_DO_NOT_HAVE_STOP_BIT);
	BOOST_REQUIRE_EQUAL(decode_u32(0, decoder, v), FC_UNEXPECTED_END_OF_BUFFER_END);
	decoder.Reset();
}

BOOST_AUTO_TEST_CASE(perf_test_decoder_int)
{
#ifdef NDEBUG
	const int cCycleCount = 50000000;
#else
	const int cCycleCount = 10;
#endif

	fast_codec::Encoder encoder;
	fast_codec::Decoder decoder;
	encoder.data_.reserve(6 * cCycleCount);
	{
		uint32_t d = 3294967295;
		for (uint32_t i = 0; i < cCycleCount; ++i)
			encode_u32(0, encoder, d + i);
		decoder.data_ = encoder.data_;
		TimeCounterGuard t("decode_u32", cCycleCount);
		std::uint32_t v = 0;
		for (uint32_t i = 0; i < cCycleCount; ++i)
			decode_u32(0, decoder, v);
	}
}
