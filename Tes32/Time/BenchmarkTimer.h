#pragma once

#include <chrono>

namespace tstd {
	namespace time {
		namespace benchmark_timer {
			class Timer {
			public:
				Timer(double* output);
				~Timer();
				void Stop();
			private:
				std::chrono::time_point<std::chrono::high_resolution_clock> StartPoint;
				double* out;
			};
		}
	}
}