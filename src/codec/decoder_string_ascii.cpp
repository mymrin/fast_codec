#include "decoder.h"
#include "decoder_string_ascii.h"

namespace fast_codec
{
	const std::uint8_t stop_bit = std::uint8_t('\x80');
	const std::uint8_t data_bits = std::uint8_t('\x7F');

	int decode_string_ascii(int, Decoder& e, char* c)
	{
		if (c != nullptr)
		{
			char str[2];
			int err = decode_string_ascii(0, e, str, sizeof(str));
			if (err == 0)
				*c = str[0];
			return err;
		}
		return FC_INCORRECT_PARAMETER;
	}

	int decode_string_ascii(int, Decoder& e, char* str, const size_t size)
	{
		if (str != nullptr && size != 0)
		{
			byte b;
			for (size_t i = 0;; i++)
			{
				if (i >= size)
					return FC_BUFFER_OVERFLOW;
				if (read_byte(e, b) == 0)
				{
					if (b & stop_bit)
					{
						str[i] = (b & data_bits);
						return 0;
					}
					str[i] = b;
				}
				else
				{
					return FC_UNEXPECTED_END_OF_BUFFER_END;
				}
			}
		}
		return FC_INCORRECT_PARAMETER;
	}

	int decode_string_ascii(int, Decoder& e, std::string& str)
	{
		byte b;
		for (size_t i = 0;; i++)
		{
			if (read_byte(e, b) == 0)
			{
				if (b & stop_bit)
				{
					str.push_back(b & data_bits);
					return 0;
				}
				str.push_back(b);
			}
			else
			{
				return FC_UNEXPECTED_END_OF_BUFFER_END;
			}
		}
		return 0;
	}

	int decode_string_ascii_optional(int, Decoder& e, char* str, size_t size)
	{
		if (get_byte(e) == 0x80)
		{
			e.AddPosition();
			return FC_NULL_VALUE;
		}
		else if (get_byte(e) == 0x00)
		{
			byte b;
			if (read_byte(e, b) == 0)
			{
				if (get_byte(e) == 0x80)
				{
					if (size >= 2)
					{
						str[0] = b;
						str[1] = (get_byte(e) & data_bits);
						e.AddPosition();
						return FC_EMPTY_VALUE;
					}
					else
					{
						return FC_BUFFER_OVERFLOW;
					}
				}
				else
				{
					--e.position_;
				}
			}
			else
			{
				return FC_UNEXPECTED_END_OF_BUFFER_END;
			}
		}
		return decode_string_ascii(0, e, str, size);
	}

	int decode_string_ascii_optional(int, Decoder& e, string_nt& str)
	{
		if (get_byte(e) == 0x80)
		{
			e.AddPosition();
			str.is_null_ = true;
			return FC_NULL_VALUE;
		}
		else if (get_byte(e) == 0x00)
		{
			byte b;
			if (read_byte(e, b) == 0)
			{
				if (get_byte(e) == 0x80)
				{
					str.value_.push_back(b);
					str.value_.push_back(get_byte(e) & data_bits);
					str.is_null_ = false;
					e.AddPosition();
					return FC_EMPTY_VALUE;
				}
				else
				{
					--e.position_;
				}
			}
			else
			{
				return FC_UNEXPECTED_END_OF_BUFFER_END;
			}
		}
		str.is_null_ = false;
		return decode_string_ascii(0, e, str.value_);
	}
} // namespace
