#if !defined(AFX_KASSALOKIRS_H__2A4AA7E3_57CE_11D3_8A0B_0000E8C7E630__INCLUDED_)
#define AFX_KASSALOKIRS_H__2A4AA7E3_57CE_11D3_8A0B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KassalokiRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKassalokiRS recordset

class CKassalokiRS : public CRRecordset
{
public:
	CKassalokiRS(/*CDatabase* pDatabase = NULL*/);
	
	DECLARE_DYNAMIC(CKassalokiRS)
	
	BOOL writeDeskLogEntry(
			CString tType = "",	// Tapahtuman tyyppi: U/D/L/....
			double dSum = NULL,	// Rahasumma kassasiirroissa (ei kohdistu mihink‰‰n lainaan, lainaNr j‰‰ tyhj‰ksi)
			CString sExplanation = "",	// Selite
			long LNr = NULL,		// Lainan numero
			double dOldLoan = 0,	// Lainasumma ennen operaatiota
			double dNewLoan = 0,	// Lainasumma operaation j‰lkeen
			double dInterest = 0,	// Korkojen osuus
			double dStorageInsurance = 0,	// SHVMaksut
			double dTransaction = 0,	// Toimitusmaksut
			double	dRounding = 0,		// Pyˆristys
			double	dTotal = 0,			// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
			double dExtra = 0,		// Ylij‰‰m‰
			double dShortfall = 0,	// Alij‰‰m‰
			long lDeskID = 0);		// Kassan tunnus (Kassasiirrot p‰‰tt‰‰ itse mik‰ kassa kyseess‰ (ei aina oletuskassa!)
	

// Field/Param Data
	//{{AFX_FIELD(CKassalokiRS, CRRecordset)
	long	m_KL_Rivi;
	long	m_KL_KS_Tunnus;
	long	m_KL_LainaNr;
	CString	m_KL_TapahtumanTyyppi;
	BOOL	m_KL_Peruttu;
	CTime	m_KL_Aika;
	CString	m_KL_AM_Nimikirjaimet;
	double	m_KL_Summa;
	double	m_KL_VanhaLaina;
	double	m_KL_UusiLaina;
    double	m_KL_Korot;
	double	m_KL_SHVMaksut;
	double	m_KL_Toimitusmaksut;
	double	m_KL_Pyoristys;
	double	m_KL_Maksettava;
	double	m_KL_Alijaama;
	double	m_KL_Ylijaama;
	CString	m_KL_Selite;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKassalokiRS)
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

#endif // !defined(AFX_KASSALOKIRS_H__2A4AA7E3_57CE_11D3_8A0B_0000E8C7E630__INCLUDED_)
