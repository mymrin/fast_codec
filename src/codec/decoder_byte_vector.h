#pragma once

#include "common_defs.h"

namespace fast_codec
{
	struct Decoder;
//	size_t decode_byte_vector(int, Decoder& e, const byte* buf, size_t size);
//	size_t decode_byte_vector(int, Decoder& e, const byte* buf, size_t size, bool is_optional);

	// pBuf == NULL is a FAST NULL value
	// pBuf != NULL and bufSize == 0 is FAST empty byte vector
//	size_t decode_byte_vector_optional(int, Decoder& e, const byte* buf, size_t size);
}
