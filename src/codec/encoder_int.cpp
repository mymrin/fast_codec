#include "encoder.h"
#include "encoder_int.h"

namespace fast_simple_codec
{

int size_of_u32(std::uint32_t d)
{
   if(d < 0x00000080) return 1; // 128
   if(d < 0x00004000) return 2; // 16384
   if(d < 0x00200000) return 3; // 2097152
   if(d < 0x10000000) return 4; // 268435456

   return 5;
}

int size_of_i32(std::int32_t d)
{
   if(d < 0)
   {
      if(d >= 0xffffffc0) return 1; // -64
      if(d >= 0xffffe000) return 2; // -8192
      if(d >= 0xfff00000) return 3; // -1048576
      if(d >= 0xf8000000) return 4; // -134217728
   }
   else
   {
      if(d < 0x00000040) return 1; // 64
      if(d < 0x00002000) return 2; // 8192
      if(d < 0x00100000) return 3; // 1048576
      if(d < 0x08000000) return 4; // 134217728
   }
   return 5;
}

int size_of_u64(std::uint64_t d)
{
	if(d < 0x0000000000000080ULL) return 1; // 128
	if(d < 0x0000000000004000ULL) return 2; // 16384
	if(d < 0x0000000000200000ULL) return 3; // 2097152
	if(d < 0x0000000010000000ULL) return 4; // 268435456
	if(d < 0x0000000800000000ULL) return 5;
	if(d < 0x0000040000000000ULL) return 6;
	if(d < 0x0002000000000000ULL) return 7;
	if(d < 0x0100000000000000ULL) return 8;
	if(d < 0x8000000000000000ULL) return 9;

	return 10;
}

int size_of_i64(std::int64_t d)
{
	if(d < 0)
	{
		if(d >= 0xffffffffffffffc0LL) return 1; // -64
		if(d >= 0xffffffffffffe000LL) return 2; // -8192
		if(d >= 0xfffffffffff00000LL) return 3; // -1048576
		if(d >= 0xfffffffff8000000LL) return 4; // -124317728
		if(d >= 0xfffffffc00000000LL) return 5;
		if(d >= 0xfffffe0000000000LL) return 6;
		if(d >= 0xffff000000000000LL) return 7;
		if(d >= 0xff80000000000000LL) return 8;
		if(d >= 0xc000000000000000LL) return 9;
	}
	else
	{
		if(d < 0x0000000000000040LL) return 1; // 64
		if(d < 0x0000000000002000LL) return 2; // 8192
		if(d < 0x0000000000100000LL) return 3; // 1048576
		if(d < 0x0000000008000000LL) return 4; // 134217728
		if(d < 0x0000000400000000LL) return 5;
		if(d < 0x0000020000000000LL) return 6;
		if(d < 0x0001000000000000LL) return 7;
		if(d < 0x0080000000000000LL) return 8;
		if(d < 0x4000000000000000LL) return 9;
	}
	return 10;
}

int encode_u32(Encoder& codec, std::uint32_t d)
{
	int size = size_of_u32(d);
	switch(size)
	{
		case 5: write_byte(codec,  d >> 28);
		case 4: write_byte(codec, (d >> 21) & 0x7f);
		case 3: write_byte(codec, (d >> 14) & 0x7f);
		case 2: write_byte(codec, (d >>  7) & 0x7f);
		case 1: write_byte(codec, (d & 0x7f) | 0x80);
			{
//				int code = set_pmap (codec, tag);
//
//				if (code < 0)
//					return code;
			}
			return size;
	}
	return 0;
}

int encode_i32(Encoder& codec, std::int32_t d)
{
	int size = size_of_i32(d);
	switch (size)
	{
		// The sign bit of data will be copied on right shifts
		case 5: write_byte(codec, (d >> 28) & 0x7f);
		case 4: write_byte(codec, (d >> 21) & 0x7f);
		case 3: write_byte(codec, (d >> 14) & 0x7f);
		case 2: write_byte(codec, (d >>  7) & 0x7f);
		case 1: write_byte(codec, (d & 0x7f) | 0x80);
			{
//				int code = set_pmap (codec, tag);
//
//				if (code < 0)
//					return code;
			}
			return size;
	}
	return 0;
}

int encode_u64(Encoder& codec, std::uint64_t d)
{
	int size = size_of_u64(d);
	switch(size)
	{
		case 10: write_byte(codec, d >> 63);
		case 9: write_byte(codec, (d >> 56) & 0x7f);
		case 8: write_byte(codec, (d >> 49) & 0x7f);
		case 7: write_byte(codec, (d >> 42) & 0x7f);
		case 6: write_byte(codec, (d >> 35) & 0x7f);
		case 5: write_byte(codec, (d >> 28) & 0x7f);
		case 4: write_byte(codec, (d >> 21) & 0x7f);
		case 3: write_byte(codec, (d >> 14) & 0x7f);
		case 2: write_byte(codec, (d >>  7) & 0x7f);
		case 1: write_byte(codec, (d & 0x7f) | 0x80);
			{
//				int code = set_pmap (codec, tag);
//
//				if (code < 0)
//					return code;
			}
			return size;
	}
	return 0;
}

int encode_i64(Encoder& codec, std::int64_t d)
{
	int size = size_of_i64(d);
	switch(size)
	{
		case 10: write_byte(codec, (d >> 63) & 0x7f);
		case 9: write_byte(codec, (d >> 56) & 0x7f);
		case 8: write_byte(codec, (d >> 49) & 0x7f);
		case 7: write_byte(codec, (d >> 42) & 0x7f);
		case 6: write_byte(codec, (d >> 35) & 0x7f);
		case 5: write_byte(codec, (d >> 28) & 0x7f);
		case 4: write_byte(codec, (d >> 21) & 0x7f);
		case 3: write_byte(codec, (d >> 14) & 0x7f);
		case 2: write_byte(codec, (d >>  7) & 0x7f);
		case 1: write_byte(codec, (d & 0x7f) | 0x80);
			{
//				int code = set_pmap (codec, tag);
//
//				if (code < 0)
//					return code;
			}
			return size;
	}
	return 0;
}

int encode_u32_optional(Encoder& codec, uint32_nt d)
{
	if(d.isNull_)
	{
		write_byte(codec, 0x80);
		return 1;
	}
	else
	{
		++d.value_;
		return encode_u32(codec, d.value_);
	}
}

int encode_i32_optional(Encoder& codec, int32_nt d)
{
	if(d.isNull_)
	{
		write_byte(codec, 0x80);
		return 1;
	}
	else
	{
		if(d.value_ >= 0)
			++d.value_;
		return encode_i32(codec, d.value_);
	}
}

int encode_u64_optional(Encoder& codec, uint64_nt d)
{
	if(d.isNull_)
	{
		write_byte(codec, 0x80);
		return 1;
	}
	else
	{
		++d.value_;
		return encode_u64(codec, d.value_);
	}
}

int encode_i64_optional(Encoder& codec, int64_nt d)
{
	if(d.isNull_)
	{
		write_byte(codec, 0x80);
		return 1;
	}
	else
	{
		if(d.value_ >= 0)
			++d.value_;
		return encode_i64(codec, d.value_);
	}
}

} // namespace
