// ClientSocket.cpp : ʵ���ļ�
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


// CClientSocket ��Ա����


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnReceive(nErrorCode);
}

BOOL CClientSocket::SendMSG(LPSTR lpBuff, int nlen)
{
	if (Send(lpBuff, nlen) == SOCKET_ERROR) {
		AfxMessageBox(_T("���ʹ���"));
		return FALSE;
	}
	return TRUE;
}