/**
 * @file util_point.hpp
 * @author Cheon Younghoe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef YH_UTIL_POINT_H
#define YH_UTIL_POINT_H

#include <limits>

namespace yh::util
{
//#define XY_TT_DOUBLE_DATA
#if defined(XY_TT_DOUBLE_DATA)
    using xy_tt = double;
#else
    using xy_tt = float;
#endif

    constexpr xy_tt k_xy_tt_init = 0.0;
    constexpr xy_tt k_xy_tt_max  = std::numeric_limits<xy_tt>::max();
    constexpr xy_tt k_xy_tt_min  = std::numeric_limits<xy_tt>::lowest();

    class Point
    {
        public:
            Point() = default;
            Point(const Point& other);
            ~Point();

            void set_x(const xy_tt x);
            xy_tt x() const;
            void set_y(const xy_tt y);
            xy_tt y() const;

        private:
            xy_tt m_x;
            xy_tt m_y;
    };
} // namespace yh::util

#endif // YH_UTIL_POINT_H
