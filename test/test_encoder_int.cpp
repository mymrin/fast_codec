#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "codec/encoder.h"
#include "codec/encoder_int.h"

BOOST_AUTO_TEST_CASE(test_encoder_int)
{
	fast_codec::Encoder encoder;

	// uInt32 test
	const unsigned char sU32Etalon[] =
	{ 
		0x80,
		0x39, 0x45, 0xa3,
		0x01, 0x80,
		0x01, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x80,
		0x01, 0x00, 0x00, 0x00, 0x80,
		0x0f, 0x7f, 0x7f, 0x7f, 0xff
	};
	
	encode_u32(0, encoder, 0);
	encode_u32(0, encoder, 942755);
	encode_u32(0, encoder, 128);
	encode_u32(0, encoder, 16384);
	encode_u32(0, encoder, 2097152);
	encode_u32(0, encoder, 268435456);
	encode_u32(0, encoder, 4294967295);
	Check(encoder, sU32Etalon);
	encoder.Reset();

	// int32 test
	const unsigned char sI32Etalon[] = { 
		0x80,
		0xc0,
		0x40, 0x80,
		0x40, 0x00, 0x80,
		0x40, 0x00, 0x00, 0x80,
		0x78, 0x00, 0x00, 0x00, 0x80,
		0x07, 0x7f, 0x7f, 0x7f, 0xff
	};
	encode_i32(0, encoder, 0);
	encode_i32(0, encoder, -64);
	encode_i32(0, encoder, -8192);
	encode_i32(0, encoder, -1048576);
	encode_i32(0, encoder, -134217728);
	encode_i32(0, encoder, 0x80000000); // -2147483648
	encode_i32(0, encoder, 2147483647);
	Check(encoder, sI32Etalon);
	encoder.Reset();

	// uInt64 test
	const unsigned char sU64Etalon[] =
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
		0x01, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff
	};
	
	encode_u64(0, encoder, 0);
	encode_u64(0, encoder, 128);
	encode_u64(0, encoder, 16384);
	encode_u64(0, encoder, 2097152);
	encode_u64(0, encoder, 268435456);
	encode_u64(0, encoder, 0x0000000800000000ULL);
	encode_u64(0, encoder, 0x0000040000000000ULL);
	encode_u64(0, encoder, 0x0002000000000000ULL);
	encode_u64(0, encoder, 0x0100000000000000ULL);
	encode_u64(0, encoder, 0x8000000000000000ULL);
	encode_u64(0, encoder, 0xffffffffffffffffULL);
	Check(encoder, sU64Etalon);
	encoder.Reset();

	// int64 test
	const unsigned char sI64Etalon[] = { 
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
		0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80
	};
	encode_i64(0, encoder, 0);
	encode_i64(0, encoder, -64);
	encode_i64(0, encoder, -8192);
	encode_i64(0, encoder, -1048576);
	encode_i64(0, encoder, -134217728);
	encode_i64(0, encoder, 0xfffffffc00000000LL);
	encode_i64(0, encoder, 0xfffffe0000000000LL);
	encode_i64(0, encoder, 0xffff000000000000LL);
	encode_i64(0, encoder, 0xff80000000000000LL);
	encode_i64(0, encoder, 0xc000000000000000LL);
	encode_i64(0, encoder, 0x7fffffffffffffffLL);
	encode_i64(0, encoder, 0x8000000000000000LL);

	Check(encoder, sI64Etalon);
	encoder.Reset();
}

BOOST_AUTO_TEST_CASE(perf_test_encoder_int)
{
#ifdef NDEBUG
	const int cCycleCount = 10000000;
#else
	const int cCycleCount = 10;
#endif
	fast_codec::Encoder encoder;
	encoder.data_.reserve(10 * cCycleCount);
	{
		TimeCounterGuard t("encode_u32", cCycleCount);
		uint32_t d = 3294967295;
		for(uint32_t i = 0; i < cCycleCount; ++i)
			encode_u32(0, encoder, d + i);
	}
	encoder.Reset();
	{
		TimeCounterGuard t("encode_i32", cCycleCount);
		int32_t d = -134217728;
		for (int32_t i = 0; i < cCycleCount; ++i)
			encode_u32(0, encoder, d - i);
	}
	encoder.Reset();
	{
		TimeCounterGuard t("encode_u64", cCycleCount);
		uint64_t v = 0x8000000000000000ULL;
		for(uint32_t j = 0; j < cCycleCount; ++j)
			encode_u64(0, encoder, v + j);
	}
	encoder.Reset();
	{
		TimeCounterGuard t("encode_i64", cCycleCount);
		int64_t v = 0x7fffffffffffffffLL;
		for (uint32_t j = 0; j < cCycleCount; ++j)
			encode_i64(0, encoder, v - j);
	}
}
