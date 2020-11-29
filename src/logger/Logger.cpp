#include "../inc/Logger.hpp"
#include "../inc/ConsoleExtension.hpp"

#include <iostream>

Logger::Logger() {}

Logger::~Logger() {}

void Logger::Log(std::string const &message, LoggerPriority priority) const
{
	ConsoleExtension::ConsoleColor color;
	std::string header;

	switch (priority)
	{
	case LoggerPriority::Fatal_Error:
		color = ConsoleExtension::ConsoleColor::Red;
		header = "[FATAL ERROR] : ";
		break;
	case LoggerPriority::Error:
		color = ConsoleExtension::ConsoleColor::LightRed;
		header = "[ERROR] : ";
		break;
	case LoggerPriority::Warn:
		color = ConsoleExtension::ConsoleColor::Yellow;
		header = "[WARN] : ";
		break;
	case LoggerPriority::Info:
		color = ConsoleExtension::ConsoleColor::Blue;
		header = "[INFO] : ";
		break;
	case LoggerPriority::Debug:
		color = ConsoleExtension::ConsoleColor::Green;
		header = "[DEBUG] : ";
		break;
	}
	ConsoleExtension::SetConsoleTextColor(color);

	std::cout << header << message << std::endl;

	ConsoleExtension::SetConsoleTextColor(ConsoleExtension::ConsoleColor::Default_Color);
}