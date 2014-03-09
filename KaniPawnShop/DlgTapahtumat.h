#if !defined(AFX_DLGTAPAHTUMAT_H__52FD6113_392A_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_DLGTAPAHTUMAT_H__52FD6113_392A_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTapahtumat.h : header file
//


#include "RGXEvents.h"
#include "RGXEventRows.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgTapahtumat dialog

class CDlgTapahtumat : public CDialog
{
// Construction
public:
	//void setLoanEventSelected(long lEventID);
	long m_lNr;
	long m_lAsId;
	CDlgTapahtumat(CWnd* pParent = NULL);   // standard constructor
	CDlgTapahtumat(CMC* pMC, CWnd* pParent = NULL);
	~CDlgTapahtumat();


// Dialog Data
	//{{AFX_DATA(CDlgTapahtumat)
	enum { IDD = IDD_DLG_TAPAHTUMA };
	CString	m_sAsiakas_LainaNr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTapahtumat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	CRGXEvents* m_pwndEs;
	CRGXEventRows* m_pwndERows;
	

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTapahtumat)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMC* m_pMC;
	
	BOOL UpdateRows();
	void SetColumns();
	void OnShowEventRows();


	int iRowCount;
	CTapahtumaRS* m_pTapRS;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTAPAHTUMAT_H__52FD6113_392A_11D3_89F5_0000E8C7E630__INCLUDED_)
