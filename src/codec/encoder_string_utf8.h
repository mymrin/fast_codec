#ifndef FAST_CODEC_ENCODER_STRING_UTF8_HEADER
#define FAST_CODEC_ENCODER_STRING_UTF8_HEADER

#include "nullable_types.h"

namespace fast_codec
{
	struct Encoder;
	
	size_t encode_string_utf8(int, Encoder& e, const std::string& str);
	size_t encode_string_utf8_optional(int, Encoder& e, const std::string& str);
	size_t encode_string_utf8_optional(int, Encoder& e, const string_nt& str);
}

#endif
