// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "PC_Client.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);
}

BOOL CClientSocket::SendMSG(LPSTR lpBuff, int nlen)
{
	if (Send(lpBuff, nlen) == SOCKET_ERROR) {
		AfxMessageBox(_T("发送错误！"));
		return FALSE;
	}
	return TRUE;
}