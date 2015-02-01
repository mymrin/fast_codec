#ifndef FAST_SIMPLE_CODEC_ENCODER_BYTE_VECTOR_HEADER
#define FAST_SIMPLE_CODEC_ENCODER_BYTE_VECTOR_HEADER

namespace fast_simple_codec
{
	typedef std::uint8_t byte;

	struct Encoder;
	size_t encode_byte_vector(Encoder& e, const byte* pBuf, size_t bufSize);

	// pBuf == NULL is a FAST NULL value
	// pBuf != NULL and bufSize == 0 is FAST empty byte vector
	size_t encode_byte_vector_optional(Encoder& e, const byte* pBuf, std::uint32_t bufSize);
}

#endif
