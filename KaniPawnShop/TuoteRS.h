#if !defined(AFX_TUOTERS_H__CCF72806_518D_11D3_8A0B_0000E8C7E630__INCLUDED_)
#define AFX_TUOTERS_H__CCF72806_518D_11D3_8A0B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TuoteRS.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CTuoteRS recordset

class CTuoteRS : public CRRecordset
{
public:
	CTuoteRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTuoteRS)

// Field/Param Data
	//{{AFX_FIELD(CTuoteRS, CRRecordset)
	long	m_TU_Tunnus;
	CString	m_TU_Ryhma;
	CString	m_TU_Numero;
	CString	m_TU_Kuvaus;
	BOOL	m_TU_Jalometalli;
	CString	m_TU_Yks;
	double	m_TU_YksHinta;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTuoteRS)
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

#endif // !defined(AFX_TUOTERS_H__CCF72806_518D_11D3_8A0B_0000E8C7E630__INCLUDED_)
