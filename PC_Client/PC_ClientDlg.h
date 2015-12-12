
// PC_ClientDlg.h : ͷ�ļ�
//

#pragma once

#include "ClientSocket.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "SerialPort.h"
#include "SerialProtocol.h"

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
	afx_msg LRESULT OnComm(WPARAM ch, LPARAM port);		// SerialPort ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// SerialPort���
public:
	CSerialPort m_SerialPort;	//SerialPort��
	bool m_bSerialPortOpened;	//�жϴ����Ƿ��
	UCHAR m_SerialRecv[PKG_SIZE + 1];		//���ڽ��մ��
	UCHAR m_pkg[PKG_SIZE + 1];				//��Ŵ��ڽ��յ������ݰ�
	CSerialProtocol m_SerialProtocol;

// Socket���
public:
	bool m_connected;			//�ж��Ƿ������ӷ�����
	CClientSocket* pSock;		//Socket������ClientSocket��
	//BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);


// Dlg��Դ
public:
	void UpdateEvent(CString str);		//������־��
	UINT m_clientid;					//����ͻ���ID
	int m_comSel;						//���洮�ں�
	CEdit m_event;
	CComboBox m_combo;
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnCbnSelchangeComboSerialport();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
};
