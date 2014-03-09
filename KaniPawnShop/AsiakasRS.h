#if !defined(AFX_ASIAKASRS_H__7D89CE83_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_)
#define AFX_ASIAKASRS_H__7D89CE83_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AsiakasRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAsiakasRS recordset

class CAsiakasRS : public CRRecordset
{
public:
	CAsiakasRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAsiakasRS)

// Field/Param Data
	//{{AFX_FIELD(CAsiakasRS, CRRecordset)
	long	m_AS_ID;
	CString	m_AS_HTun;
	BOOL	m_AS_RuotsHTun;
	BOOL	m_AS_Sp;
	CString	m_AS_Nimi;
	CString	m_AS_ENimet;
	CString	m_AS_KatuOs;
	CString	m_AS_Ptp;
	CString	m_AS_Puh;
	CString	m_AS_Huom;
	long	m_AS_Kielto;
	double	m_AS_Ylij;
	double	m_AS_Alij;
	CTime	m_AS_KieltoAika;
	long	m_AS_MuistEsto;
	CTime	m_AS_AsSuhtAlku;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsiakasRS)
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

#endif // !defined(AFX_ASIAKASRS_H__7D89CE83_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_)
