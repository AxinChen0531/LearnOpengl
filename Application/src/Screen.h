/*
* Author  : 陈鑫(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : 抽象屏幕类
*/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// <summary>
/// 屏幕类，对渲染区域进行管理
/// </summary>
class Screen
{
private:
	int m_width;				//窗口区域宽
	int m_height;				//窗口区域高

	GLFWwindow* m_window;		//glfw窗口

	static Screen* m_Instance;	//Screen全局唯一，主要用于给业务逻辑调用一些取值函数

public:
	/// <summary>
	/// 初始化渲染窗口，默认无边框，尺寸不可调
	/// </summary>
	/// <param name="w">窗口宽</param>
	/// <param name="h">窗口高</param>
	Screen(int w, int h);

	/// <summary>
	/// 获取全局唯一的Screen
	/// </summary>
	/// <returns></returns>
	static inline Screen* Instance() {
		return m_Instance;
	}

	/// <summary>
	/// 获取窗口宽
	/// </summary>
	/// <returns></returns>
	inline int GetWidth() const {
		return m_width;
	}

	/// <summary>
	/// 获取窗口高
	/// </summary>
	/// <returns></returns>
	inline int GetHeight() const {
		return m_height;
	}

	/// <summary>
	/// 执行渲染buffer清理
	/// </summary>
	void ClearBuffers() const;

	/// <summary>
	/// 设置窗口位置
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void SetWindowPos(int x, int y) const;

	/// <summary>
	/// 设置窗口尺寸
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void SetWindowSize(int w, int h);

	/// <summary>
	/// 判断渲染循环是否继续
	/// </summary>
	/// <returns></returns>
	inline bool Continue() const {
		return !glfwWindowShouldClose(m_window);
	}

	/// <summary>
	/// 执行双buffer交换Buffer操作
	/// </summary>
	inline void SwapBuffers() const {
		glfwSwapBuffers(m_window);
	}

	/// <summary>
	/// 用于手动中断
	/// </summary>
	/// <param name="conti"></param>
	inline void SetContinue(bool conti) const {
		glfwSetWindowShouldClose(m_window, conti);
	}

	/// <summary>
	/// 窗口事件回调，qnx暂不考虑
	/// </summary>
	inline void PollEvents() const {
		glfwPollEvents();
	}

	/// <summary>
	/// 结束时的资源释放操作
	/// </summary>
	inline void End() const {
		glfwTerminate();
	}
};