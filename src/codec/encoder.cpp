
#include "encoder.h"

namespace fast_codec
{

void write_byte(Encoder& codec, std::uint8_t b)
{
	codec.data_.push_back(b);
}

}
