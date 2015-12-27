#ifndef FAST_CODEC_ENCODER_DECIMAL_HEADER
#define FAST_CODEC_ENCODER_DECIMAL_HEADER

#include "decimal.h"
#include "nullable_types.h"

namespace fast_codec
{
	struct Encoder;
	int encode_decimal(int, Encoder& e, const Decimal& d);
	int encode_bcd(int, Encoder& e, const uint8_t* bcd);

	int encode_decimal_optional(int, Encoder& e, const Decimal& d);
	int encode_decimal_optional(int, Encoder& e, const DecimalNullable& d);
	int encode_bcd_optional(int, Encoder& e, const uint8_t* bcd);
}

#endif
