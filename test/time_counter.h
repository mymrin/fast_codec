#ifndef FAST_GATE_TIME_COUNTER_HEADER
#define FAST_GATE_TIME_COUNTER_HEADER

#include <cstdint>
#include <chrono>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct TimeCounter
{
	std::string name_;
	std::chrono::steady_clock::time_point start_time_;
	std::uint64_t sum_time_;
    
	TimeCounter(std::string name) : name_(name)
    {
		Reset();
	}

	void Reset()
	{
		sum_time_ = 0;
	}

	void Start()
	{
		start_time_ = std::chrono::steady_clock::now();
	}

	void Stop()
	{
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time_);
		sum_time_ += static_cast<std::uint64_t>(dur.count());			
	}

	void Print(std::uint32_t count) const
	{
		printf("%s: " ANSI_COLOR_GREEN "%.3f" ANSI_COLOR_RESET " mcs, count: %d, total: %lld mcs\n", name_.c_str(), double(sum_time_) / count, count, sum_time_);
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
