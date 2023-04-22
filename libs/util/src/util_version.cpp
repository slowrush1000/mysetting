/**
 * @file version.cpp
 * @author Cheon Younghoe (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "util_version.hpp"
#include <fmt/printf.h>

yh::util::Version::Version(const std::string program,
                           const int major_version,
                           const int minor_version,
                           const int patch_version,
                           const std::string build_date,
                           const std::string build_time)
    : m_program(program)
    , m_major_version(major_version)
    , m_minor_version(minor_version)
    , m_patch_version(patch_version)
    , m_build_date(build_date)
    , m_build_time(build_time)
{
}

yh::util::Version::Version(const yh::util::Version& other)
{
    m_program       = other.m_program;
    m_major_version = other.m_major_version;
    m_minor_version = other.m_minor_version;
    m_patch_version = other.m_patch_version;
    m_build_date    = other.m_build_date;
    m_build_time    = other.m_build_time;
}

yh::util::Version::~Version()
{
}

const std::string&
yh::util::Version::program() const
{
    return m_program;
}

int
yh::util::Version::major_version() const
{
    return m_major_version;
}

int
yh::util::Version::minor_version() const
{
    return m_minor_version;
}

int
yh::util::Version::patch_version() const
{
    return m_patch_version;
}

const std::string&
yh::util::Version::build_date() const
{
    return m_build_date;
}

const std::string&
yh::util::Version::build_time() const
{
    return m_build_time;
}

std::string
yh::util::Version::str()
{
    std::string full_versionStr = fmt::sprintf("%s, %d.%d.%d, build at %s %s",
                                               m_program,
                                               m_major_version,
                                               m_minor_version,
                                               m_patch_version,
                                               m_build_time,
                                               m_build_date);
    return full_versionStr;
}
