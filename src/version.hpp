/**
 * @file    my_version.hpp
 * @author  Cheon Younghoe
 */

#ifndef MY_VERSION_H
#define MY_VERSION_H

#include "git.hpp"
#include <string>
#include <memory>

namespace my
{
	class Version
	{
		public:
            Version()    = default;
            Version(const std::string program, const int majorVersion, const int minorVersion, const int patchVersion, const std::string buildDate = std::string(__DATE__), const std::string buildTime = std::string(__TIME__));
            Version(const Version& other);
            virtual ~Version();

            const std::string&  getProgram() const;
            int                 getMajorVersion() const;
            int                 getMinorVersion() const;
            int                 getPatchVersion() const;
            const std::string&  getBuildDate() const;
            const std::string&  getBuildTime() const;

            std::string         getStr();

        private:
            std::string     mProgram        = std::string("");
            int             mMajorVersion   = 0;
            int             mMinorversion   = 0;
            int             mPatchVersion   = 0;
            std::string     mBuildDate      = std::string(__DATE__);
            std::string     mBuildTime      = std::string(__TIME__);
	};

    using pVersion  = std::shared_ptr<Version>;
}

#endif // MY_VERSION_H
