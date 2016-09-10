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
    // ����ͼ�����ÿ�ߣ�����
	m_rectCapTarget.right = m_rectCapTarget.left + width;
	m_rectCapTarget.bottom = m_rectCapTarget.top + height;
	ExeCap();
}

void ScreenCap::ExeCap()
{
	HDC hdcWindowSource = ::GetDC(m_hWndSoure); 
    int nBitPerPixel = GetDeviceCaps(hdcWindowSource, BITSPIXEL);
	m_Image.Create(m_rectCapTarget.Width(), m_rectCapTarget.Height(), nBitPerPixel);

    // ��ָ����Դ�豸���������е����ؽ���λ�飨bit_block��ת��
    BitBlt(m_Image.GetDC(),		// ���浽��Ŀ�� ͼƬ����DC
			m_rectCapTarget.left,				// ���浽��Ŀ�� ��ʼ x ����
			m_rectCapTarget.top,				// ���浽��Ŀ�� ��ʼ y ����
			m_rectCapTarget.Width(),			// ��ͼ��
			m_rectCapTarget.Height(),			// ��ͼ��
			hdcWindowSource,					// ��ȡԴ�� DC���
			m_rectCapSource.left,				// ��ȡԴ�����������Ͻǵ� X �߼�����
			m_rectCapSource.top,				// ��ȡԴ�����������Ͻǵ� y �߼�����
			SRCCOPY);
	 
	::ReleaseDC(m_hWndSoure, hdcWindowSource);	// �ͷ� DC���
    m_Image.ReleaseDC();						// �ͷ�ͼƬ������
}

void ScreenCap::SaveCap(const CString &strPath)
{
    m_Image.Save(strPath);
}