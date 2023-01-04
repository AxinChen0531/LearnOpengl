#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC键, 设置window窗口的WindowShouldClose属性为true
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	//GLFW init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//GLEW init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//viewport setting
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//按键消息回调
	glfwSetKeyCallback(window, key_callback);

	//正面绘制面，背面绘制框
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,   // 右上角
		 0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f,  0.5f, 0.0f   // 左上角
	};
	GLuint indices[] = {
		0, 1, 3, // 第一个三角形（右上）, 顺时针背对
		3, 2, 1  // 第二个三角形（左下），逆时针正对
	};

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* vss =
		"layout(location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}";
	const char* fss =
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}";

	glShaderSource(vshader, 1, &vss, NULL);
	glShaderSource(fshader, 1, &fss, NULL);
	glCompileShader(vshader);
	glCompileShader(fshader);
	GLuint shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vshader);
	glAttachShader(shaderprogram, fshader);
	glLinkProgram(shaderprogram);
	glDeleteShader(vshader);
	glDeleteShader(fshader);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//解绑
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//rendering circle
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//用指定的shader program 绘制绑定的VAO
		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	//release and quit
	glfwTerminate();
	return 0;
}