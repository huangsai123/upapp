// Uart.cpp: implementation of the CUart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PcCtrl.h"
#include "Uart.h"
#include "time.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif





/**********************************************************************+/
2019/5/13 1 串口读取数据时系统占用资源过高问题
          2 读回版本界面显示错误




/************************************************************************/









unsigned short crc16_ccitt(unsigned char *bbuf, int len)
{
	const unsigned short ccitt_table[256] = {
		0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
		0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
		0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
		0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
		0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
		0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
		0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
		0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
		0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
		0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
		0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
		0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
		0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
		0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
		0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
		0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
		0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
		0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
		0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
		0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
		0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
		0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
		0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
		0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
		0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
		0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
		0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
		0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
		0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
		0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
		0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
		0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
	};

	unsigned short crc=0;
	while(len--)
	{
		crc = (crc<<8)^ccitt_table[((crc>>8) ^ *bbuf++) & 0x00FF];
	}
	
	return crc;
}


void CUart::DbgPrintf(char *fmt,...)
{
	size_t l;
	static char bf[4096];

	va_list vl;
	va_start(vl,fmt);
	l = vsprintf(bf,fmt,vl);
	va_end(vl);

	if(m_fpLog)
	{
		fwrite(bf,1,l,m_fpLog);
		fflush(m_fpLog);
	}
	printf(bf);
}

void CUart::Msg(int bc,char* fmt,...)
{
	static char bf[4096];
	va_list vl;
	va_start(vl,fmt);
	vsprintf(bf,fmt,vl);
	va_end(vl);
	SendMessage(m_hWind,WM_ONTXTMSG,(WPARAM)bf,(LPARAM)bc);
}



CUart::CUart()
{
	InitializeCriticalSection(&cs);
	InitializeCriticalSection(&csPrint);

	m_IsOpened = FALSE;
	
	m_hEvtSend = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEvtRecv = CreateEvent(NULL, FALSE, FALSE, NULL);

	m_usZhennum = rand()&0x7FFF;

	m_fpLog = NULL;

	m_hComHandle = INVALID_HANDLE_VALUE;
	m_skt = INVALID_SOCKET;
	m_rxThread = INVALID_HANDLE_VALUE;
}

void CUart::CanID(int iCanID)
{
	switch(iCanID)
	{
	default:
	case 0:m_ucCanID = 0x01;break;
	case 1:m_ucCanID = 0x02;break;
	case 2:m_ucCanID = 0x04;break;
	case 3:m_ucCanID = 0x11;break;
	}
}

BOOL CUart::Open(char *pIPStr, int iCI,HWND hWind,int port,char* addr)
{
	static const unsigned char ucData1[] = {0x02,0x0F,0x00,0x00,0x59,0xC1};
	static const unsigned char ucData2[] = {0x02,0x51,0x00,0xEE,0x53,0xC1};
	struct WSAData wsaData;
	struct sockaddr_in sadd;
	int sock;

	if(sscanf(addr,"%02x%02x%02x%02x%02x%02x%02x%02x"
		,&m_ucDevAddr[0],&m_ucDevAddr[1]
		,&m_ucDevAddr[2],&m_ucDevAddr[3]
		,&m_ucDevAddr[4],&m_ucDevAddr[5]
		,&m_ucDevAddr[6],&m_ucDevAddr[7]
		)!=8)return 0;

	if(m_IsOpened)
	{
		Close();
	}
	m_hComHandle = INVALID_HANDLE_VALUE;
	
	if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0)
	{
		return FALSE;
	}
	
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET)
	{
		return FALSE;
	}
	
	memset(&sadd, 0, sizeof(struct sockaddr_in));
	sadd.sin_family = AF_INET;
	sadd.sin_addr.s_addr = htonl(INADDR_ANY);
	sadd.sin_port = htons(5006);
	
	if(bind(sock, (struct sockaddr*)&sadd, sizeof(sadd)) == SOCKET_ERROR)
	{
		closesocket(sock);
		return 0;
	}

	memset(&m_gwAddr, 0, sizeof(m_gwAddr));
	m_gwAddr.sin_family = AF_INET;
	m_gwAddr.sin_addr.s_addr = inet_addr(pIPStr);
	m_gwAddr.sin_port = htons(port);
	
	m_skt = sock;

	m_RecvThreadStopFlag = FALSE;
	m_rxThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)UDPRecvThread,this,NULL,NULL);
	
	m_IsOpened = TRUE;

	m_iCI = iCI;
	m_hWind = hWind;
	m_uiRxLen = 0;
	
	m_UpgradeCtrl.uiStep = US_IDLE;
	m_usErrRxLen = 0;
	
	m_fpLog = fopen("./log.txt","ab+");

	if(sendto(m_skt,(const char*)ucData1,6,0,(struct sockaddr*)&m_gwAddr,sizeof(m_gwAddr)) != 6)
	{
		Close();
		return FALSE;
	}
	if(sendto(m_skt,(const char*)ucData2,5,0,(struct sockaddr*)&m_gwAddr,sizeof(m_gwAddr)) != 5)
	{
		Close();
		return FALSE;
	}

	return TRUE;
}
BOOL CUart::Open(char *pComStr, int iCI,HWND hWind,int iCanID)
{
	CanID(iCanID);

	if(m_IsOpened)
	{
		Close();
	}
	m_skt = INVALID_SOCKET;

	char uN[256];	
	sprintf(uN,"\\\\.\\%s",pComStr);
	m_hComHandle = ::CreateFile(uN,
		GENERIC_READ|GENERIC_WRITE,0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL);
	if(m_hComHandle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	PurgeComm(m_hComHandle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	
	if(SetupComm(m_hComHandle, 1024*4, 1024*4) == FALSE)
	{
		CloseHandle(m_hComHandle);
		return FALSE;
	}

	DCB m_DCB;
	m_DCB.DCBlength = sizeof(DCB);
	if(GetCommState(m_hComHandle, &m_DCB) == FALSE)
	{
		CloseHandle(m_hComHandle);
		return FALSE;
	}
	else
	{
		m_DCB.BaudRate     = (iCI==US_CANFROM)?460800:9600;
		m_DCB.ByteSize     = 8;
		m_DCB.Parity       = NOPARITY;
		m_DCB.StopBits     = ONESTOPBIT;
		m_DCB.fDtrControl  = 0;
		m_DCB.fRtsControl  = RTS_CONTROL_DISABLE;
		
		if(SetCommState(m_hComHandle, &m_DCB) == FALSE)
		{
			CloseHandle(m_hComHandle);
			return FALSE;
		}
	}
	
	COMMTIMEOUTS TimeOuts;
	TimeOuts.ReadIntervalTimeout = 1;
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.ReadTotalTimeoutConstant = 0;
	
	TimeOuts.WriteTotalTimeoutMultiplier = 0;
	TimeOuts.WriteTotalTimeoutConstant = 0;
	
	SetCommTimeouts(m_hComHandle,&TimeOuts);

	memset(&m_oSend, 0, sizeof(OVERLAPPED));
	memset(&m_oRecv, 0, sizeof(OVERLAPPED));
	
	m_RecvThreadStopFlag = FALSE;
	m_rxThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)RecvThread,this,NULL,NULL);
	m_IsOpened = TRUE;

	m_iCI = iCI;
	m_hWind = hWind;
	m_uiRxLen = 0;
	
	m_UpgradeCtrl.uiStep = US_IDLE;
	m_usErrRxLen = 0;

	m_fpLog = fopen("./log.txt","ab+");

	return TRUE;
}
void CUart::Close()
{
	m_RecvThreadStopFlag = TRUE;
	if(m_skt != INVALID_SOCKET)
	{
		closesocket(m_skt);
		m_skt = INVALID_SOCKET;
	}
	if(m_hComHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hComHandle);
		m_hComHandle = INVALID_HANDLE_VALUE;
	}
	if(m_rxThread != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject(m_rxThread,INFINITE);
		CloseHandle(m_rxThread);
		m_rxThread = INVALID_HANDLE_VALUE;
	}	
	m_IsOpened = FALSE;

	if(m_fpLog)
	{
		fclose(m_fpLog);
		m_fpLog = NULL;
	}
}

void CUart::PrintTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	DbgPrintf("%02d:%02d:%02d.%03d ",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
}

void CUart::UDPRecvThreadLoop()
{
	fd_set rfd;
	timeval to;

	unsigned char buf[256],prefix[16]={0x02,0x55,0x00,0x49,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x88,0x00,0x02};
	struct sockaddr_in sadd;
	int n,i,adl;
	unsigned short crc,rcrc;
	memcpy(prefix+3,m_ucDevAddr,8);
	adl = sizeof(sadd);

	for(;;)
	{
		if(m_RecvThreadStopFlag)break;

		
		if(m_UpgradeCtrl.uiStep)
		{
			EnterCriticalSection(&cs);
			if(m_UpgradeCtrl.uiStep)
			{
				WiapaUpgradeRecvMsg(NULL,0);
			}
			LeaveCriticalSection(&cs);
		}

		to.tv_sec = 1;
		to.tv_usec= 0;

		FD_ZERO(&rfd);
		FD_SET(m_skt,&rfd);
		
		n = select(m_skt+1,&rfd,NULL,NULL,&to);
		if(n <= 0 || !FD_ISSET(m_skt,&rfd))continue;

		n = recvfrom(m_skt,(char*)buf,128,0,(struct sockaddr*)&sadd,&adl);
		if(n <= 0)continue;
		EnterCriticalSection(&csPrint);
		PrintTime();
		DbgPrintf("udp +++::%02d:",n);
		for(i = 0; i < n; i++)
		{
			DbgPrintf("%02X ",buf[i]);
		}
		DbgPrintf("\r\n");
		LeaveCriticalSection(&csPrint);
		if(n > 13 && !memcmp(prefix,buf,13))
		{
			rcrc   = buf[--n];
			rcrc <<= 8;
			rcrc  |= buf[--n];
			crc = crc16_ccitt(buf,n);
			if(crc == rcrc)
			{
				n -= 13;
				if(m_UpgradeCtrl.uiStep)
				{
					EnterCriticalSection(&cs);
					if(m_UpgradeCtrl.uiStep)
					{
						WiapaUpgradeRecvMsg(buf+13,n);
					}
					LeaveCriticalSection(&cs);
				}
				PrintRecvFrame(buf+13,n);
			}
		}
	}
}
int CUart::DoSendUdp(unsigned char ucLen,unsigned char* pData)
{
	static unsigned short udpSn = rand();
	int i;
	unsigned short crc;
	unsigned char TxBuffer[1024];
	if(!IsOpened() || !ucLen)
	{
		return 0;
	}
	TxBuffer[0] = 0x02;
	TxBuffer[1] = 0x54;
	TxBuffer[2] = 0x00;
	memcpy(TxBuffer+3,m_ucDevAddr,8);
	TxBuffer[11] = 0x00;
	TxBuffer[12] = 0x02;
	udpSn++;
	TxBuffer[13] = (unsigned char)(udpSn);
	TxBuffer[14] = (unsigned char)(udpSn>>8);
	memcpy(TxBuffer+15,pData,ucLen);
	ucLen += 15;
	crc = crc16_ccitt(TxBuffer,ucLen);
	TxBuffer[ucLen++] = (unsigned char)crc;
	TxBuffer[ucLen++] = (unsigned char)(crc>>8);

	EnterCriticalSection(&csPrint);
	PrintTime();
	DbgPrintf("UDP ---::%02d:",ucLen);
	for(i = 0; i < ucLen; i++)
	{
		DbgPrintf("%02X ",TxBuffer[i]);
	}
	DbgPrintf("\r\n");
	LeaveCriticalSection(&csPrint);
	
	return sendto(m_skt,(const char*)TxBuffer,ucLen,0,(struct sockaddr*)&m_gwAddr,sizeof(m_gwAddr))==ucLen;
}

int CUart::SendUdp(unsigned char ucLen,unsigned char* pData)
{
	int ret;
	EnterCriticalSection(&cs);
	ret = DoSendUdp(ucLen,pData);
	LeaveCriticalSection(&cs);
	return ret;
}

void CUart::RecvThreadLoop()
{
	static BYTE buf[256];	
	DWORD nr;

	memset(&m_oRecv,0,sizeof(OVERLAPPED));
	m_oRecv.hEvent = m_hEvtRecv;
	for(;;)
	{
		if(m_RecvThreadStopFlag)return;
		nr = 0;
		if(!ReadFile(m_hComHandle, buf, sizeof(buf), &nr, &m_oRecv) && GetLastError() == ERROR_IO_PENDING)
		{
RR:
			if(WaitForSingleObject(m_oRecv.hEvent, 1000) == WAIT_OBJECT_0)
			{
				GetOverlappedResult(m_hComHandle, &m_oRecv, &nr, FALSE);
			}
			else
			{
				if(m_RecvThreadStopFlag)return;
				OnRecvBuf(buf, nr);
				goto RR;
			}
		}
		OnRecvBuf(buf, nr);
	}
}
void CUart::OnRecvBuf(unsigned char *pData,int iLen)
{
	if(iLen <= 0)
	{//overtime
		if(m_iCI == US_CANFROM)//can
		{
			if(m_UpgradeCtrl.uiStep)
			{
				UpgradeRecvMsg(US_CANFROM,NULL,0);
			}
		}
		else
		{
			if(m_UpgradeCtrl.uiStep)
			{
				UpgradeRecvMsg(US_COMFROM,NULL,0);
			}
		}
	}
	else
	{
		if(m_iCI == US_CANFROM)//can
		{
			while(iLen--)
			{
				CanOnRecvChar(*pData++);
			}
		}
		else
		{
			while(iLen--)
			{
				ComOnRecvChar(*pData++);
			}
		}
	}
}

int CUart::SendData(unsigned char* pData,unsigned int uiLen)
{
	DWORD dwLen,nw = 0;
	unsigned char* pc;
	
	if(!IsOpened() || !uiLen)
	{
		return 0;
	}
	
	dwLen = uiLen;
	
	EnterCriticalSection(&csPrint);
	PrintTime();
	DbgPrintf("%s ---::%02u:",m_iCI==US_CANFROM?"CAN":"COM",uiLen);
	pc = pData;
	while(uiLen--)DbgPrintf("%02X ",*pc++);
	DbgPrintf("\r\n");
	LeaveCriticalSection(&csPrint);
#if 1
	memset(&m_oSend,0,sizeof(OVERLAPPED));
	m_oSend.hEvent = m_hEvtSend;	
	if(!WriteFile(m_hComHandle, pData, dwLen, &nw, &m_oSend))
	{
		if(GetLastError() == ERROR_IO_PENDING)
		{
			GetOverlappedResult(m_hComHandle, &m_oSend, &nw, TRUE);
			m_oSend.Offset += nw;
		}
		else
		{
			return 0;
		}
	}
#else
	WriteFile(m_hComHandle, pData, dwLen, &nw, NULL);
	DbgPrintf("TxEnd\r\n");
#endif
	return nw;
}


int CUart::SendCan(unsigned char ucFunID,unsigned char* pData)
{
	unsigned char TxBuffer[32];
	TxBuffer[0] = 0xAA;
	TxBuffer[1] = 0x01;
	TxBuffer[2] = 0x00;
	TxBuffer[3] = 0x08;
	TxBuffer[4] = 0x00;
	TxBuffer[5] = ucFunID;
	TxBuffer[6] = 0x03;
	TxBuffer[7] = m_ucCanID;
	memcpy(TxBuffer+8,pData,8);
	return SendData(TxBuffer,16);
}



int memIsByte(unsigned char b,unsigned char *pd,int dl)
{
	while(dl--)
	{
		if(*pd++ != b)return 0;
	}
	return 1;
}

void CUart::CanOnRecFrame(unsigned char ucCmd,unsigned char *pc)
{
	int16_t   sXx;
	uint16_t usXx,usXx1;
	unsigned int uiXx;
	unsigned char ucXx;

	if(CANUPGRADECMD == ucCmd)
	{
		if(m_UpgradeCtrl.uiStep)
		{
			UpgradeRecvMsg(US_CANFROM,pc,8);
		}
		return;
	}

	SendMessage(m_hWind,WM_ONCANMSG,(WPARAM)pc,(LPARAM)ucCmd);

	EnterCriticalSection(&csPrint);
	switch(ucCmd)
	{
	case 0x00:
		DbgPrintf("故障信息:\r\n");
		DbgPrintf("指令:%s\r\n",pc[0]?"错误":"正常");
		DbgPrintf("温度传感器:%s\r\n",pc[1]?"错误":"正常");
		DbgPrintf("湿度传感器:%s\r\n",pc[2]?"错误":"正常");
		DbgPrintf("内压传感器:%s\r\n",pc[3]?"错误":"正常");
		DbgPrintf("外压传感器:%s\r\n",pc[4]?"错误":"正常");
		DbgPrintf("振动传感器:%s\r\n",pc[5]?"错误":"正常");
		DbgPrintf("振动超限故障:%s\r\n",pc[6]?"错误":"正常");
		DbgPrintf("压差超限故障:%s\r\n",pc[7]?"错误":"正常");
		break;
	case 0x01:
		DbgPrintf("读取初始化信息:\r\n");
		if(pc[0] == 0x00)DbgPrintf("设备状态:未知\r\n");
		else if(pc[0] == 0x0F)DbgPrintf("设备状态:正常\r\n");
		else if(pc[0] == 0xF0)DbgPrintf("设备状态:异常\r\n");
		DbgPrintf("传感器:%s\r\n",pc[1] == 0x55?"正常":"异常");
		DbgPrintf("自检通信:%s\r\n",pc[2] == 0x55?"正常":"异常");
		DbgPrintf("自检数据:%s\r\n",pc[3] == 0x55?"正常":"异常");
		DbgPrintf("接口初始化:%s\r\n",pc[4] == 0x55?"正常":"异常");
		if(pc[5] == 0x01)DbgPrintf("查询发送方式\r\n");
		else if(pc[5] == 0x02)DbgPrintf("循环发送方式\r\n");
		else if(pc[5] == 0x03)DbgPrintf("中断发送方式\r\n");
		if(pc[6] == 0x02)DbgPrintf("通信速率 250kbps\r\n");
		else if(pc[6] == 0x03)DbgPrintf("通信速率 500kbps\r\n");
		else if(pc[6] == 0x04)DbgPrintf("通信速率 1000kbps\r\n");
		DbgPrintf("记录仪ID:%02X\r\n",pc[7]);
		break;
	case 0x04:
		DbgPrintf("查询实时采集数据:\r\n");
		if(pc[0] == 0x00)
		{
			usXx = (pc[1]<<8)|pc[2];
			DbgPrintf("温度:%d.%d\r\n",usXx/10,usXx%10);
			usXx = (pc[3]<<8)|pc[4];
			DbgPrintf("湿度:%d.%d\r\n",usXx/10,usXx%10);
			usXx = (pc[5]<<8)|pc[6];
			sXx = usXx;
			DbgPrintf("压差:%0.1f\r\n",((float)sXx)/10);
		}
		else if(pc[0] == 0x01)
		{
			ucXx = pc[1];
			DbgPrintf("温度传感器:%s\r\n",(ucXx&0x02)?"故障":"正常");
			DbgPrintf("湿度传感器:%s\r\n",(ucXx&0x04)?"故障":"正常");
			DbgPrintf("内压传感器:%s\r\n",(ucXx&0x08)?"故障":"正常");
			DbgPrintf("外压传感器:%s\r\n",(ucXx&0x10)?"故障":"正常");
			DbgPrintf("振动传感器:%s\r\n",(ucXx&0x20)?"故障":"正常");
			DbgPrintf("振动超限:%s\r\n",(ucXx&0x40)?"故障":"正常");
			DbgPrintf("电量(程序中为电量,文档为压差):%s\r\n",(ucXx&0x80)?"故障":"正常");
			DbgPrintf("电量:%d%%\r\n",pc[2]);
			usXx = (pc[3]<<8)|pc[4];
			DbgPrintf("内压:%d.%d\r\n",usXx/10,usXx%10);
			usXx = (pc[5]<<8)|pc[6];
			DbgPrintf("外压:%d.%d\r\n",usXx/10,usXx%10);
		}
		break;
	case 0x05:
		if(memIsByte(0xFF,pc,8))
		{
			DbgPrintf("无温湿压记录\r\n");
		}
		else
		{
			usXx = (pc[0]<<8) | pc[1];
			DbgPrintf("温湿压记录,包序号:%u ",usXx);
			switch(usXx)
			{
			case 0x00:
				usXx = (pc[2]<<8) | pc[3];
				usXx1= (pc[4]<<8) | pc[5];
				DbgPrintf("包数:%u 条数:%u",usXx,usXx1);
				break;
			case 0x01:
				uiXx = (pc[2]<<24) | (pc[3]<<16) | (pc[4]<<8) | (pc[5]<<0);
				DbgPrintf("编号:%u %u年%u月",uiXx,pc[6],pc[7]);
				break;
			case 0x02:
				usXx = (pc[6]<<8) | pc[7];
				DbgPrintf("%u日%u时%u分%u秒 温度:%d.%d",pc[2],pc[3],pc[4],pc[5],usXx/10,usXx%10);
				break;
			case 0x03:
				usXx = (pc[2]<<8) | pc[3];
				usXx1= (pc[4]<<8) | pc[5];
				uiXx = (pc[6]<<8) | pc[7];
				DbgPrintf("湿度:%d.%d 压差:%d.%d 电量:%d.%d",usXx/10,usXx%10,usXx1/10,usXx1%10,uiXx/10,uiXx%10);
				break;
			case 0x04:
				usXx = (pc[2]<<8) | pc[3];
				usXx1= (pc[4]<<8) | pc[5];
				uiXx = (pc[6]<<8) | pc[7];
				DbgPrintf("X-G:%d.%d ",usXx/100,usXx%100);
				DbgPrintf("Y-G:%d.%d ",usXx1/100,usXx1%100);
				DbgPrintf("Z-G:%d.%d ",uiXx/100,uiXx%100);
				break;
			case 0x05:
				usXx = (pc[2]<<8) | pc[3];
				usXx1= (pc[4]<<8) | pc[5];
				uiXx = (pc[6]<<8) | pc[7];
				if(uiXx == 0xFFFF)
				{
					DbgPrintf("内压:%d.%d 外压:%d.%d 条号:最后一条",usXx/10,usXx%10,usXx1/10,usXx1%10,uiXx);
				}
				else
				{
					DbgPrintf("内压:%d.%d 外压:%d.%d 条号:%u",usXx/10,usXx%10,usXx1/10,usXx1%10,uiXx);
				}
				break;
			}
			DbgPrintf("\r\n");
		}
		break;
	case 0x06:
		if(memIsByte(0xFF,pc,8))
		{
			DbgPrintf("无振动记录\r\n");
		}
		else
		{
			usXx = (pc[0]<<8) | pc[1];
			DbgPrintf("振动记录,包序号:%u ",usXx);
			switch(usXx)
			{
			case 0x00:
				usXx = (pc[2]<<8) | pc[3];
				usXx1= (pc[4]<<8) | pc[5];
				DbgPrintf("包数:%u 条数:%u",usXx,usXx1);
				break;
			case 0x01:
				uiXx = (pc[2]<<24) | (pc[3]<<16) | (pc[4]<<8) | (pc[5]<<0);
				DbgPrintf("编号:%u %u年%u月",uiXx,pc[6],pc[7]);
				break;
			case 0x02:
				DbgPrintf("%u日%u时%u分%u秒",pc[2],pc[3],pc[4],pc[5]);
				break;
			default:
				if(usXx == 1003)
				{
					usXx = (pc[2]<<8) | pc[3];
					if(usXx == 0xFFFF)
					{
						DbgPrintf("条号:最后一条");
					}
					else
					{
						DbgPrintf("条号:%u",usXx);
					}
				}
				else
				{
					//*
					usXx = (pc[2]<<8) | pc[3];
					usXx1= (pc[4]<<8) | pc[5];
					uiXx = (pc[6]<<8) | pc[7];
					DbgPrintf("X-G:%d.%d ",usXx/100,usXx%100);
					DbgPrintf("Y-G:%d.%d ",usXx1/100,usXx1%100);
					DbgPrintf("Z-G:%d.%d ",uiXx/100,uiXx%100);
					//*/
				}
				break;
			}
			DbgPrintf("\r\n");
		}
		break;
	case 0x07:
		DbgPrintf("时间同步:%02d/%02d/%02d %02d:%02d:%02d\r\n",pc[0],pc[1],pc[2],pc[3],pc[4],pc[5]);
		break;
	case 0x08:
		DbgPrintf("设置参数:振动门限 %u;采集周期 %u [%d秒];",pc[0],((pc[1]<<8)|pc[2]),((pc[1]<<8)|pc[2])*10);
		if(pc[7] == 0x00)DbgPrintf("参数设置成功");
		else if(pc[7] == 0x01)DbgPrintf("参数设置失败");
		else if(pc[7] == 0x02)DbgPrintf("参数读取成功");
		else if(pc[7] == 0x03)DbgPrintf("参数读取失败");
		DbgPrintf("\r\n");
		break;
	case 0x09:
		DbgPrintf("历史温湿度数据擦除:%s\r\n",pc[0]==0x00?"成功":"失败");
		break;
	case 0x0A:
		DbgPrintf("历史振动数据擦除:%s\r\n",pc[0]==0x00?"成功":"失败");
		break;
	case 0x0C:
		DbgPrintf("箱号:%c%c%c%c%c%c%c ",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		if(pc[0] == 0x00)DbgPrintf("设置成功");
		else if(pc[0] == 0x01)DbgPrintf("设置失败");
		else if(pc[0] == 0x02)DbgPrintf("读取成功");
		else if(pc[0] == 0x03)DbgPrintf("读取失败");
		DbgPrintf("\r\n");
		break;
	case 0x0D:
		DbgPrintf("弹号:%c%c%c%c%c%c%c ",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		if(pc[0] == 0x00)DbgPrintf("设置成功");
		else if(pc[0] == 0x01)DbgPrintf("设置失败");
		else if(pc[0] == 0x02)DbgPrintf("读取成功");
		else if(pc[0] == 0x03)DbgPrintf("读取失败");
		DbgPrintf("\r\n");
		break;
	case 0x0E:
		DbgPrintf("+++查询+++\r\n设备软件版本:%d.%d.%d\r\n设备硬件版本:%d.%d.%d\r\n",pc[0],pc[1],pc[2],pc[3],pc[4],pc[5]);
		break;

	case CANEXTCMD:
		if(pc[0] == 0x02)
		{
			DbgPrintf("设备时间:%02d/%02d/%02d %02d:%02d:%02d\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6]);
		}
		break;
	}
	LeaveCriticalSection(&csPrint);
}

void CUart::CanOnRecvChar(unsigned char c)
{
	int i;
	m_ucRxData[m_uiRxLen++] = c;
	if(m_uiRxLen < 16)return;

	if(	   m_ucRxData[0] != 0xAA
		|| m_ucRxData[1] != 0x01
		|| m_ucRxData[2] != 0x00
		|| m_ucRxData[3] != 0x08

		|| m_ucRxData[4] != 0x01
		|| m_ucRxData[6] != m_ucCanID
		|| m_ucRxData[7] != 0x03
		)
	{
		m_ucErrRxData[m_usErrRxLen++] = m_ucRxData[0];
		for(i = 0; i < 15; i++)
		{
			m_ucRxData[i] = m_ucRxData[i +1];
		}
		m_uiRxLen = 15;
		return;
	}
	EnterCriticalSection(&csPrint);
	if(m_usErrRxLen)
	{
		PrintTime();
		DbgPrintf("Com.Error +++:");
		for(i = 0; i < m_usErrRxLen; i++)
		{
			DbgPrintf("%02X ",m_ucErrRxData[i]);
		}
		DbgPrintf("\r\n");
		m_usErrRxLen = 0;
	}
	PrintTime();
	DbgPrintf("CAN +++::16:");
	for(i = 0; i < 16; i++)
	{
		DbgPrintf("%02X ",m_ucRxData[i]);
	}
	DbgPrintf("\r\n");
	LeaveCriticalSection(&csPrint);
	CanOnRecFrame(m_ucRxData[5],m_ucRxData+8);

	m_uiRxLen = 0;
}
void CUart::ComOnRecvChar(unsigned char c)
{
	int i;
	unsigned short crc,crcr;

	m_ucErrRxData[m_usErrRxLen++] = c;
	if(c == 0x7E)
	{
		if(!m_uiRxLen)return;
		if(m_usErrRxLen)
		{
			EnterCriticalSection(&csPrint);
			PrintTime();
			DbgPrintf("Com +++::%02u:",m_usErrRxLen);
			for(i = 0; i < m_usErrRxLen; i++)
			{
				DbgPrintf("%02X ",m_ucErrRxData[i]);
			}
			DbgPrintf("\r\n");
			LeaveCriticalSection(&csPrint);
			m_usErrRxLen = 0;
		}
		if(m_uiRxLen >=5)
		{
			crcr   = m_ucRxData[--m_uiRxLen];
			crcr <<= 8;
			crcr  |= m_ucRxData[--m_uiRxLen];

			crc = crc16_ccitt(m_ucRxData,m_uiRxLen);
			if(crc != crcr)
			{
				DbgPrintf("CRC Error\r\n");
			}
			else 
			{
				ProcessRecvFrame(m_ucRxData,m_uiRxLen);
			}
		}
		m_ucLastChar = 0;
		m_uiRxLen = 0;
	}
	else
	{
		if(m_uiRxLen >= 256)
		{
			m_uiRxLen = 0;
			DbgPrintf("Data Length Error\r\n");
		}
		else
		{
			if(m_ucLastChar == 0x7D)
			{
				if(c == 0x5E)
				{
					m_ucRxData[m_uiRxLen++] = 0x7E;
				}
				else if(c == 0x5D)
				{
					m_ucRxData[m_uiRxLen++] = 0x7D;
				}
				else
				{
					m_ucRxData[m_uiRxLen++] = 0x7E;
					if(c != 0x7D)
					{
						m_ucRxData[m_uiRxLen++] = c;
					}
				}
			}
			else
			{
				if(c != 0x7D)
				{
					m_ucRxData[m_uiRxLen++] = c;
				}
			}
			m_ucLastChar = c;
		}
	}
}






void CUart::UpgradeRecvMsg(unsigned int from,unsigned char *pData,unsigned char dl)
{
	unsigned int  tn = time(0);
	unsigned char  ucLen,ucUsCmd,ucSn,ucUsErr,ucStep;
	unsigned char  TxBuffer[128];

	if(tn > m_UpgradeCtrl.uiOverTimer)
	{
		m_UpgradeCtrl.uiStep = US_IDLE;
		DbgPrintf("upgrade wait ack overtime\r\n");
		return;
	}
	if(pData && dl)
	{
		ucUsCmd	= *pData++;//US_XXX
		ucSn    = *pData++;//Sn
		ucUsErr = *pData++;
		ucStep	= *pData;

		if(ucSn != m_UpgradeCtrl.msgQueue[m_UpgradeCtrl.usMsg2Tx][2])
		{

		}		
		else if(ucUsErr == UERR_SUCCESS)
		{
			m_UpgradeCtrl.usMsg2Tx++;
			Msg(0,"%u/%u ",m_UpgradeCtrl.usMsg2Tx,m_UpgradeCtrl.usMsgCnt);			
			if(m_UpgradeCtrl.usMsg2Tx >= m_UpgradeCtrl.usMsgCnt)
			{
				m_UpgradeCtrl.uiStep = US_IDLE;
				DbgPrintf("设备升级完成\r\n");
				Msg(0,"\r\n升级完成");
				return;
			}
			m_UpgradeCtrl.uiOverTimer = tn + ((from==US_WIAFROM)?90:16);
			m_UpgradeCtrl.uiWaitMsgTimer = 0;
		}
		else
		{
			switch(ucUsErr)
			{
			case UERR_SN:
				DbgPrintf("设备升级过程序号出错\r\n");
				m_UpgradeCtrl.uiStep = US_IDLE;
				return;
			case UERR_BUSY:
				m_UpgradeCtrl.uiStep = US_IDLE;
				DbgPrintf("设备已经在升级处理中\r\n");
				return;
			case UERR_FLAG:
				m_UpgradeCtrl.uiStep = US_IDLE;
				DbgPrintf("升级标志出错\r\n");
				return;
			case UERR_FORM:
				m_UpgradeCtrl.uiStep = US_IDLE;
				DbgPrintf("设备已经在升级处理中\r\n");
				return;
			case UERR_NOINIT:
				m_UpgradeCtrl.uiStep = US_IDLE;
				DbgPrintf("设备过程状态出错\r\n");
				return;
			case UERR_NOTAPPBOOT:
				m_UpgradeCtrl.uiStep = US_IDLE;
				DbgPrintf("升级类型出错\r\n");
				return;
			case UERR_DATALEN:
				DbgPrintf("数据长度出错\r\n");
				break;
			case UERR_FLASHERASE:
				DbgPrintf("NandFlash擦除出错\r\n");
				break;
			case UERR_CRC:
				DbgPrintf("数据CRC校验出错\r\n");
				m_UpgradeCtrl.uiStep = US_IDLE;
				return;
			case UERR_NOCRCCHK:
				DbgPrintf("设备过程出错\r\n");
				m_UpgradeCtrl.uiStep = US_IDLE;
				return;
			case UERR_BOOTNOREADY:
				DbgPrintf("BOOT没有就绪\r\n");
				m_UpgradeCtrl.uiStep = US_IDLE;
				return;
			default:
				return;
			}
		}
	}

	if(m_UpgradeCtrl.usMsg2Tx < m_UpgradeCtrl.usMsgCnt)
	{
		if(tn >= m_UpgradeCtrl.uiWaitMsgTimer)
		{
			m_UpgradeCtrl.uiWaitMsgTimer = tn + ((from==US_WIAFROM)?15:2);
			ucLen = m_UpgradeCtrl.msgQueue[m_UpgradeCtrl.usMsg2Tx][0];
			if(US_CANFROM == from)
			{
				if(ucLen > 8)
				{
					m_UpgradeCtrl.uiStep = US_IDLE;
					DbgPrintf("系统错误\r\n");
					return;
				}
				SendCan(CANUPGRADECMD,&m_UpgradeCtrl.msgQueue[m_UpgradeCtrl.usMsg2Tx][1]);
			}
			else
			{
				TxBuffer[0] = WIAPAUPGRADECMDTYPE;
				TxBuffer[1] = 0x00;//OK
				TxBuffer[2] = ucLen+3;
				TxBuffer[3] = WIAPAUPGRADECMD0;
				TxBuffer[4] = WIAPAUPGRADECMD1;
				memcpy(TxBuffer + 5,&m_UpgradeCtrl.msgQueue[m_UpgradeCtrl.usMsg2Tx][1],ucLen);
				SendWiapa(TxBuffer,ucLen + 5);
			}
			if((m_UpgradeCtrl.usMsg2Tx+1) == m_UpgradeCtrl.usMsgCnt)
			{
				m_UpgradeCtrl.uiStep = US_IDLE;
				DbgPrintf("设备升级完成\r\n");
				Msg(0,"\r\n升级完成");
				return;
			}
		}
	}
}

void CUart::WiapaUpgradeRecvMsg(unsigned char *pData,unsigned char dl)
{
	if(pData && dl)
	{
		if(dl < 9)return;

		pData++;//wiapa sn0
		pData++;//wiapa sn1
		
		if(WIAPAUPGRADECMDTYPE != *pData++)return;
		pData++;//wiapa ack status		
		pData++;//wiapa payload len		
		if(WIAPAUPGRADECMD0 != *pData++)return;
		if(WIAPAUPGRADECMD1 != *pData++)return;

		dl -= 7;
	}
	UpgradeRecvMsg(US_WIAFROM,pData,dl);
}





int CUart::DoSendWiapa(unsigned char* pData,unsigned int dl)
{
	unsigned short crc;
	unsigned int  uiTxLen,uiLen = 0;
	unsigned char c,Buffer[256];
	unsigned char TxBuffer[256];
	
	
	
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = 0x73;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 0x00;//ExtCmd
	Buffer[uiLen++] = 0x02;//ExtCmd
	
	m_usZhennum++;
	m_usZhennum &= 0x7FFF;
	
	Buffer[uiLen++] = (unsigned char)(m_usZhennum);
	Buffer[uiLen++] = (unsigned char)(m_usZhennum>>8);
	
	while(dl--)Buffer[uiLen++] = *pData++;
	
	crc = crc16_ccitt(Buffer,uiLen);
				
	Buffer[uiLen++] = (unsigned char)(crc);
	Buffer[uiLen++] = (unsigned char)(crc>>8);
	
	
	
	uiTxLen = 0;
	TxBuffer[uiTxLen++] = 0x7E;
	pData = Buffer;
	while(uiLen--)
	{
		c = *pData++; 
		if(c == 0x7D)
		{
			TxBuffer[uiTxLen++] = 0x7D;
			TxBuffer[uiTxLen++] = 0x5D;
		}
		else if(c == 0x7E)
		{
			TxBuffer[uiTxLen++] = 0x7D;
			TxBuffer[uiTxLen++] = 0x5E;
		}
		else
		{
			TxBuffer[uiTxLen++] = c;
		}
	}
	
	TxBuffer[uiTxLen++] = 0x7E;
	
	
	return SendData(TxBuffer,uiTxLen);
}
int CUart::SendWiapa(unsigned char* pData,unsigned int dl)
{
	int ret;
	if(m_iCI == US_WIAFROM)
	{
		ret = DoSendUdp(dl,pData);
	}
	else
	{
		ret = DoSendWiapa(pData,dl);
	}
	return ret;
}


void CUart::PrintRecvFrame(unsigned char* pData,unsigned int dl)
{
	unsigned char CmdType,CmdAck,PLen,CmdID0,CmdID1;
	int16_t sXx;
	uint8_t  ucXx;
	uint16_t usXx,usXx1,usXx2;
	uint32_t uiXx,uiXx1;
	
	uint32_t i;

	SendMessage(m_hWind,WM_ONCOMMSG,(WPARAM)pData,(LPARAM)dl);

	pData++;//Sn0
	pData++;//Sn1

	CmdType = *pData++;
	CmdAck  = *pData++;

	PLen    = *pData++;

	CmdID0  = *pData++;
	CmdID1  = *pData++;

	if(m_UpgradeCtrl.uiStep)
	{
		if(WIAPAUPGRADECMDTYPE == CmdType)
		{
			if(WIAPAUPGRADECMD0 == CmdID0)
			{
				if(WIAPAUPGRADECMD1 == CmdID1)
				{
					UpgradeRecvMsg(US_COMFROM,pData,dl-7);
					return;
				}
			}
		}
		
	}

	EnterCriticalSection(&csPrint);

	switch(CmdAck)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	case 0x01:
		DbgPrintf("ACK:命令长度错误\r\n");
		break;
	case 0x02:
		DbgPrintf("ACK:命令号错误\r\n");
		break;
	case 0x03:
		DbgPrintf("ACK:命令类型错误\r\n");
		break;
	case 0x04:
		DbgPrintf("ACK:命令超范围\r\n");
		break;
	case 0x05:
		DbgPrintf("ACK:WIA-PA命令超时\r\n");
		break;
	case 0x06:
		DbgPrintf("ACK:配置失败\r\n");
		break;
	}
	if(CmdType == 0x01)//查询
	{
		DbgPrintf("+++查询+++\r\n");
		if(CmdID1 == 0x00)
		{
			if(CmdID0 == 0x01)//查询版本信息
			{
				DbgPrintf("设备软件版本:%d.%d.%d\r\n设备硬件版本:%d.%d.%d\r\n",
					pData[0],pData[1],pData[2],
					pData[3],pData[4],pData[5]
					);
			}
		}

		else if(CmdID1 == 0x01)
		{
			if(CmdID0 == 0x00)//查询实时采集数据
			{
				DbgPrintf("查询实时采集数据:\r\n");
				DbgPrintf("时间:%02d/%02d/%02d %02d:%02d:%02d\r\n"
					,pData[0],pData[1],pData[2]
					,pData[3],pData[4],pData[5]
					);
				pData += 6;

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				DbgPrintf("温度:%d.%d\r\n",usXx/10,usXx%10);

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				DbgPrintf("湿度:%d.%d\r\n",usXx/10,usXx%10);

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				DbgPrintf("内压:%d.%d\r\n",usXx/10,usXx%10);

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				DbgPrintf("外压:%d.%d\r\n",usXx/10,usXx%10);

				usXx  = *pData++;
				usXx |= (*pData++)<<8;

				sXx = usXx;
				DbgPrintf("压差:%.1f\r\n",((float)sXx)/10);

			

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				DbgPrintf("X-G:%d.%d\r\n",usXx/100,usXx%100);

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				DbgPrintf("Y-G:%d.%d\r\n",usXx/100,usXx%100);

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				DbgPrintf("Z-G:%d.%d\r\n",usXx/100,usXx%100);

				ucXx = *pData++;
				DbgPrintf("电量:%d%%\r\n",ucXx);

				ucXx = *pData;
				DbgPrintf("温度上限报警:%s\r\n",(ucXx&0x01)?"告警!":"正常");
				DbgPrintf("温度下限报警:%s\r\n",(ucXx&0x02)?"告警!":"正常");
				DbgPrintf("湿度上限报警:%s\r\n",(ucXx&0x04)?"告警!":"正常");
				DbgPrintf("湿度下限报警:%s\r\n",(ucXx&0x08)?"告警!":"正常");
				DbgPrintf("压力上限报警:%s\r\n",(ucXx&0x10)?"告警!":"正常");
				DbgPrintf("压力下限报警:%s\r\n",(ucXx&0x20)?"告警!":"正常");
				DbgPrintf("振动报警:%s\r\n",(ucXx&0x40)?"告警!":"正常");
				DbgPrintf("电量低报警:%s\r\n",(ucXx&0x80)?"告警!":"正常");

			}
		}

		else if(CmdID1 == 0x02)
		{
			if(CmdID0 == 0x00)////查询周期
			{
				usXx = *pData++;
				usXx1= *pData;
				usXx = (usXx1<<8)|usXx;
				DbgPrintf("采集周期:%d [%d秒]\r\n",usXx,(uint32_t)(usXx*10));
			}

			else if(CmdID0 == 0x02)//查询 温度 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("温度门限:%d - %d\r\n",(short)usXx1,(short)usXx);
			}

			else if(CmdID0 == 0x03)//查询 湿度 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("湿度门限:%u - %u\r\n",usXx1,usXx);
			}

			else if(CmdID0 == 0x04)//查询 压力 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("压力门限:%u - %u\r\n",usXx1,usXx);
			}

			else if(CmdID0 == 0x05)//查询 振动 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				DbgPrintf("振动门限:   - %u\r\n",usXx1);
			}

			else if(CmdID0 == 0x0E)//查询 弹号
			{
				DbgPrintf("弹号:");
				for(i = 0; i < 7; i++)
				{
					DbgPrintf("%c",*pData++);
				}
				DbgPrintf("\r\n");
			}

			else if(CmdID0 == 0x0F)//查询 箱号
			{
				DbgPrintf("箱号:");
				for(i = 0; i < 7; i++)
				{
					DbgPrintf("%c",*pData++);
				}
				DbgPrintf("\r\n");
			}

			else if(CmdID0 == 0x10)//查询PANID
			{
				DbgPrintf("PANID:%u\r\n",pData[0]|(pData[1]<<8));
			}
			
			else if(CmdID0 == 0x11)//查询信道
			{
				DbgPrintf("信道:%d\r\n",pData[0]);
			}
			
			else if(CmdID0 == 0x12)//查询Wiapa长地址
			{
				DbgPrintf("WIA长地址:%02X%02X%02X%02X%02X%02X%02X%02X",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6],pData[7]);
			}
			
			else if(CmdID0 == 0x16)//查询时间
			{
				DbgPrintf("设备时间:20%02d/%02d/%02d %02d:%02d:%02d\r\n",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5]);
			}

			else if(CmdID0 == 0x18)//查询贮存/非贮存模式
			{
				if(*pData == 0)DbgPrintf("贮存模式:贮存\r\n");
				else if(*pData == 1)DbgPrintf("贮存模式:非贮存\r\n");
				else DbgPrintf("贮存模式:错误\r\n");
			}
		}

		else if(CmdID1 == 0x03)//查询告警信息
		{
			switch(CmdID0)
			{
			case 0x00:
				if(*pData == 0)     DbgPrintf("温度上限告警:无\r\n");
				else if(*pData == 1)DbgPrintf("温度上限告警:!!告警!!\r\n");
				else                DbgPrintf("温度上限告警:回应错误\r\n");
				break;
			case 0x01:
				if(*pData == 0)     DbgPrintf("温度下限告警:无\r\n");
				else if(*pData == 1)DbgPrintf("温度下限告警:!!告警!!\r\n");
				else                DbgPrintf("温度下限告警:回应错误\r\n");
				break;
			case 0x02:
				if(*pData == 0)     DbgPrintf("湿度上限告警:无\r\n");
				else if(*pData == 1)DbgPrintf("湿度上限告警:!!告警!!\r\n");
				else                DbgPrintf("湿度上限告警:回应错误\r\n");
				break;
			case 0x03:
				if(*pData == 0)     DbgPrintf("湿度下限告警:无\r\n");
				else if(*pData == 1)DbgPrintf("湿度下限告警:!!告警!!\r\n");
				else                DbgPrintf("湿度下限告警:回应错误\r\n");
				break;
			case 0x04:
				if(*pData == 0)     DbgPrintf("压力上限告警:无\r\n");
				else if(*pData == 1)DbgPrintf("压力上限告警:!!告警!!\r\n");
				else                DbgPrintf("压力上限告警:回应错误\r\n");
				break;
			case 0x05:
				if(*pData == 0)     DbgPrintf("压力下限告警:无\r\n");
				else if(*pData == 1)DbgPrintf("压力下限告警:!!告警!!\r\n");
				else                DbgPrintf("压力下限告警:回应错误\r\n");
				break;
			case 0x06:
				if(*pData == 0)     DbgPrintf("差压告警:无\r\n");
				else if(*pData == 1)DbgPrintf("差压告警:!!告警!!\r\n");
				else                DbgPrintf("差压告警:回应错误\r\n");
				break;
			case 0x07:
				if(*pData == 0)     DbgPrintf("电量低告警:无\r\n");
				else if(*pData == 1)DbgPrintf("电量低告警:!!告警!!\r\n");
				else                DbgPrintf("电量低告警:回应错误\r\n");
				break;
			case 0x08:
				if(*pData == 0)     DbgPrintf("振动上限告警:无\r\n");
				else if(*pData == 1)DbgPrintf("振动上限告警:!!告警!!\r\n");
				else                DbgPrintf("振动上限告警:回应错误\r\n");
				break;
			default:
				DbgPrintf("告警类型错误:%02X 告警值:%d\r\n",CmdID0,*pData);
				break;
			}
		}
	}
	else if(CmdType == 0x02)//设置
	{
		DbgPrintf("+++设置+++\r\n");
		if(CmdID1 == 0x02)
		{
			if(CmdID0 == 0x00)////周期
			{
				usXx = *pData++;
				usXx1= *pData;
				usXx = (usXx1<<8)|usXx;
				DbgPrintf("采集周期:%d [%d秒]\r\n",usXx,(uint32_t)(usXx*10));
			}
			
			else if(CmdID0 == 0x02)//温度 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("温度门限:%d - %d\r\n",(short)usXx,(short)usXx1);
			}
			
			else if(CmdID0 == 0x03)//湿度 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("湿度门限:%u - %u\r\n",usXx,usXx1);
			}
			
			else if(CmdID0 == 0x04)//压力 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("压力门限:%u - %u\r\n",usXx,usXx1);
			}
			
			else if(CmdID0 == 0x05)//振动 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				DbgPrintf("振动门限:   - %u\r\n",usXx1);
			}

			else if(CmdID0 == 0x07)//历史温湿压擦除
			{
				DbgPrintf("历史温湿压擦除:%d\r\n",*pData);
			}

			else if(CmdID0 == 0x08)//历史振动擦除
			{
				DbgPrintf("历史温湿压擦除:%d\r\n",*pData);
			}
			
			else if(CmdID0 == 0x0E)//弹号
			{
				DbgPrintf("弹号:");
				for(i = 0; i < 7; i++)
				{
					DbgPrintf("%c",*pData++);
				}
				DbgPrintf("\r\n");
			}
			
			else if(CmdID0 == 0x0F)//箱号
			{
				DbgPrintf("箱号:");
				for(i = 0; i < 7; i++)
				{
					DbgPrintf("%c",*pData++);
				}
				DbgPrintf("\r\n");
			}

			else if(CmdID0 == 0x10)//PANID
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				DbgPrintf("PANID: %04X\r\n",usXx1);
			}

			else if(CmdID0 == 0x11)//信道
			{
				usXx1  = *pData++;
				DbgPrintf("信道: %d\r\n",usXx1);
			}

			else if(CmdID0 == 0x14)//压力校正
			{
				usXx1 = *pData++;
				usXx1 <<= 8;
				usXx1 |= *pData;
				DbgPrintf("压力校正:%d\r\n",usXx1);
			}

			else if(CmdID0 == 0x15)//终止传输
			{
				DbgPrintf("终止传输:%d\r\n",*pData);
			}

			else if(CmdID0 == 0x16)//时间同步
			{
				DbgPrintf("时间同步:");
				DbgPrintf("时间:%02d/%02d/%02d %02d:%02d:%02d\r\n"
					,pData[0],pData[1],pData[2]
					,pData[3],pData[4],pData[5]
					);
				DbgPrintf("\r\n");
			}

			else if(CmdID0 == 0x17)//无线模块重启
			{
				DbgPrintf("无线模块重启:%d\r\n",*pData);
			}
			
			else if(CmdID0 == 0x18)//贮存/非贮存模式
			{
				if(*pData == 0)DbgPrintf("贮存模式\r\n");
				else if(*pData == 1)DbgPrintf("非贮存模式\r\n");
				else DbgPrintf("错误贮存模式\r\n");
			}

			else if(CmdID0 == 0x1B)
			{
				DbgPrintf("读取参数:\r\n");

				DbgPrintf("弹号:");
				for(i = 0; i < 7; i++)DbgPrintf("%c",*pData++);
				DbgPrintf("\r\n");
				pData++;

				DbgPrintf("箱号:");
				for(i = 0; i < 7; i++)DbgPrintf("%c",*pData++);
				DbgPrintf("\r\n");
				pData++;

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				DbgPrintf("采集周期:%d [%d秒]\r\n",usXx,(uint32_t)(usXx*10));

				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("温度门限:%u - %u\r\n",usXx,usXx1);

				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("湿度门限:%u - %u\r\n",usXx,usXx1);

				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				DbgPrintf("压力门限:%u - %u\r\n",usXx,usXx1);
			
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				DbgPrintf("振动门限:   - %u\r\n",usXx1);


				if(*pData == 0)DbgPrintf("贮存模式:贮存\r\n");
				else if(*pData == 1)DbgPrintf("贮存模式:非贮存\r\n");
				else DbgPrintf("贮存模式:错误\r\n");

			}
		}
	}
	else if(CmdType == 0x03)//历史数据上报
	{
		DbgPrintf("+++历史数据上报+++\r\n");
		if(CmdID1 == 0x04)
		{
			if(CmdID0 == 0x00 || CmdID0 == 0x01)
			{
				DbgPrintf(CmdID0 == 0x00? "温湿压记录数据:\r\n":"温湿压记录数据补包:\r\n");

				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				DbgPrintf("当前包/总包数:%u/%u\r\n",usXx1,usXx);

				uiXx   = *pData++;
				uiXx  |= (*pData++)<<8;
				uiXx  |= (*pData++)<<16;
				uiXx  |= (*pData++)<<24;
				DbgPrintf("编号:%u\r\n",uiXx);
				
				DbgPrintf("时间:%02d/%02d/%02d %02d:%02d:%02d\r\n"
					,pData[0],pData[1],pData[2]
					,pData[3],pData[4],pData[5]
					);
				DbgPrintf("\r\n");
				pData += 6;

				usXx  = *pData++;
				usXx |= (*pData++<< 8);
				DbgPrintf("温度:%d.%d\r\n",usXx/10,usXx%10);
				
				usXx  = *pData++;
				usXx |= (*pData++<<8);
				DbgPrintf("湿度:%d.%d\r\n",usXx/10,usXx%10);
				
				usXx  = *pData++;
				usXx |= (*pData++<<8);
				DbgPrintf("内压:%d.%d\r\n",usXx/10,usXx%10);
				
				usXx  = *pData++;
				usXx |= (*pData++<<8);
				DbgPrintf("外压:%d.%d\r\n",usXx/10,usXx%10);

				usXx  = *pData++;
				usXx |= (*pData++<<8);
				DbgPrintf("压差:%d.%d\r\n",((int)usXx)/10,((int)usXx)%10);
				
				usXx  = *pData++;
				usXx |= (*pData++<<8);
				DbgPrintf("X-G:%d.%d\r\n",usXx/100,usXx%100);
				
				usXx  = *pData++;
				usXx |= (*pData++<<8);
				DbgPrintf("Y-G:%d.%d\r\n",usXx/100,usXx%100);
				
				usXx  = *pData++;
				usXx |= (*pData++<<8);
				DbgPrintf("Z-G:%d.%d\r\n",usXx/100,usXx%100);
				
				ucXx  = *pData++;
				DbgPrintf("电量:%d\r\n",ucXx);
				ucXx = *pData;

				DbgPrintf("指令:%s\r\n",(ucXx&0x01)?"错误":"正常");
				DbgPrintf("温度传感器:%s\r\n",(ucXx&0x02)?"故障":"正常");
				DbgPrintf("湿度传感器:%s\r\n",(ucXx&0x04)?"故障":"正常");
				DbgPrintf("内压传感器:%s\r\n",(ucXx&0x08)?"故障":"正常");
				DbgPrintf("外压传感器:%s\r\n",(ucXx&0x10)?"故障":"正常");
				DbgPrintf("振动传感器:%s\r\n",(ucXx&0x20)?"故障":"正常");
				DbgPrintf("振动超限:%s\r\n",(ucXx&0x40)?"故障":"正常");
				DbgPrintf("电量(程序中为电量,文档为压差):%s\r\n",(ucXx&0x80)?"故障":"正常");


			}

			else if(CmdID0 == 0x02 || CmdID0 == 0x03)
			{
				DbgPrintf(CmdID0 == 0x02? "振动记录数据:\r\n":"振动记录数据补包:\r\n");

				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				DbgPrintf("当前包/总包数:%u/%u\r\n",usXx1,usXx);
				
				uiXx   = *pData++;
				uiXx  |= (*pData++)<<8;
				uiXx  |= (*pData++)<<16;
				uiXx  |= (*pData++)<<24;
				DbgPrintf("编号:%u\r\n",uiXx);
				
				DbgPrintf("时间:%02d/%02d/%02d %02d:%02d:%02d\r\n"
					,pData[0],pData[1],pData[2]
					,pData[3],pData[4],pData[5]
					);
				DbgPrintf("\r\n");
				pData += 6;

				uiXx   = *pData++;
				uiXx  |= (*pData++)<<8;
				for(uiXx1 = 0; uiXx1 < 10; uiXx1++)
				{
					usXx   = *pData++;
					usXx  |= (*pData++)<<8;

					usXx1  = *pData++;
					usXx1 |= (*pData++)<<8;

					usXx2  = *pData++;
					usXx2 |= (*pData++)<<8;

					DbgPrintf("帧编号:%-3u X-G:%3d.%-2d Y-G:%3d.%-2d Z-G:%3d.%-2d\r\n"
						,uiXx+uiXx1,usXx/100,usXx%100,usXx1/100,usXx1%100,usXx2/100,usXx2%100);
				}
			}
		}
	}
	else if(CmdType == 0x04)//实时数据/报警上报
	{
		DbgPrintf("+++实时数据/报警上报+++\r\n");
	}
	else if(CmdType != WIAPAUPGRADECMDTYPE)
	{
		DbgPrintf("命令类型错误:%02X\r\n",CmdType);
	}
	LeaveCriticalSection(&csPrint);
}

BOOL CUart::ProcessRecvFrame(unsigned char*pData,unsigned int dl)
{
	if(!pData   || !dl )goto RET;
	if(*pData++ != 0x02)goto RET;
	if(*pData++ != 0x74)goto RET;
	if(*pData++ != 0x00)goto RET;
	if(*pData++ != 0x00)goto RET;
	if(*pData++ != 0x02)goto RET;
	
	PrintRecvFrame(pData,dl-5);
RET:
	return FALSE;
}


int CUart::UpgradeReset()
{
	EnterCriticalSection(&cs);
	memset(&m_UpgradeCtrl,0,sizeof(m_UpgradeCtrl));
	memset(m_UpgradeCtrl.ucFwBin,0xFF,sizeof(m_UpgradeCtrl.ucFwBin));

	m_UpgradeCtrl.usAppEndPos = 0x0000;	//主程序空间:0x0000 ~ 0xDFFF
	m_UpgradeCtrl.usBootEndPos= 0x0000; //BOOT  空间:0xE000 ~ 0xFD00

	LeaveCriticalSection(&cs);
	return 0;
}

int CUart::UpgradeAddFile(char*fn)
{
	unsigned int First_Word,Address;
	unsigned int Type,Nb_Bytes,Checksum,Highest_Address,Lowest_Address,n,c;
	unsigned char *ps,*pd,*pns,*pnd;
	int  dl,err;
	char szLine[512],szDataStr[512];
	char *pc;
	//主程序程序常量定义: 0x1000
	//BOOT      常量定义: 0xE000
	//BOOT      程序入口: 0xE040
	FILE *fp = NULL;
	int ret = 0;
	err = 0;
	EnterCriticalSection(&cs);
	
	if(m_UpgradeCtrl.uiStep)
	{
		DbgPrintf("正在升级中\r\n");
		ret = 1;
		goto RET;			 
	}
	fp = fopen(fn,"rb");
	if(!fp)
	{
		DbgPrintf("读取文件%s失败\r\n",fn);
		ret = 2;
		goto RET;
	}
	memset(m_UpgradeCtrl.ucTempFwBin,0xFF,sizeof(m_UpgradeCtrl.ucTempFwBin));
	memset(m_UpgradeCtrl.ucTempFwBinNull,0,sizeof(m_UpgradeCtrl.ucTempFwBinNull));
	Highest_Address = 0;
	Lowest_Address  = -1;
	while(!feof(fp))
	{
		pc = fgets(szLine,511,fp);
		if(!pc)break;
		dl = strlen(pc);
		if(dl < 8)
		{
			DbgPrintf("data format error\r\n");
			continue;
		}
		if(szLine[--dl] == '\n')szLine[dl] = 0;
		if(sscanf(szLine,":%2x%4x%2x%s",&Nb_Bytes,&First_Word,&Type,szDataStr) != 4)
		{
			DbgPrintf("data format error\r\n");
			continue;
		}
		Checksum = Nb_Bytes + (First_Word >> 8) + (First_Word & 0xFF) + Type;
		switch(Type)
		{
		case 0:
			if(Nb_Bytes == 0)break;
			if(First_Word < Lowest_Address)
			{
				Lowest_Address = First_Word;
			}
			Address = First_Word;
			if(Address >= 64*1024)
			{
				err = 1;
				DbgPrintf("over 64*1024\r\n");
				break;//error
			}
			pc = szDataStr;
			for(n = 0; n < Nb_Bytes; n++)
			{
				if(sscanf(pc,"%2x",&c) == 1)
				{
					if(m_UpgradeCtrl.ucTempFwBinNull[Address])
					{//error
						err = 1;
						DbgPrintf("data Overlapped\r\n");
						break;
					}
					m_UpgradeCtrl.ucTempFwBinNull[Address] = 1;
					m_UpgradeCtrl.ucTempFwBin    [Address] = (unsigned char)c;
					Address++;

					Checksum += c;
				}
				else
				{//error
					err = 1;
					DbgPrintf("read data error\r\n");
				}
				pc += 2;
			}
			if(sscanf(pc,"%2x",&c) != 1)
			{//error
				err = 1;
				DbgPrintf("read data error\r\n");
			}
			Checksum += c;
			Checksum &= 0xFF;
			if(Checksum != 0)
			{//error
				err = 1;
				DbgPrintf("checksum error\r\n");
			}
			if(Address > Highest_Address)
			{
				Highest_Address = Address;
			}
			break;
		case 1://End of file record
			break;
		case 2:
			break;
		}
	}
	if(err)
	{
		DbgPrintf("解析HEX文件异常");
		ret = 2;
		m_UpgradeCtrl.usAppEndPos = 0;
		m_UpgradeCtrl.usBootEndPos = 0;
	}
	else
	{
		if(Highest_Address >= 0xE000)
		{//BOOT
			if(m_UpgradeCtrl.usBootEndPos < Highest_Address)
			{
				m_UpgradeCtrl.usBootEndPos = Highest_Address;
			}
			if(Lowest_Address)
			{
				DbgPrintf("BOOL 启动代码位置错误\r\n");
			}
			else
			{
				Lowest_Address = 0xE000;

				m_UpgradeCtrl.ucTempFwBin[0xE000 + 12] = m_UpgradeCtrl.ucTempFwBin[0];
				m_UpgradeCtrl.ucTempFwBin[0xE000 + 13] = m_UpgradeCtrl.ucTempFwBin[1];
				m_UpgradeCtrl.ucTempFwBin[0xE000 + 14] = m_UpgradeCtrl.ucTempFwBin[2];

				m_UpgradeCtrl.ucTempFwBinNull[0xE000 + 12] = 1;
				m_UpgradeCtrl.ucTempFwBinNull[0xE000 + 13] = 1;
				m_UpgradeCtrl.ucTempFwBinNull[0xE000 + 14] = 1;
			}
		}
		else
		{
			if(m_UpgradeCtrl.usAppEndPos < Highest_Address)
			{
				m_UpgradeCtrl.usAppEndPos = Highest_Address;
			}
		}
		n   = Highest_Address				- Lowest_Address;
		ps  = m_UpgradeCtrl.ucTempFwBin		+ Lowest_Address;
		pd  = m_UpgradeCtrl.ucFwBin			+ Lowest_Address;
		pns = m_UpgradeCtrl.ucTempFwBinNull + Lowest_Address;
		pnd = m_UpgradeCtrl.ucFwBinNull     + Lowest_Address;
		for(c = 0; c < n; c++)
		{
			if(*pns)
			{
				if(*pnd)
				{//error 有覆盖
					err = 3;
					break;
				}
				*pnd = 1;
				*pd = *ps;
			}
			pns++;
			pnd++;
			ps++;
			pd++;
		}
		if(err)
		{
			DbgPrintf("固件有重叠");
			m_UpgradeCtrl.usAppEndPos = 0;
			m_UpgradeCtrl.usBootEndPos = 0;
		}
		else
		{
			DbgPrintf("Hex File:%s\r\n",fn);
			DbgPrintf("起始地址:%u(0x%04X) 结束地址:%u(0x%04X)\r\n",Lowest_Address,Lowest_Address,Highest_Address,Highest_Address);		
		}		
	}
RET:
	if(fp)fclose(fp);
	LeaveCriticalSection(&cs);
	return ret;
}

int CUart::UpgradeStart()
{
	unsigned short usCrc,usLen;
	unsigned char *pd;
	int ret = 0;
	EnterCriticalSection(&cs);
	
	if(m_UpgradeCtrl.usAppEndPos)
	{
		pd = m_UpgradeCtrl.ucFwBin;
		DbgPrintf("upgrade Application\r\n");
		usLen = m_UpgradeCtrl.usAppEndPos;
		usCrc = crc16_ccitt(pd,usLen);
		m_UpgradeCtrl.appHeader.usCrc  = usCrc;
		m_UpgradeCtrl.appHeader.usLength = usLen;
		
		m_UpgradeCtrl.uiStep = US_APP_START;
	}

	if(m_UpgradeCtrl.usBootEndPos)
	{
		if(m_UpgradeCtrl.usBootEndPos < 0xE100)
		{
			DbgPrintf("Boot length Error\r\n");
			ret = 3;
			goto RET;
		}
		pd = m_UpgradeCtrl.ucFwBin + 0xE000;
		if(	   pd[0x00] == 'B' 
			&& pd[0x01] == 'O'
			&& pd[0x02] == 'O'
			&& pd[0x03] == 'T' )
		{
			if(((pd[0x40] == 0x00) && (pd[0x41] == 0x00)) 
				|| ((pd[0x40] == 0xFF) && (pd[0x41] == 0xFF)))
			{
				DbgPrintf("Boot Flag Error\r\n");
				ret = 3;
				goto RET;
			}
			DbgPrintf("upgrade Bootloader\r\n");
			
			usLen = m_UpgradeCtrl.usBootEndPos - 0xE000;
			
			usCrc = crc16_ccitt(pd,usLen);
			m_UpgradeCtrl.bootHeader.usCrc  = usCrc;
			m_UpgradeCtrl.bootHeader.usLength = usLen;
			m_UpgradeCtrl.bootHeader.uiVersion   = pd[0x04];
			m_UpgradeCtrl.bootHeader.uiVersion  |= pd[0x05]<<8;
			m_UpgradeCtrl.bootHeader.uiVersion  |= pd[0x06]<<16;
			m_UpgradeCtrl.bootHeader.uiVersion  |= pd[0x07]<<24;
			
		}
		else
		{
			DbgPrintf("Boot Flag Error\r\n");
			ret = 3;
			goto RET;
		}
		m_UpgradeCtrl.uiStep = US_BOOT_START;
	}

	if(!m_UpgradeCtrl.uiStep)	
	{
		ret = 1;
		goto RET;
	}

	UpgradePreprocessData((m_iCI==US_CANFROM)?6:63);

	
	if(m_UpgradeCtrl.usMsgCnt < 3)
	{
		m_UpgradeCtrl.uiStep = US_IDLE;
	}
	else
	{
		m_UpgradeCtrl.uiWaitMsgTimer = 0;
		m_UpgradeCtrl.uiOverTimer = time(0) + ((m_iCI==US_WIAFROM)?60:16);		
		Msg(1,"开始升级\r\n");
	}
	

RET:
	LeaveCriticalSection(&cs);

	return ret;
}

int CUart::UpgradeStop()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	int ret = 0;
	EnterCriticalSection(&cs);
	if(m_UpgradeCtrl.uiStep != US_IDLE)
	{
		m_UpgradeCtrl.uiStep = US_IDLE;
		ret =1;
	}
	LeaveCriticalSection(&cs);
	if(ret)
	{
		Msg(0,"中断升级");
		if(m_iCI == US_CANFROM)
		{
			Buffer[0] = US_RESET;
			return SendCan(CANUPGRADECMD,Buffer);
		}
		
		Buffer[uiLen++] = WIAPAUPGRADECMDTYPE;
		
		Buffer[uiLen++] = 0x00;
		
		Buffer[uiLen++] = 3+1;
		
		Buffer[uiLen++] = WIAPAUPGRADECMD0;
		Buffer[uiLen++] = WIAPAUPGRADECMD1;
		
		Buffer[uiLen++] = US_RESET;
		
		return SendWiapa(Buffer,uiLen);	
	}
	return 1;
}

void CUart::UpgradePreprocessData(unsigned char msgMaxLen)
{
	unsigned char  ucSn = rand();
	unsigned char  *pd,ucLen;
	unsigned short usMsgCnt;
	unsigned short usPos;
	
	
	m_UpgradeCtrl.usMsgCnt = 0;
	
	usMsgCnt  = 0;
	
	pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
	pd[0] = 2;
	pd[1] = US_RESET;
	pd[2] = ucSn++;
	
	if(m_UpgradeCtrl.usBootEndPos)
	{
		pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
		pd[0] = 8;
		pd[1] = US_BOOT_START;
		pd[2] = ucSn++;
		pd[3] = UPGRADECHAR;
		pd[4] = UPGRADEBOOT;
		pd[5] = (unsigned char)m_UpgradeCtrl.bootHeader.usLength;
		pd[6] = (unsigned char)(m_UpgradeCtrl.bootHeader.usLength>>8);
		pd[7] = (unsigned char)m_UpgradeCtrl.bootHeader.usCrc;
		pd[8] = (unsigned char)(m_UpgradeCtrl.bootHeader.usCrc>>8);
		for(usPos = 0xE000; usPos < m_UpgradeCtrl.usBootEndPos;)
		{
			ucLen = ((m_UpgradeCtrl.usBootEndPos - usPos) >= msgMaxLen) ? msgMaxLen:((unsigned char)(m_UpgradeCtrl.usBootEndPos - usPos));
			pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
			*pd++ = ucLen +2;
			*pd++ = US_BOOT_BIN;
			*pd++ = ucSn++;
			memcpy(pd,m_UpgradeCtrl.ucFwBin+usPos,ucLen);
			usPos += ucLen;
		}
		
		pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
		pd[0] = 2;
		pd[1] = US_BOOT_END;
		pd[2] = ucSn++;
		pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
		pd[0] = 2;
		pd[1] = US_BOOT_READY;
		pd[2] = ucSn++;
		m_UpgradeCtrl.usMsgCnt = usMsgCnt;
	}
	if(m_UpgradeCtrl.usAppEndPos)
	{
		pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
		pd[0] = 8;
		pd[1] = US_APP_START;
		pd[2] = ucSn++;
		pd[3] = UPGRADECHAR;
		pd[4] = UPGRADEAPP;
		pd[5] = (unsigned char)m_UpgradeCtrl.appHeader.usLength;
		pd[6] = (unsigned char)(m_UpgradeCtrl.appHeader.usLength>>8);
		pd[7] = (unsigned char)m_UpgradeCtrl.appHeader.usCrc;
		pd[8] = (unsigned char)(m_UpgradeCtrl.appHeader.usCrc>>8);
		for(usPos = 0x0000; usPos < m_UpgradeCtrl.usAppEndPos;)
		{
			ucLen = (m_UpgradeCtrl.usAppEndPos - usPos >= msgMaxLen) ? msgMaxLen:((unsigned char)(m_UpgradeCtrl.usAppEndPos - usPos));
			pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
			*pd++ = ucLen +2;
			*pd++ = US_APP_BIN;
			*pd++ = ucSn++;
			memcpy(pd,m_UpgradeCtrl.ucFwBin+usPos,ucLen);
			usPos += ucLen;
		}
		
		pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
		pd[0] = 2;
		pd[1] = US_APP_END;
		pd[2] = ucSn++;
		pd = m_UpgradeCtrl.msgQueue[usMsgCnt++];
		pd[0] = 2;
		pd[1] = US_REBOOT;
		pd[2] = ucSn++;
		m_UpgradeCtrl.usMsgCnt = usMsgCnt;
	}
}


int CUart::GetVersion()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		return SendCan(0x0E,Buffer);
	}
	
	Buffer[uiLen++] = 0x01;//Query Cmd
	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3+6;
	
	Buffer[uiLen++] = 0x01;//version
	Buffer[uiLen++] = 0x00;//version
	
	Buffer[uiLen++] = 0x00;
	Buffer[uiLen++] = 0x00;
	Buffer[uiLen++] = 0x00;
	Buffer[uiLen++] = 0x00;
	Buffer[uiLen++] = 0x00;
	Buffer[uiLen++] = 0x00;
	
	return SendWiapa(Buffer,uiLen);	
}

int CUart::DoCollectOnce()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[7] = 0x04;//发送采集数据
		return SendCan(0x04,Buffer);// 查询信息
	}
	
	Buffer[uiLen++] = 0x01;//Query Cmd
	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3+6;
	
	Buffer[uiLen++] = 0x00;//实时采集
	Buffer[uiLen++] = 0x01;	
	
	return SendWiapa(Buffer,uiLen);	
}



int CUart::SetZhouqi(unsigned short zq)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3+2;
	
	Buffer[uiLen++] = 0x00;//设置周期
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = (unsigned char)zq;
	Buffer[uiLen++] = zq>>8;
	
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetZhouqi()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	Buffer[uiLen++] = 0x01;//Query Cmd	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x00;//zhouqi
	Buffer[uiLen++] = 0x02;
	
	return SendWiapa(Buffer,uiLen);
}


int CUart::SetWenduMenXian(short shang,short xia)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETTEMPMENXIAN;
		Buffer[1] = (char)shang;
		Buffer[2] = shang>>8;
		Buffer[3] = (char)xia;
		Buffer[4] = xia>>8;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3+4;
	
	Buffer[uiLen++] = 0x02;//设置温度门限
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = (char)shang;
	Buffer[uiLen++] = shang>>8;

	Buffer[uiLen++] = (char)xia;
	Buffer[uiLen++] = xia>>8;

	return SendWiapa(Buffer,uiLen);
}

int CUart::GetWenduMenXian()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETTEMPMENXIAN;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x01;//Query Cmd	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x02;

	return SendWiapa(Buffer,uiLen);
}


int CUart::SetShiduMenXian(unsigned short shang,unsigned short xia)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETSHIDUMENXIAN;
		Buffer[1] = (unsigned char)shang;
		Buffer[2] = shang>>8;
		Buffer[3] = (unsigned char)xia;
		Buffer[4] = xia>>8;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3+4;
	
	Buffer[uiLen++] = 0x03;//设置湿度门限
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = (unsigned char)shang;
	Buffer[uiLen++] = shang>>8;
	
	Buffer[uiLen++] = (unsigned char)xia;
	Buffer[uiLen++] = xia>>8;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetShiduMenXian()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETSHIDUMENXIAN;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x01;//Query Cmd	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x03;
	Buffer[uiLen++] = 0x02;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetYaliMenXian(unsigned short shang,unsigned short xia)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETYALIMENXIAN;
		Buffer[1] = (unsigned char)shang;
		Buffer[2] = shang>>8;
		Buffer[3] = (unsigned char)xia;
		Buffer[4] = xia>>8;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3+4;
	
	Buffer[uiLen++] = 0x04;//设置压力门限
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = (unsigned char)shang;
	Buffer[uiLen++] = shang>>8;
	
	Buffer[uiLen++] = (unsigned char)xia;
	Buffer[uiLen++] = xia>>8;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetYaliMenXian()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETYALIMENXIAN;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x01;//Query Cmd	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x04;
	Buffer[uiLen++] = 0x02;
	
	return SendWiapa(Buffer,uiLen);
}


int CUart::SetZhendongMenXian(unsigned short v)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3+2;
	
	Buffer[uiLen++] = 0x05;//设置振动门限
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = (unsigned char)v;
	Buffer[uiLen++] = v>>8;
	
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetZhendongMenXian()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	Buffer[uiLen++] = 0x01;//Query Cmd	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x05;
	Buffer[uiLen++] = 0x02;
	
	return SendWiapa(Buffer,uiLen);
}


int CUart::DelWenshiyaRecord()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		return SendCan(0x09,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +1;
	
	Buffer[uiLen++] = 0x07;//历史温湿压擦除
	Buffer[uiLen++] = 0x02;

	Buffer[uiLen++] = 0x01;
	
	return SendWiapa(Buffer,uiLen);
}


int CUart::DelZhendongRecord()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		return SendCan(0x0A,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +1;
	
	Buffer[uiLen++] = 0x08;//历史振动擦除
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = 0x01;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetDanNumber(unsigned char *pd)
{
	unsigned int i,uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		Buffer[0] = 0x01;
		memcpy(Buffer+1,pd,7);
		return SendCan(0x0D,Buffer);
	}

	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +7;
	
	Buffer[uiLen++] = 0x0E;//设置弹号
	Buffer[uiLen++] = 0x02;

	for(i = 0; i < 7; i++)
	{
		Buffer[uiLen++] = *pd++;
	}

	return SendWiapa(Buffer,uiLen);
}

int CUart::GetDanNumber()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		Buffer[0] = 0x02;
		memset(Buffer+1,0xFF,7);
		return SendCan(0x0D,Buffer);
	}
	
	Buffer[uiLen++] = 0x01;//Query Cmd	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x0E;
	Buffer[uiLen++] = 0x02;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetBangNumber(unsigned char *pd)
{
	unsigned int i,uiLen = 0;
	unsigned char Buffer[256];
	if(m_iCI == US_CANFROM)
	{
		Buffer[0] = 0x01;
		memcpy(Buffer+1,pd,7);
		return SendCan(0x0C,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +7;
	
	Buffer[uiLen++] = 0x0F;//设置箱号
	Buffer[uiLen++] = 0x02;
	
	for(i = 0; i < 7; i++)
	{
		Buffer[uiLen++] = *pd++;
	}
	
	return SendWiapa(Buffer,uiLen);
}
int CUart::GetBangNumber()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		Buffer[0] = 0x02;
		memset(Buffer+1,0xFF,7);
		return SendCan(0x0C,Buffer);
	}
	
	Buffer[uiLen++] = 0x01;//Query Cmd	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x0F;
	Buffer[uiLen++] = 0x02;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetPanID(unsigned short panid)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETPANID;
		Buffer[1] = (unsigned char)panid;
		Buffer[2] = panid>>8;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +2;
	
	Buffer[uiLen++] = 0x10;//设置PANID
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = (unsigned char)panid;
	Buffer[uiLen++] = panid>>8;
	
	return SendWiapa(Buffer,uiLen);
}


int CUart::SetBoardcast(unsigned char bd)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETBDCAST;
		Buffer[1] = bd;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +1;
	
	Buffer[uiLen++] = 0x11;//设置信道
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = bd;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetCalibrationYali(unsigned short v)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_YALICAL;
		Buffer[1] = (unsigned char)v;
		Buffer[2] = v>>8;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +2;
	
	Buffer[uiLen++] = 0x14;//压力校准
	Buffer[uiLen++] = 0x02;

	Buffer[uiLen++] = (unsigned char)v;
	Buffer[uiLen++] = v>>8;
	
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetStop()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		return SendCan(0x1F,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +1;
	
	Buffer[uiLen++] = 0x15;//终止传输
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = 0x01;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetDateTime()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	time_t timep;
	struct tm *p;
	
	time(&timep);
	p = localtime(&timep);
		
	if(m_iCI == US_CANFROM)
	{
		Buffer[0] = (p->tm_year+1900-2000);
		Buffer[1] = p->tm_mon+1;
		Buffer[2] = p->tm_mday;
		Buffer[3] = p->tm_hour;
		Buffer[4] = p->tm_min;
		Buffer[5] = p->tm_sec;
		Buffer[6] = 0xFF;
		Buffer[7] = 0xFF;
		return SendCan(0x07,Buffer);
	}

	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3+6;
	
	Buffer[uiLen++] = 0x16;//时间同步
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = (p->tm_year+1900-2000);
	Buffer[uiLen++] = p->tm_mon+1;
	Buffer[uiLen++] = p->tm_mday;
	Buffer[uiLen++] = p->tm_hour;
	Buffer[uiLen++] = p->tm_min;
	Buffer[uiLen++] = p->tm_sec;
	
	return SendWiapa(Buffer,uiLen);	
}

int CUart::SetZhendongMenXianZhouqi(unsigned short mx,unsigned short zq)
{
	unsigned char Buffer[256];
	memset(Buffer,0xFF,8);
	Buffer[0] = (unsigned char)mx;
	Buffer[1] = (unsigned char)(zq>>8);
	Buffer[2] = (unsigned char)zq;
	Buffer[7] = 0x01;
	return SendCan(0x08,Buffer);
}
int CUart::GetZhendongMenXianZhouqi()
{
	unsigned char Buffer[256];
	memset(Buffer,0xFF,8);
	Buffer[7] = 0x02;
	return SendCan(0x08,Buffer);
}


int CUart::SetSaveMode(int mode)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETWORKMODE;
		Buffer[1] = mode;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +1;
	
	Buffer[uiLen++] = 0x18;//设置贮存，非贮存
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = mode?1:0;//1 0x0A/SM_ZHENGDONG,0 0x0B/SM_NOZHENGDONG
	
	return SendWiapa(Buffer,uiLen);
}
int CUart::GetSaveMode()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETWORKMODE;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x01;//Query Cmd	
	Buffer[uiLen++] = 0x00;//CmdAck OK
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x18;
	Buffer[uiLen++] = 0x02;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetBatterySwap()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_BATTERYSWAP;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +1;
	
	Buffer[uiLen++] = 0x19;//电池更换
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = 1;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetRebootWiapa()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_WIAPAREBOOT;
		return SendCan(CANEXTCMD,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +1;
	
	Buffer[uiLen++] = 0x1A;//无线重启
	Buffer[uiLen++] = 0x02;
	
	Buffer[uiLen++] = 0x01;
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetParameter()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[7] = 0x01;//发送初始化数据
		return SendCan(0x04,Buffer);// 查询信息
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = 0x1B;//读取参数
	Buffer[uiLen++] = 0x02;
	
	
	return SendWiapa(Buffer,uiLen);
}


int CUart::GetWarning(unsigned char w)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[7] = 0x00;///发送故障信息
		return SendCan(0x04,Buffer);// 查询信息
	}
	
	Buffer[uiLen++] = 0x01;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3;
	
	Buffer[uiLen++] = w;//0x00 ~ 0x08
	Buffer[uiLen++] = 0x03;//查询告警信息
	
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetWsyRecord(unsigned char* s,unsigned char* e)
{
	unsigned int i,uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = 0x00;
		memcpy(Buffer+1,s,6);
		Buffer[7] = 0xFF;
		SendCan(0x05,Buffer);// 查询信息
		memset(Buffer,0xFF,8);
		Buffer[0] = 0x01;
		memcpy(Buffer+1,e,6);
		Buffer[7] = 0xFF;
		return SendCan(0x05,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +12;
	
	Buffer[uiLen++] = 0x00;//历史温湿压
	Buffer[uiLen++] = 0x04;
	
	for(i = 0;i < 6; i++)
	{
		Buffer[uiLen++] = *s++;
	}
	for(i = 0;i < 6; i++)
	{
		Buffer[uiLen++] = *e++;
	}
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetWsyRecordBu(unsigned int cnt,unsigned int* pid)
{
	unsigned int i,v,uiLen = 0;
	unsigned char Buffer[256];
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +(cnt*4);
	
	Buffer[uiLen++] = 0x01;//历史温湿压补包
	Buffer[uiLen++] = 0x04;
	
	for(i = 0;i < cnt; i++)
	{
		v = *pid++;
		Buffer[uiLen++] = (uint8_t)(v>>0);
		Buffer[uiLen++] = (uint8_t)(v>>8);
		Buffer[uiLen++] = (uint8_t)(v>>16);
		Buffer[uiLen++] = (uint8_t)(v>>24);
	}
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetZhendongRecord(unsigned char* s,unsigned char* e)
{
	unsigned int i,uiLen = 0;
	unsigned char Buffer[256];

	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = 0x00;
		memcpy(Buffer+1,s,6);
		Buffer[7] = 0xFF;
		SendCan(0x06,Buffer);// 查询信息
		Buffer[0] = 0x01;
		memcpy(Buffer+1,e,6);
		Buffer[7] = 0xFF;
		return SendCan(0x06,Buffer);
	}
	
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +12;
	
	Buffer[uiLen++] = 0x02;//历史振动
	Buffer[uiLen++] = 0x04;
	
	for(i = 0;i < 6; i++)
	{
		Buffer[uiLen++] = *s++;
	}
	for(i = 0;i < 6; i++)
	{
		Buffer[uiLen++] = *e++;
	}
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetZhendongRecordBu(unsigned int cnt,unsigned int* pid)
{
	unsigned int i,v,uiLen = 0;
	unsigned char Buffer[256];

	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;
	
	Buffer[uiLen++] = 3 +(cnt*4);
	
	Buffer[uiLen++] = 0x03;//历史振动补包
	Buffer[uiLen++] = 0x04;
	
	for(i = 0;i < cnt; i++)
	{
		v = *pid++;
		Buffer[uiLen++] = (uint8_t)(v>>0);
		Buffer[uiLen++] = (uint8_t)(v>>8);
		Buffer[uiLen++] = (uint8_t)(v>>16);
		Buffer[uiLen++] = (uint8_t)(v>>24);
	}
	
	return SendWiapa(Buffer,uiLen);
}

int CUart::TD_SystemReset()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SYSRESET;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 4;	
	Buffer[uiLen++] = 0x17;
	Buffer[uiLen++] = 0x02;		
	Buffer[uiLen++] = 0x01;
	return SendWiapa(Buffer,uiLen);
}
int CUart::TD_SetHwVersion(unsigned int uiVer)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_HWVERSION;
		Buffer[1] = (uint8_t)(uiVer/100);
		Buffer[2] = (uint8_t)((uiVer%100)/10);
		Buffer[3] = (uint8_t)(uiVer%10);
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 7;	
	Buffer[uiLen++] = 0x17;
	Buffer[uiLen++] = 0x02;		
	Buffer[uiLen++] = 0x02;

	Buffer[uiLen++] = (uint8_t)(uiVer/100);
	Buffer[uiLen++] = (uint8_t)((uiVer%100)/10);
	Buffer[uiLen++] = (uint8_t)(uiVer%10);

	return SendWiapa(Buffer,uiLen);
}
int CUart::TD_GetDateTime()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETTIME;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x01;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 3;	
	Buffer[uiLen++] = 0x16;
	Buffer[uiLen++] = 0x02;
	return SendWiapa(Buffer,uiLen);
}
int CUart::TD_Reboot()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SYSREBOOT;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 4;	
	Buffer[uiLen++] = 0x17;
	Buffer[uiLen++] = 0x02;		
	Buffer[uiLen++] = 0x03;
	return SendWiapa(Buffer,uiLen);
}

int CUart::TD_TempAC(unsigned int uiSetAcTemp)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_TEMPCAL;
		//20190809
		Buffer[1] = (unsigned char)(uiSetAcTemp>>8);
		Buffer[2] = (unsigned char)(uiSetAcTemp);
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 6;//4; //20190809	
	Buffer[uiLen++] = 0x17;
	Buffer[uiLen++] = 0x02;		
	Buffer[uiLen++] = 0x04;
	
	//20190809
	Buffer[uiLen++] = (unsigned char)(uiSetAcTemp>>8);
	Buffer[uiLen++] = (unsigned char)(uiSetAcTemp);
	return SendWiapa(Buffer,uiLen);
}

int CUart::GetPanID()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETPANID;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x01;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 3;	
	Buffer[uiLen++] = 0x10;
	Buffer[uiLen++] = 0x02;		
	return SendWiapa(Buffer,uiLen);
}
int CUart::GetBoardcast()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETBDCAST;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x01;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 3;	
	Buffer[uiLen++] = 0x11;
	Buffer[uiLen++] = 0x02;		
	return SendWiapa(Buffer,uiLen);
}

int CUart::SetWiapaAddress(unsigned char*pd)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETWIAADDR;
		Buffer[1] = 0;
		memcpy(Buffer+2,pd,4);
		SendCan(CANEXTCMD,Buffer);
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETWIAADDR;
		Buffer[1] = 1;
		memcpy(Buffer+2,pd+4,4);
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 3+8;	
	Buffer[uiLen++] = 0x12;
	Buffer[uiLen++] = 0x02;
	memcpy(Buffer+uiLen,pd,8);
	uiLen += 8;
	return SendWiapa(Buffer,uiLen);
}
int CUart::GetWiapaAddress()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETWIAADDR;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x01;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 3;	
	Buffer[uiLen++] = 0x12;
	Buffer[uiLen++] = 0x02;		
	return SendWiapa(Buffer,uiLen);
}

int CUart::TD_ZhendongAC()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_ZHENDONGCAL;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 4;	
	Buffer[uiLen++] = 0x17;
	Buffer[uiLen++] = 0x02;		
	Buffer[uiLen++] = 0x05;
	return SendWiapa(Buffer,uiLen);
}

int CUart::TD_SetWaitCmdTime(unsigned char ucTm)
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_SETWAITCMDTIME;
		Buffer[1] = ucTm;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x02;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 5;	
	Buffer[uiLen++] = 0x17;
	Buffer[uiLen++] = 0x02;		
	Buffer[uiLen++] = 0x06;
	Buffer[uiLen++] = ucTm;
	return SendWiapa(Buffer,uiLen);
}
int CUart::TD_GetWaitCmdTime()
{
	unsigned int uiLen = 0;
	unsigned char Buffer[256];
	
	if(m_iCI == US_CANFROM)
	{
		memset(Buffer,0xFF,8);
		Buffer[0] = CCE_GETWAITCMDTIME;
		return SendCan(CANEXTCMD,Buffer);
	}
	Buffer[uiLen++] = 0x01;
	Buffer[uiLen++] = 0x00;	
	Buffer[uiLen++] = 4;	
	Buffer[uiLen++] = 0x17;
	Buffer[uiLen++] = 0x02;		
	Buffer[uiLen++] = 0x06;
	return SendWiapa(Buffer,uiLen);
}