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

	// int32 test
	std::int32_t v1 = 0;
	decoder.data_ =
	{
		0x80,
		0xc0,
		0x40, 0x80,
		0x40, 0x00, 0x80,
		0x40, 0x00, 0x00, 0x80,
		0x78, 0x00, 0x00, 0x00, 0x80,
		0x07, 0x7f, 0x7f, 0x7f, 0xff,
		0x10, 0x7f, 0x7f, 0x7f, 0xff,
		0x40, 0x7f, 0x7f, 0x7f, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	};
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), 0);
	BOOST_REQUIRE_EQUAL(v1, 0);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), 0);
	BOOST_REQUIRE_EQUAL(v1, -64);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), 0);
	BOOST_REQUIRE_EQUAL(v1, -8192);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), 0);
	BOOST_REQUIRE_EQUAL(v1, -1048576);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), 0);
	BOOST_REQUIRE_EQUAL(v1, -134217728);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), 0);
	BOOST_REQUIRE_EQUAL(v1, 0x80000000); // -2147483648
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), 0);
	BOOST_REQUIRE_EQUAL(v1, 2147483647);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), FC_INTEGER_OVERFLOW);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), FC_INTEGER_OVERFLOW);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), FC_INTEGER_DO_NOT_HAVE_STOP_BIT);
	BOOST_REQUIRE_EQUAL(decode_i32(0, decoder, v1), FC_UNEXPECTED_END_OF_BUFFER_END);
	decoder.Reset();

	// uInt64 test
	std::uint64_t v2 = 0;
	decoder.data_ =
	{
		0x80,
		0x01, 0x80,
		0x01, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff,
		0x03, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 0);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 128);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 16384);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 2097152);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 268435456);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 0x0000000800000000ULL);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 0x0000040000000000ULL);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 0x0002000000000000ULL);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 0x0100000000000000ULL);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 0x8000000000000000ULL);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), 0);
	BOOST_REQUIRE_EQUAL(v2, 0xffffffffffffffffULL);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), FC_INTEGER_OVERFLOW);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), FC_INTEGER_DO_NOT_HAVE_STOP_BIT);
	BOOST_REQUIRE_EQUAL(decode_u64(0, decoder, v2), FC_UNEXPECTED_END_OF_BUFFER_END);
	decoder.Reset();

	// int64 test
	std::int64_t v3 = 0;
	decoder.data_ =
	{
		0x80,
		0xc0,
		0x40, 0x80,
		0x40, 0x00, 0x80,
		0x40, 0x00, 0x00, 0x80,
		0x40, 0x00, 0x00, 0x00, 0x80,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff,
		0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, 0);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, -64);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, -8192);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, -1048576);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, -134217728);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, 0xfffffffc00000000LL);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, 0xfffffe0000000000LL);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, 0xffff000000000000LL);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, 0xff80000000000000LL);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, 0xc000000000000000LL);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, 0x7fffffffffffffffLL);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), 0);
	BOOST_REQUIRE_EQUAL(v3, 0x8000000000000000LL);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), FC_INTEGER_OVERFLOW);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), FC_INTEGER_OVERFLOW);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), FC_INTEGER_DO_NOT_HAVE_STOP_BIT);
	BOOST_REQUIRE_EQUAL(decode_i64(0, decoder, v3), FC_UNEXPECTED_END_OF_BUFFER_END);
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
	encoder.data_.reserve(10 * cCycleCount);
	{
		uint32_t d = 3294967295;
		for (uint32_t i = 0; i < cCycleCount; ++i)
			encode_u32(0, encoder, d + i);
		decoder.data_ = encoder.data_;
		TimeCounterGuard t("decode_int_warmup", cCycleCount);
		std::uint32_t v = 0;
		for (uint32_t i = 0; i < cCycleCount; ++i)
			decode_u32(0, decoder, v);
	}
	encoder.Reset();
	decoder.Reset();
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
	encoder.Reset();
	decoder.Reset();
	{
		int32_t d = -134217728;
		for (int32_t i = 0; i < cCycleCount; ++i)
			encode_u32(0, encoder, d - i);
		decoder.data_ = encoder.data_;
		TimeCounterGuard t("decode_i32", cCycleCount);
		std::int32_t v = 0;
		for (uint32_t i = 0; i < cCycleCount; ++i)
			decode_i32(0, decoder, v);
	}
#ifdef NDEBUG
	const int cCycleCount64 = 10000000;
#else
	const int cCycleCount64 = 10;
#endif
	encoder.Reset();
	decoder.Reset();
	{
		uint64_t d = 0x8000000000000000ULL;
		for (uint32_t i = 0; i < cCycleCount64; ++i)
			encode_u64(0, encoder, d + i);
		decoder.data_ = encoder.data_;
		TimeCounterGuard t("decode_u64", cCycleCount64);
		std::uint64_t v = 0;
		for (uint32_t i = 0; i < cCycleCount64; ++i)
			decode_u64(0, decoder, v);
	}
	encoder.Reset();
	decoder.Reset();
	{
		int64_t d = 0x7fffffffffffffffLL;
		for (uint32_t i = 0; i < cCycleCount64; ++i)
			encode_i64(0, encoder, d + i);
		decoder.data_ = encoder.data_;
		TimeCounterGuard t("decode_i64", cCycleCount64);
		std::int64_t v = 0;
		for (uint32_t i = 0; i < cCycleCount64; ++i)
			decode_i64(0, decoder, v);
	}
}
