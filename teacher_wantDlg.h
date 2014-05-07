
// teacher_wantDlg.h : 头文件
//

#pragma once


// Cteacher_wantDlg 对话框
class Cteacher_wantDlg : public CDialogEx
{
// 构造
public:
	Cteacher_wantDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEACHER_WANT_DIALOG };

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
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
	CString email;
	CString passwd;
	afx_msg void OnBnClickedOk();
	CString filepath;
	afx_msg void OnEnChangeEdit1();
	CString suffix;
	afx_msg void OnCbnSelchangeCombo1();
};
