#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_ascii.h"

BOOST_AUTO_TEST_CASE(test_encoder_ascii)
{
	fast_simple_codec::Encoder encoder;

	const unsigned char sTestEtalon[] =
	{
		0x80,
		0x80,
		0x80,
		'a', 'b'|0x80,
		'A', 'B', 'C', 'D', 'E'|0x80
	};
	
	char s1[1] = { '\0' };
	encode_ascii(encoder, s1, sizeof(s1));
	encode_ascii(encoder, s1, 0);
	encode_ascii(encoder, 0, 0);

	char s2[2] = { 'a', 'b' };
	encode_ascii(encoder, s2, sizeof(s2));

	char s3[] = "ABCDE";
	encode_ascii(encoder, s3, sizeof(s3));

	Check(encoder, sTestEtalon);
	encoder.Reset();
}

BOOST_AUTO_TEST_CASE(perf_test_encoder_ascii)
{
#ifdef NDEBUG
	const int cCycleCount = 1000000;
#else
	const int cCycleCount = 10;
#endif

	fast_simple_codec::Encoder encoder;
	char s[] = "TEST_STRING";
	{
		TimeCounterGuard t("encode_ascii (11 bytes)", cCycleCount);
		for(int i = 0; i < cCycleCount; ++i)
		{
			s[0] = i % 27;
			encode_ascii(encoder, s, sizeof(s));
		}
	}
}
