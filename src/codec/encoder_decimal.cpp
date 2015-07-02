#include "encoder.h"
#include "encoder_int.h"
#include "encoder_decimal.h"

namespace fast_codec
{
	int encode_decimal(Encoder& e, const Decimal& d)
	{
		int size = encode_i32(e, d.exponent_);
		size += encode_i64(e, d.mantissa_);
		return size;	
	}

	int encode_bcd(Encoder& e, const uint8_t* bcd)
	{
		if(!bcd)
			return 0;

		Decimal d(bcd);
		return encode_decimal(e, d);
	}

	int encode_decimal_optional(Encoder& e, const Decimal& d)
	{
		if (d.exponent_ > 0)
		{
			Decimal t{ d.exponent_ + 1, d.mantissa_ };
			return encode_decimal(e, t);
		}
		else
		{
			return encode_decimal(e, d);
		}
	}

	int encode_decimal_optional(Encoder& e, const DecimalNullable& d)
	{
		if(d.is_null_)
		{
			write_byte(e, 0x80);
			return 1;
		}
		else
		{
			return encode_decimal_optional(e, d.value_);
		}
	}

	int encode_bcd_optional(Encoder& e, const uint8_t* bcd)
	{
		if(bcd == NULL)
		{
			write_byte(e, 0x80);
			return 1;
		}
		else
		{
			Decimal d(bcd);
			return encode_decimal_optional(e, d);
		}
	}
} // namespace
