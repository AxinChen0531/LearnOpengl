/*
* Author  : 陈鑫(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : log日志类
*/


#pragma once

class Log
{
public:
	/// <summary>
	/// 输出信息
	/// </summary>
	/// <param name="msg">输出内容</param>
	/// <param name="info">信息类别名</param>
	void static Info(const char* msg, const char* info = "");

	/// <summary>
	/// 输出警告
	/// </summary>
	/// <param name="msg">警告内容</param>
	/// <param name="warn">警告类比名</param>
	void static Warning(const char* msg, const char* warn = "");

	/// <summary>
	/// 输出错误
	/// </summary>
	/// <param name="msg">错误内容</param>
	/// <param name="err">错误类名名</param>
	void static Error(const char* msg, const char* err = "");
};