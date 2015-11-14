
// PC_ClientDlg.h : 头文件
//

#pragma once

#include "ClientSocket.h"
#include "afxcmn.h"
#include "afxwin.h"

// CPC_ClientDlg 对话框
class CPC_ClientDlg : public CDialogEx
{
// 构造
public:
	CPC_ClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PC_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

// Socket相关
public:
	bool m_connected;
	CClientSocket* pSock;
	//BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Dlg资源
public:
	void UpdateEvent(CString str);
	afx_msg void OnBnClickedButtonRun();
	UINT m_clientid;
	CString m_comSel;
	CEdit m_event;
	CComboBox m_combo;
	afx_msg void OnCbnSelchangeComboSerialport();
};
