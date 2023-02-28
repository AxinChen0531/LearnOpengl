/*
* Author  : ����(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : GameObject��������Transform��ʵ����
*/

#pragma once

#include <typeinfo>
#include <vector>

#include "AMath.h"
#include "Object.h"

class GameObject : public Entity, public IAwake, public IAwake1<GameObject*>, public IAwake2<GameObject*, const Vec3&>
{
private:
	static unsigned long long cid;
	static GameObject SceneRoot;

private:
	Vec3 m_position;
	Vec3 m_Scale;
	Quaternion m_Rotation;
	Vec3 m_localPosition;
	Vec3 m_localScale;
	Quaternion m_LocalRotation;

	unsigned long long m_uid;
	int m_depth;
	int m_indexAsChild;
	GameObject* m_Parent;
	std::vector<GameObject*> m_children;
	bool updateFlag;

public:
	GameObject();
	~GameObject() override;
	void Dispose() override;
	void Awake() override;											//ȫĬ�ϣ���ΪSceneRootֱ��������
	void Awake(GameObject* parent) override;						//��Ϊָ������������壬����Ĭ��
	void Awake(GameObject* parent, const Vec3& localPos) override;	//��Ϊָ������������壬�����ó�ʼlocal����

	inline Vec3 Position() const {
		return m_position;
	}
	inline Vec3 LocalPosition() const {
		return m_localPosition;
	}
	inline Vec3 Scale() const {
		return m_Scale;
	}
	inline Vec3 LocalScale() const {
		return m_localScale;
	}
	inline Quaternion Rotation() const {
		return m_Rotation;
	}
	inline Quaternion LocalRotation() const {
		return m_LocalRotation;
	}

	inline Vec3& RawPosition() {
		return m_position;
	}
	inline Vec3& RawLocalPosition() {
		return m_localPosition;
	}
	inline Vec3& RawScale() {
		return m_Scale;
	}
	inline Vec3& RawLocalScale() {
		return m_localScale;
	}
	inline Quaternion& RawRotation() {
		return m_Rotation;
	}
	inline Quaternion& RawLocalRotation() {
		return m_LocalRotation;
	}

	inline unsigned long long GetID() const {
		return m_uid;
	}
	inline int IndexAsChild() const {
		return m_indexAsChild;
	}
	inline int ChildCount() const {
		return m_children.size();
	}

	/// <summary>
	/// ���index���ޣ�������nullptr
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	GameObject* GetChild(int index);

	/// <summary>
	/// ���踸ʵ�壬
	/// �����踸ʵ��Ϊnullptr�����Զ����ص�SceneRoot
	/// ������Ϊ���踸ʵ������ȣ���������������false�������������ת�Ʒ���true
	/// </summary>
	/// <param name="newParent"></param>
	/// <returns></returns>
	bool SetParent(GameObject* newParent);

	/// <summary>
	/// ��index���ޣ�������������false�����򷵻�true
	/// ѡ���Ӧ�����壬����ֱ�ӹ��ص�SceneRoot
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	bool MakeIndep(int index);

	/// <summary>
	/// ��child������ֱ�������壬������������false�����򷵻�true
	/// ѡ���Ӧ�����壬����ֱ�ӹ��ص�SceneRoot
	/// </summary>
	/// <param name="child"></param>
	/// <returns></returns>
	bool MakeIndep(GameObject* child);

private:
	void UpdateDepth(int depth);
	void SetParentWithoutJudge(GameObject* newParent);
};