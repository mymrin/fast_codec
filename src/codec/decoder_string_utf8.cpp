#include "decoder.h"
#include "decoder_int.h"
#include "decoder_string_utf8.h"

namespace fast_codec
{
	int decode_string_utf8(int, Decoder& e, std::string& str, bool is_optional)
	{
		int err = 0;
		size_t size = 0;
		if (is_optional)
			err = decode_u64_optional(0, e, size);
		else
			err = decode_u64(0, e, size);
		if (err == 0)
		{
			if (e.Size() - e.Position() >= size)
			{
				str.reserve(size);
				str.assign(&e.Data()[e.Position()], &e.Data()[e.Position() + size]);
			}
			else
			{
				return FC_UNEXPECTED_END_OF_BUFFER_END;
			}
		}
		return err;
	}

	int decode_string_utf8(int, Decoder& e, std::string& str)
	{
		return decode_string_utf8(0, e, str, false);
	}

	int decode_string_utf8_optional(int, Decoder& e, std::string& str)
	{
		return decode_string_utf8(0, e, str, true);
	}

	int decode_string_utf8_optional(int, Decoder& e, string_nt& str)
	{
		if (get_byte(e) == 0x80)
		{
			e.AddPosition();
			str.is_null_ = true;
			return FC_NULL_VALUE;
		}
		str.is_null_ = false;
		return decode_string_utf8(0, e, str.value_, true);
	}
} // namespace
