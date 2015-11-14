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
