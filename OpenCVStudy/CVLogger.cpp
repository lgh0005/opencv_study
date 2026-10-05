#include "pch.h"
#include "CVLogger.h"

CVLogger::CVLogger() = default;
CVLogger::~CVLogger() = default;

void CVLogger::SetLogLevel(LogLevel level)
{
	cv::utils::logging::setLogLevel(level);
}

LogLevel CVLogger::GetLogLevel()
{
	return cv::utils::logging::getLogLevel();
}

void CVLogger::Fatal(std::string_view message)
{
	CV_LOG_FATAL(nullptr, message);
}

void CVLogger::Error(std::string_view message)
{
	CV_LOG_ERROR(nullptr, message);
}

void CVLogger::Warning(std::string_view message)
{
	CV_LOG_WARNING(nullptr, message);
}

void CVLogger::Info(std::string_view message)
{
	CV_LOG_INFO(nullptr, message);
}

void CVLogger::Debug(std::string_view message)
{
	CV_LOG_DEBUG(nullptr, message);
}
