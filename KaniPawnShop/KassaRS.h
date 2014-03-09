#if !defined(AFX_KASSARS_H__4DDEA09E_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_KASSARS_H__4DDEA09E_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KassaRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKassaRS recordset

class CKassaRS : public CRRecordset
{
public:
	CKassaRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CKassaRS)

// Field/Param Data
	//{{AFX_FIELD(CKassaRS, CRRecordset)
	long	m_KS_Tunnus;
	CString	m_KS_KassanNimi;
	double	m_KS_Saldo;
	CTime	m_KS_TarkastusAika;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKassaRS)
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

#endif // !defined(AFX_KASSARS_H__4DDEA09E_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_)
