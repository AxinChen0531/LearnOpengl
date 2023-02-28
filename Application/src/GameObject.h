/*
* Author  : 陈鑫(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : GameObject，整合了Transform的实体类
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
	void Awake() override;											//全默认，作为SceneRoot直接子物体
	void Awake(GameObject* parent) override;						//作为指定物体的子物体，其他默认
	void Awake(GameObject* parent, const Vec3& localPos) override;	//作为指定物体的子物体，且设置初始local坐标

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
	/// 如果index超限，将返回nullptr
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	GameObject* GetChild(int index);

	/// <summary>
	/// 重设父实体，
	/// 若新设父实体为nullptr，则自动挂载到SceneRoot
	/// 若自身为新设父实体的祖先，则不做动作并返回false，其余情况正常转移返回true
	/// </summary>
	/// <param name="newParent"></param>
	/// <returns></returns>
	bool SetParent(GameObject* newParent);

	/// <summary>
	/// 若index超限，则不做动作返回false，否则返回true
	/// 选择对应子物体，将其直接挂载到SceneRoot
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	bool MakeIndep(int index);

	/// <summary>
	/// 若child不属于直接子物体，则不做动作返回false，否则返回true
	/// 选择对应子物体，将其直接挂载到SceneRoot
	/// </summary>
	/// <param name="child"></param>
	/// <returns></returns>
	bool MakeIndep(GameObject* child);

private:
	void UpdateDepth(int depth);
	void SetParentWithoutJudge(GameObject* newParent);
};