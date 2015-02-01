#ifndef FAST_SIMPLE_CODEC_ENCODER_HEADER
#define FAST_SIMPLE_CODEC_ENCODER_HEADER

#include <cstdint>
#include <vector>

#define FAST_MAX_MSG_SIZE 65507

namespace fast_simple_codec
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

	void write_byte(Encoder& codec, std::uint8_t b);
}

#endif
