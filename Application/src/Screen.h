/*
* Author  : ����(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : ������Ļ��
*/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// <summary>
/// ��Ļ�࣬����Ⱦ������й���
/// </summary>
class Screen
{
private:
	int m_width;				//���������
	int m_height;				//���������

	GLFWwindow* m_window;		//glfw����

	static Screen* m_Instance;	//Screenȫ��Ψһ����Ҫ���ڸ�ҵ���߼�����һЩȡֵ����

public:
	/// <summary>
	/// ��ʼ����Ⱦ���ڣ�Ĭ���ޱ߿򣬳ߴ粻�ɵ�
	/// </summary>
	/// <param name="w">���ڿ�</param>
	/// <param name="h">���ڸ�</param>
	Screen(int w, int h);

	/// <summary>
	/// ��ȡȫ��Ψһ��Screen
	/// </summary>
	/// <returns></returns>
	static inline Screen* Instance() {
		return m_Instance;
	}

	/// <summary>
	/// ��ȡ���ڿ�
	/// </summary>
	/// <returns></returns>
	inline int GetWidth() const {
		return m_width;
	}

	/// <summary>
	/// ��ȡ���ڸ�
	/// </summary>
	/// <returns></returns>
	inline int GetHeight() const {
		return m_height;
	}

	/// <summary>
	/// ִ����Ⱦbuffer����
	/// </summary>
	void ClearBuffers() const;

	/// <summary>
	/// ���ô���λ��
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void SetWindowPos(int x, int y) const;

	/// <summary>
	/// ���ô��ڳߴ�
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void SetWindowSize(int w, int h);

	/// <summary>
	/// �ж���Ⱦѭ���Ƿ����
	/// </summary>
	/// <returns></returns>
	inline bool Continue() const {
		return !glfwWindowShouldClose(m_window);
	}

	/// <summary>
	/// ִ��˫buffer����Buffer����
	/// </summary>
	inline void SwapBuffers() const {
		glfwSwapBuffers(m_window);
	}

	/// <summary>
	/// �����ֶ��ж�
	/// </summary>
	/// <param name="conti"></param>
	inline void SetContinue(bool conti) const {
		glfwSetWindowShouldClose(m_window, conti);
	}

	/// <summary>
	/// �����¼��ص���qnx�ݲ�����
	/// </summary>
	inline void PollEvents() const {
		glfwPollEvents();
	}

	/// <summary>
	/// ����ʱ����Դ�ͷŲ���
	/// </summary>
	inline void End() const {
		glfwTerminate();
	}
};