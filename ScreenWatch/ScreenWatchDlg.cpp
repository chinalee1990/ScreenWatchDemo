
// ScreenWatchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenWatch.h"
#include "ScreenWatchDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CScreenWatchDlg �Ի���




CScreenWatchDlg::CScreenWatchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenWatchDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenWatchDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_START, &CScreenWatchDlg::OnBnClickedBtnStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_BTN_STOP, &CScreenWatchDlg::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CScreenWatchDlg ��Ϣ��������

BOOL CScreenWatchDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ����Ӷ���ĳ�ʼ������
	m_nCount = 0;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CScreenWatchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScreenWatchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CScreenWatchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CScreenWatchDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_nCount=0;
	m_strStartTime = GetSystemCurTime();
	SetTimer(1,1000,NULL);
}

void CScreenWatchDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	KillTimer(1);
}

void CScreenWatchDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if(nIDEvent==1)
	{
		CapScreen();
	}
	CDialog::OnTimer(nIDEvent);
}

void CScreenWatchDlg::CapScreen()
{
	m_nCount++;
	m_Cap.StartCap(NULL,0,0);
	m_Cap.ExeCap(1920,1080);
	CString strSavePath;
	strSavePath.Format(_T("E:\\Save\\%d.png"),m_nCount);
	try
	{
		m_Cap.SaveCap(strSavePath);
	}
	catch(...)
	{
		TRACE("����ͼƬ����!");
	}
	m_Cap.m_Image.Destroy();
}

// ��ȡϵͳʱ��
CString CScreenWatchDlg::GetSystemCurTime()
{
	CTime time = CTime::GetCurrentTime();
	return time.Format(_T("%H:%M:%S"));
}