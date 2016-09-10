
// ScreenWatchDlg.h : ͷ�ļ�
//

#pragma once
#include "ScreenCap.h"

// CScreenWatchDlg �Ի���
class CScreenWatchDlg : public CDialog
{
// ����
public:
	CScreenWatchDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCREENWATCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
