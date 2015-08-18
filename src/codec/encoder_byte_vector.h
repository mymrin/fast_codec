#ifndef FAST_CODEC_ENCODER_BYTE_VECTOR_HEADER
#define FAST_CODEC_ENCODER_BYTE_VECTOR_HEADER

namespace fast_codec
{
	typedef std::uint8_t byte;

	struct Encoder;
	size_t encode_byte_vector(int, Encoder& e, const byte* buf, size_t size);
	size_t encode_byte_vector(int, Encoder& e, const byte* buf, size_t size, bool is_optional);

	// pBuf == NULL is a FAST NULL value
	// pBuf != NULL and bufSize == 0 is FAST empty byte vector
	size_t encode_byte_vector_optional(int, Encoder& e, const byte* buf, size_t size);
}

#endif
