#if !defined(AFX_ASETUSRS_H__7D89CE82_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_)
#define AFX_ASETUSRS_H__7D89CE82_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AsetusRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAsetusRS recordset

class CAsetusRS : public CRRecordset
{
public:
	CAsetusRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAsetusRS)

// Field/Param Data
	//{{AFX_FIELD(CAsetusRS, CRRecordset)
	CString	m_AT_Toimisto;
	CString	m_AT_Katu;
	CString	m_AT_Ptp;
	CString	m_AT_Puh;
	CString	m_AT_Fax;
	long	m_AT_LainaAika;
	double	m_AT_LKorkoPr1;
	double	m_AT_LRaja1;	// Euro!
	double	m_AT_LKorkoPr2;
	double	m_AT_LRaja2;	// Euro!
	double	m_AT_LKorkoPr3;
	double	m_AT_LRaja3;	// Euro!
	double	m_AT_LKorkoPr4;
	double	m_AT_MyValmMaksuPr;
	long	m_AT_MyValmMaksuaikaEr;
	double m_AT_MyValmMaksuMin;	// Euro!
	double m_AT_ArvopapValMaksuPr;
	double	m_AT_Lisakulut;
	double	m_AT_Kuittimaksu;	// Euro!
	double	m_AT_MuKirjemaksu;	// Euro!
	double	m_AT_HKMaksuPr;
	double	m_AT_HKPoMaksu;		// Euro!
	double	m_AT_HKKulut;
	double	m_AT_PostitusMaksu;	// Euro!
	double	m_AT_KuitinKatoaminen;	// Euro!
	long	m_AT_ToimenpideKieltoPv;
	double	m_AT_SHVMaksuPr; //  (PanttiTodMaksu pitäisi lisätä)
	double	m_AT_VakVarmMaksu;	// Euro!
	CTime	m_AT_SeurHKPv;
	CTime	m_AT_HKEraPvRaja;
	double	m_AT_MuKirjeRajaMk;	// Euro!
	long	m_AT_MuKirje1RajaPv;
	long	m_AT_MuKirje2RajaPv;
	long	m_AT_HKSiirtoRajaPv;  // ei käytössä !
	long	m_AT_YlijKuitAikaraja; // oletusarvo 365 pv
	double	m_AT_YlijIlmMaksu;     // oletusarvo 50 mk	// Euro!
	double	m_AT_LainYlijAlarajaMk;// oletusarvo 300 mk	// Euro!
	double	m_AT_OsakArvoOsuus;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsetusRS)
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

#endif // !defined(AFX_ASETUSRS_H__7D89CE82_DEA2_11D2_89C3_0000E8C7E630__INCLUDED_)
