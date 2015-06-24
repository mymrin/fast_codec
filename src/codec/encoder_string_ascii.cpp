#include "encoder.h"
#include "encoder_string_ascii.h"

namespace fast_codec
{

	size_t encode_string_ascii(Encoder& e, const char* pStr, size_t length)
	{
		if(pStr != NULL && length != 0)
		{
			for(uint32_t i = 0; i < length - 1; ++i)
			{
				if(pStr[i+1] == '\0')
				{
					// Stop bit
					write_byte(e, pStr[i] | 0x80);
					return i+1;				
				}
				write_byte(e, pStr[i]);
			}
			// Stop bit
			write_byte(e, pStr[length-1] | 0x80);
			return length-1;
		}
		else
		{
			write_byte(e, 0x80);
			return 1;
		}
		return 0;
	}

	size_t encode_string_ascii(Encoder& e, const std::string& str)
	{
		return encode_string_ascii(e, str.c_str(), str.size());
	}

	size_t encode_string_ascii_optional(Encoder& e, const char* pStr, size_t length)
	{
		if(pStr == NULL)
		{
			write_byte(e, 0x80);
			return 1;
		}
		else if(length == 0)
		{
			write_byte(e, 0x00);
			write_byte(e, 0x80);
			return 2;
		}
		else
		{
			return encode_string_ascii(e, pStr, length);
		}
	}

	size_t encode_string_ascii_optional(Encoder& e, const string_nt& str)
	{
		if (str.is_null_)
			return encode_string_ascii_optional(e, nullptr, 0);
		else
			return encode_string_ascii_optional(e, str.value_.c_str(), str.value_.size());
	}

} // namespace
