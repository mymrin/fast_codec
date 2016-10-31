#include "decoder.h"
#include "decoder_int.h"

namespace fast_codec
{
	const std::uint8_t stop_bit = std::uint8_t('\x80');
	const std::uint8_t sign_bit = std::uint8_t('\x40');
	const std::uint8_t data_bits = std::uint8_t('\x7F');

	int decode_i8(int, Decoder& codec, std::int8_t& d)
	{
		std::uint8_t b;
		std::uint8_t first_byte;
		d = 0;
		if (read_byte(codec, b) == 0)
		{
				first_byte = b;
				if (b & sign_bit)
					d = std::int8_t(0xFF);
				d <<= 7;
				d |= (b & data_bits);
				if (b & stop_bit)
					return 0;
		}
		else
		{
			return FC_UNEXPECTED_END_OF_BUFFER_END;
		}
		if (read_byte(codec, b) == 0)
		{
			if (first_byte & sign_bit)
			{
				if ((first_byte & data_bits) >> 4 != 0x00000001) // 0x01 - 0000 0001
					return FC_INTEGER_OVERFLOW;
			}
			else
			{
				if ((first_byte & data_bits) >> 4 != 0)
					return FC_INTEGER_OVERFLOW;
			}
			d <<= 7;
			d |= (b & data_bits);
			if (b & stop_bit)
				return 0;
			else
				return FC_INTEGER_DO_NOT_HAVE_STOP_BIT;
		}
		return FC_UNEXPECTED_END_OF_BUFFER_END;
	}

	int decode_u32(int, Decoder& codec, std::uint32_t& d)
	{
		std::uint8_t b;
		std::uint8_t first_byte;
		d = 0;
		for (std::uint8_t i = 0; i != 4; ++i)
		{
			if (read_byte(codec, b) == 0)
			{
				if (i == 0)
					first_byte = b;
				d <<= 7;
				d |= (b & data_bits);
				if (b & stop_bit)
					return 0;
			}
			else
			{
				return FC_UNEXPECTED_END_OF_BUFFER_END;
			}
		}
		if (read_byte(codec, b) == 0)
		{
			if ((first_byte & data_bits) >> 4 != 0)
				return FC_INTEGER_OVERFLOW;
			d <<= 7;
			d |= (b & data_bits);
			if (b & stop_bit)
				return 0;
			else
				return FC_INTEGER_DO_NOT_HAVE_STOP_BIT;
		}
		return FC_UNEXPECTED_END_OF_BUFFER_END;
	}

	int decode_i32(int, Decoder& codec, std::int32_t& d)
	{
		std::uint8_t b;
		std::uint8_t first_byte;
		d = 0;
		for (std::uint8_t i = 0; i != 4; ++i)
		{
			if (read_byte(codec, b) == 0)
			{
				if (i == 0)
				{
					first_byte = b;
					if (b & sign_bit)
						d = 0xFFFFFFFF;
				}
				d <<= 7;
				d |= (b & data_bits);
				if (b & stop_bit)
					return 0;
			}
			else
			{
				return FC_UNEXPECTED_END_OF_BUFFER_END;
			}
		}
		if (read_byte(codec, b) == 0)
		{
			if (first_byte & sign_bit)
			{
				if ((first_byte & data_bits) >> 4 != 0x00000007) // 0x07 - 0000 0111
					return FC_INTEGER_OVERFLOW;
			}
			else
			{
				if ((first_byte & data_bits) >> 4 != 0)
					return FC_INTEGER_OVERFLOW;
			}
			d <<= 7;
			d |= (b & data_bits);
			if (b & stop_bit)
				return 0;
			else
				return FC_INTEGER_DO_NOT_HAVE_STOP_BIT;
		}
		return FC_UNEXPECTED_END_OF_BUFFER_END;
	}

	int decode_u64(int, Decoder& codec, std::uint64_t& d)
	{
		std::uint8_t b;
		std::uint8_t first_byte;
		d = 0;
		for (std::uint8_t i = 0; i != 9; ++i)
		{
			if (read_byte(codec, b) == 0)
			{
				if (i == 0)
					first_byte = b;
				d <<= 7;
				d |= (b & data_bits);
				if (b & stop_bit)
					return 0;
			}
			else
			{
				return FC_UNEXPECTED_END_OF_BUFFER_END;
			}
		}
		if (read_byte(codec, b) == 0)
		{
			if ((first_byte & data_bits) >> 1 != 0)
				return FC_INTEGER_OVERFLOW;
			d <<= 7;
			d |= (b & data_bits);
			if (b & stop_bit)
				return 0;
			else
				return FC_INTEGER_DO_NOT_HAVE_STOP_BIT;
		}
		return FC_UNEXPECTED_END_OF_BUFFER_END;
	}

	int decode_i64(int, Decoder& codec, std::int64_t& d)
	{
		std::uint8_t b;
		std::uint8_t first_byte;
		d = 0;
		for (std::uint8_t i = 0; i != 9; ++i)
		{
			if (read_byte(codec, b) == 0)
			{
				if (i == 0)
				{
					first_byte = b;
					if (b & sign_bit)
						d = 0xFFFFFFFFFFFFFFFF;
				}
				d <<= 7;
				d |= (b & data_bits);
				if (b & stop_bit)
					return 0;
			}
			else
			{
				return FC_UNEXPECTED_END_OF_BUFFER_END;
			}
		}
		if (read_byte(codec, b) == 0)
		{
			if (first_byte & sign_bit)
			{
				if ((first_byte & data_bits) >> 1 != 0x0000003F) // 0x3F - 0011 1111
					return FC_INTEGER_OVERFLOW;
			}
			else
			{
				if ((first_byte & data_bits) >> 1 != 0)
					return FC_INTEGER_OVERFLOW;
			}
			d <<= 7;
			d |= (b & data_bits);
			if (b & stop_bit)
				return 0;
			else
				return FC_INTEGER_DO_NOT_HAVE_STOP_BIT;
		}
		return FC_UNEXPECTED_END_OF_BUFFER_END;
	}

	int decode_u32_optional(int, Decoder& codec, std::uint32_t& d)
	{
		if (get_byte(codec) == 0x80)
		{
			codec.AddPosition();
			return FC_NULL_VALUE;
		}
		int error = decode_u32(0, codec, d);
		if (!error) 
			--d;
		return error;
	}

	int decode_i32_optional(int, Decoder& codec, std::int32_t& d)
	{
		if (get_byte(codec) == 0x80)
		{
			codec.AddPosition();
			return FC_NULL_VALUE;
		}
		int error = decode_i32(0, codec, d);
		if (!error && d > 0)
			--d;
		return error;
	}

	int decode_u64_optional(int, Decoder& codec, std::uint64_t& d)
	{
		if (get_byte(codec) == 0x80)
		{
			codec.AddPosition();
			return FC_NULL_VALUE;
		}
		int error = decode_u64(0, codec, d);
		if (!error)
			--d;
		return error;
	}

	int decode_i64_optional(int, Decoder& codec, std::int64_t& d)
	{
		if (get_byte(codec) == 0x80)
		{
			codec.AddPosition();
			return FC_NULL_VALUE;
		}
		int error = decode_i64(0, codec, d);
		if (!error && d > 0)
			--d;
		return error;
	}

	int decode_u32_optional(int, Decoder& codec, uint32_nt& d)
	{
		if (get_byte(codec) == 0x80)
		{
			d.is_null_ = true;
			codec.AddPosition();
			return FC_NULL_VALUE;
		}
		d.is_null_ = false;
		int error = decode_u32(0, codec, d.value_);
		if (!error)
			--d.value_;
		return error;
	}

	int decode_i32_optional(int, Decoder& codec, int32_nt& d)
	{
		if (get_byte(codec) == 0x80)
		{
			d.is_null_ = true;
			codec.AddPosition();
			return FC_NULL_VALUE;
		}
		d.is_null_ = false;
		int error = decode_i32(0, codec, d.value_);
		if (!error && d.value_ > 0)
			--d.value_;
		return error;
	}

	int decode_u64_optional(int, Decoder& codec, uint64_nt& d)
	{
		if (get_byte(codec) == 0x80)
		{
			d.is_null_ = true;
			codec.AddPosition();
			return FC_NULL_VALUE;
		}
		d.is_null_ = false;
		int error = decode_u64(0, codec, d.value_);
		if (!error)
			--d.value_;
		return error;
	}

	int decode_i64_optional(int, Decoder& codec, int64_nt& d)
	{
		if (get_byte(codec) == 0x80)
		{
			d.is_null_ = true;
			codec.AddPosition();
			return FC_NULL_VALUE;
		}
		d.is_null_ = false;
		int error = decode_i64(0, codec, d.value_);
		if (!error && d.value_ > 0)
			--d.value_;
		return error;
	}
} // namespace
