// PcCtrl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PcCtrl.h"
#include "PcCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPcCtrlApp

BEGIN_MESSAGE_MAP(CPcCtrlApp, CWinApp)
	//{{AFX_MSG_MAP(CPcCtrlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcCtrlApp construction

CPcCtrlApp::CPcCtrlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPcCtrlApp object

CPcCtrlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPcCtrlApp initialization



BOOL CPcCtrlApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


	srand(time(0));

	CPcCtrlDlg *dlg = new CPcCtrlDlg;
	m_pMainWnd = dlg;
	int nResponse = dlg->DoModal();
	dlg->StopUart();
	delete dlg;
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}