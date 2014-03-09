#if !defined(AFX_DLGKASSALOKI_H__5308A3A3_A5FB_11D5_8AC1_0000E8C7E630__INCLUDED_)
#define AFX_DLGKASSALOKI_H__5308A3A3_A5FB_11D5_8AC1_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKassaloki.h : header file
//

#include "RGXDeskLogRows.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgKassaloki dialog


class CDlgKassaloki : public CDialog
{
// Construction
public:
	CRGXDeskLogRows* m_pDeskLogRows;
	CDlgKassaloki(CWnd* pParent = NULL);   // standard constructor
	~CDlgKassaloki();

// Dialog Data
	//{{AFX_DATA(CDlgKassaloki)
	enum { IDD = IDD_DLG_KASSALOKI };
	CComboBox	m_ctlKassa;
	CString	m_sPvm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKassaloki)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKassaloki)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeKassa();
	afx_msg void OnHae();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CKassaRS* m_pKRS;
	void getDeskList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGKASSALOKI_H__5308A3A3_A5FB_11D5_8AC1_0000E8C7E630__INCLUDED_)
