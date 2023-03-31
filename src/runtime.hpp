
#ifndef MY_RUNTIME_H
#define MY_RUNTIME_H

#include <memory>
#include <chrono>

namespace my
{
	class Runtime
	{
		public:
            Runtime();
            virtual ~Runtime();

            double          getCPUTimeSecs();
            double          getWallTimeSecs();

            std::size_t     getPeakRSSBytes();
            std::size_t     getCurrentRSSBytes();

            std::string     getRuntimeStr();

        private:
            std::clock_t    mCPUTime;
            std::chrono::time_point<std::chrono::high_resolution_clock> mWallTime;
	};

    using pRuntime  = std::shared_ptr<Runtime>;
}

#endif // MY_RUNTIME_H
