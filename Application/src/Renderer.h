/*
 * Author  : ����(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobil   : (+86)136 4741 2733
 * Comment : �� Mesh - Material �������Ⱦ��Ԫ����ΪRender��
 */

#pragma once
#include "Mesh.h"
#include "Material.h"
#include <memory>

class Renderer
{
private:
	std::shared_ptr<Mesh> m_mesh;		//����ָ��
	std::shared_ptr<Material> m_mat;	//����ָ��

public:
	/// <summary>
	/// ���������Ͷ�Ӧ���ʣ���Ϊһ����Ⱦ��Ԫ
	/// ��ͳһ������Ͳ��ʹ������ʹ������ָ����й������������ԴΪ�գ���Ⱦ��������
	/// �����ͷ�����Ͳ���ǰ����Ҫ���ͷŹ������ǵ���Ⱦ��Ԫ
	/// </summary>
	/// <param name="mesh">�������ָ��</param>
	/// <param name="mat">���ʶ���ָ��</param>
	Renderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> mat);

	/// <summary>
	/// ����ʱ�����ͷŹ��������Ͳ�������ָ��
	/// </summary>
	~Renderer();

	/// <summary>
	/// ���ù��������Ͳ��ʽ�����Ⱦ
	/// </summary>
	void Render() const;
};