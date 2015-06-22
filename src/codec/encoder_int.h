#ifndef FAST_ENCODER_INT_HEADER
#define FAST_ENCODER_INT_HEADER

#include "nullable_types.h"

namespace fast_codec
{
	struct Encoder;

	int encode_u32(Encoder& codec, std::uint32_t d);
	int encode_i32(Encoder& codec, std::int32_t d);
	int encode_u64(Encoder& codec, std::uint64_t d);
	int encode_i64(Encoder& codec, std::int64_t d);

	int encode_u32_optional(Encoder& codec, uint32_nt d);
	int encode_i32_optional(Encoder& codec, int32_nt d);
	int encode_u64_optional(Encoder& codec, uint64_nt d);
	int encode_i64_optional(Encoder& codec, int64_nt d);
}

#endif
