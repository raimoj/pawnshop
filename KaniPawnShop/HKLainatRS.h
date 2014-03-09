#if !defined(AFX_HKLAINATRS_H__4960BCE3_9933_11D3_8A1F_0000E8C7E630__INCLUDED_)
#define AFX_HKLAINATRS_H__4960BCE3_9933_11D3_8A1F_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HKLainatRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHKLainatRS recordset

class CHKLainatRS : public CRRecordset
{
public:
	CHKLainatRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHKLainatRS)

// Field/Param Data
	//{{AFX_FIELD(CHKLainatRS, CRRecordset)
	long	m_HKL_LA_Nr;
	long	m_HKL_VNr;
	long	m_HKL_AsID;
	CString	m_HKL_AsHTun;
	long	m_HKL_HK_Nr;
	CTime	m_HKL_PoistettuHKsta;
	CString	m_HKL_LainanNimi;
	CString	m_HKL_LainanTuoteryhma;
	CTime	m_HKL_EraPv;
	double	m_HKL_Laina;
	double	m_HKL_KorotKulut;
	double	m_HKL_HKkulut;
	double	m_HKL_Pohjahinta;
	double	m_HKL_Myyntihinta;
	double	m_HKL_Ylij_Alij;
	CString	m_HKL_OstajanNimi;
	CTime	m_HKL_MyyntiPv;
	BOOL	m_HKL_Kuittaus;
	CTime	m_HKL_KuittausAika;
	long	m_HKL_KirjeNr;
	CTime	m_HKL_KirjePv;
	CTime	m_HKL_YlijMaksuPv;
	CTime	m_HKL_YlijKuittausPv;
	CString	m_HKL_Huom;
	//CTime	m_HKL_ts;
	//CByteArray	m_HKL_ts;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHKLainatRS)
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

#endif // !defined(AFX_HKLAINATRS_H__4960BCE3_9933_11D3_8A1F_0000E8C7E630__INCLUDED_)
