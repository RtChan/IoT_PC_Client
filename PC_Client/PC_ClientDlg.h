
// PC_ClientDlg.h : 头文件
//

#pragma once

#include "ClientSocket.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "SerialPort.h"

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

// SerialPort相关
public:
	CSerialPort m_SerialPort;	//SerialPort类
	bool m_bSerialPortOpened;	//判断串口是否打开
	UCHAR m_SerialRecv[9];		//串口接收存放

// Socket相关
public:
	bool m_connected;			//判断是否已连接服务器
	CClientSocket* pSock;		//Socket派生的ClientSocket类
	//BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);


// Dlg资源
public:
	void UpdateEvent(CString str);		//更新日志框
	UINT m_clientid;					//储存客户端ID
	int m_comSel;						//储存串口号
	CEdit m_event;
	CComboBox m_combo;
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnCbnSelchangeComboSerialport();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
