/*
* Author  : ����(Axin Chen)
* E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
* Mobile  : (+86)136 4741 2733
* Comment : һЩ�����ĳ����ṹ��
*/

#include "Object.h"

GameObject* GameObject::m_root = new GameObject();
GameObject::GameObject() : m_indexAsChild(0), m_active(true), m_transFlag(true), m_needDestroy(false)
{
}