
#include "log.hpp"
#include <iostream>

my::Log::Log()
{
    try
    {
        mConsoleSink    = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        mConsoleSink->set_pattern(mLogPattern);
        mConsoleSink->set_level(mLogLevel);

        mFileSink       = std::make_shared<spdlog::sinks::basic_file_sink_mt>(mLogFileName, true);
        mFileSink->set_pattern(mLogPattern);
        mFileSink->set_level(mLogLevel);

        spdlog::sinks_init_list sinks   = { mConsoleSink, mFileSink };

        mLogger         = std::make_shared<spdlog::logger>(mLoggerName, sinks);
        mLogger->set_pattern(mLogPattern);
        mLogger->set_level(mLogLevel);

        spdlog::set_default_logger(mLogger);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "# error: log init. failed. : " << ex.what() << "\n";
        exit(0);
    }
}

my::Log::Log(const std::string& loggerName, const std::string& logFileName) : mLoggerName(loggerName), mLogFileName(logFileName)
{
    try
    {
        mConsoleSink    = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        mConsoleSink->set_pattern(mLogPattern);
        mConsoleSink->set_level(mLogLevel);

        mFileSink       = std::make_shared<spdlog::sinks::basic_file_sink_mt>(mLogFileName, true);
        mFileSink->set_pattern(mLogPattern);
        mFileSink->set_level(mLogLevel);

        spdlog::sinks_init_list sink_lists  = { mConsoleSink, mFileSink };

        mLogger         = std::make_shared<spdlog::logger>(mLoggerName, sink_lists);
        mLogger->set_pattern(mLogPattern);
        mLogger->set_level(mLogLevel);

        spdlog::set_default_logger(mLogger);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "# error: log init. failed. : " << ex.what() << "\n";
        exit(0);
    }
}

my::Log::~Log()
{
}

std::shared_ptr<spdlog::logger>  
my::Log::getDefaultLogger(const std::string& defaultLoggerName)
{
    return spdlog::get(defaultLoggerName);
}

void                                
my::Log::setLoggerName(const std::string& loggerName)
{
    mLoggerName = loggerName;
}

const std::string&                  
my::Log::getLoggerName() const
{
    return mLoggerName;
}

void                                
my::Log::setLogFileName(const std::string& logFileName)
{
    mLogFileName    = logFileName;
}

const std::string&                  
my::Log::getLogFileName() const
{
    return mLogFileName;
}

void                                
my::Log::changeLogLevel(const spdlog::level::level_enum logLevel)
{
    if ((nullptr != mLogger) && (nullptr != mFileSink) && (nullptr != mConsoleSink))
    {
        mLogLevel = logLevel;

        mConsoleSink->set_level(logLevel);
        mFileSink->set_level(logLevel);
        mLogger->set_level(logLevel);
    }
}
