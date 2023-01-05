#pragma once

class Log
{
public:
	void static Info(const char* msg, const char* info = "");
	void static Warning(const char* msg, const char* warn = "");
	void static Error(const char* msg, const char* err = "");
};