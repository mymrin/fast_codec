#include "encoder.h"
#include "encoder_ascii.h"

namespace fast_simple_codec
{

int encode_ascii(Encoder& e, const char* pStr, std::uint32_t length)
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

int encode_ascii_optional(Encoder& e, const char* pStr, std::uint32_t length)
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
		return encode_ascii(e, pStr, length);
	}
}

} // namespace
