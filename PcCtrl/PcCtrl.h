// PcCtrl.h : main header file for the PCCTRL application
//

#if !defined(AFX_PCCTRL_H__0F47FAE0_3BA1_45FA_9A80_C94793D6DACA__INCLUDED_)
#define AFX_PCCTRL_H__0F47FAE0_3BA1_45FA_9A80_C94793D6DACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPcCtrlApp:
// See PcCtrl.cpp for the implementation of this class
//

class CPcCtrlApp : public CWinApp
{
public:
	CPcCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPcCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCCTRL_H__0F47FAE0_3BA1_45FA_9A80_C94793D6DACA__INCLUDED_)
