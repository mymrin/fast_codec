#include "encoder.h"
#include "encoder_int.h"
#include "encoder_byte_vector.h"

namespace fast_codec
{

	size_t encode_byte_vector(Encoder& e, const byte* pBuf, size_t bufSize)
	{
		size_t size = encode_u64(e, bufSize);
	
		if(pBuf != 0 && bufSize != 0)
		{
			size_t size = e.data_.size();
			e.data_.resize(size + bufSize);
			memcpy(&e.data_[size], pBuf, bufSize);
		}
	
		return size + bufSize;
	}

	size_t encode_byte_vector_optional(Encoder& e, const byte* pBuf, std::uint32_t bufSize)
	{
		if(pBuf == NULL)
		{
			write_byte(e, 0x80);
			return 1;
		}
		else if(bufSize == 0)
		{
			write_byte(e, 0x81);
			return 1;
		}
		else
		{
			return encode_byte_vector(e, pBuf, bufSize);
		}
	}

} // namespace
