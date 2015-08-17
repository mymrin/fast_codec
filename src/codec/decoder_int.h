#ifndef FAST_DECODER_INT_HEADER
#define FAST_DECODER_INT_HEADER

#include "nullable_types.h"

namespace fast_codec
{
	struct Decoder;

	int decode_u32(Decoder& codec, std::uint32_t& d);
	int decode_i32(Decoder& codec, std::int32_t& d);
	int decode_u64(Decoder& codec, std::uint64_t& d);
	int decode_i64(Decoder& codec, std::int64_t& d);

	int decode_u32_optional(Decoder& codec, std::uint32_t& d);
	int decode_i32_optional(Decoder& codec, std::int32_t& d);
	int decode_u64_optional(Decoder& codec, std::uint64_t& d);
	int decode_i64_optional(Decoder& codec, std::int64_t& d);

	int decode_u32_optional(Decoder& codec, uint32_nt& d);
	int decode_i32_optional(Decoder& codec, int32_nt& d);
	int decode_u64_optional(Decoder& codec, uint64_nt& d);
	int decode_i64_optional(Decoder& codec, int64_nt& d);
}

#endif
