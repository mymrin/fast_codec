#include "encoder.h"
#include "encoder_string_utf8.h"
#include "encoder_byte_vector.h"

namespace fast_codec
{
	size_t encode_string_utf8(Encoder& e, const std::string& str)
	{
		return encode_byte_vector(e, reinterpret_cast<const byte*>(str.c_str()), str.size());
	}

	size_t encode_string_utf8_optional(Encoder& e, const string_nt& str)
	{
		if (str.is_null_ == NULL)
		{
			write_byte(e, 0x80);
			return 1;
		}
		else
		{
			return encode_string_utf8(e, str.value_);
		}
	}
}