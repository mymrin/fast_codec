#pragma once

#include "nullable_types.h"

namespace fast_codec
{
	struct Decoder;
	int decode_string_ascii(int, Decoder& e, char* c);
	int decode_string_ascii(int, Decoder& e, char* str, const size_t size);
	int decode_string_ascii(int, Decoder& e, std::string& str);
	int decode_string_ascii_optional(int, Decoder& e, char* str, size_t size);
	int decode_string_ascii_optional(int, Decoder& e, string_nt& str);
}
