#ifndef FAST_CODEC_ENCODER_STRING_ASCII_HEADER
#define FAST_CODEC_ENCODER_STRING_ASCII_HEADER

#include "nullable_types.h"

namespace fast_codec
{
	struct Encoder;
	size_t encode_string_ascii(int, Encoder& e, const char c);
	size_t encode_string_ascii(int, Encoder& e, const char* str, size_t size);
	size_t encode_string_ascii(int, Encoder& e, const std::string& str);

	// pStr == NULL is a FAST NULL value
	// pStr != NULL and length == 0 is FAST ASCII empty string
	size_t encode_string_ascii_optional(int, Encoder& e, const char* str, size_t size);
	size_t encode_string_ascii_optional(int, Encoder& e, const string_nt& str);
}

#endif
