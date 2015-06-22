#ifndef FAST_BCD_HEADER
#define FAST_BCD_HEADER

#include <stdint.h>

namespace fast_codec
{
	typedef int8_t exponent_t;
	typedef int64_t mantissa_t;

	// BCD type for N (decimal numbers) and M (decimal numbers in mantissa)
	#define BCD_TYPE uint16_t
	#define BCD_MAKE_TYPE(N, M) (BCD_TYPE)(((N) << 8) | ((M) & 0xFF ))
	#define BCD_TYPE_N(TYPE) ((uint8_t)((TYPE) >> 8 ))
	#define BCD_TYPE_M(TYPE) ((uint8_t)(TYPE))
	#define BCD_SIZEOF(TYPE) (BCD_TYPE_N(TYPE) ? ((TYPE) >> 9) + (((TYPE) | ((TYPE) >> 8)) & 1 ) : 0)

	#define BCD_RESULT_OVERFLOW   0x0001
	#define BCD_RESULT_ZERO       0x0002
	#define BCD_RESULT_NEGATIVE   0x0004
	#define BCD_RESULT_BAD        0x0010
	#define BCD_OPERAND_BAD       0x0020
	#define BCD_RESULT_PREC       0x0040
	#define BCD_OPERAND_NAN       0x0080
	#define BCD_NOT_STRICT_FORMAT 0x0100

	uint32_t decimal_to_bcd(uint8_t* bcd, BCD_TYPE type, mantissa_t intpart, exponent_t scale);
	void bcd_to_decimal(const uint8_t* bcd, mantissa_t& intpart, exponent_t& pscale);

#pragma pack(push, 1)
	template<uint8_t N, uint8_t M>
	struct BCD
	{
		uint16_t typ_;
		uint8_t val_[BCD_SIZEOF(BCD_MAKE_TYPE(N, M))];

		BCD() : typ_(BCD_MAKE_TYPE(N, M)) {}

		BCD(mantissa_t intpart, exponent_t scale) : typ_(BCD_MAKE_TYPE(N, M))
		{
			decimal_to_bcd(val_, BCD_MAKE_TYPE(N, M), intpart, scale);
		}
	};
#pragma pack(pop)
}

#endif
