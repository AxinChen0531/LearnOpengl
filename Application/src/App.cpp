#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Log.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"

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
		//pos				 normal  uv
		 0.5f,  0.5f, 0.0f,  0,0,0,  1,1, // ���Ͻ�
		 0.5f, -0.5f, 0.0f,  0,0,0,  1,0,// ���½�
		-0.5f, -0.5f, 0.0f,  0,0,0,  0,0,// ���½�
		-0.5f,  0.5f, 0.0f,  0,0,0,  0,1// ���Ͻ�
	};
	GLuint indices[] = {
		0, 1, 3, // ��һ�������Σ����ϣ�, ˳ʱ�뱳��
		3, 2, 1  // �ڶ��������Σ����£�����ʱ������
	};

	Shader shader("./res/Shader/SampleShader.shader");
	Material mat(shader);
	Mesh mesh(vertices, 32, indices, 6);
	Renderer renderer(&mesh, &mat);

	//rendering circle
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.Render();

		glfwSwapBuffers(window);
	}

	//release and quit
	glfwTerminate();
	return 0;
}