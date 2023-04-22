/**
 * @file mysetting_main.cpp
 * @author Cheon Younghoe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "mysetting_main.hpp"
#include "util/include/util_git.hpp"
#include "util/include/util_util.hpp"
#include <iostream>
#include <string>

int
main(int argc, char** argv)
{
    std::string a = {"aaa bbb"};

    std::cout << a << "\n";
    yh::util::to_upper_str(a);
    std::cout << a << "\n";
    std::cout << yh::util::k_git_branch << "\n";

    return 0;
}