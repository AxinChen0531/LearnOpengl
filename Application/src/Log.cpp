#include "Log.h"
#include <iostream>

void Log::Info(const char* msg, const char* info)
{
	std::cout << "[INFO]" << info << ":\n"<< msg << std::endl;
}

void Log::Warning(const char* msg, const char* warn)
{
	std::cout << "[WARN]" << warn << ":\n"<< msg << std::endl;
}

void Log::Error(const char* msg, const char* err)
{
	std::cout << "[ERR]" << err << ":\n" << msg << std::endl;
}
