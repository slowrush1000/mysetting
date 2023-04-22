/**
 * @file util_util.test.cpp
 * @author Cheon Younghoe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "util/include/util_util.hpp"
#include "util/include/util_git.hpp"
#include "gtest/gtest.h"

TEST(UTIL_TEST, is_gzfile)
{
    auto gz_filename = yh::util::make_line(
        std::vector<std::string> {yh::util::k_source_dir, std::string("data/a.txt.gz")}, 0, 2, std::string {"/"});

    EXPECT_TRUE(yh::util::is_gzfile(gz_filename));
}

TEST(UTIL_TEST, get_cpu_info)
{
    const auto k_cpu_info = std::string("Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz, 4 cores");

    EXPECT_STREQ(k_cpu_info.c_str(), yh::util::cpu_info().c_str());
}