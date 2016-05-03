#pragma once

#include "nullable_types.h"

namespace fast_codec
{
	struct Decoder;
	int decode_decimal(int, Decoder& e, Decimal& d);
	int decode_decimal_optional(int, Decoder& e, Decimal& d);
	int decode_decimal_optional(int, Decoder& e, DecimalNullable& d);
}
