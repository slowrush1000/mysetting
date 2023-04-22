/**
 * @file util_point.cpp
 * @author Cheon Younghoe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "util_point.hpp"

yh::util::Point(const yh::util::Point& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
}

yh::util::~Point()
{
}

void
yh::util::set_x(const yh::util::xy_tt x)
{
    m_x = x;
}

yh::util::xy_tt
yh::util::x() const
{
    return m_x;
}

void
yh::util::set_y(const yh::util::xy_tt y)
{
    m_y = y;
}

yh::util::xy_tt
y() const
{
    return m_y;
}