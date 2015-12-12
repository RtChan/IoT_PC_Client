#pragma once
#include "stdafx.h"

#define PKG_SIZE 8

// 传感器ID定义
#define NAME_DHT11		0x01
#define NAMR_BODYIR		0x02

class CSerialProtocol
{
// 构造
public:
	CSerialProtocol();
	CSerialProtocol(const UCHAR *pPkg);
	~CSerialProtocol();


// 方法
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


// 成员
private:
	CString SensorType;
	bool Verified;
	UCHAR Pkg[PKG_SIZE + 1];
	CString ResolovedStr;


// 传感器解析方法
private:
	void solveDHT11(void);
	void solveBODYIR(void);
	void solveUnknown(void);
};
