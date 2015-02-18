#ifndef FAST_GATE_TEST_TOOLS_HEADER
#define FAST_GATE_TEST_TOOLS_HEADER

#include <iostream>
#include <string>
#include "time_counter.h"

template<typename E, typename T>
void Check(E& codec, T& etalon)
{
	BOOST_REQUIRE_EQUAL(codec.data_.size(), sizeof(etalon));
	BOOST_CHECK(memcmp(&codec.data_[0], etalon, sizeof(etalon)) == 0);
}

#endif
