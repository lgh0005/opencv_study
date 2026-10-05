#pragma once

class CVLogger
{
	DISABLE_COPY(CVLogger)
	DISABLE_MOVE(CVLogger)

private:
	CVLogger();
	~CVLogger();

public:
	// Changes the global level, including OpenCV's own messages.
	static void SetLogLevel(LogLevel level);
	static LogLevel GetLogLevel();

	// Uses OpenCV's default output and filtering. Fatal only logs a message.
	static void Fatal(std::string_view message);
	static void Error(std::string_view message);
	static void Warning(std::string_view message);
	static void Info(std::string_view message);

	// Compiled out in Release builds by OpenCV's default logging policy.
	static void Debug(std::string_view message);
};

