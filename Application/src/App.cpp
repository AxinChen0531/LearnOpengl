#include "AMath.h"
#include "Log.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Screen.h"
#include "GameObject.h"

int main()
{
	Screen screen(800, 600);

	//正面绘制面，背面绘制框
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	
	GLfloat vertices[] = {
		//pos				 normal			    uv
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, -1.0f,  2.0f,2.0f,	// 右上角
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, -1.0f,  2.0f,0.0f,	// 右下角
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,0.0f,	// 左下角
		-0.5f,  0.5f, 0.0f,  0.0f, 0.0f, -1.0f,  0.0f,2.0f	// 左上角
	};
	GLuint indices[] = {
		3, 1, 0, // 第一个三角形（右上），逆时针正对
		3, 2, 1  // 第二个三角形（左下），逆时针正对
	};

	//一般图形库会设计Y反转API，根据需要设定
	Texture2D::SetYFlip(true);
	std::shared_ptr<Mesh> mesh(new Mesh(vertices, sizeof(vertices), indices, sizeof(indices)/sizeof(unsigned int)));
	std::shared_ptr<Shader> shader(new Shader("./res/Shader/Sample3DShader.glsl"));
	std::shared_ptr<Material> mat(new Material(shader.get()));
	std::shared_ptr<Texture2D> t2d_base(new Texture2D("./res/Texture/container.jpg"));
	std::shared_ptr<Texture2D> t2d_over(new Texture2D("./res/Texture/awesomeface.png"));
	mat.get()->SetTexture2D("MainTexture", t2d_base);
	mat.get()->SetTexture2D("Overlap", t2d_over);	
	std::shared_ptr<Shader> post_shader(new Shader("./res/Shader/SamplePostProcessing.glsl"));
	std::shared_ptr<Material> post_mat(new Material(post_shader.get()));

	GameObject* Scene = ObjectFactory::Create<GameObject>();
	Renderer* renderer = Scene->AddComponent<Renderer, std::shared_ptr<Mesh>&, std::shared_ptr<Material>&>(mesh, mat);
	Camera* cam = Scene->AddComponent<Camera, ProjectionType>(ProjectionType::Perspective);
	cam->SetPostProcessingMat(post_mat);

	shader = nullptr;
	post_shader = nullptr;

	//rendering circle
	while (screen.Continue()) {
		screen.PollEvents();
		screen.ClearBuffers();
		//逻辑循环
		EventCenter::Update();
		//逻辑结束后进行渲染
		//离屏渲染
		cam->Begin();
		renderer->Render();
		cam->End();
		//后处理输出结果，此时无离屏渲染截取，因此成为了最终输出
		cam->PostProcessing();

		screen.SwapBuffers();
	}
	screen.End();
	return 0;
}