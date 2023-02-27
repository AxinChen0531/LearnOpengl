/*
* Author  : ≥¬ˆŒ(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : log»’÷æ¿‡
*/

#include <iostream>

#include "Log.h"

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
