#if !defined(AFX_SETACTEMP_H__545817EC_26E3_476C_994E_833C6E871543__INCLUDED_)
#define AFX_SETACTEMP_H__545817EC_26E3_476C_994E_833C6E871543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetACTemp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetACTemp dialog

class CSetACTemp : public CDialog
{
// Construction
public:
	CSetACTemp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetACTemp)
	enum { IDD = IDD_DLG_CFG_TEMP };
	UINT	m_uiSetAcTemp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetACTemp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetACTemp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETACTEMP_H__545817EC_26E3_476C_994E_833C6E871543__INCLUDED_)
