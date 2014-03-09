#if !defined(AFX_ARVIOMIESRS_H__18C413D3_1DAB_11D3_89DD_0000E8C7E630__INCLUDED_)
#define AFX_ARVIOMIESRS_H__18C413D3_1DAB_11D3_89DD_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArviomiesRS.h : header file
//
#include "RRecordset.h"

/////////////////////////////////////////////////////////////////////////////
// CArviomiesRS recordset

class CArviomiesRS : public CRRecordset
{
public:
	CArviomiesRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CArviomiesRS)

// Field/Param Data
	//{{AFX_FIELD(CArviomiesRS, CRRecordset)
	long	m_AM_Tunnus;
	CString m_AM_Nimikirjaimet;
	CString	m_AM_Nimi;
	long	m_AM_Oikeudet;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArviomiesRS)
	public:
	//virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARVIOMIESRS_H__18C413D3_1DAB_11D3_89DD_0000E8C7E630__INCLUDED_)
