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
	static unsigned long long cid;				//用于组织GO的ID，确保此数永远递增，runntime过程中所有GO不会重号
	static GameObject SceneRoot;				//场景根物体，作为场景树状更新的起点

private:
	Vec3 m_position;							//世界坐标系中的坐标，主要用于渲染和场景计算，作为更新时的随变量
	Vec3 m_Scale;								//世界坐标系中的缩放，主要用于渲染和场景计算，作为更新时的随便量
	Quaternion m_Rotation;						//世界坐标系中的旋转，主要用于渲染和场景计算，作为更新时的随便量

	Vec3 m_localPosition;						//相对父物体的坐标，主要用于设置，作为更新时的因变量
	Vec3 m_localScale;							//相对父物体的缩放，主要用于设置，作为更新时的因变量
	Quaternion m_LocalRotation;					//相对父物体的旋转，主要用于设置，作为更新时的因变量

	unsigned long long m_uid;					//独有ID，根据cid生成，runtime周期中所有GO不会重复
	int m_depth;								//GO的场景深度，认为SceneRoot深度为0，每层父子关系会增加1的深度，主要用于在父子关系设置时高效率定位等
	int m_indexAsChild;							//当前物体为父物体对应的第几个子物体，主要用于高效率处理父子关系变化等
	GameObject* m_Parent;						//父层物体指针
	std::vector<GameObject*> m_children;		//子层物体指针
	bool updateFlag;							//更新flag，为true时需要更新，脏标记算法

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

	/// <summary>
	/// 获取UID
	/// </summary>
	/// <returns></returns>
	inline unsigned long long GetID() const {
		return m_uid;
	}

	/// <summary>
	/// 获取作为父物体的第几个子物体序号，从0开始
	/// </summary>
	/// <returns></returns>
	inline int IndexAsChild() const {
		return m_indexAsChild;
	}

	/// <summary>
	/// 获取子物体数量
	/// </summary>
	/// <returns></returns>
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
	/// <summary>
	/// 用于父子关系变化后递归更新深度
	/// </summary>
	/// <param name="depth"></param>
	void UpdateDepth(int depth);
	/// <summary>
	/// 用于更新父子关系（不加判断）
	/// </summary>
	/// <param name="newParent"></param>
	void SetParentWithoutJudge(GameObject* newParent);
};