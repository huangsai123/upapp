// Uart.h: interface for the CUart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UART_H__27D75DE5_2C94_4989_A2C8_4485C3999C94__INCLUDED_)
#define AFX_UART_H__27D75DE5_2C94_4989_A2C8_4485C3999C94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

#define WM_ONCOMMSG		(WM_USER+100)
#define WM_ONCANMSG		(WM_USER+101)
#define WM_ONTXTMSG		(WM_USER+102)


typedef   signed char	int8_t;
typedef   signed short	int16_t;
typedef   signed int	int32_t;

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;




/*****************
C51/PC++
*****************/
#define US_IDLE				0x00
#define US_RESET			0x01
#define US_BOOT_START		0x02
#define US_BOOT_BIN			0x03
#define US_BOOT_END			0x04
#define US_BOOT_READY		0x05
#define US_APP_START		0x06
#define US_APP_BIN			0x07
#define US_APP_END			0x08
#define US_REBOOT			0x09

#define CANUPGRADECMD		0x1E
#define CANEXTCMD			0x1D
#define WIAPAUPGRADECMDTYPE	0x08
#define WIAPAUPGRADECMD0	0x08
#define WIAPAUPGRADECMD1	0x08
#define UPGRADECHAR			'U'
#define UPGRADEAPP			1
#define UPGRADEBOOT			2

#define UERR_SUCCESS		0
#define UERR_SN				1
#define UERR_BUSY			2
#define UERR_FLAG			3
#define UERR_FORM			4
#define UERR_STATE			5
#define UERR_NOINIT			6
#define UERR_NOTAPPBOOT		7
#define UERR_DATALEN		8
#define UERR_FLASHERASE		9
#define UERR_CRC			10
#define UERR_NOCRCCHK		11
#define UERR_BOOTNOREADY	12


#define CCE_HWVERSION		0x00
#define CCE_SYSRESET		0x01
#define CCE_GETTIME			0x02
#define CCE_SYSREBOOT		0x03
#define CCE_TEMPCAL			0x04
#define CCE_YALICAL			0x05
#define CCE_SETPANID		0x06
#define CCE_GETPANID		0x07
#define CCE_SETBDCAST		0x08
#define CCE_GETBDCAST		0x09
#define CCE_WIAPAREBOOT		0x0A
#define CCE_SETWORKMODE		0x0B
#define CCE_GETWORKMODE		0x0C
#define CCE_SETWIAADDR		0x0D
#define CCE_GETWIAADDR		0x0E

#define CCE_BATTERYSWAP		0x0F

#define CCE_SETTEMPMENXIAN	0x10
#define CCE_GETTEMPMENXIAN	0x11
#define CCE_SETSHIDUMENXIAN	0x12
#define CCE_GETSHIDUMENXIAN	0x13
#define CCE_SETYALIMENXIAN	0x14
#define CCE_GETYALIMENXIAN	0x15

#define CCE_ZHENDONGCAL		0x16
#define CCE_SETWAITCMDTIME  0x17
#define CCE_GETWAITCMDTIME  0x18

/*****************
--PC/C51
*****************/

#define US_CANFROM			0x01
#define US_WIAFROM			0x02
#define US_COMFROM			0x03

typedef struct _UDHEADER
{
	unsigned short usCrc;
	unsigned short usLength;
	unsigned int   uiVersion;
}UDHEADER,*PUDHEADER;



typedef struct _UDCTRL
{
	unsigned int	uiStep;

	unsigned int	uiOverTimer;
	unsigned int    uiWaitMsgTimer;

	unsigned short	usAppEndPos;
	unsigned short	usBootEndPos;

	UDHEADER	    Header;
	UDHEADER	    appHeader;
	UDHEADER	    bootHeader;
	unsigned char	ucFwBin[128*1024];
	unsigned char	ucFwBinNull[128*1024];
	unsigned char	ucTempFwBin[128*1024];
	unsigned char	ucTempFwBinNull[128*1024];

	unsigned char	ucRxData[1024];

	unsigned short  usMsg2Tx;
	unsigned short  usMsgCnt;
	unsigned char	msgQueue[32768][72];
	

}UDCTRL,*PUDCTRL;


class CUart  
{
public:
	CUart();

	BOOL IsOpened(){return m_IsOpened;}
	BOOL Open(char *pComStr, int iCI,HWND hWind,int iCanID);
	BOOL Open(char *pIPStr, int iCI,HWND hWind,int port,char* addr);
	void Close();
	void CanID(int iCanID);

	int UpgradeReset();
	int UpgradeAddFile(char*fn);
	int UpgradeStart();
	int UpgradeStop();

	int GetVersion();
	int DoCollectOnce();
		
	int SetZhendongMenXianZhouqi(unsigned short mx,unsigned short zq);
	int GetZhendongMenXianZhouqi();
	int SetZhouqi(unsigned short zq);
	int GetZhouqi();
	int SetZhendongMenXian(unsigned short v);
	int GetZhendongMenXian();

	int SetWenduMenXian(short shang,short xia);
	int GetWenduMenXian();

	int SetShiduMenXian(unsigned short shang,unsigned short xia);
	int GetShiduMenXian();

	int SetYaliMenXian(unsigned short shang,unsigned short xia);
	int GetYaliMenXian();

	int DelWenshiyaRecord();
	int DelZhendongRecord();

	int SetDanNumber(unsigned char *pd);
	int GetDanNumber();

	int SetBangNumber(unsigned char *pd);
	int GetBangNumber();

	int SetPanID(unsigned short panid);
	int SetBoardcast(unsigned char bd);
	int SetCalibrationYali(unsigned short v);
	int SetStop();
	int SetDateTime();

	int GetPanID();
	int GetBoardcast();

	int SetWiapaAddress(unsigned char*pd);
	int GetWiapaAddress();

	int SetSaveMode(int mode);
	int GetSaveMode();

	int SetBatterySwap();
	int SetRebootWiapa();
	int GetParameter();

	int GetWarning(unsigned char w);

	int GetWsyRecord(unsigned char* s,unsigned char* e);
	int GetWsyRecordBu(unsigned int cnt,unsigned int* pid);
	int GetZhendongRecord(unsigned char* s,unsigned char* e);
	int GetZhendongRecordBu(unsigned int cnt,unsigned int* pid);

	int TD_SystemReset();
	int TD_SetHwVersion(unsigned int uiVer);
	int TD_GetDateTime();
	int TD_Reboot();
	int TD_TempAC(unsigned int uiSetAcTemp);

	int TD_ZhendongAC();
	int TD_SetWaitCmdTime(unsigned char ucTm);
	int TD_GetWaitCmdTime();

private:

	UDCTRL	m_UpgradeCtrl;
		
	unsigned char m_ucRxData[4096],m_ucLastChar;
	unsigned int m_uiRxLen;

	unsigned char	m_ucErrRxData[65536];
	unsigned short	m_usErrRxLen;

	unsigned short m_usZhennum;

	CRITICAL_SECTION cs;
	CRITICAL_SECTION csPrint;

	unsigned char m_ucCanID;
	int  m_iCI;
	BOOL m_IsOpened;
	BOOL m_RecvThreadStopFlag;

	HANDLE m_hComHandle;
	OVERLAPPED m_oSend;
	OVERLAPPED m_oRecv;
	HANDLE	m_hEvtRecv;
	HANDLE	m_hEvtSend;
	HANDLE	m_rxThread;

	int		m_skt;
	unsigned char m_ucDevAddr[8];
	struct sockaddr_in m_gwAddr;


	HWND m_hWind;

	FILE *m_fpLog;
	void DbgPrintf(char *fmt,...);
	void PrintTime();
	void Msg(int bc,char* fmt,...);

	int SendCan(unsigned char ucFunID,unsigned char* pData);

	int DoSendUdp(unsigned char ucLen,unsigned char* pData);
	int SendUdp(unsigned char ucLen,unsigned char* pData);

	int DoSendWiapa(unsigned char* pData,unsigned int dl);
	int SendWiapa(unsigned char* pData,unsigned int dl);

	int SendData(unsigned char* pData,unsigned int uiLen);

	void WiapaUpgradeRecvMsg(unsigned char *pData,unsigned char dl);

	void UpgradePreprocessData(unsigned char msgMaxLen);

	void CanOnRecvChar(unsigned char c);
	void CanOnRecFrame(unsigned char ucCmd,unsigned char *pc);
	void ComOnRecvChar(unsigned char c);
	void UpgradeRecvMsg(unsigned int from,unsigned char *pData,unsigned char dl);
	BOOL UpgradeProcessRecvFrame(unsigned char*pData,unsigned int dl);
	BOOL ProcessRecvFrame(unsigned char*pData,unsigned int dl);
	void PrintRecvFrame(unsigned char* pData,unsigned int dl);
	void OnRecvBuf(unsigned char *pData,int iLen);
	void RecvThreadLoop();
	void UDPRecvThreadLoop();
	static DWORD RecvThread(LPVOID lpParameter)
	{
		((CUart *)lpParameter)->RecvThreadLoop();
		return 0;
	}
	static DWORD UDPRecvThread(LPVOID lpParameter)
	{
		((CUart *)lpParameter)->UDPRecvThreadLoop();
		return 0;
	}
};

#endif // !defined(AFX_UART_H__27D75DE5_2C94_4989_A2C8_4485C3999C94__INCLUDED_)
