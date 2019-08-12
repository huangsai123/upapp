// SetACTemp.cpp : implementation file
//

#include "stdafx.h"
#include "PcCtrl.h"
#include "SetACTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetACTemp dialog


CSetACTemp::CSetACTemp(CWnd* pParent /*=NULL*/)
	: CDialog(CSetACTemp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetACTemp)
	m_uiSetAcTemp = 2345;
	//}}AFX_DATA_INIT
}


void CSetACTemp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetACTemp)
	DDX_Text(pDX, IDC_EDIT1_TEMP, m_uiSetAcTemp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetACTemp, CDialog)
	//{{AFX_MSG_MAP(CSetACTemp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetACTemp message handlers
