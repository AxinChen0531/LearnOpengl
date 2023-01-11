/*
 * Author  : 陈鑫(Axin Chen)
 * E-mail  : axin.chen@raythinktech.com, m13647412733@163.com
 * Mobil   : (+86)136 4741 2733
 * Comment : 抽象Texture2D类，对显存中的纹理数据进行管理
 */

#pragma once

#include <GL/glew.h>

/// <summary>
/// GL的图片解析格式，默认提供3种
/// </summary>
enum ImageFormat
{
	RGB = GL_RGB,		//(R,G,B,1);
	RGBA = GL_RGBA,		//(R,G,B,A);
	Alpha = GL_ALPHA,	//(0,0,0,A);
};

/// <summary>
/// GL的图片采样uv循环模式，提供四种，注意ClampToBorder不提供自定义颜色，默认为黑
/// </summary>
enum ImageWarpingMode
{
	REPEAT = GL_REPEAT,				//单向循环
	MIRROR = GL_MIRRORED_REPEAT,	//乒乓循环
	FIXED = GL_CLAMP_TO_EDGE,		//固定图边缘像素颜色
	CLAMP = GL_CLAMP_TO_BORDER,		//固定黑色
};

/// <summary>
/// GL的图片采样取色模式，提供线性取值及靠近取值两种
/// </summary>
enum ImageFilter
{
	LINEAR = GL_LINEAR,		//线性插值
	NEAREST = GL_NEAREST,	//就近取值
};

/// <summary>
/// 使用Texture2D类，对2D纹理进行封装管理
/// 请使用智能指针对纹理对象进行管理，避免出现空渲染
/// </summary>
class Texture2D final
{
private:
	unsigned int m_id;		//texture id

	int m_width;			//纹理宽度
	int m_height;			//纹理高度
	int m_channelCount;		//纹理通道数，支持1,3,4通道，对应A,RGB,RGBA
	int m_format;			//的图片解析格式

	int m_verWarping;		//纵向uv循环模式
	int m_horWarping;		//横向uv循环模式
	int m_minfilter;		//显示较原图小时，采样取色模式
	int m_magfilter;		//显示较原图大时，采样取色模式

public:
	/// <summary>
	/// 设置纹理加载API上下翻转需求，请在程序初始化阶段时设置
	/// </summary>
	/// <param name="flip">是否需要翻转</param>
	static void SetYFlip(bool flip);

	/// <summary>
	/// 加载纹理
	/// 只有纹理通道数满足1,3,4时将正常载入显存
	/// uv循环模式双方向均默认单向循环，采样取色模式缩放均默认为线性差值
	/// </summary>
	/// <param name="imgPath">纹理路径，包括拓展名</param>
	Texture2D(const char* imgPath);

	/// <summary>
	/// 析构时，将释放纹理数据显存
	/// </summary>
	~Texture2D();

	/// <summary>
	/// 获取纹理分辨率(pixels)
	/// </summary>
	/// <param name="w">宽度数据位</param>
	/// <param name="h">高度数据位</param>
	inline void GetResolution(int* w, int* h) const
	{
		*w = m_width;
		*h = m_height;
	}

	/// <summary>
	/// 获取纹理格式
	/// </summary>
	/// <returns></returns>
	inline ImageFormat GetFormat() const
	{
		return (ImageFormat)m_format;
	}

	/// <summary>
	/// 获取纹理通道数
	/// </summary>
	/// <returns></returns>
	inline int GetChannelCount() const
	{
		return m_channelCount;
	}

	/// <summary>
	/// 使用纹理（绑定）
	/// </summary>
	inline void Use() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	/// <summary>
	/// 禁用纹理（解绑）
	/// </summary>
	inline void Unuse() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	/// <summary>
	/// 设置横向uv循环模式
	/// </summary>
	/// <param name="mode">循环模式</param>
	void SetHorizontalWarpingMode(ImageWarpingMode mode);

	/// <summary>
	/// 设置纵向uv循环模式
	/// </summary>
	/// <param name="mode">循环模式</param>
	void SetVerticalWarpingMode(ImageWarpingMode mode);

	/// <summary>
	/// 设置缩小时取色模式
	/// </summary>
	/// <param name="filter">取色模式</param>
	void SetMinFilter(ImageFilter filter);

	/// <summary>
	/// 设置放大时取色模式
	/// </summary>
	/// <param name="filter">取色模式</param>
	void SetMagFilter(ImageFilter filter);

};