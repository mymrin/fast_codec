#include "decoder.h"
#include "decoder_int.h"
#include "decoder_decimal.h"

namespace fast_codec
{
	int decode_decimal(int, Decoder& e, Decimal& d)
	{
		int error = decode_i8(0, e, d.exponent_);
		if (!error)
			error = decode_i64(0, e, d.mantissa_);
		return error;
	}

	int decode_decimal_optional(int, Decoder& e, Decimal& d)
	{
		if (get_byte(e) == 0x80)
		{
			e.AddPosition();
			return FC_NULL_VALUE;
		}
		int error = decode_decimal(0, e, d);
		if (!error && d.exponent_ > 0)
			--d.exponent_;		
		return error;
	}

	int decode_decimal_optional(int, Decoder& e, DecimalNullable& d)
	{
		int error = decode_decimal_optional(0, e, d.value_);
		if (error == FC_NULL_VALUE)
			d.is_null_ = true;
		return error;
	}
}
