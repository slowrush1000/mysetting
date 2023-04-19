#include "version.hpp"
#include <fmt/printf.h>

myname::Version::Version(const std::string program,
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

myname::Version::Version(const myname::Version& other)
{
    m_program       = other.m_program;
    m_major_version = other.m_major_version;
    m_minor_version = other.m_minor_version;
    m_patch_version = other.m_patch_version;
    m_build_date    = other.m_build_date;
    m_build_time    = other.m_build_time;
}

myname::Version::~Version()
{
}

const std::string&
myname::Version::program() const
{
    return m_program;
}

int
myname::Version::major_version() const
{
    return m_major_version;
}

int
myname::Version::minor_version() const
{
    return m_minor_version;
}

int
myname::Version::patch_version() const
{
    return m_patch_version;
}

const std::string&
myname::Version::build_date() const
{
    return m_build_date;
}

const std::string&
myname::Version::build_time() const
{
    return m_build_time;
}

std::string
myname::Version::str()
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
