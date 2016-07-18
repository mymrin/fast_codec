#include "decoder.h"
#include "decoder_int.h"
#include "decoder_byte_vector.h"

namespace fast_codec
{
	int decode_byte_vector(int, Decoder& e, byte* buf, const size_t size, size_t& decoded_size, bool is_optional)
	{
		int err = 0;
		if (buf != nullptr && size != 0)
		{
			if (is_optional)
				err = decode_u64_optional(0, e, decoded_size);
			else
				err = decode_u64(0, e, decoded_size);
			if (err == 0)
			{
				if (decoded_size <= size)
				{
					if (e.Size() - e.Position() >= decoded_size)
						memcpy(buf, &e.Data()[e.Position()], decoded_size);
					else
						return FC_UNEXPECTED_END_OF_BUFFER_END;
				}
				else
				{
					return FC_BUFFER_OVERFLOW;
				}
			}
		}
		else
		{
			return FC_INCORRECT_PARAMETER;
		}
		return err;
	}

	int decode_byte_vector(int, Decoder& e, byte* buf, const size_t size, size_t& decoded_size)
	{
		return decode_byte_vector(0, e, buf, size, decoded_size, false);
	}

	int decode_byte_vector_optional(int, Decoder& e, byte* buf, const size_t size, size_t& decoded_size)
	{
		if (get_byte(e) == 0x80)
		{
			e.AddPosition();
			decoded_size = 0;
			return FC_NULL_VALUE;
		}
		else if (get_byte(e) == 0x81)
		{
			e.AddPosition();
			decoded_size = 0;
			return FC_EMPTY_VALUE;
		}
		return decode_byte_vector(0, e, buf, size, decoded_size, true);
	}
}
