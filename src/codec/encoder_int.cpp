#include "encoder.h"
#include "encoder_int.h"

namespace fast_codec
{
	int size_of_u32(std::uint32_t d)
	{
		if(d < static_cast<std::uint32_t>(0x00000080)) return 1; // 128
		if(d < static_cast<std::uint32_t>(0x00004000)) return 2; // 16384
		if(d < static_cast<std::uint32_t>(0x00200000)) return 3; // 2097152
		if(d < static_cast<std::uint32_t>(0x10000000)) return 4; // 268435456
		return 5;
	}

	int size_of_i32(std::int32_t d)
	{
		if(d < 0) {
			if(d >= static_cast<std::int32_t>(0xffffffc0)) return 1; // -64
			if(d >= static_cast<std::int32_t>(0xffffe000)) return 2; // -8192
			if(d >= static_cast<std::int32_t>(0xfff00000)) return 3; // -1048576
			if(d >= static_cast<std::int32_t>(0xf8000000)) return 4; // -134217728
		}
		else {
			if(d < static_cast<std::int32_t>(0x00000040)) return 1; // 64
			if(d < static_cast<std::int32_t>(0x00002000)) return 2; // 8192
			if(d < static_cast<std::int32_t>(0x00100000)) return 3; // 1048576
			if(d < static_cast<std::int32_t>(0x08000000)) return 4; // 134217728
		}
		return 5;
	}

	int size_of_u64(std::uint64_t d)
	{
		if(d < static_cast<std::uint64_t>(0x0000000000000080)) return 1; // 128
		if(d < static_cast<std::uint64_t>(0x0000000000004000)) return 2; // 16384
		if(d < static_cast<std::uint64_t>(0x0000000000200000)) return 3; // 2097152
		if(d < static_cast<std::uint64_t>(0x0000000010000000)) return 4; // 268435456
		if(d < static_cast<std::uint64_t>(0x0000000800000000)) return 5;
		if(d < static_cast<std::uint64_t>(0x0000040000000000)) return 6;
		if(d < static_cast<std::uint64_t>(0x0002000000000000)) return 7;
		if(d < static_cast<std::uint64_t>(0x0100000000000000)) return 8;
		if(d < static_cast<std::uint64_t>(0x8000000000000000)) return 9;
		return 10;
	}

	int size_of_i64(std::int64_t d)
	{
		if(d < 0) {
			std::int64_t absd = -d;
			if((d << 1) == 0) return 10;
			if(absd <= static_cast<std::int64_t>(0x0000000000000040)) return 1; // 64
			if(absd <= static_cast<std::int64_t>(0x0000000000002000)) return 2; // 8192
			if(absd <= static_cast<std::int64_t>(0x0000000000100000)) return 3; // 1048576
			if(absd <= static_cast<std::int64_t>(0x0000000008000000)) return 4; // 124317728
			if(absd <= static_cast<std::int64_t>(0x0000000400000000)) return 5;
			if(absd <= static_cast<std::int64_t>(0x0000020000000000)) return 6;
			if(absd <= static_cast<std::int64_t>(0x0001000000000000)) return 7;
			if(absd <= static_cast<std::int64_t>(0x0080000000000000)) return 8;
			if(absd <= static_cast<std::int64_t>(0x4000000000000000)) return 9;
		}
		else {
			if(d < static_cast<std::int64_t>(0x0000000000000040)) return 1; // 64
			if(d < static_cast<std::int64_t>(0x0000000000002000)) return 2; // 8192
			if(d < static_cast<std::int64_t>(0x0000000000100000)) return 3; // 1048576
			if(d < static_cast<std::int64_t>(0x0000000008000000)) return 4; // 134217728
			if(d < static_cast<std::int64_t>(0x0000000400000000)) return 5;
			if(d < static_cast<std::int64_t>(0x0000020000000000)) return 6;
			if(d < static_cast<std::int64_t>(0x0001000000000000)) return 7;
			if(d < static_cast<std::int64_t>(0x0080000000000000)) return 8;
			if(d < static_cast<std::int64_t>(0x4000000000000000)) return 9;
		}
		return 10;
	}

	int encode_u32(int, Encoder& codec, std::uint32_t d)
	{
		int size = size_of_u32(d);
		switch(size) {
			case 5: write_byte(codec,  d >> 28);
			case 4: write_byte(codec, (d >> 21) & 0x7f);
			case 3: write_byte(codec, (d >> 14) & 0x7f);
			case 2: write_byte(codec, (d >>  7) & 0x7f);
			case 1: write_byte(codec, (d & 0x7f) | 0x80);
				{}
				return size;
		}
		return 0;
	}

	int encode_i32(int, Encoder& codec, std::int32_t d)
	{
		int size = size_of_i32(d);
		switch (size) {
			// The sign bit of data will be copied on right shifts
			case 5: write_byte(codec, (d >> 28) & 0x7f);
			case 4: write_byte(codec, (d >> 21) & 0x7f);
			case 3: write_byte(codec, (d >> 14) & 0x7f);
			case 2: write_byte(codec, (d >>  7) & 0x7f);
			case 1: write_byte(codec, (d & 0x7f) | 0x80);
				{}
				return size;
		}
		return 0;
	}

	int encode_u64(int, Encoder& codec, std::uint64_t d)
	{
		int size = size_of_u64(d);
		switch(size) {
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
				{}
				return size;
		}
		return 0;
	}

	int encode_i64(int, Encoder& codec, std::int64_t d)
	{
		int size = size_of_i64(d);
		switch(size) {
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
				{}
				return size;
		}
		return 0;
	}

	int encode_u8(int, Encoder& codec, size_t pos, std::uint8_t d)
	{
		buffer& data = codec.Data();
		data[pos] = ((d & 0x7f) | 0x80);
		return 1;
	}

	int encode_u8_optional(int, Encoder& codec, size_t pos, std::uint8_t d)
	{
		++d;
		encode_u8(0, codec, pos, d);
		return 1;
	}

	int encode_u32_optional(int, Encoder& codec, std::uint32_t d)
	{
		++d;
		return encode_u32(0, codec, d);
	}

	int encode_i32_optional(int, Encoder& codec, std::int32_t d)
	{
		if (d >= 0)
			++d;
		return encode_i32(0, codec, d);
	}

	int encode_u64_optional(int, Encoder& codec, std::uint64_t d)
	{
		++d;
		return encode_u64(0, codec, d);
	}

	int encode_i64_optional(int, Encoder& codec, std::int64_t d)
	{
		if (d >= 0)
			++d;
		return encode_i64(0, codec, d);
	}

	int encode_u32_optional(int, Encoder& codec, uint32_nt d)
	{
		if(d.is_null_) {
			write_byte(codec, 0x80);
			return 1;
		}
		else {
			return encode_u32_optional(0, codec, d.value_);
		}
	}

	int encode_i32_optional(int, Encoder& codec, int32_nt d)
	{
		if(d.is_null_) {
			write_byte(codec, 0x80);
			return 1;
		}
		else {
			return encode_i32_optional(0, codec, d.value_);
		}
	}

	int encode_u64_optional(int, Encoder& codec, uint64_nt d)
	{
		if(d.is_null_) {
			write_byte(codec, 0x80);
			return 1;
		}
		else {
			return encode_u64_optional(0, codec, d.value_);
		}
	}

	int encode_i64_optional(int, Encoder& codec, int64_nt d)
	{
		if(d.is_null_) {
			write_byte(codec, 0x80);
			return 1;
		}
		else {
			return encode_i64_optional(0, codec, d.value_);
		}
	}
} // namespace
