#pragma once

#include "common_defs.h"

namespace fast_codec
{
	struct Decoder;
	int decode_byte_vector(int, Decoder& e, byte* buf, const size_t size, size_t& decoded_size);
	int decode_byte_vector(int, Decoder& e, byte* buf, const size_t size, size_t& decoded_size, bool is_optional);
	int decode_byte_vector_optional(int, Decoder& e, byte* buf, const size_t size, size_t& decoded_size);
}
