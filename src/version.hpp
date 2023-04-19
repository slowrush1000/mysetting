#ifndef MYNAME_VERSION_H
#define MYNAME_VERSION_H
#include <memory>
#include <string>
namespace myname
{
    class Version;
    using pVersion = std::shared_ptr<Version>;

    class Version
    {
        public:
            Version() = default;
            Version(const std::string program,
                    const int majorVersion,
                    const int minorVersion,
                    const int patchVersion,
                    const std::string buildDate = std::string(__DATE__),
                    const std::string buildTime = std::string(__TIME__));
            Version(const Version& other);
            virtual ~Version();

            const std::string& program() const;
            int major_version() const;
            int minor_version() const;
            int patch_version() const;
            const std::string& build_date() const;
            const std::string& build_time() const;

            std::string str();

        private:
            std::string m_program    = std::string("");
            int m_major_version      = 0;
            int m_minor_version      = 0;
            int m_patch_version      = 0;
            std::string m_build_date = std::string(__DATE__);
            std::string m_build_time = std::string(__TIME__);
    };
} // namespace myname
#endif // MYNAME_VERSION_H
