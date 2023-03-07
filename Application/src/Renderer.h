/*
 * Author  : ����(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobile  : (+86)136 4741 2733
 * Comment : �� Mesh - Material �������Ⱦ��Ԫ����ΪRender��
 */

#pragma once

#include <memory>

#include "Mesh.h"
#include "Material.h"
#include "Object.h"

class Renderer : public Component, public IAwake2<std::shared_ptr<Mesh>&, std::shared_ptr<Material>&>
{
protected:
	std::shared_ptr<Mesh> m_mesh;		//����ָ��
	std::shared_ptr<Material> m_mat;	//����ָ��

public:
	Renderer();
	/// <summary>
	/// ���������Ͷ�Ӧ���ʣ���Ϊһ����Ⱦ��Ԫ
	/// ��ͳһ������Ͳ��ʹ������ʹ������ָ����й������������ԴΪ�գ���Ⱦ��������
	/// �����ͷ�����Ͳ���ǰ����Ҫ���ͷŹ������ǵ���Ⱦ��Ԫ
	/// </summary>
	/// <param name="mesh">�������ָ��</param>
	/// <param name="mat">���ʶ���ָ��</param>
	void Awake(std::shared_ptr<Mesh>& mesh, std::shared_ptr<Material>& mat) override;

	/// <summary>
	/// ����ʱ�����ͷŹ��������Ͳ�������ָ��
	/// </summary>
	~Renderer();

	inline const type_info* GetTypeInfo() const override {
		return &typeid(Renderer);
	}

	/// <summary>
	/// ���ù��������Ͳ��ʽ�����Ⱦ
	/// </summary>
	virtual void Render() const;
};