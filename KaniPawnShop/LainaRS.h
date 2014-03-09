#if !defined(AFX_LAINARS_H__7D89CE84_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_)
#define AFX_LAINARS_H__7D89CE84_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LainaRS.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CLainaRS recordset

class CLainaRS : public CRRecordset
{
public:
	CLainaRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLainaRS)

// Field/Param Data
	//{{AFX_FIELD(CLainaRS, CRRecordset)
	long	m_LA_Nr;
	
	long	m_LA_AS_ID;
	CString	m_LA_AS_HTun;

	CString	m_LA_LainanNimi;
	CString m_LA_TR_Ryhma;
	CTime	m_LA_AlkupPv;
	CTime	m_LA_Pv;
	CTime	m_LA_EraPv;
	CString	m_LA_Tila;
	double	m_LA_VakSumma;
	double	m_LA_Laina;
	double	m_LA_Korko;
	CString	m_LA_Kielto;
	CTime	m_LA_KieltoRajaPv;
	double	m_LA_SaVakMaksuPr;
	double	m_LA_YlimSaMaksu;


	BOOL	m_LA_KuitinKatoaminen;
	double	m_LA_KuitinKatoamisMaksu;
	double	m_LA_MuistKirjeMaksu1;
	double	m_LA_MuistKirjeMaksu2;
	double	m_LA_VakVarmMaksu;
	double	m_LA_PostitusMaksu;

	double m_LA_HkPoistomaksu;
	double m_LA_MyValmKorvaus;
	double m_LA_ArvopapValMaksu;

	double	m_LA_Alennus;


	CString	m_LA_Liitteet;
	CString	m_LA_Huom;
	BOOL	m_LA_EiMuistutusta;
	CString	m_LA_MuistHuom;
	CTime	m_LA_OdotusPv;
	CTime	m_LA_MuistKirje1;
	CTime	m_LA_MuistKirje2;
	CTime	m_LA_HuutokPv;
	CTime	m_LA_YlijKirjePv;
	CTime	m_LA_Aika;
	CString	m_LA_Varasto;
	//CTime	m_LA_ts;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLainaRS)
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

#endif // !defined(AFX_LAINARS_H__7D89CE84_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_)
