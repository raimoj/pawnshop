#if !defined(AFX_HKLAINARIVITRS_H__65286001_B09C_11D3_8A1F_0000E8C7E630__INCLUDED_)
#define AFX_HKLAINARIVITRS_H__65286001_B09C_11D3_8A1F_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HKLainarivitRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHKLainarivitRS recordset

class CHKLainarivitRS : public CRRecordset
{
public:
	CHKLainarivitRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHKLainarivitRS)

// Field/Param Data
	//{{AFX_FIELD(CHKLainarivitRS, CRRecordset)
	long	m_HLR_ID;
	long	m_HLR_HKL_LA_Nr;
	long	m_HLR_RiviNr;
	CString	m_HLR_TuNr;
	long	m_HLR_Maara;
	CString	m_HLR_Yks;
	double	m_HLR_YksPaino;
	BOOL	m_HLR_SiirtoMyymalaan;
	BOOL	m_HLR_EiListoille;
	CString	m_HLR_Kuvaus;
	CString m_HLR_Huom;
	double	m_HLR_Laina;
	CString m_HLR_Varasto;
	double	m_HLR_KorotKulut;
	double	m_HLR_HKkulut;
	double	m_HLR_Pohjahinta;
	double	m_HLR_KorkeinTarjous;
	CString	m_HLR_TarjoajanNimi;
	double	m_HLR_MyyntiRaja;
	double	m_HLR_Myyntihinta;
	CString	m_HLR_OstajanNimi;
	CString	m_HLR_MyyntiHuom;
	CTime	m_HLR_MyyntiPv;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHKLainarivitRS)
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

#endif // !defined(AFX_HKLAINARIVITRS_H__65286001_B09C_11D3_8A1F_0000E8C7E630__INCLUDED_)
