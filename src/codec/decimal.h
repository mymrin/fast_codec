#ifndef FAST_CODEC_DECIMAL_HEADER
#define FAST_CODEC_DECIMAL_HEADER

#include <stdint.h>
#include "bcd.h"

namespace fast_codec
{
	struct Decimal
	{
		exponent_t exponent_;
		mantissa_t mantissa_;

		explicit Decimal(const uint8_t* bcd)
		{
			bcd_to_decimal(bcd, mantissa_, exponent_);
			exponent_ = -exponent_;
		}

		Decimal(exponent_t e, mantissa_t m) : exponent_(e), mantissa_(m) {}

		template<uint8_t N, uint8_t M>
		uint32_t ToBCD(uint8_t (&bcd)[sizeof(uint16_t) + BCD_SIZEOF(BCD_MAKE_TYPE(N, M))])
		{
			uint16_t& typ = reinterpret_cast<uint16_t&>(bcd);
			typ = BCD_MAKE_TYPE(N, M);
			return decimal_to_bcd(bcd + sizeof(uint16_t), BCD_MAKE_TYPE(N, M), mantissa_, -exponent_);
		}
	};
}

#endif
