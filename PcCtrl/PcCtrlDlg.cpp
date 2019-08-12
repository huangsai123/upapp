// PcCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PcCtrl.h"
#include "PcCtrlDlg.h"
#include "SetACTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcCtrlDlg dialog

CPcCtrlDlg::CPcCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPcCtrlDlg::IDD, pParent)
{
	char bf[256],IP[256],devAddr[256];
	bf[0] = 0;
	GetProfileString("C040","COM","",bf,255);
	IP[0] = 0;
	GetProfileString("C040","UDPIP","",IP,255);
	devAddr[0] = 0;
	GetProfileString("C040","DevAddr","",devAddr,255);

	//{{AFX_DATA_INIT(CPcCtrlDlg)
	m_csUsart = bf;
	m_uiZhouqi = 0;
	m_uiWenduMenxianXia = 0;
	m_uiWenduMenxiaShang = 0;
	m_uiShiduMenxianXia = 0;
	m_uiShiduMenxiaShang = 0;
	m_uiYaliMenxianXia = 0;
	m_uiYaliMenXiaShang = 0;
	m_uiZhendongMenxian = 0;
	m_csDanNumber = _T("");
	m_csBangNumber = _T("");
	m_uiPanID = 0;
	m_uiBoardcast = 0;
	m_uiYaliCaliration = 0;
	m_uiWarning = 0;
	m_csWsyStart = _T("180101000000");
	m_csWsyEnd = _T("200101000000");
	m_csZhendongStart = _T("180101000000");
	m_csZhendongEnd = _T("200101000000");
	m_csWsyBu = _T("");
	m_csZhendongBu = _T("");
	m_iCanID = 0;
	m_csIP = IP;
	m_uiPort = GetProfileInt("C040","UDPPort",0);;
	m_csDevAddr = devAddr;
	m_iCI = GetProfileInt("C040","CI",0);
	m_csMsg = _T("");
	m_uiHwVersion = 0;
	m_csWiaAddress = _T("");
	m_uiWaitCmdTime = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPcCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPcCtrlDlg)
	DDX_Control(pDX, IDC_COMBO_COM, m_UartList);
	DDX_CBString(pDX, IDC_COMBO_COM, m_csUsart);
	DDX_Text(pDX, IDC_EDIT_ZHOUQI, m_uiZhouqi);
	DDX_Text(pDX, IDC_EDIT_WENDUMENGXIANXIA, m_uiWenduMenxianXia);
	DDX_Text(pDX, IDC_EDIT_WENDUMENXAINGSHAGN, m_uiWenduMenxiaShang);
	DDX_Text(pDX, IDC_EDIT_SHIDUMENGXIANXIA, m_uiShiduMenxianXia);
	DDX_Text(pDX, IDC_EDIT_SHIDUMENXAINGSHAGN, m_uiShiduMenxiaShang);
	DDX_Text(pDX, IDC_EDIT_YALIMENGXIANXIA, m_uiYaliMenxianXia);
	DDX_Text(pDX, IDC_EDIT_YALIMENXAINGSHAGN, m_uiYaliMenXiaShang);
	DDX_Text(pDX, IDC_EDIT_ZHENDONGMENGXIANXIA, m_uiZhendongMenxian);
	DDX_Text(pDX, IDC_EDIT_DANNUMBER, m_csDanNumber);
	DDX_Text(pDX, IDC_EDIT_BANDNUMBER, m_csBangNumber);
	DDX_Text(pDX, IDC_EDIT_PANID, m_uiPanID);
	DDX_Text(pDX, IDC_EDIT_SETBOARDCAST, m_uiBoardcast);
	DDX_Text(pDX, IDC_EDIT_YALICALIRATION, m_uiYaliCaliration);
	DDX_CBIndex(pDX, IDC_COMBO_WARNING, m_uiWarning);
	DDX_Text(pDX, IDC_EDIT_HISTORY_WSY_START, m_csWsyStart);
	DDX_Text(pDX, IDC_EDIT_HISTORY_WSY_END, m_csWsyEnd);
	DDX_Text(pDX, IDC_EDIT_HISTORY_ZHENDONG_START, m_csZhendongStart);
	DDX_Text(pDX, IDC_EDIT_HISTORY_ZHENDONG_END, m_csZhendongEnd);
	DDX_Text(pDX, IDC_EDIT_WSY_BU, m_csWsyBu);
	DDX_Text(pDX, IDC_EDIT_ZHENDONG_BU, m_csZhendongBu);
	DDX_CBIndex(pDX, IDC_COMBO_CANID, m_iCanID);
	DDX_Text(pDX, IDC_EDIT_UDP_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_UDP_PORT, m_uiPort);
	DDX_Text(pDX, IDC_EDIT_DEVADDR, m_csDevAddr);
	DDX_Radio(pDX, IDC_RADIO_CI_CAN, m_iCI);
	DDX_Text(pDX, IDC_STATIC_MSG, m_csMsg);
	DDX_Text(pDX, IDC_EDIT_HWVERSION, m_uiHwVersion);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_csWiaAddress);
	DDX_Text(pDX, IDC_EDIT_WAITCMDTIME, m_uiWaitCmdTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPcCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CPcCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_DROPDOWN(IDC_COMBO_COM, OnDropdownComboCom)
	ON_BN_CLICKED(IDC_BUTTON_COM_OC, OnButtonComOc)
	ON_BN_CLICKED(IDC_BUTTON_GETVER, OnButtonGetVersion)
	ON_BN_CLICKED(IDC_BUTTON_UPGRADE, OnButtonUpgrade)
	ON_BN_CLICKED(IDC_BUTTON_CONSOLE, OnButtonConsole)
	ON_BN_CLICKED(IDC_BTN_SYNCDATETIME, OnBtnSyncdatetime)
	ON_BN_CLICKED(IDC_BTN_SETZHOUQI, OnBtnSetzhouqi)
	ON_BN_CLICKED(IDC_BTN_GETZHOUQI, OnBtnGetzhouqi)
	ON_BN_CLICKED(IDC_BTN_SETWENDUMENXIAN, OnBtnSetwendumenxian)
	ON_BN_CLICKED(IDC_BTN_GETWENDUMENXIAN, OnBtnGetwendumenxian)
	ON_BN_CLICKED(IDC_BTN_SETSHIDUMENXIAN, OnBtnSetshidumenxian)
	ON_BN_CLICKED(IDC_BTN_GETSHIDUMENXIAN, OnBtnGetshidumenxian)
	ON_BN_CLICKED(IDC_BTN_SETYALIMENXIAN, OnBtnSetyalimenxian)
	ON_BN_CLICKED(IDC_BTN_GETYALIMENXIAN, OnBtnGetyalimenxian)
	ON_BN_CLICKED(IDC_BTN_SETZHENDONGMENXIAN, OnBtnSetzhendongmenxian)
	ON_BN_CLICKED(IDC_BTN_GETZHENDONGMENXIAN, OnBtnGetzhendongmenxian)
	ON_BN_CLICKED(IDC_BTN_DELWSYRECORD, OnBtnDelwsyrecord)
	ON_BN_CLICKED(IDC_BTN_DELZHENDONGRECORD, OnBtnDelzhendongrecord)
	ON_BN_CLICKED(IDC_BTN_SETDANNUMBER, OnBtnSetdannumber)
	ON_BN_CLICKED(IDC_BTN_GETDANNUMBER, OnBtnGetdannumber)
	ON_BN_CLICKED(IDC_BTN_SETBANDNUMBER, OnBtnSetbandnumber)
	ON_BN_CLICKED(IDC_BTN_GETBANDNUMBER, OnBtnGetbandnumber)
	ON_BN_CLICKED(IDC_BTN_SETPANID, OnBtnSetpanid)
	ON_BN_CLICKED(IDC_BTN_SETBOARDCAST, OnBtnSetboardcast)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_SETSAVEMODE, OnBtnSetsavemode)
	ON_BN_CLICKED(IDC_BTN_BATTERYSWAP, OnBtnBatteryswap)
	ON_BN_CLICKED(IDC_BTN_GETSAVEMODE, OnBtnGetsavemode)
	ON_BN_CLICKED(IDC_BTN_SETYALICALIRATION, OnBtnSetyalicaliration)
	ON_BN_CLICKED(IDC_BTN_GETPARAMETER, OnBtnGetparameter)
	ON_BN_CLICKED(IDC_BTN_QUERYWARNING, OnBtnQuerywarning)
	ON_BN_CLICKED(IDC_BTN_HISTORY_WSY, OnBtnHistoryWsy)
	ON_BN_CLICKED(IDC_BTN_HISTORY_ZHENDONG, OnBtnHistoryZhendong)
	ON_BN_CLICKED(IDC_BTN_DOCOLLECTONCE, OnBtnDocollectonce)
	ON_BN_CLICKED(IDC_BTN_SETSAVEMODE_NO, OnBtnSetsavemodeNo)
	ON_BN_CLICKED(IDC_BTN_WSY_BU, OnBtnWsyBu)
	ON_BN_CLICKED(IDC_BTN_ZHENDONG_BU, OnBtnZhendongBu)
	ON_CBN_SELENDOK(IDC_COMBO_CANID, OnSelendokComboCanid)
	ON_BN_CLICKED(IDC_BTN_REBOOTWIAPA, OnBtnRebootwiapa)
	ON_BN_CLICKED(IDC_BUTTON_SETVER, OnButtonSetHwVersion)
	ON_BN_CLICKED(IDC_BTN_GETDATETIME, OnBtnGetdatetime)
	ON_BN_CLICKED(IDC_BTN_SYSRESET, OnBtnSysreset)
	ON_BN_CLICKED(IDC_BTN_GETPANID, OnBtnGetpanid)
	ON_BN_CLICKED(IDC_BTN_GETBOARDCAST, OnBtnGetboardcast)
	ON_BN_CLICKED(IDC_BTN_SETADDRESS, OnBtnSetaddress)
	ON_BN_CLICKED(IDC_BTN_GETADDRESS, OnBtnGetaddress)
	ON_BN_CLICKED(IDC_BTN_SETTEMPCALIRATION, OnBtnSettempcaliration)
	ON_BN_CLICKED(IDC_BTN_REBOOTMCU, OnBtnRebootmcu)
	ON_BN_CLICKED(IDC_BUTTON_STOP_UPGRADE, OnButtonStopUpgrade)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_ZHENDONGCA, OnBtnZhendongca)
	ON_BN_CLICKED(IDC_BTN_SETWAITTIME, OnBtnSetwaittime)
	ON_BN_CLICKED(IDC_BTN_GETWAITTIME, OnBtnGetwaittime)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ONCOMMSG,OnComRxMsg)
	ON_MESSAGE(WM_ONCANMSG,OnCanRxMsg)
	ON_MESSAGE(WM_ONTXTMSG,OnTxtMsg)

	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcCtrlDlg message handlers

BOOL CPcCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_bConsole = FALSE;
	OnDropdownComboCom();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPcCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	UINT _nID = nID & 0xFFF0;
	if (_nID == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPcCtrlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPcCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



BOOL CPcCtrlDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CPcCtrlDlg::OnDropdownComboCom() 
{
	// TODO: Add your control notification handler code here
	while(m_UartList.GetCount()>0)m_UartList.DeleteString(0);
	HKEY hKey;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Hardware\\DeviceMap\\SerialComm",NULL,KEY_READ,&hKey) == ERROR_SUCCESS)
	{
		int i=0,id=-1;
		TCHAR portName[256],commName[256];
		DWORD dwLong,dwSize;
		
		while(1)
		{
			dwLong = dwSize = sizeof(portName);
			if(RegEnumValue(hKey, i, portName, &dwLong, NULL, NULL, (LPBYTE)commName, &dwSize ) == ERROR_NO_MORE_ITEMS )break;
			m_UartList.AddString(commName);
			i++;
		}
		RegCloseKey(hKey);
	}
}
#include "io.h"
#include "fcntl.h"
void CPcCtrlDlg::OnButtonConsole() 
{
	if(!m_bConsole)
	{
		m_bConsole = TRUE;
		((CWnd*)GetDlgItem(IDC_BUTTON_CONSOLE))->SetWindowText("关闭DBG");
		AllocConsole();
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		int hCrt = _open_osfhandle((long)handle,_O_TEXT);
		FILE *hf = _fdopen(hCrt,"w");
		*stdout = *hf;
	}
	else
	{
		m_bConsole = FALSE;
		((CWnd*)GetDlgItem(IDC_BUTTON_CONSOLE))->SetWindowText("打开DBG");
		FreeConsole();
	}
}
void CPcCtrlDlg::OnClose() 
{
	m_Uart.Close();
	CDialog::OnClose();
}
void CPcCtrlDlg::OnButtonComOc() 
{
	if(m_Uart.IsOpened())
	{
		GetDlgItem(IDC_BUTTON_COM_OC)->SetWindowText("打开");
		m_Uart.Close();
	}
	else
	{
		UpdateData();
		char bf[256],addr[256];
		strcpy(bf,m_csUsart);
		if(m_iCI == 0 || m_iCI == 1)
		{
			if(m_Uart.Open(bf,m_iCI==0?US_CANFROM:US_COMFROM,m_hWnd,m_iCanID))
			{
				m_bUDP = FALSE;
				m_bCan = m_iCI==0;
				GetDlgItem(IDC_BUTTON_COM_OC)->SetWindowText("关闭");
				WriteProfileString("C040","COM",bf);
				sprintf(bf,"%d",m_iCI);
				WriteProfileString("C040","CI",bf);		
			}
			else
			{
				AfxMessageBox("打开串口失败");
			}
		}
		else if(m_iCI == 2)
		{
			strcpy(bf,m_csIP);
			strcpy(addr,m_csDevAddr);
			if(m_Uart.Open(bf,US_WIAFROM,m_hWnd,m_uiPort,addr))
			{
				m_bUDP = TRUE;
				m_bCan = FALSE;
				GetDlgItem(IDC_BUTTON_COM_OC)->SetWindowText("关闭");
				WriteProfileString("C040","UDPIP",bf);
				sprintf(bf,"%d",m_iCI);
				WriteProfileString("C040","CI",bf);
				sprintf(bf,"%d",m_uiPort);
				WriteProfileString("C040","UDPPort",bf);
				WriteProfileString("C040","DevAddr",addr);		
			}
			else
			{
				AfxMessageBox("UDP连接失败");
			}
		}
	}
}


LRESULT CPcCtrlDlg::OnTxtMsg(WPARAM wp,LPARAM ucCmd)
{
	unsigned char *pc = (unsigned char *)wp;
	CString cs(pc);
	UpdateData();
	if(ucCmd)m_csMsg = "";
	m_csMsg += cs;
	UpdateData(FALSE);
	SendDlgItemMessage(IDC_STATIC_MSG,WM_VSCROLL,SB_BOTTOM,0);
	return 0;
}
LRESULT CPcCtrlDlg::OnCanRxMsg(WPARAM wp,LPARAM ucCmd)
{
	uint16_t usXx,usXx1;
	unsigned char ucXx;
	CString cs;
	unsigned char *pc = (unsigned char *)wp;

	switch(ucCmd)
	{
	case 0x00:
		UpdateData();
		m_csMsg.Format("故障信息:\r\n");
		cs.Format("指令:%s\r\n",pc[0]?"错误":"正常");		m_csMsg += cs;
		cs.Format("温度传感器:%s\r\n",pc[1]?"错误":"正常");	m_csMsg += cs;
		cs.Format("湿度传感器:%s\r\n",pc[2]?"错误":"正常");	m_csMsg += cs;
		cs.Format("内压传感器:%s\r\n",pc[3]?"错误":"正常");	m_csMsg += cs;
		cs.Format("外压传感器:%s\r\n",pc[4]?"错误":"正常");	m_csMsg += cs;
		cs.Format("振动传感器:%s\r\n",pc[5]?"错误":"正常");	m_csMsg += cs;
		cs.Format("振动超限故障:%s\r\n",pc[6]?"错误":"正常");m_csMsg += cs;
		cs.Format("压差超限故障:%s\r\n",pc[7]?"错误":"正常");m_csMsg += cs;
		UpdateData(FALSE);
		break;
	case 0x01:
		UpdateData();
		m_csMsg.Format("读取初始化信息:\r\n");
		if(pc[0] == 0x00)cs.Format("设备状态:未知\r\n");
		else if(pc[0] == 0x0F)cs.Format("设备状态:正常\r\n");
		else if(pc[0] == 0xF0)cs.Format("设备状态:异常\r\n");		m_csMsg += cs;
		cs.Format("传感器:%s\r\n",pc[1] == 0x55?"正常":"异常");		m_csMsg += cs;
		cs.Format("自检通信:%s\r\n",pc[2] == 0x55?"正常":"异常");	m_csMsg += cs;
		cs.Format("自检数据:%s\r\n",pc[3] == 0x55?"正常":"异常");	m_csMsg += cs;
		cs.Format("接口初始化:%s\r\n",pc[4] == 0x55?"正常":"异常");	m_csMsg += cs;
		if(pc[5] == 0x01)cs.Format("查询发送方式\r\n");
		else if(pc[5] == 0x02)cs.Format("循环发送方式\r\n");
		else if(pc[5] == 0x03)cs.Format("中断发送方式\r\n");		m_csMsg += cs;
		if(pc[6] == 0x02)cs.Format("通信速率 250kbps\r\n");
		else if(pc[6] == 0x03)cs.Format("通信速率 500kbps\r\n");
		else if(pc[6] == 0x04)cs.Format("通信速率 1000kbps\r\n");	m_csMsg += cs;
		cs.Format("记录仪ID:%02X\r\n",pc[7]);						m_csMsg += cs;
		UpdateData(FALSE);
		break;
	case 0x04:
		UpdateData();
		m_csMsg.Format("查询实时采集数据:\r\n");
		if(pc[0] == 0x00)
		{
			usXx = (pc[1]<<8)|pc[2];
			cs.Format("温度:%d.%d\r\n",usXx/10,usXx%10);			m_csMsg += cs;
			usXx = (pc[3]<<8)|pc[4];
			cs.Format("湿度:%d.%d\r\n",usXx/10,usXx%10);			m_csMsg += cs;
			usXx = (pc[5]<<8)|pc[6];
			cs.Format("压差:%d.%d\r\n",usXx/10,usXx%10);			m_csMsg += cs;
		}
		else if(pc[0] == 0x01)
		{
			ucXx = pc[1];
			cs.Format("温度传感器:%s  ",(ucXx&0x02)?"故障":"正常");m_csMsg += cs;
			cs.Format("湿度传感器:%s\r\n",(ucXx&0x04)?"故障":"正常");m_csMsg += cs;
			cs.Format("内压传感器:%s  ",(ucXx&0x08)?"故障":"正常");m_csMsg += cs;
			cs.Format("外压传感器:%s\r\n",(ucXx&0x10)?"故障":"正常");m_csMsg += cs;
			cs.Format("振动传感器:%s  ",(ucXx&0x20)?"故障":"正常");m_csMsg += cs;
			cs.Format("振动超限  :%s\r\n",(ucXx&0x40)?"故障":"正常");	 m_csMsg += cs;
			cs.Format("电量      :%s\r\n",(ucXx&0x80)?"故障":"正常");m_csMsg += cs;
			cs.Format("电量:%d%%\r\n",pc[2]);						m_csMsg += cs;
			usXx = (pc[3]<<8)|pc[4];
			cs.Format("内压:%d.%d\r\n",usXx/10,usXx%10);			m_csMsg += cs;
			usXx = (pc[5]<<8)|pc[6];
			cs.Format("外压:%d.%d\r\n",usXx/10,usXx%10);			m_csMsg += cs;
		}
		UpdateData(FALSE);
		break;
	case 0x07:
		UpdateData();
		m_csMsg.Format("时间同步:%02d/%02d/%02d %02d:%02d:%02d\r\n",pc[0],pc[1],pc[2],pc[3],pc[4],pc[5]);
		UpdateData(FALSE);
		break;
	case 0x08:
		UpdateData();
		     if(pc[7] == 0x00)m_csMsg.Format("振动门限 %u;采集周期 %u [%d秒] 设置成功\r\n",pc[0],((pc[1]<<8)|pc[2]),((pc[1]<<8)|pc[2])*10);
		else if(pc[7] == 0x01)m_csMsg.Format("振动门限 %u;采集周期 %u [%d秒] 设置失败\r\n",pc[0],((pc[1]<<8)|pc[2]),((pc[1]<<8)|pc[2])*10);
		else if(pc[7] == 0x02)m_csMsg.Format("振动门限 %u;采集周期 %u [%d秒] 读取成功\r\n",pc[0],((pc[1]<<8)|pc[2]),((pc[1]<<8)|pc[2])*10);
		else if(pc[7] == 0x03)m_csMsg.Format("振动门限 %u;采集周期 %u [%d秒] 读取失败\r\n",pc[0],((pc[1]<<8)|pc[2]),((pc[1]<<8)|pc[2])*10);
		if(pc[7] == 0x02)
		{
			m_uiZhendongMenxian = pc[0];
			m_uiZhouqi = ((pc[1]<<8)|pc[2]);
		}
		UpdateData(FALSE);
		break;
	case 0x09:
		UpdateData();
		m_csMsg.Format("历史温湿度数据擦除:%s\r\n",pc[0]==0x00?"成功":"失败");
		UpdateData(FALSE);
		break;
	case 0x0A:
		UpdateData();
		m_csMsg.Format("历史振动数据擦除:%s\r\n",pc[0]==0x00?"成功":"失败");
		UpdateData(FALSE);
		break;
	case 0x0C:
		UpdateData();
		     if(pc[0] == 0x00)m_csMsg.Format("箱号 设置成功:%c%c%c%c%c%c%c\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		else if(pc[0] == 0x01)m_csMsg.Format("箱号 设置失败:%c%c%c%c%c%c%c\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		else if(pc[0] == 0x02)m_csMsg.Format("箱号 读取成功:%c%c%c%c%c%c%c\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		else if(pc[0] == 0x03)m_csMsg.Format("箱号 读取失败:%c%c%c%c%c%c%c\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);		
		if(pc[0] == 0x02)
		{
			m_csBangNumber.Format("%c%c%c%c%c%c%c",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		}
		UpdateData(FALSE);
		break;
	case 0x0D:
		UpdateData();
		     if(pc[0] == 0x00)m_csMsg.Format("弹号 设置成功:%c%c%c%c%c%c%c\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		else if(pc[0] == 0x01)m_csMsg.Format("弹号 设置失败:%c%c%c%c%c%c%c\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		else if(pc[0] == 0x02)m_csMsg.Format("弹号 读取成功:%c%c%c%c%c%c%c\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		else if(pc[0] == 0x03)m_csMsg.Format("弹号 读取失败:%c%c%c%c%c%c%c\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		if(pc[0] == 0x02)
		{
			m_csDanNumber.Format("%c%c%c%c%c%c%c",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6],pc[7]);
		}
		UpdateData(FALSE);
		break;
	case 0x0E:
		UpdateData();
		m_csMsg.Format("设备软件版本:%d.%d.%d\r\n设备硬件版本:%d.%d.%d\r\n",pc[0],pc[1],pc[2],pc[3],pc[4],pc[5]);
		m_uiHwVersion = (pc[3]%10)*100+(pc[4]%10)*10+(pc[5]%10);
		UpdateData(FALSE);
		break;
	case CANEXTCMD:
		UpdateData();
		switch(pc[0])
		{
		case CCE_GETTIME:			
			m_csMsg.Format("设备时间:20%02d/%02d/%02d %02d:%02d:%02d\r\n",pc[1],pc[2],pc[3],pc[4],pc[5],pc[6]);			
			break;
		case CCE_GETPANID:
			m_uiPanID = pc[1]|(pc[2]<<8);
			m_csMsg.Format("PANID:%u\r\n",m_uiPanID);
			break;
		case CCE_GETBDCAST:
			m_uiBoardcast = pc[1];
			m_csMsg.Format("信道:%d\r\n",m_uiBoardcast);
			break;
		case CCE_GETWORKMODE:
			m_csMsg.Format("贮存模式:%s\r\n",pc[1]?"非贮存":"贮存");
			break;
		case CCE_GETWIAADDR:
			if(!pc[1])
			{
				m_csMsg.Format("WIA长地址:%02X%02X%02X%02X",pc[2],pc[3],pc[4],pc[5]);
				m_csWiaAddress.Format("%02X%02X%02X%02X",pc[2],pc[3],pc[4],pc[5]);
			}
			else
			{
				cs.Format("%02X%02X%02X%02X",pc[2],pc[3],pc[4],pc[5]);
				m_csMsg += cs;
				m_csWiaAddress += cs;
			}
			break;
		case CCE_GETTEMPMENXIAN:
			usXx1  = pc[3]|(pc[4]<<8);
			usXx   = pc[1]|(pc[2]<<8);
			m_uiWenduMenxianXia = (short)usXx;
			m_uiWenduMenxiaShang = (short)usXx1;
			m_csMsg.Format("温度门限:%d - %d\r\n",(short)usXx,(short)usXx1);
			break;
		case CCE_GETSHIDUMENXIAN:
			usXx1  = pc[3]|(pc[4]<<8);
			usXx   = pc[1]|(pc[2]<<8);
			m_uiShiduMenxianXia = usXx;
			m_uiShiduMenxiaShang = usXx1;
			m_csMsg.Format("湿度门限:%u - %u\r\n",usXx,usXx1);
			break;
		case CCE_GETYALIMENXIAN:
			usXx1  = pc[3]|(pc[4]<<8);
			usXx   = pc[1]|(pc[2]<<8);
			m_uiYaliMenxianXia = usXx;
			m_uiYaliMenXiaShang = usXx1;
			m_csMsg.Format("压力门限:%u - %u\r\n",usXx,usXx1);
			break;
		case CCE_GETWAITCMDTIME:
			m_csMsg.Format("等待命令时间:%u秒\r\n",pc[1]);
			m_uiWaitCmdTime = pc[1];
			break;
		}
		UpdateData(FALSE);
		break;
	}

	return 0;
}
LRESULT CPcCtrlDlg::OnComRxMsg(WPARAM wp,LPARAM lp)
{
	unsigned char* pData = (unsigned char*)wp;
	unsigned int dl = (unsigned int)lp;

	unsigned char CmdType,CmdAck,PLen,CmdID0,CmdID1;
	
	uint8_t  ucXx;
	uint16_t usXx,usXx1;

	CString cs;



	pData++;//Sn0
	pData++;//Sn1
	
	CmdType = *pData++;
	CmdAck  = *pData++;
	
	PLen    = *pData++;
	
	CmdID0  = *pData++;
	CmdID1  = *pData++;


	switch(CmdAck)
	{
	case 0x00:
		break;
	case 0xFF:
		break;
	case 0x01:
	case 0x02:
	case 0x03:
	case 0x04:
	case 0x05:
	case 0x06:
		return 0;
		break;
	}
	if(CmdType == 0x01)//查询
	{
		if(CmdID1 == 0x00)
		{
			if(CmdID0 == 0x01)//查询版本信息
			{
				UpdateData();
				m_csMsg.Format("设备软件版本:%d.%d.%d\r\n设备硬件版本:%d.%d.%d\r\n",
					pData[0],pData[1],pData[2],
					pData[3],pData[4],pData[5]
					);
				m_uiHwVersion = (pData[3]%10)*100+(pData[4]%10)*10+(pData[5]%10);
				UpdateData(FALSE);
			}
		}

		else if(CmdID1 == 0x01)
		{
			if(CmdID0 == 0x00)//查询实时采集数据
			{
				UpdateData();
				m_csMsg.Format("查询实时采集数据,");
				cs.Format("时间:%02d/%02d/%02d %02d:%02d:%02d\r\n"
					,pData[0],pData[1],pData[2]
					,pData[3],pData[4],pData[5]
					);	m_csMsg += cs;
				pData += 6;

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				cs.Format("温度:%d.%d  ",usXx/10,usXx%10);	m_csMsg += cs;

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				cs.Format("湿度:%d.%d  ",usXx/10,usXx%10);	m_csMsg += cs;

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				cs.Format("内压:%d.%d   ",usXx/10,usXx%10);	m_csMsg += cs;
				
				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				cs.Format("外压:%d.%d   ",usXx/10,usXx%10);	m_csMsg += cs;

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				int16_t x = usXx;
				cs.Format("压差:%.1f  ",((float)x/10));	m_csMsg += cs;

				
				

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				cs.Format("X-G:%d.%d    ",usXx/100,usXx%100);	m_csMsg += cs;

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				cs.Format("Y-G:%d.%d    ",usXx/100,usXx%100);	m_csMsg += cs;

				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				cs.Format("Z-G:%d.%d\r\n",usXx/100,usXx%100);	m_csMsg += cs;

				ucXx = *pData++;
				cs.Format("电量:%d%%\r\n",ucXx);				m_csMsg += cs;


				ucXx = *pData;
				cs.Format("指令:%s ",(ucXx&0x01)?"错误":"正常");			m_csMsg += cs;
				cs.Format("温度传感器:%s ",(ucXx&0x02)?"故障":"正常");	m_csMsg += cs;
				cs.Format("湿度传感器:%s ",(ucXx&0x04)?"故障":"正常");	m_csMsg += cs;
				cs.Format("内压传感器:%s\r\n",(ucXx&0x08)?"故障":"正常");	m_csMsg += cs;
				cs.Format("外压传感器:%s ",(ucXx&0x10)?"故障":"正常");	m_csMsg += cs;
				cs.Format("振动传感器:%s ",(ucXx&0x20)?"故障":"正常");	m_csMsg += cs;
				cs.Format("振动超限:%s  ",(ucXx&0x40)?"故障":"正常");		m_csMsg += cs;
				cs.Format("电量(程序中为电量,文档为压差):%s",(ucXx&0x80)?"故障":"正常");m_csMsg += cs;
				UpdateData(FALSE);
			}
		}

		else if(CmdID1 == 0x02)
		{
			UpdateData();
			if(CmdID0 == 0x00)////查询周期
			{				
				usXx = *pData++;
				usXx1= *pData;
				usXx = (usXx1<<8)|usXx;
				m_csMsg.Format("采集周期:%d [%d秒]\r\n",usXx,(uint32_t)(usXx*10));
				m_uiZhouqi = usXx;
			}

			else if(CmdID0 == 0x02)//查询 温度 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				m_csMsg.Format("温度门限:%d - %d\r\n",(short)usXx1,(short)usXx);

				m_uiWenduMenxianXia = (short)usXx1;
				m_uiWenduMenxiaShang = (short)usXx;
			}

			else if(CmdID0 == 0x03)//查询 湿度 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				m_csMsg.Format("湿度门限:%u - %u\r\n",usXx1,usXx);
				m_uiShiduMenxianXia = usXx1;
				m_uiShiduMenxiaShang = usXx;
			}

			else if(CmdID0 == 0x04)//查询 压力 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				m_csMsg.Format("压力门限:%u - %u\r\n",usXx1,usXx);
				m_uiYaliMenxianXia = usXx1;
				m_uiYaliMenXiaShang = usXx;
			}

			else if(CmdID0 == 0x05)//查询 振动 门限
			{
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				m_csMsg.Format("振动门限:   - %u\r\n",usXx1);
				m_uiZhendongMenxian = usXx1;
			}

			else if(CmdID0 == 0x0E)//查询 弹号
			{
				m_csMsg.Format("弹号:%c%c%c%c%c%c%c",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6]);
				m_csDanNumber.Format("%c%c%c%c%c%c%c",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6]);
			}

			else if(CmdID0 == 0x0F)//查询 箱号
			{
				m_csMsg.Format("箱号:%c%c%c%c%c%c%c",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6]);
				m_csBangNumber.Format("%c%c%c%c%c%c%c",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6]);
			}

			else if(CmdID0 == 0x10)//查询PANID
			{
				m_uiPanID = pData[0]|(pData[1]<<8);
				m_csMsg.Format("PANID:%u\r\n",m_uiPanID);
			}

			else if(CmdID0 == 0x11)//查询信道
			{
				m_uiBoardcast = pData[0];
				m_csMsg.Format("信道:%d\r\n",m_uiBoardcast);
			}

			else if(CmdID0 == 0x12)//查询Wiapa长地址
			{
				m_csMsg.Format("WIA长地址:%02X%02X%02X%02X%02X%02X%02X%02X",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6],pData[7]);
				m_csWiaAddress.Format("%02X%02X%02X%02X%02X%02X%02X%02X",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6],pData[7]);
			}

			else if(CmdID0 == 0x16)//查询时间
			{
				m_csMsg.Format("设备时间:20%02d/%02d/%02d %02d:%02d:%02d\r\n",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5]);
			}

			else if(CmdID0 == 0x17)
			{
				if(pData[0] == 0x06)
				{
					m_csMsg.Format("等待命令时间:%u秒\r\n",pData[1]);
					m_uiWaitCmdTime = pData[1];
				}
			}

			else if(CmdID0 == 0x18)//查询贮存/非贮存模式
			{
				if(*pData == 0)m_csMsg.Format("贮存模式:贮存\r\n");
				else if(*pData == 1)m_csMsg.Format("贮存模式:非贮存\r\n");
				else m_csMsg.Format("贮存模式:错误\r\n");
			}

			UpdateData(FALSE);
		}

		else if(CmdID1 == 0x03)//查询告警信息
		{
			UpdateData();
			switch(CmdID0)
			{
			case 0x00:
				if(*pData == 0)     m_csMsg.Format("温度上限告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("温度上限告警:!!告警!!\r\n");
				else                m_csMsg.Format("温度上限告警:回应错误\r\n");
				break;
			case 0x01:
				if(*pData == 0)     m_csMsg.Format("温度下限告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("温度下限告警:!!告警!!\r\n");
				else                m_csMsg.Format("温度下限告警:回应错误\r\n");
				break;
			case 0x02:
				if(*pData == 0)     m_csMsg.Format("湿度上限告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("湿度上限告警:!!告警!!\r\n");
				else                m_csMsg.Format("湿度上限告警:回应错误\r\n");
				break;
			case 0x03:
				if(*pData == 0)     m_csMsg.Format("湿度下限告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("湿度下限告警:!!告警!!\r\n");
				else                m_csMsg.Format("湿度下限告警:回应错误\r\n");
				break;
			case 0x04:
				if(*pData == 0)     m_csMsg.Format("压力上限告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("压力上限告警:!!告警!!\r\n");
				else                m_csMsg.Format("压力上限告警:回应错误\r\n");
				break;
			case 0x05:
				if(*pData == 0)     m_csMsg.Format("压力下限告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("压力下限告警:!!告警!!\r\n");
				else                m_csMsg.Format("压力下限告警:回应错误\r\n");
				break;
			case 0x06:
				if(*pData == 0)     m_csMsg.Format("差压告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("差压告警:!!告警!!\r\n");
				else                m_csMsg.Format("差压告警:回应错误\r\n");
				break;
			case 0x07:
				if(*pData == 0)     m_csMsg.Format("电量低告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("电量低告警:!!告警!!\r\n");
				else                m_csMsg.Format("电量低告警:回应错误\r\n");
				break;
			case 0x08:
				if(*pData == 0)     m_csMsg.Format("振动上限告警:无\r\n");
				else if(*pData == 1)m_csMsg.Format("振动上限告警:!!告警!!\r\n");
				else                m_csMsg.Format("振动上限告警:回应错误\r\n");
				break;
			default:
				m_csMsg.Format("告警类型错误:%02X 告警值:%d\r\n",CmdID0,*pData);
				break;
			}

			UpdateData(FALSE);
		}
	}

	else if(CmdType == 0x02)//设置
	{
		if(CmdID1 == 0x02)
		{
			if(CmdID0 == 0x1B)
			{
				int i;
				UpdateData();
				m_csMsg.Format("读取参数:\r\n");
				
				m_csDanNumber.Format("%c%c%c%c%c%c%c",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6]);
				cs.Format("弹号:");	m_csMsg += cs;
				for(i = 0; i < 7; i++)
				{
					cs.Format("%c",*pData++);
					m_csMsg += cs;
				}
				cs.Format("\r\n");	m_csMsg += cs;
				pData++;
				
				m_csBangNumber.Format("%c%c%c%c%c%c%c",pData[0],pData[1],pData[2],pData[3],pData[4],pData[5],pData[6]);
				cs.Format("箱号:");	m_csMsg += cs;
				for(i = 0; i < 7; i++){cs.Format("%c",*pData++);m_csMsg += cs;}
				cs.Format("\r\n");	m_csMsg += cs;
				pData++;
				
				usXx  = *pData++;
				usXx |= (*pData++)<<8;
				cs.Format("采集周期:%d [%d秒]\r\n",usXx,(uint32_t)(usXx*10));	m_csMsg += cs;
				m_uiZhouqi = usXx;
				
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				cs.Format("温度门限:%d - %d\r\n",(short)usXx,(short)usXx1);	m_csMsg += cs;
				m_uiWenduMenxianXia = (short)usXx;
				m_uiWenduMenxiaShang = (short)usXx1;
				
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				cs.Format("湿度门限:%u - %u\r\n",usXx,usXx1);	m_csMsg += cs;
				m_uiShiduMenxianXia = usXx;
				m_uiShiduMenxiaShang = usXx1;
				
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				usXx   = *pData++;
				usXx  |= (*pData++)<<8;
				cs.Format("压力门限:%u - %u\r\n",usXx,usXx1);	m_csMsg += cs;
				m_uiYaliMenxianXia = usXx;
				m_uiYaliMenXiaShang = usXx1;
				
				usXx1  = *pData++;
				usXx1 |= (*pData++)<<8;
				cs.Format("振动门限:   - %u\r\n",usXx1);	m_csMsg += cs;
				m_uiZhendongMenxian = usXx1;
				
				
				if(*pData == 0)cs.Format("贮存模式:贮存\r\n");
				else if(*pData == 1)cs.Format("贮存模式:非贮存\r\n");
				else cs.Format("贮存模式:错误\r\n");

				m_csMsg += cs;
			
				UpdateData(FALSE);
			}
		}
	}


	return 0;
}

void CPcCtrlDlg::OnButtonGetVersion() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetVersion();
}

#include "cderr.h"
void CPcCtrlDlg::OnButtonUpgrade() 
{
	if(!m_Uart.IsOpened())return;

	TCHAR fns[(MAX_PATH+1)*2];
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,"hex文件(*.hex)|*.hex||");
	dlg.m_ofn.nMaxFile = (MAX_PATH+1)*2;
	dlg.m_ofn.lpstrFile = fns;
	ZeroMemory(dlg.m_ofn.lpstrFile,sizeof(TCHAR)*dlg.m_ofn.nMaxFile);	
	if(dlg.DoModal() == IDOK)
	{
		int e = m_Uart.UpgradeReset();
		char cfgfn[MAX_PATH];
		POSITION pos = dlg.GetStartPosition();
		while(pos)
		{
			strcpy(cfgfn,dlg.GetNextPathName(pos));
			e |= m_Uart.UpgradeAddFile(cfgfn);
		}
		e |= m_Uart.UpgradeStart();
		if(e)
		{
			AfxMessageBox("升级失败");
		}
	}
	else
	{
		if(CommDlgExtendedError() == FNERR_BUFFERTOOSMALL)
		{
			AfxMessageBox("最多选择2个文件");
		}
	}
}



void CPcCtrlDlg::OnBtnSyncdatetime() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.SetDateTime();
}

void CPcCtrlDlg::OnBtnSetzhouqi() 
{
	if(!m_Uart.IsOpened())return;
	if(m_bCan)
	{
		OnBtnSetzhendongmenxian();
	}
	else
	{
		UpdateData();
		m_Uart.SetZhouqi(m_uiZhouqi);
	}
}

void CPcCtrlDlg::OnBtnGetzhouqi() 
{
	if(!m_Uart.IsOpened())return;
	if(m_bCan)
	{
		OnBtnGetzhendongmenxian();
	}
	else
	{
		m_Uart.GetZhouqi();	
	}
}
void CPcCtrlDlg::OnBtnSetzhendongmenxian() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	if(m_bCan)
	{
		m_Uart.SetZhendongMenXianZhouqi(m_uiZhendongMenxian,m_uiZhouqi);
	}
	else
	{
		m_Uart.SetZhendongMenXian(m_uiZhendongMenxian);
	}
}

void CPcCtrlDlg::OnBtnGetzhendongmenxian() 
{
	if(!m_Uart.IsOpened())return;
	if(m_bCan)
	{
		m_Uart.GetZhendongMenXianZhouqi();
	}
	else
	{
		m_Uart.GetZhendongMenXian();
	}
}



void CPcCtrlDlg::OnBtnSetwendumenxian() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.SetWenduMenXian(m_uiWenduMenxiaShang,m_uiWenduMenxianXia);
}

void CPcCtrlDlg::OnBtnGetwendumenxian() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetWenduMenXian();
}

void CPcCtrlDlg::OnBtnSetshidumenxian() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.SetShiduMenXian(m_uiShiduMenxiaShang,m_uiShiduMenxianXia);
}

void CPcCtrlDlg::OnBtnGetshidumenxian() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetShiduMenXian();
}

void CPcCtrlDlg::OnBtnSetyalimenxian() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.SetYaliMenXian(m_uiYaliMenXiaShang,m_uiYaliMenxianXia);
}

void CPcCtrlDlg::OnBtnGetyalimenxian() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetYaliMenXian();
}



void CPcCtrlDlg::OnBtnDelwsyrecord() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.DelWenshiyaRecord();
}

void CPcCtrlDlg::OnBtnDelzhendongrecord() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.DelZhendongRecord();
}

void CPcCtrlDlg::OnBtnSetdannumber() 
{
	if(!m_Uart.IsOpened())return;
	char dn[32];
	UpdateData();
	strncpy(dn,m_csDanNumber,8);
	m_Uart.SetDanNumber((unsigned char*)dn);
}

void CPcCtrlDlg::OnBtnGetdannumber() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetDanNumber();
}

void CPcCtrlDlg::OnBtnSetbandnumber() 
{	
	if(!m_Uart.IsOpened())return;
	char bn[32];
	UpdateData();
	strncpy(bn,m_csBangNumber,8);
	m_Uart.SetBangNumber((unsigned char*)bn);
}

void CPcCtrlDlg::OnBtnGetbandnumber() 
{	
	if(!m_Uart.IsOpened())return;
	m_Uart.GetBangNumber();
}

void CPcCtrlDlg::OnBtnSetpanid() 
{
	UpdateData();
	m_Uart.SetPanID(m_uiPanID);
}

void CPcCtrlDlg::OnBtnSetboardcast() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.SetBoardcast((unsigned char)m_uiBoardcast);
}

void CPcCtrlDlg::OnBtnStop() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.SetStop();
}

void CPcCtrlDlg::OnBtnSetsavemode() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.SetSaveMode(0);
}
void CPcCtrlDlg::OnBtnSetsavemodeNo() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.SetSaveMode(1);
}
void CPcCtrlDlg::OnBtnGetsavemode() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetSaveMode();
}

void CPcCtrlDlg::OnBtnBatteryswap() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.SetBatterySwap();
}



void CPcCtrlDlg::OnBtnSetyalicaliration() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.SetCalibrationYali(m_uiYaliCaliration);
}

void CPcCtrlDlg::OnBtnGetparameter() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetParameter();
}

void CPcCtrlDlg::OnBtnQuerywarning() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.GetWarning((unsigned char)m_uiWarning);
}

void Cs2Date(CString& cs,unsigned char *pd)
{
	int i;
	unsigned char c0,c1;
	char bf[128];

	strncpy(bf,cs,32);
	for(i = 0;i < 6;i++)
	{
		c0 = bf[i*2 +0] - '0';
		c1 = bf[i*2 +1] - '0';
		*pd++ = c0*10+c1;
	}
}
void CPcCtrlDlg::OnBtnHistoryWsy() 
{
	if(!m_Uart.IsOpened())return;
	unsigned char s[16],e[16];
	UpdateData();
	Cs2Date(m_csWsyStart,s);
	Cs2Date(m_csWsyEnd,e);
	m_Uart.GetWsyRecord(s,e);
}

void CPcCtrlDlg::OnBtnHistoryZhendong() 
{
	if(!m_Uart.IsOpened())return;
	unsigned char s[16],e[16];
	UpdateData();
	Cs2Date(m_csZhendongStart,s);
	Cs2Date(m_csZhendongEnd,e);
	m_Uart.GetZhendongRecord(s,e);
}

void CPcCtrlDlg::OnBtnDocollectonce() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.DoCollectOnce();
}



void CPcCtrlDlg::OnBtnWsyBu() 
{
	if(!m_Uart.IsOpened())return;
	if(m_bCan)return;
	int cnt;
	uint32_t uiID[10];
	char bf[1024];
	UpdateData();
	m_csWsyBu.TrimLeft();
	m_csWsyBu.TrimRight();
	strncpy(bf,m_csWsyBu,1023);
	if(strlen(bf) > 0)
	{
		cnt = sscanf(bf,"%d %d %d %d %d %d %d %d %d %d",uiID+0,uiID+1,uiID+2,uiID+3,uiID+4,uiID+5,uiID+6,uiID+7,uiID+8,uiID+9);
		m_Uart.GetWsyRecordBu(cnt,uiID);
	}
}

void CPcCtrlDlg::OnBtnZhendongBu() 
{
	if(!m_Uart.IsOpened())return;
	if(m_bCan)return;
	int cnt;
	uint32_t uiID[10];
	char bf[1024];
	UpdateData();
	m_csZhendongBu.TrimLeft();
	m_csZhendongBu.TrimRight();
	strncpy(bf,m_csZhendongBu,1023);
	if(strlen(bf) > 0)
	{
		cnt = sscanf(bf,"%d %d %d %d %d %d %d %d %d %d",uiID+0,uiID+1,uiID+2,uiID+3,uiID+4,uiID+5,uiID+6,uiID+7,uiID+8,uiID+9);
		m_Uart.GetZhendongRecordBu(cnt,uiID);
	}
}

void CPcCtrlDlg::OnSelendokComboCanid() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.CanID(m_iCanID);
}

void CPcCtrlDlg::OnBtnRebootwiapa() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.SetRebootWiapa();
}

void CPcCtrlDlg::OnButtonSetHwVersion() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.TD_SetHwVersion(m_uiHwVersion);
}

void CPcCtrlDlg::OnBtnGetdatetime() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.TD_GetDateTime();		
}

void CPcCtrlDlg::OnBtnSysreset() 
{
	if(!m_Uart.IsOpened())return;
	if(AfxMessageBox("确信删除所有配置和数据!",MB_OKCANCEL) != IDOK)return;
	m_Uart.TD_SystemReset();
}

void CPcCtrlDlg::OnBtnGetpanid() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetPanID();
}

void CPcCtrlDlg::OnBtnGetboardcast() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetBoardcast();
}

void CPcCtrlDlg::OnBtnSetaddress() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	char bf[1024];
	unsigned char add[128];
	m_csWiaAddress.TrimLeft();
	m_csWiaAddress.TrimRight();
	strncpy(bf,m_csWiaAddress,1023);
	if(strlen(bf) >= 16)
	{
		if(sscanf(bf,"%02x%02x%02x%02x%02x%02x%02x%02x",add+0,add+1,add+2,add+3,add+4,add+5,add+6,add+7) == 8)
		{
			m_Uart.SetWiapaAddress(add);
		}
	}
}

void CPcCtrlDlg::OnBtnGetaddress() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.GetWiapaAddress();
}

void CPcCtrlDlg::OnBtnSettempcaliration() 
{
	if(!m_Uart.IsOpened())return;

	//20190809
	CSetACTemp dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_Uart.TD_TempAC(dlg.m_uiSetAcTemp);
	}
}

void CPcCtrlDlg::OnBtnRebootmcu() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.TD_Reboot();
}

void CPcCtrlDlg::OnButtonStopUpgrade() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.UpgradeStop();
}


void CPcCtrlDlg::OnBtnZhendongca() 
{	
	if(!m_Uart.IsOpened())return;
	m_Uart.TD_ZhendongAC();
}

void CPcCtrlDlg::OnBtnSetwaittime() 
{
	if(!m_Uart.IsOpened())return;
	UpdateData();
	m_Uart.TD_SetWaitCmdTime((unsigned char)m_uiWaitCmdTime);
}

void CPcCtrlDlg::OnBtnGetwaittime() 
{
	if(!m_Uart.IsOpened())return;
	m_Uart.TD_GetWaitCmdTime();
}
