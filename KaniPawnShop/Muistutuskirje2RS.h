#if !defined(AFX_MUISTUTUSKIRJE2RS_H__A975F5B0_F4EA_4F40_9B6B_C88EF53DE546__INCLUDED_)
#define AFX_MUISTUTUSKIRJE2RS_H__A975F5B0_F4EA_4F40_9B6B_C88EF53DE546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Muistutuskirje2RS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMuistutuskirje2RS recordset

class CMuistutuskirje2RS : public CRRecordset
{
public:
	CMuistutuskirje2RS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMuistutuskirje2RS)

// Field/Param Data
	//{{AFX_FIELD(CMuistutuskirje2RS, CRecordset)
	long	m_AS_ID;
	CString	m_AS_HTun;
	CString	m_AS_Nimi;
	CString	m_AS_KatuOs;
	CString	m_AS_Ptp;
	long	m_AS_Kielto;
	CTime	m_AS_KieltoAika;
	long	m_AS_MuistEsto;
	
	CString	m_MU_AS_ID;
	CString	m_MU_Nimi;
	long	m_MU_LA_Nr;
	double	m_MU_Laina;
	CTime	m_MU_EraPv;
	long	m_MU_KirjeNr;
	BOOL	m_MU_EiMuistutusta;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMuistutuskirje2RS)
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

#endif // !defined(AFX_MUISTUTUSKIRJE2RS_H__A975F5B0_F4EA_4F40_9B6B_C88EF53DE546__INCLUDED_)
