#pragma once

#include "nullable_types.h"

namespace fast_codec
{
	struct Decoder;

	int decode_u32(int, Decoder& codec, std::uint32_t& d);
	int decode_i32(int, Decoder& codec, std::int32_t& d);
	int decode_u64(int, Decoder& codec, std::uint64_t& d);
	int decode_i64(int, Decoder& codec, std::int64_t& d);

	int decode_u32_optional(int, Decoder& codec, std::uint32_t& d);
	int decode_i32_optional(int, Decoder& codec, std::int32_t& d);
	int decode_u64_optional(int, Decoder& codec, std::uint64_t& d);
	int decode_i64_optional(int, Decoder& codec, std::int64_t& d);

	int decode_u32_optional(int, Decoder& codec, uint32_nt& d);
	int decode_i32_optional(int, Decoder& codec, int32_nt& d);
	int decode_u64_optional(int, Decoder& codec, uint64_nt& d);
	int decode_i64_optional(int, Decoder& codec, int64_nt& d);
}
