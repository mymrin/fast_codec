#ifndef FAST_SIMPLE_CODEC_ENCODER_ASCII_HEADER
#define FAST_SIMPLE_CODEC_ENCODER_ASCII_HEADER

namespace fast_simple_codec
{
	struct Encoder;
	int encode_ascii(Encoder& e, const char* pStr, std::uint32_t length);

	// pStr == NULL is a FAST NULL value
	// pStr != NULL and length == 0 is FAST ASCII empty string
	int encode_ascii_optional(Encoder& e, const char* pStr, std::uint32_t length);
}

#endif
