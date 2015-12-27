#include <string.h>
#include "encoder.h"
#include "encoder_int.h"
#include "encoder_byte_vector.h"

namespace fast_codec
{
	size_t encode_byte_vector(int, Encoder& e, const byte* buf, size_t size, bool is_optional)
	{
		size_t preamble_size = 0;
		if (buf != 0 && size != 0)
		{
			if (is_optional)
				preamble_size = encode_u64_optional(0, e, size);
			else
				preamble_size = encode_u64(0, e, size);
			size_t n = e.Data().size();
			e.data_.resize(n + size);
			memcpy(&e.data_[n], buf, size);
		}
		return preamble_size + size;
	}

	size_t encode_byte_vector(int, Encoder& e, const byte* buf, size_t size)
	{
		return encode_byte_vector(0, e, buf, size, false);
	}

	size_t encode_byte_vector_optional(int, Encoder& e, const byte* buf, size_t size)
	{
		if (buf == NULL)
		{
			// Null
			write_byte(e, 0x80);
			return 1;
		}
		else if (size == 0)
		{
			// Empty byte vector
			write_byte(e, 0x81);
			return 1;
		}
		else
		{
			return encode_byte_vector(0, e, buf, size, true);
		}
	}
} // namespace
