#include "encoder.h"
#include "encoder_int.h"
#include "encoder_decimal.h"

namespace fast_codec
{
	int encode_decimal(int, Encoder& e, const Decimal& d)
	{
		int size = encode_i32(0, e, d.exponent_);
		size += encode_i64(0, e, d.mantissa_);
		return size;	
	}

	int encode_bcd(int, Encoder& e, const uint8_t* bcd)
	{
		if(!bcd)
			return 0;

		Decimal d(bcd);
		return encode_decimal(0, e, d);
	}

	int encode_decimal_optional(int, Encoder& e, const Decimal& d)
	{
		if (d.exponent_ > 0)
		{
			Decimal t{ d.exponent_ + 1, d.mantissa_ };
			return encode_decimal(0, e, t);
		}
		else
		{
			return encode_decimal(0, e, d);
		}
	}

	int encode_decimal_optional(int, Encoder& e, const DecimalNullable& d)
	{
		if(d.is_null_)
		{
			write_byte(e, 0x80);
			return 1;
		}
		else
		{
			return encode_decimal_optional(0, e, d.value_);
		}
	}

	int encode_bcd_optional(int, Encoder& e, const uint8_t* bcd)
	{
		if(bcd == NULL)
		{
			write_byte(e, 0x80);
			return 1;
		}
		else
		{
			Decimal d(bcd);
			return encode_decimal_optional(0, e, d);
		}
	}
} // namespace
