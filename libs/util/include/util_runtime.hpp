/**
 * @file util_runtime.hpp
 * @author Cheon Younghoe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef YH_UTIL_RUNTIME_H
#define YH_UTIL_RUNTIME_H

#include <chrono>
#include <memory>

namespace yh::util
{
    class Runtime;
    using pRuntime = std::shared_ptr<Runtime>;

    class Runtime
    {
        public:
            Runtime();
            virtual ~Runtime();

            double cpu_time_secs();
            double wall_time_secs();

            std::size_t peak_rss_bytes();
            std::size_t current_rss_bytes();

            std::string str();

        private:
            std::clock_t m_cpu_time;
            std::chrono::time_point<std::chrono::high_resolution_clock> m_wall_time;
    };

} // namespace yh::util

#endif // YH_UTIL_RUNTIME_H
