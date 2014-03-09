#if !defined(AFX_DLGKASSATARKASTUS_H__65FEB6B3_5EF5_11D3_8A0B_0000E8C7E630__INCLUDED_)
#define AFX_DLGKASSATARKASTUS_H__65FEB6B3_5EF5_11D3_8A0B_0000E8C7E630__INCLUDED_

#include "KassalokiRS.h"	// Added by ClassView
#include "KassaRS.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKassatarkastus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgKassatarkastus dialog

class CDlgKassatarkastus : public CDialog
{
// Construction
public:
	CDlgKassatarkastus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgKassatarkastus)
	enum { IDD = IDD_DLG_KASSATARKASTUS };
	CString	m_sKassanNimi;
	CString	m_sArviomies;
	CString	m_sAika;
	CString	m_sEdellinenTarkastusaika;
	CString	m_sEdellinenSaldo;
	CString	m_sSaldo;
	CString	m_sYht;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKassatarkastus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKassatarkastus)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	double m_dS;
	BOOL UpdateDeskBalance();
	CKassalokiRS m_KassalokiRS;
	double GetTotal(long lDeskId, CTime tchecked);
	CKassaRS m_KassaRS;
	CString sDateAndTime;
	CTime t;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKASSATARKASTUS_H__65FEB6B3_5EF5_11D3_8A0B_0000E8C7E630__INCLUDED_)
