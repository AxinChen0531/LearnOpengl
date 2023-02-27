/*
* Author  : ����(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : log��־��
*/


#pragma once

class Log
{
public:
	/// <summary>
	/// �����Ϣ
	/// </summary>
	/// <param name="msg">�������</param>
	/// <param name="info">��Ϣ�����</param>
	void static Info(const char* msg, const char* info = "");

	/// <summary>
	/// �������
	/// </summary>
	/// <param name="msg">��������</param>
	/// <param name="warn">���������</param>
	void static Warning(const char* msg, const char* warn = "");

	/// <summary>
	/// �������
	/// </summary>
	/// <param name="msg">��������</param>
	/// <param name="err">����������</param>
	void static Error(const char* msg, const char* err = "");
};