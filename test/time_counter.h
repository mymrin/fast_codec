#ifndef FAST_GATE_TIME_COUNTER_HEADER
#define FAST_GATE_TIME_COUNTER_HEADER

#include <cstdint>
#include <chrono>

struct TimeCounter
{
	std::string name_;
	std::chrono::steady_clock::time_point startTime_;
	std::uint64_t sumTime_;
    
	TimeCounter(std::string name) : name_(name)
    {
		Reset();
	}

	void Reset()
	{
		sumTime_ = 0;
	}

	void Start()
	{
		startTime_ = std::chrono::steady_clock::now();
	}

	void Stop()
	{
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startTime_);
		sumTime_ += static_cast<std::uint64_t>(dur.count());			
	}

	void Print(std::uint32_t count) const
	{
		printf("%s: %.3f mcs\n", name_.c_str(), double(sumTime_)/count);
	}
};

struct TimeCounterGuard
{
	TimeCounter t_;
	uint32_t count_;

	TimeCounterGuard(std::string name, uint32_t count)
		: t_(name)
		, count_(count)
	{
		t_.Start();
	}

	~TimeCounterGuard()
	{
		t_.Stop();
		t_.Print(count_);
	}
};

#endif
