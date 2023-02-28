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
		//�߼�ѭ��
		EventCenter::Update();
		//�߼������������Ⱦ
		//������Ⱦ
		cam->Begin();
		renderer->Render();
		cam->End();
		//��������������ʱ��������Ⱦ��ȡ����˳�Ϊ���������
		cam->PostProcessing();

		screen.SwapBuffers();
	}
	screen.End();
	return 0;
}