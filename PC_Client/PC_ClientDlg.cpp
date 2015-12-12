
// PC_ClientDlg.cpp : 实现文件
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


// CPC_ClientDlg 对话框



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
	ON_MESSAGE(WM_COMM_RXCHAR, OnComm)	// SerialPort消息映射
	ON_BN_CLICKED(ID_BUTTON_RUN, &CPC_ClientDlg::OnBnClickedButtonRun)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIALPORT, &CPC_ClientDlg::OnCbnSelchangeComboSerialport)
	ON_BN_CLICKED(IDCANCEL, &CPC_ClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPC_ClientDlg 消息处理程序

BOOL CPC_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//  设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 下拉列表组合框初始化
	CString str_port;
	char portnum[3];
	for (int i = 1; i < 16; ++i) {
		sprintf_s(portnum, "%d", i);
		str_port = portnum;
		str_port = _T("COM") + str_port;
		m_combo.AddString(str_port);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPC_ClientDlg::OnPaint()
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
			UpdateEvent(_T("错误的串口数据包"));
			
		str = m_pkg;
		AfxMessageBox(str);
	}

	return LRESULT();
}

void CPC_ClientDlg::UpdateEvent(CString str)
{
	CString string;
	
	CTime time = CTime::GetCurrentTime();						// 获取系统当前时间	
	str += _T("\r\n");											// 用于换行显示日志
	//string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;		// 格式化当前时间
	string = time.Format(_T("%H:%M:%S  ")) + str;

	int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);	//获取编辑框最后一行索引
	m_event.SetSel(lastLine + 1, lastLine + 2, 0);					//选择编辑框最后一行
	m_event.ReplaceSel(string);										//替换所选那一行的内容
}

void CPC_ClientDlg::OnBnClickedButtonRun()
{
	CString _str, _sel;

	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_combo.GetLBText(m_comSel - 1, _sel);

	// 串口相关处理
	if (!m_bSerialPortOpened) {
		if (m_SerialPort.InitPort(this, m_comSel, 115200, 'N', 8, 1, EV_RXFLAG | EV_RXCHAR, 512)) {
			m_SerialPort.StartMonitoring();
			m_bSerialPortOpened = true;

			_str = _T("串口");
			_str.Append(_sel);
			_str.Append(_T("打开成功"));
			UpdateEvent(_str);
			UpdateData(false);
		}
		else {
			AfxMessageBox(_T("串口打开失败！"));
			m_bSerialPortOpened = false;
		}
	}
	else {
		//m_SerialPort.ClosePort();
		//_str = _T("串口");
		//_str.Append(_sel);
		//_str.Append(_T("关闭"));
		//UpdateEvent(_str);
		//UpdateData(false);
	}

	// 获取IPAddressCtrl
	CIPAddressCtrl * pIP = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS);
	BYTE nf1, nf2, nf3, nf4;
	pIP->GetAddress(nf1, nf2, nf3, nf4);
	CString serverIPAddress;
	serverIPAddress.Format(_T("%d.%d.%d.%d"), nf1, nf2, nf3, nf4);

	// 启动socket连接
	if (m_connected) {
		pSock->Close();

		delete pSock;
		pSock = nullptr;

		m_connected = false;

		SetDlgItemText(ID_BUTTON_RUN, _T("运行客户端"));
		_str = _T("服务器");
		_str.Append(serverIPAddress);
		_str.Append(_T("已断开"));
		UpdateEvent(_str);
		UpdateData(false);
		return;
	}

	pSock = new CClientSocket();
	if (!pSock->Create()) {
		AfxMessageBox(_T("套接字创建失败！"));
		return;
	}

	if (!pSock->Connect(serverIPAddress, 6000)) {
		AfxMessageBox(_T("连接服务器失败！"));
		return;
	}

	m_connected = true;
	SetDlgItemText(ID_BUTTON_RUN, _T("断开连接"));
	_str = _T("服务器");
	_str.Append(serverIPAddress);
	_str.Append(_T("已连接"));
	UpdateEvent(_str);
	UpdateData(false);

	return;
}


void CPC_ClientDlg::OnCbnSelchangeComboSerialport()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = m_combo.GetCurSel();
	
	//获取CString型串口号
	//m_combo.GetLBText(sel, m_comSel);
	
	//获取int型串口号
	m_comSel = sel + 1;
}


void CPC_ClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_SerialPort.ClosePort();
	CDialogEx::OnCancel();
}
