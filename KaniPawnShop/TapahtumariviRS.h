#if !defined(AFX_TAPAHTUMARIVIRS_H__CACD3373_93BF_11D5_8AB6_0000E8C7E630__INCLUDED_)
#define AFX_TAPAHTUMARIVIRS_H__CACD3373_93BF_11D5_8AB6_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TapahtumariviRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTapahtumariviRS recordset

class CTapahtumariviRS : public CRRecordset
{
public:
	CTapahtumariviRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTapahtumariviRS)

// Field/Param Data
	//{{AFX_FIELD(CTapahtumariviRS, CRRecordset)
	long	m_TR_ID;
	long	m_TR_TP_Tap;
	long	m_TR_RiviNr;
	CString	m_TR_TuoteNr;
	long	m_TR_Maara;
	CString	m_TR_Yks;
	double	m_TR_YksPaino;
	CString	m_TR_Kuvaus;
	CString	m_TR_Huom;
	double	m_TR_Vakuus;
	double	m_TR_Laina;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTapahtumariviRS)
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

#endif // !defined(AFX_TAPAHTUMARIVIRS_H__CACD3373_93BF_11D5_8AB6_0000E8C7E630__INCLUDED_)
