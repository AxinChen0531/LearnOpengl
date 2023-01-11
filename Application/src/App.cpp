#include <iostream>
#include <memory>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Log.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "AMath.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ���û�����ESC��, ����window���ڵ�WindowShouldClose����Ϊtrue
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	//GLFW init
	glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		Log::Error("Failed to create GLFW window", "GLFW ERROR");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//V-sync
	glfwSwapInterval(1);

	//GLEW init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		Log::Error("Failed to initialize GLEW", "GLEW ERROR");
		return -1;
	}

	//viewport setting
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//ע�ᰴ����Ϣ�ص�
	glfwSetKeyCallback(window, key_callback);

	//��������棬������ƿ�
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	GLfloat vertices[] = {
		//pos				 normal			    uv
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, -1.0f,  2.0f,2.0f,	// ���Ͻ�
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, -1.0f,  2.0f,0.0f,	// ���½�
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,0.0f,	// ���½�
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,2.0f	// ���Ͻ�
	};
	GLuint indices[] = {
		3, 1, 0, // ��һ�������Σ����ϣ�����ʱ������
		3, 2, 1  // �ڶ��������Σ����£�����ʱ������
	};

	//һ��ͼ�ο�����Y��תAPI��������Ҫ�趨
	Texture2D::SetYFlip(true);

	std::shared_ptr<Mesh> mesh(new Mesh(vertices, sizeof(vertices), indices, sizeof(indices)/sizeof(unsigned int)));
	std::shared_ptr<Shader> shader(new Shader("./res/Shader/SampleShader.shader"));
	std::shared_ptr<Material> mat(new Material(shader.get()));
	std::shared_ptr<Texture2D> t2d_base(new Texture2D("./res/Texture/container.jpg"));
	std::shared_ptr<Texture2D> t2d_over(new Texture2D("./res/Texture/awesomeface.png"));
	mat.get()->SetTexture2D("MainTexture", t2d_base);
	mat.get()->SetTexture2D("Overlap", t2d_over);
	std::shared_ptr<Renderer> renderer(new Renderer(mesh, mat));

	//rendering circle
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDepthMask(GL_TRUE);
		glClear(GL_DEPTH_BUFFER_BIT);

		renderer->Render();

		glfwSwapBuffers(window);
	}

	//release and quit
	glfwTerminate();
	return 0;
}