#ifndef FAST_CODEC_ENCODER_DECIMAL_HEADER
#define FAST_CODEC_ENCODER_DECIMAL_HEADER

#include "decimal.h"
#include "nullable_types.h"

namespace fast_codec
{
	struct Encoder;
	int encode_decimal(Encoder& e, const Decimal& d);
	int encode_bcd(Encoder& e, const uint8_t* bcd);

	int encode_decimal_optional(Encoder& e, const Decimal& d);
	int encode_decimal_optional(Encoder& e, const DecimalNullable& d);
	int encode_bcd_optional(Encoder& e, const uint8_t* bcd);
}

#endif
