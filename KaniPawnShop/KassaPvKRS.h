#if !defined(AFX_KASSAPVKRS_H__DD297B46_6DA3_11D3_8A0D_0000E8C7E630__INCLUDED_)
#define AFX_KASSAPVKRS_H__DD297B46_6DA3_11D3_8A0D_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KassaPvKRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKassaPvKRS recordset

class CKassaPvKRS : public CRRecordset
{
public:
	CKassaPvKRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CKassaPvKRS)

// Field/Param Data
	//{{AFX_FIELD(CKassaPvKRS, CRRecordset)
	long	m_KP_Rivi;
	long	m_KP_KS_Tunnus;
	long	m_KP_KPP_Rivi;
	double	m_KP_Saldo;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKassaPvKRS)
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

#endif // !defined(AFX_KASSAPVKRS_H__DD297B46_6DA3_11D3_8A0D_0000E8C7E630__INCLUDED_)
