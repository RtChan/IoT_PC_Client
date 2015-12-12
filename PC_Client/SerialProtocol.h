#pragma once
#include "stdafx.h"

#define PKG_SIZE 8

// ������ID����
#define NAME_DHT11		0x01
#define NAMR_BODYIR		0x02

class CSerialProtocol
{
// ����
public:
	CSerialProtocol();
	CSerialProtocol(const UCHAR *pPkg);
	~CSerialProtocol();


// ����
public:
	bool isVerified(void);
	int setRawPkg(const UCHAR *pPkg);
	CString getResolvedStr();
//	CString getResolvedStr(const UCHAR *pPkg);
//	CString getSensorType();
//	CString getSensorType(const UCHAR *pPkg);
//	int isVerified(const UCHAR *pPkg);
private:
	int isVerified(const UCHAR code);
	void solvePkg(const UCHAR * pPkg);


// ��Ա
private:
	CString SensorType;
	bool Verified;
	UCHAR Pkg[PKG_SIZE + 1];
	CString ResolovedStr;


// ��������������
private:
	void solveDHT11(void);
	void solveBODYIR(void);
	void solveUnknown(void);
};
