#ifndef FAST_ENCODER_INT_HEADER
#define FAST_ENCODER_INT_HEADER

#include "nullable_types.h"

namespace fast_codec
{
	struct Encoder;

	int encode_u32(int, Encoder& codec, std::uint32_t d);
	int encode_i32(int, Encoder& codec, std::int32_t d);
	int encode_u64(int, Encoder& codec, std::uint64_t d);
	int encode_i64(int, Encoder& codec, std::int64_t d);
	int encode_u8(int, Encoder& codec, size_t pos, std::uint8_t d);

	int encode_u32_optional(int, Encoder& codec, std::uint32_t d);
	int encode_i32_optional(int, Encoder& codec, std::int32_t d);
	int encode_u64_optional(int, Encoder& codec, std::uint64_t d);
	int encode_i64_optional(int, Encoder& codec, std::int64_t d);
	int encode_u8_optional(int, Encoder& codec, size_t pos, std::uint8_t d);

	int encode_u32_optional(int, Encoder& codec, uint32_nt d);
	int encode_i32_optional(int, Encoder& codec, int32_nt d);
	int encode_u64_optional(int, Encoder& codec, uint64_nt d);
	int encode_i64_optional(int, Encoder& codec, int64_nt d);
}

#endif
