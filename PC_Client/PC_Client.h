
// PC_Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPC_ClientApp: 
// �йش����ʵ�֣������ PC_Client.cpp
//

class CPC_ClientApp : public CWinApp
{
public:
	CPC_ClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPC_ClientApp theApp;