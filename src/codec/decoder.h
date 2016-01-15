#pragma once

#include "common_defs.h"

#define FC_UNEXPECTED_END_OF_BUFFER_END 1
#define FC_INTEGER_OVERFLOW 2
#define FC_INTEGER_DO_NOT_HAVE_STOP_BIT 3

namespace fast_codec
{
	struct Decoder
	{
		Decoder() : position_(0)
		{
			data_.reserve(FAST_MAX_MSG_SIZE);
		}

		void Reset()
		{
			position_ = 0;
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

		buffer::size_type Position() const
		{
			return position_;
		}

		size_t Size() const
		{
			return data_.size();
		}

		void Resize(size_t size)
		{
			data_.resize(size);
		}

		buffer::size_type position_;
		buffer data_;
	};

	int read_byte(int, Decoder& c, std::uint8_t& b);
	int read_byte(Decoder& c, std::uint8_t& b);
}
