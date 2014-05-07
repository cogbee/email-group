
// teacher_wantDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "email.h"
#include "teacher_want.h"
#include "teacher_wantDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cteacher_wantDlg 对话框




Cteacher_wantDlg::Cteacher_wantDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cteacher_wantDlg::IDD, pParent)
	, email(_T(""))
	, passwd(_T(""))
	, filepath(_T(""))
	, suffix(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cteacher_wantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, email);
	DDX_Text(pDX, IDC_EDIT2, passwd);
	DDX_Text(pDX, IDC_EDIT3, filepath);
	DDX_CBString(pDX, IDC_COMBO1, suffix);
}

BEGIN_MESSAGE_MAP(Cteacher_wantDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT2, &Cteacher_wantDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cteacher_wantDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &Cteacher_wantDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &Cteacher_wantDlg::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Cteacher_wantDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// Cteacher_wantDlg 消息处理程序

BOOL Cteacher_wantDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cteacher_wantDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cteacher_wantDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cteacher_wantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cteacher_wantDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	// TODO:  在此添加控件通知处理程序代码
}


void Cteacher_wantDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog filedlg(true); 
    filedlg.m_ofn.lpstrTitle=_T("打开");
    filedlg.m_ofn.lpstrFilter=_T("Text Files(*.txt)/0*.txt/0All Files(*.*)/0*.*/0/0");

    if(IDOK == filedlg.DoModal())
	{       
		filepath=filedlg.GetPathName();
		UpdateData(FALSE);
	}
}


void Cteacher_wantDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	path = filepath;
	yourEmail = email + "@" + suffix;
	suffixOfEmail = suffix;
	yourPasswd = passwd;
	run();
	CDialogEx::OnOK();
}


void Cteacher_wantDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	// TODO:  在此添加控件通知处理程序代码
}


void Cteacher_wantDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
