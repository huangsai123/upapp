// PcCtrlDlg.h : header file
//

#if !defined(AFX_PCCTRLDLG_H__E21EF530_7E5F_480F_9536_4EF5B0729C96__INCLUDED_)
#define AFX_PCCTRLDLG_H__E21EF530_7E5F_480F_9536_4EF5B0729C96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPcCtrlDlg dialog

#include "Uart.h"

class CPcCtrlDlg : public CDialog
{
// Construction
public:
	CPcCtrlDlg(CWnd* pParent = NULL);	// standard constructor
	void StopUart(){m_Uart.Close();}

// Dialog Data
	//{{AFX_DATA(CPcCtrlDlg)
	enum { IDD = IDD_PCCTRL_DIALOG };
	CComboBox	m_UartList;
	CString	m_csUsart;
	UINT	m_uiZhouqi;
	int		m_uiWenduMenxianXia;
	int		m_uiWenduMenxiaShang;
	UINT	m_uiShiduMenxianXia;
	UINT	m_uiShiduMenxiaShang;
	UINT	m_uiYaliMenxianXia;
	UINT	m_uiYaliMenXiaShang;
	UINT	m_uiZhendongMenxian;
	CString	m_csDanNumber;
	CString	m_csBangNumber;
	UINT	m_uiPanID;
	UINT	m_uiBoardcast;
	UINT	m_uiYaliCaliration;
	int		m_uiWarning;
	CString	m_csWsyStart;
	CString	m_csWsyEnd;
	CString	m_csZhendongStart;
	CString	m_csZhendongEnd;
	CString	m_csWsyBu;
	CString	m_csZhendongBu;
	int		m_iCanID;
	CString	m_csIP;
	UINT	m_uiPort;
	CString	m_csDevAddr;
	int		m_iCI;
	CString	m_csMsg;
	int		m_uiHwVersion;
	CString	m_csWiaAddress;
	int		m_uiWaitCmdTime;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcCtrlDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	

// Implementation
protected:
	HICON m_hIcon;

	BOOL  m_bUDP;
	BOOL  m_bCan;
	BOOL  m_bConsole;
	CUart m_Uart;

	LRESULT OnCanRxMsg(WPARAM,LPARAM);
	LRESULT OnComRxMsg(WPARAM,LPARAM);
	LRESULT OnTxtMsg(WPARAM,LPARAM);

	// Generated message map functions
	//{{AFX_MSG(CPcCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropdownComboCom();
	afx_msg void OnButtonComOc();
	afx_msg void OnButtonGetVersion();
	afx_msg void OnButtonUpgrade();
	afx_msg void OnButtonConsole();
	afx_msg void OnBtnSyncdatetime();
	afx_msg void OnBtnSetzhouqi();
	afx_msg void OnBtnGetzhouqi();
	afx_msg void OnBtnSetwendumenxian();
	afx_msg void OnBtnGetwendumenxian();
	afx_msg void OnBtnSetshidumenxian();
	afx_msg void OnBtnGetshidumenxian();
	afx_msg void OnBtnSetyalimenxian();
	afx_msg void OnBtnGetyalimenxian();
	afx_msg void OnBtnSetzhendongmenxian();
	afx_msg void OnBtnGetzhendongmenxian();
	afx_msg void OnBtnDelwsyrecord();
	afx_msg void OnBtnDelzhendongrecord();
	afx_msg void OnBtnSetdannumber();
	afx_msg void OnBtnGetdannumber();
	afx_msg void OnBtnSetbandnumber();
	afx_msg void OnBtnGetbandnumber();
	afx_msg void OnBtnSetpanid();
	afx_msg void OnBtnSetboardcast();
	afx_msg void OnBtnStop();
	afx_msg void OnBtnSetsavemode();
	afx_msg void OnBtnBatteryswap();
	afx_msg void OnBtnGetsavemode();
	afx_msg void OnBtnSetyalicaliration();
	afx_msg void OnBtnGetparameter();
	afx_msg void OnBtnQuerywarning();
	afx_msg void OnBtnHistoryWsy();
	afx_msg void OnBtnHistoryZhendong();
	afx_msg void OnBtnDocollectonce();
	afx_msg void OnBtnSetsavemodeNo();
	afx_msg void OnBtnWsyBu();
	afx_msg void OnBtnZhendongBu();
	afx_msg void OnSelendokComboCanid();
	afx_msg void OnBtnRebootwiapa();
	afx_msg void OnButtonSetHwVersion();
	afx_msg void OnBtnGetdatetime();
	afx_msg void OnBtnSysreset();
	afx_msg void OnBtnGetpanid();
	afx_msg void OnBtnGetboardcast();
	afx_msg void OnBtnSetaddress();
	afx_msg void OnBtnGetaddress();
	afx_msg void OnBtnSettempcaliration();
	afx_msg void OnBtnRebootmcu();
	afx_msg void OnButtonStopUpgrade();
	afx_msg void OnClose();
	afx_msg void OnBtnZhendongca();
	afx_msg void OnBtnSetwaittime();
	afx_msg void OnBtnGetwaittime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCCTRLDLG_H__E21EF530_7E5F_480F_9536_4EF5B0729C96__INCLUDED_)
