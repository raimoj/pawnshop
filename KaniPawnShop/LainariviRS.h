#if !defined(AFX_LAINARIVIRS_H__EF505A36_DF7F_11D2_89C3_0000E8C7E630__INCLUDED_)
#define AFX_LAINARIVIRS_H__EF505A36_DF7F_11D2_89C3_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LainariviRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLainariviRS recordset

class CLainariviRS : public CRRecordset
{
public:
	CLainariviRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLainariviRS)

// Field/Param Data
	//{{AFX_FIELD(CLainariviRS, CRRecordset)
	long	m_LR_LRivi;
	long	m_LR_LA_Nr;
	long	m_LR_TP_Tap;
	long	m_LR_RiviNr;
	CString	m_LR_TU_Numero;
	long	m_LR_Maara;
	CString	m_LR_Yks;
	double	m_LR_YksPaino;
	CString	m_LR_Kuvaus;
	CString	m_LR_Huom;
	double	m_LR_Vakuus;
	double	m_LR_Laina;
	CString	m_LR_Varasto;
	double	m_LR_SeurLyh;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLainariviRS)
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

#endif // !defined(AFX_LAINARIVIRS_H__EF505A36_DF7F_11D2_89C3_0000E8C7E630__INCLUDED_)
