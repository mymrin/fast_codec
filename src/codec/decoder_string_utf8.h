#pragma once

#include "nullable_types.h"

namespace fast_codec
{
	struct Decoder;
	int decode_string_utf8(int, Decoder& e, std::string& str);
	int decode_string_utf8_optional(int, Decoder& e, std::string& str);
	int decode_string_utf8_optional(int, Decoder& e, string_nt& str);
}
