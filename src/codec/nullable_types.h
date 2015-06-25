#ifndef FAST_CODEC_NULLABLE_TYPES_HEADER
#define FAST_CODEC_NULLABLE_TYPES_HEADER

#include "decimal.h"

namespace fast_codec
{
	template<typename T>
	struct NullableType
	{
		T value_;
		bool is_null_;

		NullableType() : is_null_(true) {}
		explicit NullableType(const T& val) : value_(val), is_null_(false) {}
		NullableType(const T& val, bool b) : value_(val), is_null_(b) {}
	};

	typedef NullableType<std::string> string_nt;
	typedef NullableType<std::uint32_t> uint32_nt;
	typedef NullableType<std::int32_t> int32_nt;
	typedef NullableType<std::uint64_t> uint64_nt;
	typedef NullableType<std::int64_t> int64_nt;
	typedef NullableType<Decimal> DecimalNullable;
}

#endif
