#include "encoder.h"
#include "encoder_string_utf8.h"
#include "encoder_byte_vector.h"

namespace fast_codec
{
	size_t encode_string_utf8(int, Encoder& e, const std::string& str)
	{
		return encode_byte_vector(0, e, reinterpret_cast<const byte*>(str.c_str()), str.size(), false);
	}

	size_t encode_string_utf8_optional(int, Encoder& e, const std::string& str)
	{
		return encode_byte_vector(0, e, reinterpret_cast<const byte*>(str.c_str()), str.size(), true);
	}

	size_t encode_string_utf8_optional(int, Encoder& e, const string_nt& str)
	{
		if (str.is_null_ == NULL)
		{
			write_byte(e, 0x80);
			return 1;
		}
		else
		{
			return encode_byte_vector(0, e, reinterpret_cast<const byte*>(str.value_.c_str()), str.value_.size(), true);
		}
	}
} // namespace fast_codec
