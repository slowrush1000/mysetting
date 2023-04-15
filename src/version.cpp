#include "version.hpp"
#include <fmt/printf.h>

my::Version::Version(const std::string program,
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

my::Version::Version(const my::Version& other)
{
    m_program       = other.m_program;
    m_major_version = other.m_major_version;
    m_minor_version = other.m_minor_version;
    m_patch_version = other.m_patch_version;
    m_build_date    = other.m_build_date;
    m_build_time    = other.m_build_time;
}

my::Version::~Version()
{
}

const std::string&
my::Version::program() const
{
    return m_program;
}

int
my::Version::major_version() const
{
    return m_major_version;
}

int
my::Version::minor_version() const
{
    return m_minor_version;
}

int
my::Version::patch_version() const
{
    return m_patch_version;
}

const std::string&
my::Version::build_date() const
{
    return m_build_date;
}

const std::string&
my::Version::build_time() const
{
    return m_build_time;
}

std::string
my::Version::str()
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
