/**
 * @file util.cpp
 * @author Cheon Younghoe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "util_util.hpp"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <fmt/printf.h>
#include <fstream>
#include <iostream>
#include <sys/utsname.h>
#include <unistd.h>

std::string
yh::util::current_time()
{
    auto today     = std::chrono::system_clock::now();
    auto tt        = std::chrono::system_clock::to_time_t(today);
    auto ctime_str = std::string(std::ctime(&tt));

    yh::util::change_str(ctime_str, std::string("\n"), std::string(""));

    return ctime_str;
}

std::string
yh::util::current_dir()
{
    auto currentPath = yh::util::fs_tt::current_path();

    return currentPath.native();
}

std::string
yh::util::user()
{
    char user[yh::util::k_buffer_size_1k];

    if (0 == getlogin_r(user, yh::util::k_buffer_size_1k))
        return std::string(user);
    else
        return std::string("");
}

std::string
yh::util::host_name()
{
    char host_name[yh::util::k_buffer_size_1k];

    if (0 == gethostname(host_name, yh::util::k_buffer_size_1k))
        return std::string(host_name);
    else
        return std::string("");
}

int
yh::util::process_id()
{
    return getpid();
}

std::string
yh::util::os_version()
{
    struct utsname buf;

    if (0 != uname(&buf))
    {
        return std::string("");
    }
    else
    {
        return fmt::sprintf("%s %s %s %s %s", buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
    }
}

std::string
yh::util::cpu_info()
{
    const std::string k_cpu_info_filename = std::string("/proc/cpuinfo");

    std::ifstream file(k_cpu_info_filename);

    if (false == file.is_open())
    {
        return std::string("");
    }

    std::string line;
    std::string delims     = std::string(" \t\r\n");
    // std::vector<std::string> tokens;

    std::string model_name = std::string("");
    std::string cpu_cores  = std::string("");

    while (std::getline(file, line))
    {
        auto tokens = yh::util::tokenize(line, delims);
        // yh::util::tokenize(line, tokens, delims);

        if (true == tokens.empty())
        {
            continue;
        }

        if (std::string("model") == tokens[0])
        {
            if (std::string("name") == tokens[1])
            {
                model_name = tokens[3];

                for (auto i = 4; i < tokens.size(); ++i)
                {
                    model_name += std::string(" ");
                    model_name += tokens[i];
                }
            }
        }
        else if (std::string("cpu") == tokens[0])
        {
            if (std::string("cores") == tokens[1])
            {
                cpu_cores = tokens[3];
            }
        }
    }

    file.close();

    auto str = fmt::sprintf("%s, %s cores", model_name, cpu_cores);

    return str;
}

void
yh::util::change_str(std::string& str, const std::string& from, const std::string& to)
{
    if (true == from.empty())
    {
        return;
    }

    std::size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::vector<std::string_view>
yh::util::tokenize(std::string_view str, std::string_view delims)
{
    std::vector<std::string_view> tokens;

    std::string::size_type last_pos = str.find_first_not_of(delims, 0);
    std::string::size_type pos      = str.find_first_of(delims, last_pos);

    while (std::string::npos != pos || std::string::npos != last_pos)
    {
        tokens.emplace_back(str.substr(last_pos, pos - last_pos));

        last_pos = str.find_first_not_of(delims, pos);
        pos      = str.find_first_of(delims, last_pos);
    }

    return tokens;
}

/*
void
yh::util::tokenize(std::string_view str, std::vector<std::string>& tokens, std::string_view delims)
{
    tokens.clear();

    std::string::size_type last_pos = str.find_first_not_of(delims, 0);
    std::string::size_type pos      = str.find_first_of(delims, last_pos);

    while (std::string::npos != pos || std::string::npos != last_pos)
    {
        tokens.emplace_back(str.substr(last_pos, pos - last_pos));

        last_pos = str.find_first_not_of(delims, pos);
        pos      = str.find_first_of(delims, last_pos);
    }
}
*/

void
yh::util::set_casesensitive(std::string& str, const bool casesensitive)
{
    if (false == casesensitive)
        yh::util::to_lower_str(str);
}

void
yh::util::to_upper_str(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
}

void
yh::util::to_lower_str(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
}

bool
yh::util::is_equal(const std::string& str1, const std::string& str2, const bool casesensitive)
{
    if (true == casesensitive)
        return yh::util::is_equal_casesensitive(str1, str2);
    else
        return yh::util::is_equal_incasesensitive(str1, str2);
}

bool
yh::util::is_equal_casesensitive(const std::string& str1, const std::string& str2)
{
    return str1 == str2;
}

bool
yh::util::is_equal_incasesensitive(const std::string& str1, const std::string& str2)
{
    return std::equal(str1.begin(),
                      str1.end(),
                      str2.begin(),
                      str2.end(),
                      [](unsigned char a, unsigned char b) { return std::tolower(a) == std::tolower(b); });
}

bool
yh::util::is_equal(const unsigned char str1, const unsigned char str2, const bool casesensitive)
{
    if (true == casesensitive)
        return yh::util::is_equal(str1, str2);
    else
        return yh::util::is_equal_incasesensitive(str1, str2);
}

bool
yh::util::is_equal_casesensitive(const unsigned char str1, const unsigned char str2)
{
    return str1 == str2;
}

bool
yh::util::is_equal_incasesensitive(const unsigned char str1, const unsigned char str2)
{
    return tolower(str1) == tolower(str2);
}

bool
yh::util::is_equal(const float f1, const float f2, const float max_rel_diff)
{
    float diff    = fabsf(f1 - f2);
    float ff1     = fabsf(f1);
    float ff2     = fabsf(f2);

    float largest = (ff2 > ff1) ? ff2 : ff1;

    if (diff <= (largest * max_rel_diff))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool
yh::util::is_equal(const double d1, const double d2, const double max_rel_diff)
{
    double diff    = fabs(d1 - d2);
    double fd1     = fabs(d1);
    double fd2     = fabs(d2);

    double largest = (fd2 > fd1) ? fd2 : fd1;

    if (diff <= (largest * max_rel_diff))
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string
yh::util::make_line(const std::vector<std::string>& tokens,
                    const std::size_t from_pos,
                    const std::size_t to_pos,
                    const std::string& delims)
{
    auto line = std::string("");
    for (auto pos = from_pos; pos < to_pos; ++pos)
    {
        line += delims;
        line += tokens[pos];
    }

    return line;
}

// ref : https://stackoverflow.com/questions/6059302/how-to-check-if-a-file-is-gzip-compressed
bool
yh::util::is_gzfile(const std::string& filename)
{
    std::ifstream file(filename, std::ifstream::binary);
    if (false == file.is_open())
    {
        return false;
    }

    const unsigned char k_gzipfile_heads[2] = {0x1f, 0x8b};
    unsigned char file_heads[2]             = {0x0, 0x0};

    file.read((char*)file_heads, 2);
    file.close();

    if ((k_gzipfile_heads[0] == file_heads[0]) && (k_gzipfile_heads[1] == file_heads[1]))
    {
        return true;
    }

    return false;
}

// TODO
double
yh::util::atof2(const std::string& str)
{
    return std::atof(str.c_str());
}
