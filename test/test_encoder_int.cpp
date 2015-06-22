
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
	
	encode_u32(encoder, 0);
	encode_u32(encoder, 942755);
	encode_u32(encoder, 128);
	encode_u32(encoder, 16384);
	encode_u32(encoder, 2097152);
	encode_u32(encoder, 268435456);
	encode_u32(encoder, 4294967295);
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
	encode_i32(encoder, 0);
	encode_i32(encoder, -64);
	encode_i32(encoder, -8192);
	encode_i32(encoder, -1048576);
	encode_i32(encoder, -134217728);
	encode_i32(encoder, 0x80000000); // -2147483648
	encode_i32(encoder, 2147483647);
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
	
	encode_u64(encoder, 0);
	encode_u64(encoder, 128);
	encode_u64(encoder, 16384);
	encode_u64(encoder, 2097152);
	encode_u64(encoder, 268435456);
	encode_u64(encoder, 0x0000000800000000ULL);
	encode_u64(encoder, 0x0000040000000000ULL);
	encode_u64(encoder, 0x0002000000000000ULL);
	encode_u64(encoder, 0x0100000000000000ULL);
	encode_u64(encoder, 0x8000000000000000ULL);
	encode_u64(encoder, 0xffffffffffffffffULL);
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
	encode_i64(encoder, 0);
	encode_i64(encoder, -64);
	encode_i64(encoder, -8192);
	encode_i64(encoder, -1048576);
	encode_i64(encoder, -134217728);
	encode_i64(encoder, 0xfffffffc00000000LL);
	encode_i64(encoder, 0xfffffe0000000000LL);
	encode_i64(encoder, 0xffff000000000000LL);
	encode_i64(encoder, 0xff80000000000000LL);
	encode_i64(encoder, 0xc000000000000000LL);
	encode_i64(encoder, 0x7fffffffffffffffLL);
	encode_i64(encoder, 0x8000000000000000LL);

	Check(encoder, sI64Etalon);
	encoder.Reset();

/*	// TEST CODE
	encoder.Reset();
	encode_i64(encoder, -2305);

	//unsigned char buf[] = { 0x12, 0x81 }; // delta = 2305-1 (-1 - due optional field) = 2304
	unsigned char buf[] = { 0x6d, 0xff }; // delta = -2305
	//Byte = sddd dddd, where s = stop bit (1=last byte, 0=continued byte), d = data

	//Standard extraction:
	int count = 0;
	uint64_t lastValue = 1000000;
	uint64_t value = 0;
	int64_t delta = 0;
	int64_t offset = 0;
	unsigned char byte = 0;
	unsigned char* pBuf = buf;

	do
	{
		byte = *pBuf;
		delta = (delta << 7) + (byte & 0x7f);
		++count;
		++pBuf;
	}
	while ((byte & 0x80) == 0);

	//Delta algorithm:
	if ((delta & 1) == 1) // -ve
	{
		offset = (1 << (7 * count)) - 1;
		value = lastValue - (offset - delta);
	}
	else // +ve
	{
		value = lastValue + delta;
	}
*/
}

BOOST_AUTO_TEST_CASE(perf_test_encoder_int)
{
#ifdef NDEBUG
	const int cCycleCount = 1000000;
#else
	const int cCycleCount = 10;
#endif

	fast_codec::Encoder encoder;
	encoder.data_.reserve(6*cCycleCount);
	{
		TimeCounterGuard t("encode_u32", cCycleCount);
		uint32_t d = 3294967295;
		for(uint32_t i = 0; i < cCycleCount; ++i)
			encode_u32(encoder, d+i);
	}
	{
		TimeCounterGuard t("encode_u64", cCycleCount);
		encoder.Reset();
		uint64_t v = 0x8000000000000000ULL;
		for(uint32_t j = 0; j < cCycleCount; ++j)
			encode_u64(encoder, v+j);
	}
}
