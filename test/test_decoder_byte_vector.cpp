#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_byte_vector.h"
#include "codec/decoder.h"
#include "codec/decoder_byte_vector.h"

BOOST_AUTO_TEST_CASE(test_decoder_byte_vector)
{
	fast_codec::Decoder decoder;

	fast_codec::byte v[64];
	size_t decoded_size = 0;
	decoder.data_ =
	{
		0x80,
		0x81,
		0x84, 'A', 'B', 'C'
	};
	BOOST_REQUIRE_EQUAL(decode_byte_vector_optional(0, decoder, &v[0], sizeof(v), decoded_size), FC_NULL_VALUE);
	BOOST_REQUIRE_EQUAL(decoded_size, 0);
	BOOST_REQUIRE_EQUAL(decode_byte_vector_optional(0, decoder, &v[0], sizeof(v), decoded_size), FC_EMPTY_VALUE);
	BOOST_REQUIRE_EQUAL(decoded_size, 0);
	BOOST_REQUIRE_EQUAL(decode_byte_vector_optional(0, decoder, &v[0], sizeof(v), decoded_size), 0);
	BOOST_REQUIRE_EQUAL(decoded_size, 3);
	fast_codec::byte etalon[] = { 'A', 'B', 'C' };
	BOOST_REQUIRE_EQUAL(memcmp(v, etalon, sizeof(etalon)), 0);
}

BOOST_AUTO_TEST_CASE(perf_test_decoder_byte_vector)
{
#ifdef NDEBUG
	const int cCycleCount = 5000000;
#else
	const int cCycleCount = 10;
#endif

	fast_codec::Encoder encoder;
	encoder.data_.reserve(200 * cCycleCount);
	fast_codec::byte s[] = "TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING"
		"TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING"
		"TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING";
	{
		for (int i = 0; i < cCycleCount; ++i)
		{
			s[0] = i % 27;
			encode_byte_vector(0, encoder, s, sizeof(s));
		}
		fast_codec::byte v[178];
		size_t decoded_size = 0;
		fast_codec::Decoder decoder;
		decoder.data_ = encoder.data_;
		TimeCounterGuard t("decode_byte_vector (178 bytes)", cCycleCount);
		for (int i = 0; i < cCycleCount; ++i)
			decode_byte_vector_optional(0, decoder, &v[0], sizeof(v), decoded_size);
	}
}
