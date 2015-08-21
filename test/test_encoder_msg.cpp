#include <fstream>
#include <boost/test/unit_test.hpp>
#include "test_tools.h"
#include "templates_encoders.h"

BOOST_AUTO_TEST_CASE(test_encoder_msg)
{
	fast_codec::Encoder encoder;
	DefaultIncrementalRefreshMessage msg_inc
	{
		1000,
		20150624174141414,
		{ 1, false },
		{
			{
				0,
				"2",
				{ 121212, false },
				{ "Symbol", true },
				{ "SecurityGroup", true },
				{ 4098, false },
				1,
				{ 50, false },
				{ 5, false },
				{ 1, false },
				{ { -3, 5 }, false },
				{ 1, false },
				{ 0, true },
				174141414,
				{ 1, true },
				{ "", true },
				{ 0, false },
				{ { 0, 0 }, true },
				{ 0, true },
				{ "", true },
				{ 123456789, false},
				{ "1", false }
			}
		}
	};
	Encode(encoder, msg_inc);
	std::ofstream of_inc("DefaultIncrementalRefreshMessage.fast", std::ios::out | std::ios::binary);
	of_inc.write(&encoder.data_[0], encoder.data_.size());

	// Performance test
#ifdef NDEBUG
	const int cCycleCount = 1000000;
#else
	const int cCycleCount = 10;
#endif
	size_t encoded_msg_size = encoder.data_.size();
	encoder.Reset();
	encoder.data_.reserve(100 * cCycleCount);
	{
		TimeCounterGuard t("encode_DefaultIncrementalRefreshMessage_MDEntries_1 (" + std::to_string(encoded_msg_size) + " bytes)", cCycleCount);
		for (int i = 0; i < cCycleCount; ++i)
			Encode(encoder, msg_inc);
	}

	// Test DefaultIncrementalRefreshMessage with 100 MDEntries
	DefaultIncrementalRefreshMessage msg_inc100(msg_inc);
	msg_inc100.MDEntriesSeq.clear();
	msg_inc100.MDEntriesSeq.reserve(100);
	for (int i = 0; i < 100; ++i)
	{
		DefaultIncrementalRefreshMessage::MDEntries entry(msg_inc.MDEntriesSeq[0]);
		entry.MDPriceLevel.value_ = i;
		msg_inc100.MDEntriesSeq.push_back(entry);
	}
	encoder.Reset();
	Encode(encoder, msg_inc100);
	std::ofstream of_inc100("DefaultIncrementalRefreshMessage100.fast", std::ios::out | std::ios::binary);
	of_inc100.write(&encoder.data_[0], encoder.data_.size());

	// Performance test of encoding DefaultIncrementalRefreshMessage with 100 MDEntries
#ifdef NDEBUG
	const int cCycleCount2 = 10000;
#else
	const int cCycleCount2 = 10;
#endif
	encoded_msg_size = encoder.data_.size();
	encoder.Reset();
	encoder.data_.reserve(size_t(5000) * cCycleCount2);
	{
		TimeCounterGuard t("encode_DefaultIncrementalRefreshMessage_MDEntries_100 (" + std::to_string(encoded_msg_size) + " bytes)", cCycleCount2);
		for (int i = 0; i < cCycleCount2; ++i)
			Encode(encoder, msg_inc100);
	}
}
