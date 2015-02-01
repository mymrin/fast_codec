#ifndef FAST_SIMPLE_CODEC_NULLABLE_TYPES_HEADER
#define FAST_SIMPLE_CODEC_NULLABLE_TYPES_HEADER

#include "decimal.h"

namespace fast_simple_codec
{
	template<typename T>
	struct NullableType
	{
		T value_;
		bool isNull_;

		NullableType() : isNull_(true) {}
		explicit NullableType(const T& val) : value_(val), isNull_(false) {}
	};

	typedef NullableType<std::uint32_t> uint32_nt;
	typedef NullableType<std::int32_t> int32_nt;
	typedef NullableType<std::uint64_t> uint64_nt;
	typedef NullableType<std::int64_t> int64_nt;
	typedef NullableType<Decimal> DecimalNullable;
}

#endif
