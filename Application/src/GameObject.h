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
	static unsigned long long cid;				//������֯GO��ID��ȷ��������Զ������runntime����������GO�����غ�
	static GameObject SceneRoot;				//���������壬��Ϊ������״���µ����

private:
	Vec3 m_position;							//��������ϵ�е����꣬��Ҫ������Ⱦ�ͳ������㣬��Ϊ����ʱ�������
	Vec3 m_Scale;								//��������ϵ�е����ţ���Ҫ������Ⱦ�ͳ������㣬��Ϊ����ʱ�������
	Quaternion m_Rotation;						//��������ϵ�е���ת����Ҫ������Ⱦ�ͳ������㣬��Ϊ����ʱ�������

	Vec3 m_localPosition;						//��Ը���������꣬��Ҫ�������ã���Ϊ����ʱ�������
	Vec3 m_localScale;							//��Ը���������ţ���Ҫ�������ã���Ϊ����ʱ�������
	Quaternion m_LocalRotation;					//��Ը��������ת����Ҫ�������ã���Ϊ����ʱ�������

	unsigned long long m_uid;					//����ID������cid���ɣ�runtime����������GO�����ظ�
	int m_depth;								//GO�ĳ�����ȣ���ΪSceneRoot���Ϊ0��ÿ�㸸�ӹ�ϵ������1����ȣ���Ҫ�����ڸ��ӹ�ϵ����ʱ��Ч�ʶ�λ��
	int m_indexAsChild;							//��ǰ����Ϊ�������Ӧ�ĵڼ��������壬��Ҫ���ڸ�Ч�ʴ����ӹ�ϵ�仯��
	GameObject* m_Parent;						//��������ָ��
	std::vector<GameObject*> m_children;		//�Ӳ�����ָ��
	bool updateFlag;							//����flag��Ϊtrueʱ��Ҫ���£������㷨

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

	/// <summary>
	/// ��ȡUID
	/// </summary>
	/// <returns></returns>
	inline unsigned long long GetID() const {
		return m_uid;
	}

	/// <summary>
	/// ��ȡ��Ϊ������ĵڼ�����������ţ���0��ʼ
	/// </summary>
	/// <returns></returns>
	inline int IndexAsChild() const {
		return m_indexAsChild;
	}

	/// <summary>
	/// ��ȡ����������
	/// </summary>
	/// <returns></returns>
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
	/// <summary>
	/// ���ڸ��ӹ�ϵ�仯��ݹ�������
	/// </summary>
	/// <param name="depth"></param>
	void UpdateDepth(int depth);
	/// <summary>
	/// ���ڸ��¸��ӹ�ϵ�������жϣ�
	/// </summary>
	/// <param name="newParent"></param>
	void SetParentWithoutJudge(GameObject* newParent);
};