#ifndef FAST_CODEC_ENCODER_HEADER
#define FAST_CODEC_ENCODER_HEADER

#include <cstdint>
#include <vector>

#define FAST_MAX_MSG_SIZE 65507

namespace fast_codec
{
	struct Encoder
	{
		Encoder()
		{
			data_.reserve(FAST_MAX_MSG_SIZE);
		}

		void Reset()
		{
			data_.clear();
		}

		std::vector<std::uint8_t> data_;
	};

	void write_byte(Encoder& c, std::uint8_t b);
	void write(Encoder& c, std::uint32_t msg_seq_num);
}

#endif
