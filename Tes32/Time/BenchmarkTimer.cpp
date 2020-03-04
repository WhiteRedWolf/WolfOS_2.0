#include "BenchmarkTimer.h"

tstd::time::benchmark_timer::Timer::Timer(double* output)
{
	this->StartPoint = std::chrono::high_resolution_clock::now();
	this->out = output;
}

tstd::time::benchmark_timer::Timer::~Timer()
{
	this->Stop();
}

void tstd::time::benchmark_timer::Timer::Stop()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> EndPoint = std::chrono::high_resolution_clock::now();
	long long start = std::chrono::time_point_cast<std::chrono::microseconds>(this->StartPoint).time_since_epoch().count();
	long long end = std::chrono::time_point_cast<std::chrono::microseconds>(EndPoint).time_since_epoch().count();

	long long duration = end - start;

	double ms = duration * 0.001;

	*out = ms;
}
