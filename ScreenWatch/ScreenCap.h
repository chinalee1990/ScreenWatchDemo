#pragma once

class ScreenCap
{
public:
	ScreenCap(void);
	~ScreenCap(void);
public:		void StartCap(HWND hWnd,int ptStart_X,int ptStart_Y);
public:		void ExeCap(int height,int width);
private:	void ExeCap();
public:		void SaveCap(const CString &strPath);
public:		CRect m_rectCapSource;
public:		CRect m_rectCapTarget;
public:		HWND m_hWndSoure;
public:	    CImage m_Image;
};
