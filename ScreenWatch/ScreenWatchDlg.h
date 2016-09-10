
// ScreenWatchDlg.h : 头文件
//

#pragma once
#include "ScreenCap.h"

// CScreenWatchDlg 对话框
class CScreenWatchDlg : public CDialog
{
// 构造
public:
	CScreenWatchDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCREENWATCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStop();
	ScreenCap m_Cap;
	CString m_strStartTime;
	int m_nCount;


	void CapScreen();
	CString GetSystemCurTime();

};
