#if !defined(AFX_DLGTUOTE_H__CCF72803_518D_11D3_8A0B_0000E8C7E630__INCLUDED_)
#define AFX_DLGTUOTE_H__CCF72803_518D_11D3_8A0B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTuote.h : header file
//


//#include "RGXTuoterivit.h"
#include "RGXTuoterivit2.h"
//#include "TuoteRS.h"
#include "RGXTuoteryhmat.h"



/////////////////////////////////////////////////////////////////////////////
// CDlgTuote dialog

class CDlgTuote : public CDialog
{
// Construction
public:
	CDlgTuote(CWnd* pParent = NULL);   // standard constructor
	~CDlgTuote();   // standard destructor

// Dialog Data
	//{{AFX_DATA(CDlgTuote)
	enum { IDD = IDD_DLG_TUOTE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTuote)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTuote)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CRGXTuoteryhmat* m_pGXTuoteryhmat;
	int m_iRowCount;
	//CTuoteRS* m_pTuRS;
	//CRGXTuoterivit* m_pGXTuoterivit;
	CRGXTuoterivit2* m_pGXTuoterivit2;


	BOOL ShowTuotteet();
	void SetColumns();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTUOTE_H__CCF72803_518D_11D3_8A0B_0000E8C7E630__INCLUDED_)
