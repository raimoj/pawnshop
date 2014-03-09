#if !defined(AFX_MUISTUTUSLISTARS_H__CB8447B9_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_MUISTUTUSLISTARS_H__CB8447B9_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MuistutusListaRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMuistutusListaRS recordset

class CMuistutusListaRS : public CRRecordset
{
public:
	CMuistutusListaRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMuistutusListaRS)

// Field/Param Data
	//{{AFX_FIELD(CMuistutusListaRS, CRRecordset)
	long	m_MU_Rivi;
	long	m_MU_AS_ID;
	CString	m_MU_Nimi;
	long	m_MU_LA_Nr;
	double	m_MU_Laina;
	CTime	m_MU_EraPv;
	long	m_MU_KirjeNr;
	BOOL	m_MU_EiMuistutusta;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMuistutusListaRS)
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

#endif // !defined(AFX_MUISTUTUSLISTARS_H__CB8447B9_93B2_11D3_8A1B_0000E8C7E630__INCLUDED_)
