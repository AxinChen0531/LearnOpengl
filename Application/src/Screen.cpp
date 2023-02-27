/*
* Author  : ³ÂöÎ(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : ³éÏóÆÁÄ»Àà
*/

#include "AMath.h"
#include "Screen.h"
#include "Log.h"

Screen* Screen::m_Instance = nullptr;

Screen::Screen(int w, int h) : m_height(h), m_width(w)
{
	m_window = nullptr;
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_DECORATED, false);
	m_window = glfwCreateWindow(w, h, "AxE", nullptr, nullptr);
	if (m_window == nullptr) {
		Log::Error("Failed to create GLFW window", "GLFW ERROR");
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
	//V-sync
	glfwSwapInterval(1);
	//GLEW init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		Log::Error("Failed to initialize GLEW", "GLEW ERROR");
	}
	glViewport(0, 0, w, h);
	Screen::m_Instance = this;
}

void Screen::ClearBuffers() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDepthMask(GL_TRUE);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Screen::SetWindowPos(int x, int y) const
{
	glfwSetWindowPos(m_window, x, y);
}

void Screen::SetWindowSize(int w, int h)
{
	glfwSetWindowSize(m_window, w, h);
	m_width = w;
	m_height = h;
	glViewport(0, 0, w, h);
}
