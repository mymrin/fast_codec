#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_byte_vector.h"

BOOST_AUTO_TEST_CASE(test_encoder_byte_vector)
{
	fast_codec::Encoder encoder;

	const unsigned char sTestEtalon[] =
	{
		0x80,
		0x83, 'A', 'B', 'C'
	};
	
	encode_byte_vector(encoder, 0, 0);

	fast_codec::byte buf[] = "ABC";
	encode_byte_vector(encoder, buf, sizeof(buf) - 1);

	Check(encoder, sTestEtalon);
	encoder.Reset();
}

BOOST_AUTO_TEST_CASE(perf_test_encoder_byte_vector)
{
#ifdef NDEBUG
	const int cCycleCount = 1000000;
#else
	const int cCycleCount = 10;
#endif

	fast_codec::Encoder encoder;
	fast_codec::byte s[] = "TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING"
		"TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING"
		"TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING_TEST_STRING";
	{
		TimeCounterGuard t("encode_byte_vector (178 bytes)", cCycleCount);
		for(int i = 0; i < cCycleCount; ++i)
		{
			s[0] = i % 27;
			encode_byte_vector(encoder, s, sizeof(s));
		}
	}
}
