/**
 * @file util_util.hpp
 * @author Cheon Younghoe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef YH_UTIL_UTIL_H
#define YH_UTIL_UTIL_H

#include <cfloat>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace yh::util
{
    namespace fs_tt                    = std::filesystem;
    const std::size_t k_buffer_size_1k = 1024;

    std::string current_time();
    std::string current_dir();
    std::string user();
    std::string host_name();
    int process_id();
    std::string os_version();
    std::string cpu_info();
    void change_str(std::string& str, const std::string& from, const std::string& to);
    std::vector<std::string_view> tokenize(std::string_view str, std::string_view delims = " ");
    // void tokenize(std::string_view str, std::vector<std::string>& tokens, std::string_view delims = " ");
    void set_casesensitive(std::string& str, const bool casesensitive);
    void to_upper_str(std::string& str);
    void to_lower_str(std::string& str);
    bool is_equal(const std::string& str1, const std::string& str2, const bool casesensitive = false);
    bool is_equal_casesensitive(const std::string& str1, const std::string& str2);
    bool is_equal_incasesensitive(const std::string& str1, const std::string& str2);
    bool is_equal(const unsigned char str1, const unsigned char str2, const bool casesensitive = false);
    bool is_equal_casesensitive(const unsigned char str1, const unsigned char str2);
    bool is_equal_incasesensitive(const unsigned char str1, const unsigned char str2);
    bool is_equal(const float f1, const float f2, const float max_rel_diff = FLT_EPSILON);
    bool is_equal(const double d1, const double d2, const double max_rel_diff = DBL_EPSILON);
    std::string make_line(const std::vector<std::string>& tokens,
                          const std::size_t from_pos,
                          const std::size_t to_pos,
                          const std::string& delims = std::string(" "));
    bool is_gzfile(const std::string& filename);
    // TODO
    double atof2(const std::string& str);
} // namespace yh::util

#endif // YH_UTIL_UTIL_H
