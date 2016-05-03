#pragma once

#include "common_defs.h"

namespace fast_codec
{
	struct Encoder;
	size_t encode_byte_vector(int, Encoder& e, const byte* buf, size_t size);
	size_t encode_byte_vector(int, Encoder& e, const byte* buf, size_t size, bool is_optional);

	// pBuf == NULL is a FAST NULL value
	// pBuf != NULL and bufSize == 0 is FAST empty byte vector
	size_t encode_byte_vector_optional(int, Encoder& e, const byte* buf, size_t size);
}
