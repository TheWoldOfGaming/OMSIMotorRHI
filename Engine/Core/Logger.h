#pragma once
#include <fstream>

namespace Engine
{
	enum class LogLevel
	{
		Trace = 0,
		Debug,
		Info,
		Warning,
		Error,
		Critical
	};

	enum class LogCategory
	{
		General,
		Game,
		DX3D,
		Audio,
		Input,
		Physics,
		AI,
		Network,
		UI,
		Scripting,
		ResourceManagement
	};

	class Logger
	{
	public:
		static void Initialize(const std::string& logFile);

		static void SetLogLevel(LogLevel level) { s_MinLogLevel = level; }

		static void Log(
			LogLevel level,
			LogCategory category,
			const std::string& message
		);

		static void Trace(
			LogCategory category,
			const std::string& message
		);

		static void Debug(
			LogCategory category,
			const std::string& message
		);

		static void Info(
			LogCategory category,
			const std::string& message
		);

		static void Warning(
			LogCategory category,
			const std::string& message
		);

		static void Error(
			LogCategory category,
			const std::string& message
		);

		static void Critical(
			LogCategory category,
			const std::string& message
		);

		static std::ofstream s_LogFile;

	private:
		static LogLevel s_MinLogLevel;
	};
}
