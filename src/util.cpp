
#include "util.hpp"
#include <chrono>
#include <algorithm>
#include <fstream>
#include <fmt/printf.h>
#include <cctype>
#include <unistd.h>
#include <sys/utsname.h>
#include <cstdlib>

std::string     
my::getCurrentTime()
{
    auto    today       = std::chrono::system_clock::now();
    auto    tt          = std::chrono::system_clock::to_time_t(today);
    auto    ctimeStr    = std::string(std::ctime(&tt));

    my::changeStr(ctimeStr, std::string("\n"), std::string(""));

    return  ctimeStr;
}

std::string     
my::getCurrentDir()
{
    auto    currentPath     = my::fs_tt::current_path();

    return  currentPath.native();
}

std::string     
my::getUser()
{
    char    user[my::kBufferSize1k];

    if (0 == getlogin_r(user, my::kBufferSize1k))
        return  std::string(user);
    else
        return  std::string("");
}

std::string     
my::getHostName()
{
    char    hostName[my::kBufferSize1k];

    if (0 == gethostname(hostName, my::kBufferSize1k))
        return  std::string(hostName);
    else
        return  std::string("");
}

int             
my::getProcessId()
{
    return getpid();
}

std::string
my::getOSVersion()
{
    struct utsname buf;

    if (0 != uname(&buf))
    {
        return std::string("");
    }
    else
    {
        return fmt::sprintf("%s %s %s %s %s",
                            buf.sysname,
                            buf.nodename,
                            buf.release,
                            buf.version,
                            buf.machine
                            );
    }
}

std::string
my::getCPUInfo()
{
    const std::string kCPUINFOFileName   = std::string("/proc/cpuinfo");

    std::ifstream   file(kCPUINFOFileName);

    if (false == file.is_open())
    {
        return std::string("");
    }

    std::string                 line;
    std::string                 delims = std::string(" \t\r\n");
    std::vector<std::string>    tokens;

    std::string                 modelName   = std::string("");
    std::string                 cpuCores    = std::string("");

    while (std::getline(file, line))
    {
        my::tokenize(line, tokens, delims);

        if (true == tokens.empty())
        {
            continue;
        }

        if (std::string("model") == tokens[0])
        {
            if (std::string("name") == tokens[1])
            {
                modelName   = tokens[3];

                for (auto i = 4; i < tokens.size(); ++i)
                {
                    modelName   += std::string(" ");
                    modelName   += tokens[i];
                }
            }
        }
        else if (std::string("cpu") == tokens[0])
        {
            if (std::string("cores") == tokens[1])
            {
                cpuCores        = tokens[3];
            }
        }
    }

    file.close();

    auto str     = fmt::sprintf("%s, %s cores", modelName, cpuCores);

    return str;
}

void            
my::changeStr(std::string& str, const std::string& from, const std::string& to)
{
    if(true == from.empty())
    {
        return;
    }

    std::size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos   += to.length();
    }
}

void            
my::tokenize(std::string_view str, std::vector<std::string>& tokens, std::string_view delims)
{
    tokens.clear();

    std::string::size_type  lastPos     = str.find_first_not_of(delims, 0);
    std::string::size_type  pos         = str.find_first_of(delims, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        tokens.emplace_back(str.substr(lastPos, pos - lastPos));

        lastPos     = str.find_first_not_of(delims, pos);
        pos         = str.find_first_of(delims, lastPos);
    }
}

void            
my::setCasesensitive(std::string& str, const bool casesensitive)
{
    if (false == casesensitive)
        my::toLowerStr(str);
}

void            
my::toUpperStr(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c)
            {
                return std::toupper(c);
            }
            );
}

void            
my::toLowerStr(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(),
            [](unsigned char c)
            {
                return std::tolower(c);
            }
            );
}

bool
my::isEqual(const std::string& str1, const std::string& str2, const bool casesensitive)
{
    if (true == casesensitive)
        return my::isEqualCasesensitive(str1, str2);
    else
        return my::isEqualIncasesensitive(str1, str2);
}

bool
my::isEqualCasesensitive(const std::string& str1, const std::string& str2)
{
    return str1 == str2;
}

bool
my::isEqualIncasesensitive(const std::string& str1, const std::string& str2)
{
    return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
            [](unsigned char a, unsigned char b) 
            {
                return std::tolower(a) == std::tolower(b);
            }
            );
}

bool            
my::isEqual(const unsigned char str1, const unsigned char str2, const bool casesensitive)
{
    if (true == casesensitive)
        return my::isEqual(str1, str2);
    else
        return my::isEqualIncasesensitive(str1, str2);
}

bool            
my::isEqualCasesensitive(const unsigned char str1, const unsigned char str2)
{
    return str1 == str2;
}

bool            
my::isEqualIncasesensitive(const unsigned char str1, const unsigned char str2)
{
    return tolower(str1) == tolower(str2);
}

bool            
my::isEqual(const float f1, const float f2, const float max_rel_diff)
{
    float   diff    = fabsf(f1 - f2);
    float   ff1     = fabsf(f1);
    float   ff2     = fabsf(f2);

    float   largest = (ff2 > ff1) ? ff2 : ff1;

    if (diff <= (largest * max_rel_diff))
    {
        return  true;
    }
    else
    {
        return  false;
    }
}

bool            
my::isEqual(const double d1, const double d2, const double max_rel_diff)
{
    double  diff    = fabs(d1 - d2);
    double  fd1     = fabs(d1);
    double  fd2     = fabs(d2);

    double  largest = (fd2 > fd1) ? fd2 : fd1;

    if (diff <= (largest * max_rel_diff))
    {
        return  true;
    }
    else
    {
        return  false;
    }
}

std::string     
my::makeLine(const std::vector<std::string>& tokens, const std::size_t fromPos, const std::size_t toPos, const std::string& delims)
{
    auto    line    = std::string("");
    for (auto pos = fromPos; pos < toPos; ++pos)
    {
        line        += delims;
        line        += tokens[pos];
    }

    return line;
}

// TODO
double          
my::atof2(const std::string& str)
{
    return std::atof(str.c_str());
}
