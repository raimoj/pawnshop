#if !defined(AFX_TAPAHTUMARS_H__C163CA93_F421_11D2_89CE_0000E8C7E630__INCLUDED_)
#define AFX_TAPAHTUMARS_H__C163CA93_F421_11D2_89CE_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TapahtumaRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTapahtumaRS recordset

class CTapahtumaRS : public CRRecordset
{
public:
	CTapahtumaRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTapahtumaRS)

// Field/Param Data
	//{{AFX_FIELD(CTapahtumaRS, CRRecordset)
	long	m_TP_Tap;
	long	m_TP_LA_Nr;
	long	m_TP_KS_Tunnus;
	CString m_TP_Varmennus;
	CTime	m_TP_Aika;
	CString	m_TP_AM_Nimikirjaimet;
		double m_TP_Summa; //Rahasumma kassasiirroissa. Tällöin operaatio ei kohdistu mihinkään lainaan, joten KL_LainaNr-kenttä jää tyhjäksi
	double	m_TP_VakSumma;
	double	m_TP_VanhaLaina;
	double	m_TP_UusiLaina;
	//double	m_TP_Muutos; // TÄHÄN PITÄISI LASKEA VANHAN JA UUDEN LAINAN EROTUS, MUUTOS
		double m_TP_Korot;
		double m_TP_SHVMaksut;
		double m_TP_Toimitusmaksut;	//ylimSailMaksu + kuittimaksu + kuitinKatoaminen + muistutusmaksut + vakuusvarmennus + postituskulut + muutKulut
		double m_TP_AlePyor;		//alennus+ pyöristys, Rahasumma laskennallisen summan pyöristämiseksi sopivaksi tasaluvuksi (=Maksettava)
	double	m_TP_Maksettava;		//Lopullinen summa, joka tulee kassaan (positiivinen) tai lähtee kassasta (negatiivinen), Kassasiirroissa tyhjä (Null)
	CString	m_TP_Tyyppi;			//Tarkasta tunnukset: ?=Uusi laina,?L=Lunastus ?=uudistus,... katso dokumentaatio (muistilista)
		double m_TP_Alijaama;	
		double m_TP_Ylijaama;
	CString	m_TP_Selitys;
	CString	m_TP_Huom;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTapahtumaRS)
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

#endif // !defined(AFX_TAPAHTUMARS_H__C163CA93_F421_11D2_89CE_0000E8C7E630__INCLUDED_)
