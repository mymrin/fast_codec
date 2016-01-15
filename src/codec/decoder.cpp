#include "decoder.h"

namespace fast_codec
{
	int read_byte(int, Decoder& c, std::uint8_t& b)
	{
		return read_byte(c, b);
	}

	int read_byte(Decoder& c, std::uint8_t& b)
	{
		if (c.position_ < c.data_.size())
		{
			b = c.data_[c.position_];
			++c.position_;
			return 0;
		}
		return FC_UNEXPECTED_END_OF_BUFFER_END;
	}
}
