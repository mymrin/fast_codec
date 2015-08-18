
#include "encoder.h"

namespace fast_codec
{
	void write_byte(int, Encoder& c, std::uint8_t b)
	{
		c.data_.push_back(b);
	}

	void write_byte(Encoder& c, std::uint8_t b)
	{
		c.data_.push_back(b);
	}

	void write_byte(Encoder& c, std::uint8_t b, std::uint32_t count)
	{
		for (std::uint32_t i = 0; i < count; i++)
			c.data_.push_back(b);
	}

	void write(Encoder& c, std::uint32_t msg_seq_num)
	{
		c.data_.resize(c.data_.size() + sizeof(msg_seq_num));
		std::uint32_t* dst = reinterpret_cast<std::uint32_t*>(&(c.data_[c.data_.size() - sizeof(msg_seq_num)]));
		*dst = msg_seq_num;
	}
}
