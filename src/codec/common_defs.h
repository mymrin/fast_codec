#pragma once

#include <stddef.h>
#include <cstdint>
#include <vector>

#define FAST_MAX_MSG_SIZE 65507

namespace fast_codec
{
	const std::uint8_t null = 0x80;
	typedef std::uint8_t byte;
	typedef std::vector<std::uint8_t> buffer;
}
