#include "stdafx.h"
#include "SerialProtocol.h"


CSerialProtocol::CSerialProtocol()
	: Verified(false)
	, SensorType(_T(""))
	, ResolovedStr(_T(""))
{
	memset(Pkg, 0, sizeof(Pkg));
}

CSerialProtocol::CSerialProtocol(const UCHAR * pPkg)
	: Verified(false)
	, SensorType(_T(""))
	, ResolovedStr(_T(""))
{
	solvePkg(pPkg);
}

CSerialProtocol::~CSerialProtocol()
{
}

int CSerialProtocol::setRawPkg(const UCHAR * pPkg)
{
	solvePkg(pPkg);

	if (Verified) return 0;
	else return -1;
}

CString CSerialProtocol::getResolvedStr()
{
	return ResolovedStr;
}

int CSerialProtocol::isVerified(const UCHAR code)
{
	UCHAR ans = 0;

	for (int i = 0; i <= PKG_SIZE; ++i) {
		ans += Pkg[i];
	}

	if (code == ans) return 0;
	else return -1;
}

bool CSerialProtocol::isVerified(void) 
{
	if (false == Verified) return false;
	else return true;
}

void CSerialProtocol::solvePkg(const UCHAR * pPkg) {

	//strncpy_s((char *)Pkg, (PKG_SIZE+1)*sizeof(UCHAR), (const char *)pPkg, PKG_SIZE + 1);
	memcpy_s(Pkg, (PKG_SIZE + 1)*sizeof(UCHAR), pPkg, (PKG_SIZE + 1)*sizeof(UCHAR));

	if (!isVerified(Pkg[PKG_SIZE])) {
		Verified = false;
		SensorType = "";
		ResolovedStr = "";
		return;
	}
	else {
		Verified = true;
	}
	
	switch (pPkg[0]) {
	case NAME_DHT11:
		SensorType = _T("DHT11");
		solveDHT11();
		break;
	case NAMR_BODYIR:
		SensorType = _T("BodyIR");
		solveBODYIR();
		break;
	default:
		SensorType = _T("Unknown");
		solveUnknown();
		break;
	}
}

void CSerialProtocol::solveDHT11(void) {
	LPWSTR wszTemp = new WCHAR[4];
	LPWSTR wszHumi = new WCHAR[4];
	wsprintf(wszTemp, _T("%u"), Pkg[1]);
	wsprintf(wszHumi, _T("%u"), Pkg[3]);

	ResolovedStr = _T("DHT11:");
	ResolovedStr.Append(_T("Temperature:"));
	ResolovedStr.Append(wszTemp);
	ResolovedStr.Append(_T(" "));
	ResolovedStr.Append(_T("Humidity:"));
	ResolovedStr.Append(wszHumi);
	ResolovedStr.Append(_T("."));

	delete wszTemp;
	delete wszHumi;
}

void CSerialProtocol::solveBODYIR(void)
{
	ResolovedStr = _T("BodyIR:");
	ResolovedStr.Append(Pkg[1] ? _T("ON") : _T("OFF"));
	ResolovedStr.Append(_T("."));
}

void CSerialProtocol::solveUnknown(void)
{
	ResolovedStr = _T("Unknown sensor.");
}
