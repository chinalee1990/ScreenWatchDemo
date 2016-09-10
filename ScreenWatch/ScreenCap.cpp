#include "StdAfx.h"
#include "ScreenCap.h"

ScreenCap::ScreenCap(void)
{
	m_hWndSoure = NULL;
	m_rectCapSource.SetRect(0,0,0,0);
	m_rectCapTarget.SetRect(0,0,800,600);
}

ScreenCap::~ScreenCap(void)
{
}

void ScreenCap::StartCap(HWND hWnd,int ptStart_X,int ptStart_Y)
{
	m_hWndSoure = hWnd;
	m_rectCapSource.left = ptStart_X;
	m_rectCapSource.top = ptStart_Y;
}

void ScreenCap::ExeCap(int width,int height)
{
    // 创建图像，设置宽高，像素
	m_rectCapTarget.right = m_rectCapTarget.left + width;
	m_rectCapTarget.bottom = m_rectCapTarget.top + height;
	ExeCap();
}

void ScreenCap::ExeCap()
{
	HDC hdcWindowSource = ::GetDC(m_hWndSoure); 
    int nBitPerPixel = GetDeviceCaps(hdcWindowSource, BITSPIXEL);
	m_Image.Create(m_rectCapTarget.Width(), m_rectCapTarget.Height(), nBitPerPixel);

    // 对指定的源设备环境区域中的像素进行位块（bit_block）转换
    BitBlt(m_Image.GetDC(),		// 保存到的目标 图片对象DC
			m_rectCapTarget.left,				// 保存到的目标 起始 x 坐标
			m_rectCapTarget.top,				// 保存到的目标 起始 y 坐标
			m_rectCapTarget.Width(),			// 截图宽
			m_rectCapTarget.Height(),			// 截图高
			hdcWindowSource,					// 截取源的 DC句柄
			m_rectCapSource.left,				// 截取源矩形区域左上角的 X 逻辑坐标
			m_rectCapSource.top,				// 截取源矩形区域左上角的 y 逻辑坐标
			SRCCOPY);
	 
	::ReleaseDC(m_hWndSoure, hdcWindowSource);	// 释放 DC句柄
    m_Image.ReleaseDC();						// 释放图片上下文
}

void ScreenCap::SaveCap(const CString &strPath)
{
    m_Image.Save(strPath);
}