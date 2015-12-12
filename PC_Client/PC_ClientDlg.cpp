
// PC_ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PC_Client.h"
#include "PC_ClientDlg.h"
#include "afxdialogex.h"

#include "ClientSocket.h"
#include "SerialProtocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPC_ClientDlg �Ի���



CPC_ClientDlg::CPC_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PC_CLIENT_DIALOG, pParent)
	, m_clientid(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPC_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERID, m_clientid);
	DDX_Control(pDX, IDC_EDIT_EVENT, m_event);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT, m_combo);
}

BEGIN_MESSAGE_MAP(CPC_ClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)	// SerialPort��Ϣӳ��
	ON_BN_CLICKED(ID_BUTTON_RUN, &CPC_ClientDlg::OnBnClickedButtonRun)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIALPORT, &CPC_ClientDlg::OnCbnSelchangeComboSerialport)
	ON_BN_CLICKED(IDCANCEL, &CPC_ClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPC_ClientDlg ��Ϣ�������

BOOL CPC_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//  ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	// �����б���Ͽ��ʼ��
	CString str_port;
	char portnum[3];
	for (int i = 1; i < 16; ++i) {
		sprintf_s(portnum, "%d", i);
		str_port = portnum;
		str_port = _T("COM") + str_port;
		m_combo.AddString(str_port);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPC_ClientDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPC_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CPC_ClientDlg::OnComm(WPARAM ch, LPARAM port)
{
	static int i = 0;
	CString str;

	m_pkg[i++] = ch;

	if (i == PKG_SIZE) {
		i = 0;
		m_pkg[PKG_SIZE] = '\0';
		m_SerialProtocol.setRawPkg(m_pkg);
		if (m_SerialProtocol.isVerified()) 
			UpdateEvent(m_SerialProtocol.getResolvedStr());
		else
			UpdateEvent(_T("����Ĵ������ݰ�"));
			
		str = m_pkg;
		AfxMessageBox(str);
	}

	return LRESULT();
}

void CPC_ClientDlg::UpdateEvent(CString str)
{
	CString string;
	
	CTime time = CTime::GetCurrentTime();						// ��ȡϵͳ��ǰʱ��	
	str += _T("\r\n");											// ���ڻ�����ʾ��־
	//string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;		// ��ʽ����ǰʱ��
	string = time.Format(_T("%H:%M:%S  ")) + str;

	int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);	//��ȡ�༭�����һ������
	m_event.SetSel(lastLine + 1, lastLine + 2, 0);					//ѡ��༭�����һ��
	m_event.ReplaceSel(string);										//�滻��ѡ��һ�е�����
}

void CPC_ClientDlg::OnBnClickedButtonRun()
{
	CString _str, _sel;

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	m_combo.GetLBText(m_comSel - 1, _sel);

	// ������ش���
	if (!m_bSerialPortOpened) {
		if (m_SerialPort.InitPort(this, m_comSel, 115200, 'N', 8, 1, EV_RXFLAG | EV_RXCHAR, 512)) {
			m_SerialPort.StartMonitoring();
			m_bSerialPortOpened = true;

			_str = _T("����");
			_str.Append(_sel);
			_str.Append(_T("�򿪳ɹ�"));
			UpdateEvent(_str);
			UpdateData(false);
		}
		else {
			AfxMessageBox(_T("���ڴ�ʧ�ܣ�"));
			m_bSerialPortOpened = false;
		}
	}
	else {
		//m_SerialPort.ClosePort();
		//_str = _T("����");
		//_str.Append(_sel);
		//_str.Append(_T("�ر�"));
		//UpdateEvent(_str);
		//UpdateData(false);
	}

	// ��ȡIPAddressCtrl
	CIPAddressCtrl * pIP = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS);
	BYTE nf1, nf2, nf3, nf4;
	pIP->GetAddress(nf1, nf2, nf3, nf4);
	CString serverIPAddress;
	serverIPAddress.Format(_T("%d.%d.%d.%d"), nf1, nf2, nf3, nf4);

	// ����socket����
	if (m_connected) {
		pSock->Close();

		delete pSock;
		pSock = nullptr;

		m_connected = false;

		SetDlgItemText(ID_BUTTON_RUN, _T("���пͻ���"));
		_str = _T("������");
		_str.Append(serverIPAddress);
		_str.Append(_T("�ѶϿ�"));
		UpdateEvent(_str);
		UpdateData(false);
		return;
	}

	pSock = new CClientSocket();
	if (!pSock->Create()) {
		AfxMessageBox(_T("�׽��ִ���ʧ�ܣ�"));
		return;
	}

	if (!pSock->Connect(serverIPAddress, 6000)) {
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));
		return;
	}

	m_connected = true;
	SetDlgItemText(ID_BUTTON_RUN, _T("�Ͽ�����"));
	_str = _T("������");
	_str.Append(serverIPAddress);
	_str.Append(_T("������"));
	UpdateEvent(_str);
	UpdateData(false);

	return;
}


void CPC_ClientDlg::OnCbnSelchangeComboSerialport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel = m_combo.GetCurSel();
	
	//��ȡCString�ʹ��ں�
	//m_combo.GetLBText(sel, m_comSel);
	
	//��ȡint�ʹ��ں�
	m_comSel = sel + 1;
}


void CPC_ClientDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_SerialPort.ClosePort();
	CDialogEx::OnCancel();
}
