#ifndef FAST_SIMPLE_CODEC_DECIMAL_HEADER
#define FAST_SIMPLE_CODEC_DECIMAL_HEADER

#include <cstdint>

namespace fast_simple_codec
{
	typedef std::int8_t exponent_t;
	typedef std::int64_t mantissa_t;

	struct Decimal
	{
		exponent_t exponent_;
		mantissa_t mantissa_;
	};
}

#endif
