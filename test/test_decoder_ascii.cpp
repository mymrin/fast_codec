#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_string_ascii.h"
#include "codec/decoder.h"
#include "codec/decoder_string_ascii.h"

BOOST_AUTO_TEST_CASE(test_decoder_ascii)
{
	fast_codec::Decoder decoder;
	decoder.data_ =
	{
		0x80,
		0x00, 0x80,
		0x00, 0xC1,
		'a', 'b' | 0x80,
		'A', 'B', 'C', 'D', 'E', 0x80,
		'x', 0x80,
		'y'
	};
	char s[8];
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, nullptr, sizeof(s)), FC_INCORRECT_PARAMETER);
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, s, 0), FC_INCORRECT_PARAMETER);
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, nullptr, 0), FC_INCORRECT_PARAMETER);
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(s[0], '\0');
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(s[0], '\0');
	BOOST_REQUIRE_EQUAL(s[1], '\0');
	// ERR R9 - user of fast_codec should check it on his side
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(s[0], '\0');
	BOOST_REQUIRE_EQUAL(s[1], 'A');
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(s[0], 'a');
	BOOST_REQUIRE_EQUAL(s[1], 'b');
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(strncmp(s, "ABCDE", 6), 0);
	char c;
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, nullptr), FC_INCORRECT_PARAMETER);
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, &c), 0);
	BOOST_REQUIRE_EQUAL(c, 'x');
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, &c), FC_UNEXPECTED_END_OF_BUFFER_END);
	decoder.position_ = 0;
	std::string str;
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, str), 0);
	BOOST_REQUIRE_EQUAL(str.c_str(), "");
	str.clear();
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, str), 0);
	BOOST_REQUIRE_EQUAL(str.c_str(), "");
	// ERR R9 - user of fast_codec should check it on his side
	str.clear();
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, str), 0);
	BOOST_REQUIRE_EQUAL(str.c_str(), "");
	str.clear();
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, str), 0);
	BOOST_REQUIRE_EQUAL(str[0], 'a');
	BOOST_REQUIRE_EQUAL(str[1], 'b');
	str.clear();
	BOOST_REQUIRE_EQUAL(decode_string_ascii(0, decoder, str), 0);
	BOOST_REQUIRE_EQUAL(strncmp(str.c_str(), "ABCDE", 6), 0);

	decoder.Reset();
	decoder.data_ =
	{
		0x80,
		0x00, 0x80,
		0x00, 0xC1,
		0x00, 0x00, 0x80,
		0x00, 0x00, 0xC1,
		'a', 'b' | 0x80,
		'A', 'B', 'C', 'D', 'E', 0x80,
	};
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, s, sizeof(s)), FC_NULL_VALUE);
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, s, 1), FC_BUFFER_OVERFLOW);
	--decoder.position_;
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, s, sizeof(s)), FC_EMPTY_VALUE);
	BOOST_REQUIRE_EQUAL(s[0], '\0');
	// ERR R9 - user of fast_codec should check it on his side
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(s[0], '\0');
	BOOST_REQUIRE_EQUAL(s[1], 'A');
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(s[0], '\0');
	BOOST_REQUIRE_EQUAL(s[1], '\0');
	BOOST_REQUIRE_EQUAL(s[2], '\0');
	// ERR R9 - user of fast_codec should check it on his side
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(s[0], '\0');
	BOOST_REQUIRE_EQUAL(s[1], '\0');
	BOOST_REQUIRE_EQUAL(s[2], 'A');
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(s[0], 'a');
	BOOST_REQUIRE_EQUAL(s[1], 'b');
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, s, sizeof(s)), 0);
	BOOST_REQUIRE_EQUAL(strncmp(s, "ABCDE", 6), 0);
	decoder.position_ = 0;
	fast_codec::string_nt strn;
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, strn), FC_NULL_VALUE);
	strn = fast_codec::string_nt{};
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, strn), FC_EMPTY_VALUE);
	BOOST_REQUIRE_EQUAL(strn.value_.c_str(), "");
	BOOST_REQUIRE_EQUAL(strn.is_null_, false);
	strn = fast_codec::string_nt{};
	// ERR R9 - user of fast_codec should check it on his side
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, strn), 0);
	BOOST_REQUIRE_EQUAL(strn.value_.c_str(), "");
	BOOST_REQUIRE_EQUAL(strn.is_null_, false);
	strn = fast_codec::string_nt{};
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, strn), 0);
	BOOST_REQUIRE_EQUAL(strn.value_.c_str(), "");
	BOOST_REQUIRE_EQUAL(strn.is_null_, false);
	strn = fast_codec::string_nt{};
	// ERR R9 - user of fast_codec should check it on his side
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, strn), 0);
	BOOST_REQUIRE_EQUAL(strn.value_.c_str(), "");
	BOOST_REQUIRE_EQUAL(strn.is_null_, false);
	strn = fast_codec::string_nt{};
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, strn), 0);
	BOOST_REQUIRE_EQUAL(strn.value_[0], 'a');
	BOOST_REQUIRE_EQUAL(strn.value_[1], 'b');
	BOOST_REQUIRE_EQUAL(strn.is_null_, false);
	strn = fast_codec::string_nt{};
	BOOST_REQUIRE_EQUAL(decode_string_ascii_optional(0, decoder, strn), 0);
	BOOST_REQUIRE_EQUAL(strncmp(strn.value_.c_str(), "ABCDE", 6), 0);
	BOOST_REQUIRE_EQUAL(strn.is_null_, false);
}

BOOST_AUTO_TEST_CASE(perf_test_decoder_ascii)
{
#ifdef NDEBUG
	const int cCycleCount = 5000000;
#else
	const int cCycleCount = 10;
#endif

	fast_codec::Encoder encoder;
	encoder.data_.reserve(20 * cCycleCount);
	char s[] = "TEST_STRING";
	{
		for (int i = 0; i < cCycleCount; ++i)
		{
			s[0] = i % 27;
			encode_string_ascii(0, encoder, s, sizeof(s));
		}
		fast_codec::Decoder decoder;
		decoder.data_ = encoder.data_;
		char s1[20];
		TimeCounterGuard t("decode_ascii (11 bytes)", cCycleCount);
		for (int i = 0; i < cCycleCount; ++i)
			decode_string_ascii(0, decoder, s1, sizeof(s1));
	}
}
