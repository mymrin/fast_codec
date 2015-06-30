#ifndef FAST_CODEC_ENCODER_HEADER
#define FAST_CODEC_ENCODER_HEADER

#include <cstdint>
#include <vector>

#define FAST_MAX_MSG_SIZE 65507

namespace fast_codec
{
	const std::uint8_t null = 0x80;
	typedef std::vector<char> buffer;

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

		buffer& Data()
		{
			return data_;
		}

		const buffer& Data() const
		{
			return data_;
		}

		buffer data_;
	};

	void write_byte(Encoder& c, std::uint8_t b);
	void write_byte(Encoder& c, std::uint8_t b, std::uint32_t count);
	void write(Encoder& c, std::uint32_t msg_seq_num);
}

#endif
