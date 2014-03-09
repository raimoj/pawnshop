#if !defined(AFX_PAAPVKRS_H__DD297B47_6DA3_11D3_8A0D_0000E8C7E630__INCLUDED_)
#define AFX_PAAPVKRS_H__DD297B47_6DA3_11D3_8A0D_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaaPvKRS.h : header file
//
#include "RRecordset.h"
/////////////////////////////////////////////////////////////////////////////
// CPaaPvKRS recordset

class CPaaPvKRS : public CRRecordset
{
public:
	CPaaPvKRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPaaPvKRS)

// Field/Param Data
	//{{AFX_FIELD(CPaaPvKRS, CRRecordset)
	long	m_KPP_Rivi;
	double	m_KPP_LoppuSaldoYht;
	double	m_KPP_Lainakanta;
	CTime	m_KPP_Aika;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaaPvKRS)
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

#endif // !defined(AFX_PAAPVKRS_H__DD297B47_6DA3_11D3_8A0D_0000E8C7E630__INCLUDED_)
