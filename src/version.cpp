/**
 * @file    my_version.cpp
 * @author  Cheon Younghoe
 */

#include "version.hpp"
#include <fmt/printf.h>

my::Version::Version(const std::string program, const int majorVersion, const int minorVersion, const int patchVersion, const std::string buildDate, const std::string buildTime) : mProgram(program), mMajorVersion(majorVersion), mMinorversion(minorVersion), mPatchVersion(patchVersion), mBuildDate(buildDate), mBuildTime(buildTime)
{
}

my::Version::Version(const my::Version& other)
{
    mProgram        = other.mProgram;
    mMajorVersion   = other.mMajorVersion;
    mMinorversion   = other.mMinorversion;
    mPatchVersion   = other.mPatchVersion;
    mBuildDate      = other.mBuildDate;
    mBuildTime      = other.mBuildTime;
}

my::Version::~Version()
{
}

const std::string&  my::Version::getProgram() const
{
    return mProgram;
}

int                 
my::Version::getMajorVersion() const
{
    return mMajorVersion;
}

int                 
my::Version::getMinorVersion() const
{
    return mMinorversion;
}

int                 
my::Version::getPatchVersion() const
{
    return mPatchVersion;
}

const std::string&  
my::Version::getBuildDate() const
{
    return mBuildDate;
}

const std::string&  
my::Version::getBuildTime() const
{
    return mBuildTime;
}

std::string         
my::Version::getStr()
{
    std::string     fullVersionStr  = fmt::sprintf("%s, %d.%d.%d, build at %s %s, id: %s", 
            mProgram,
            mMajorVersion,
            mMinorversion,
            mPatchVersion,
            mBuildTime,
            mBuildDate,
            my::Git::getGitCommitHash()
            );

    return fullVersionStr;
}
