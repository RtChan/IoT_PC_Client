
// PC_ClientDlg.h : ͷ�ļ�
//

#pragma once

#include "ClientSocket.h"
#include "afxcmn.h"
#include "afxwin.h"

// CPC_ClientDlg �Ի���
class CPC_ClientDlg : public CDialogEx
{
// ����
public:
	CPC_ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PC_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

// Socket���
public:
	bool m_connected;
	CClientSocket* pSock;
	//BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Dlg��Դ
public:
	void UpdateEvent(CString str);
	afx_msg void OnBnClickedButtonRun();
	UINT m_clientid;
	CString m_comSel;
	CEdit m_event;
	CComboBox m_combo;
	afx_msg void OnCbnSelchangeComboSerialport();
};
