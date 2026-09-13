#include <Core/Logger.h>

#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace Engine
{
	std::ofstream Logger::s_LogFile;
	LogLevel Logger::s_MinLogLevel = LogLevel::Trace;

	void Logger::Initialize(const std::string& logFile)
	{
		s_LogFile.open(logFile, std::ios::app);
	}

	void Logger::Log(
		LogLevel level,
		LogCategory category,
		const std::string& message
	)
	{
		if (level < s_MinLogLevel)
		{
			return;
		}

		const auto now = std::chrono::system_clock::now();
		const std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

		std::tm localTime;

#ifdef _WIN32
		localtime_s(&localTime, &currentTime);
#else
		localtime_r(&currentTime, &localTime);
#endif

		std::string levelString;

		switch (level)
		{
		case LogLevel::Trace:
			levelString = "TRACE";
			break;

		case LogLevel::Debug:
			levelString = "DEBUG";
			break;

		case LogLevel::Info:
			levelString = "INFO";
			break;

		case LogLevel::Warning:
			levelString = "WARNING";
			break;

		case LogLevel::Error:
			levelString = "ERROR";
			break;

		case LogLevel::Critical:
			levelString = "CRITICAL";
			break;
		}

		std::string categoryString;

		switch (category)
		{
		case LogCategory::General:
			categoryString = "General";
			break;

		case LogCategory::Game:
			categoryString = "Game";
			break;

		case LogCategory::DX3D:
			categoryString = "DX3D";
			break;

		case LogCategory::Audio:
			categoryString = "Audio";
			break;

		case LogCategory::Input:
			categoryString = "Input";
			break;

		case LogCategory::Physics:
			categoryString = "Physics";
			break;

		case LogCategory::AI:
			categoryString = "AI";
			break;

		case LogCategory::Network:
			categoryString = "Network";
			break;

		case LogCategory::UI:
			categoryString = "UI";
			break;

		case LogCategory::Scripting:
			categoryString = "Scripting";
			break;

		case LogCategory::ResourceManagement:
			categoryString = "ResourceManagement";
			break;
		}

		std::ostringstream output;
		output << '['
			<< std::setfill('0')
			<< std::setw(2) << localTime.tm_hour
			<< ':'
			<< std::setw(2) << localTime.tm_min
			<< ':'
			<< std::setw(2) << localTime.tm_sec
			<< "] ["
			<< categoryString
			<< "] ["
			<< levelString
			<< "] "
			<< message
			<< std::endl;

		const std::string formattedMessage = output.str();


		// Console output
		std::cout << formattedMessage;


		// File output
		if (s_LogFile.is_open())
		{
			s_LogFile << formattedMessage;
			s_LogFile.flush();
		}
	}

	void Logger::Trace(
		LogCategory category,
		const std::string& message
	)
	{
		Log(LogLevel::Trace, category, message);
	}

	void Logger::Debug(
		LogCategory category,
		const std::string& message
	)
	{
		Log(LogLevel::Debug, category, message);
	}

	void Logger::Info(
		LogCategory category,
		const std::string& message
	)
	{
		Log(LogLevel::Info, category, message);
	}

	void Logger::Warning(
		LogCategory category,
		const std::string& message
	)
	{
		Log(LogLevel::Warning, category, message);
	}

	void Logger::Error(
		LogCategory category,
		const std::string& message
	)
	{
		Log(LogLevel::Error, category, message);
	}

	void Logger::Critical(
		LogCategory category,
		const std::string& message
	)
	{
		Log(LogLevel::Critical, category, message);
	}
}