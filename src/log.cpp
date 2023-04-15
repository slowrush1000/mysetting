#include "log.hpp"
#include <iostream>

my::Log::Log()
{
    try
    {
        m_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        m_console_sink->set_pattern(m_log_pattern);
        m_console_sink->set_level(m_log_level);

        m_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(m_log_filename, true);
        m_file_sink->set_pattern(m_log_pattern);
        m_file_sink->set_level(m_log_level);

        spdlog::sinks_init_list sinks = {m_console_sink, m_file_sink};

        m_logger                      = std::make_shared<spdlog::logger>(m_logger_name, sinks);
        m_logger->set_pattern(m_log_pattern);
        m_logger->set_level(m_log_level);

        spdlog::set_default_logger(m_logger);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "# error: log init. failed. : " << ex.what() << "\n";
        exit(0);
    }
}

my::Log::Log(const std::string& _logger_name, const std::string& log_filename)
    : m_logger_name(_logger_name)
    , m_log_filename(log_filename)
{
    try
    {
        m_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        m_console_sink->set_pattern(m_log_pattern);
        m_console_sink->set_level(m_log_level);

        m_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(m_log_filename, true);
        m_file_sink->set_pattern(m_log_pattern);
        m_file_sink->set_level(m_log_level);

        spdlog::sinks_init_list sink_lists = {m_console_sink, m_file_sink};

        m_logger                           = std::make_shared<spdlog::logger>(m_logger_name, sink_lists);
        m_logger->set_pattern(m_log_pattern);
        m_logger->set_level(m_log_level);

        spdlog::set_default_logger(m_logger);
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
my::Log::default_logger(const std::string& default_logger_name)
{
    return spdlog::get(default_logger_name);
}

void
my::Log::set_logger_name(const std::string& logger_name)
{
    m_logger_name = logger_name;
}

const std::string&
my::Log::logger_name() const
{
    return m_logger_name;
}

void
my::Log::set_log_filename(const std::string& log_filename)
{
    m_log_filename = log_filename;
}

const std::string&
my::Log::log_filename() const
{
    return m_log_filename;
}

void
my::Log::change_log_level(const spdlog::level::level_enum log_level)
{
    if ((nullptr != m_logger) && (nullptr != m_file_sink) && (nullptr != m_console_sink))
    {
        m_log_level = log_level;

        m_console_sink->set_level(log_level);
        m_file_sink->set_level(log_level);
        m_logger->set_level(log_level);
    }
}
