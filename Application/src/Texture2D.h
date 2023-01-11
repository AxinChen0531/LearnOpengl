/*
 * Author  : ����(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobil   : (+86)136 4741 2733
 * Comment : ����Texture2D�࣬���Դ��е��������ݽ��й���
 */

#pragma once

#include <GL/glew.h>

/// <summary>
/// GL��ͼƬ������ʽ��Ĭ���ṩ3��
/// </summary>
enum ImageFormat
{
	RGB = GL_RGB,		//(R,G,B,1);
	RGBA = GL_RGBA,		//(R,G,B,A);
	Alpha = GL_ALPHA,	//(0,0,0,A);
};

/// <summary>
/// GL��ͼƬ����uvѭ��ģʽ���ṩ���֣�ע��ClampToBorder���ṩ�Զ�����ɫ��Ĭ��Ϊ��
/// </summary>
enum ImageWarpingMode
{
	REPEAT = GL_REPEAT,				//����ѭ��
	MIRROR = GL_MIRRORED_REPEAT,	//ƹ��ѭ��
	FIXED = GL_CLAMP_TO_EDGE,		//�̶�ͼ��Ե������ɫ
	CLAMP = GL_CLAMP_TO_BORDER,		//�̶���ɫ
};

/// <summary>
/// GL��ͼƬ����ȡɫģʽ���ṩ����ȡֵ������ȡֵ����
/// </summary>
enum ImageFilter
{
	LINEAR = GL_LINEAR,		//���Բ�ֵ
	NEAREST = GL_NEAREST,	//�ͽ�ȡֵ
};

/// <summary>
/// ʹ��Texture2D�࣬��2D������з�װ����
/// ��ʹ������ָ������������й���������ֿ���Ⱦ
/// </summary>
class Texture2D final
{
private:
	unsigned int m_id;		//texture id

	int m_width;			//������
	int m_height;			//����߶�
	int m_channelCount;		//����ͨ������֧��1,3,4ͨ������ӦA,RGB,RGBA
	int m_format;			//��ͼƬ������ʽ

	int m_verWarping;		//����uvѭ��ģʽ
	int m_horWarping;		//����uvѭ��ģʽ
	int m_minfilter;		//��ʾ��ԭͼСʱ������ȡɫģʽ
	int m_magfilter;		//��ʾ��ԭͼ��ʱ������ȡɫģʽ

public:
	/// <summary>
	/// �����������API���·�ת�������ڳ����ʼ���׶�ʱ����
	/// </summary>
	/// <param name="flip">�Ƿ���Ҫ��ת</param>
	static void SetYFlip(bool flip);

	/// <summary>
	/// ��������
	/// ֻ������ͨ��������1,3,4ʱ�����������Դ�
	/// uvѭ��ģʽ˫�����Ĭ�ϵ���ѭ��������ȡɫģʽ���ž�Ĭ��Ϊ���Բ�ֵ
	/// </summary>
	/// <param name="imgPath">����·����������չ��</param>
	Texture2D(const char* imgPath);

	/// <summary>
	/// ����ʱ�����ͷ����������Դ�
	/// </summary>
	~Texture2D();

	/// <summary>
	/// ��ȡ����ֱ���(pixels)
	/// </summary>
	/// <param name="w">�������λ</param>
	/// <param name="h">�߶�����λ</param>
	inline void GetResolution(int* w, int* h) const
	{
		*w = m_width;
		*h = m_height;
	}

	/// <summary>
	/// ��ȡ�����ʽ
	/// </summary>
	/// <returns></returns>
	inline ImageFormat GetFormat() const
	{
		return (ImageFormat)m_format;
	}

	/// <summary>
	/// ��ȡ����ͨ����
	/// </summary>
	/// <returns></returns>
	inline int GetChannelCount() const
	{
		return m_channelCount;
	}

	/// <summary>
	/// ʹ�������󶨣�
	/// </summary>
	inline void Use() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	/// <summary>
	/// �����������
	/// </summary>
	inline void Unuse() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	/// <summary>
	/// ���ú���uvѭ��ģʽ
	/// </summary>
	/// <param name="mode">ѭ��ģʽ</param>
	void SetHorizontalWarpingMode(ImageWarpingMode mode);

	/// <summary>
	/// ��������uvѭ��ģʽ
	/// </summary>
	/// <param name="mode">ѭ��ģʽ</param>
	void SetVerticalWarpingMode(ImageWarpingMode mode);

	/// <summary>
	/// ������Сʱȡɫģʽ
	/// </summary>
	/// <param name="filter">ȡɫģʽ</param>
	void SetMinFilter(ImageFilter filter);

	/// <summary>
	/// ���÷Ŵ�ʱȡɫģʽ
	/// </summary>
	/// <param name="filter">ȡɫģʽ</param>
	void SetMagFilter(ImageFilter filter);

};