// KassalokiRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "KassalokiRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CPanttiApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CKassalokiRS

IMPLEMENT_DYNAMIC(CKassalokiRS, CRecordset)

CKassalokiRS::CKassalokiRS(/*CDatabase* pdb*/)
	: CRRecordset(/*pdb*/ theApp.GetDatabase())
{
	//{{AFX_FIELD_INIT(CKassalokiRS)
	m_KL_Rivi = 0;//_T("");
	m_KL_KS_Tunnus = 0;//_T("");
	m_KL_LainaNr = 0;
	m_KL_TapahtumanTyyppi = _T("");
	m_KL_Peruttu = FALSE;
	m_KL_Aika = 0;		// HUOM ! Tämä pitää muistaa lisätä !
	m_KL_AM_Nimikirjaimet = _T("");
	m_KL_Summa = 0;//_T("");
	m_KL_VanhaLaina = 0;
	m_KL_UusiLaina = 0;
    m_KL_Korot = 0;
	m_KL_SHVMaksut = 0;
	m_KL_Toimitusmaksut = 0;
	m_KL_Pyoristys = 0;
	m_KL_Maksettava = 0;
	m_KL_Alijaama = 0;
	m_KL_Ylijaama = 0;
	m_KL_Selite = _T("");
	m_nFields = 18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CKassalokiRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CKassalokiRS::GetDefaultSQL()
{
	//return _T("[dbo].[KASSALOKI]");
	return _T("[KASSALOKI]");
}

void CKassalokiRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CKassalokiRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[KL_Rivi]"), m_KL_Rivi);
	RFX_Long(pFX, _T("[KL_KS_Tunnus]"), m_KL_KS_Tunnus);
	RFX_Long(pFX, _T("[KL_LainaNr]"), m_KL_LainaNr);
	RFX_Text(pFX, _T("[KL_TapahtumanTyyppi]"), m_KL_TapahtumanTyyppi);
	RFX_Bool(pFX, _T("[KL_Peruttu]"), m_KL_Peruttu);
	RFX_Date(pFX, _T("[KL_Aika]"), m_KL_Aika);
	RFX_Text(pFX, _T("[KL_AM_Nimikirjaimet]"), m_KL_AM_Nimikirjaimet);
	RFX_Double(pFX, _T("[KL_Summa]"), m_KL_Summa);
	RFX_Double(pFX, _T("[KL_VanhaLaina]"), m_KL_VanhaLaina);
	RFX_Double(pFX, _T("[KL_UusiLaina]"), m_KL_UusiLaina);
	RFX_Double(pFX, _T("[KL_Korot]"), m_KL_Korot);
	RFX_Double(pFX, _T("[KL_SHVMaksut]"), m_KL_SHVMaksut);
	RFX_Double(pFX, _T("[KL_Toimitusmaksut]"), m_KL_Toimitusmaksut);
	RFX_Double(pFX, _T("[KL_Pyoristys]"), m_KL_Pyoristys);
	RFX_Double(pFX, _T("[KL_Maksettava]"), m_KL_Maksettava);
	RFX_Double(pFX, _T("[KL_Alijaama]"), m_KL_Alijaama);
	RFX_Double(pFX, _T("[KL_Ylijaama]"), m_KL_Ylijaama);
	RFX_Text(pFX, _T("[KL_Selite]"), m_KL_Selite);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CKassalokiRS diagnostics

#ifdef _DEBUG
void CKassalokiRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CKassalokiRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG



BOOL CKassalokiRS::writeDeskLogEntry(
	CString tType,	// Tapahtuman tyyppi: U/D/L/....
	double dSum,	// Rahasumma kassasiirroissa (ei kohdistu mihinkään lainaan, lainaNr jää tyhjäksi)
	CString sExplanation,	// Selite
	long LNr,		// Lainan numero
	double dOldLoan,	// Lainasumma ennen operaatiota
	double dNewLoan,	// Lainasumma operaation jälkeen
	double dInterest,	// Korkojen osuus
	double dStorageInsurance,	// SHVMaksut
	double dTransaction,	// Toimitusmaksut
	double	dRounding,		// Pyöristys
	double	dTotal,			// Lopullinen maksettava summa kassaan (positiivinen) tai kassasta (negatiivinen)
	double dExtra,		// Ylijäämä
	double dShortfall,	// Alijäämä
	long lDeskID)		// NULL->oletuskassa - // Kassan tunnus (Kassasiirrot päättää itse mikä kassa kyseessä (ei aina oletuskassa!)
{
	BOOL brtn = TRUE;
	CTime t = CTime::GetCurrentTime();
	try
	{
		Open();
		AddNew();
		//m_pKLRS->m_KL_Rivi;
		if (lDeskID == NULL)
		{
			m_KL_KS_Tunnus = theApp.m_lDeskId;
		}
		else
		{
			m_KL_KS_Tunnus = lDeskID;
		}
		//m_pKLRS->m_KL_LainaNr = 0;
		if (LNr > 0)
			m_KL_LainaNr = LNr;
		m_KL_TapahtumanTyyppi = tType;
		//
		// --- mitätöintitapahtumille asetetaan peruttu-lippu ylös ---
		if (tType == "H" || tType == "C" || tType == "E" || tType == "F" || tType == "G")
			m_KL_Peruttu = TRUE;
		else
			m_KL_Peruttu = FALSE;
		//
		m_KL_Aika = t;
		m_KL_AM_Nimikirjaimet = theApp.m_sUser;
		m_KL_Summa = dSum;

		m_KL_VanhaLaina = dOldLoan;
		m_KL_UusiLaina = dNewLoan;
		m_KL_Korot = dInterest;
		m_KL_SHVMaksut = dStorageInsurance;
		m_KL_Toimitusmaksut = dTransaction;
		m_KL_Pyoristys = dRounding;
		m_KL_Maksettava = dTotal;
		m_KL_Alijaama = dShortfall;
		m_KL_Ylijaama = dExtra;

		m_KL_Selite = sExplanation;
		Update();
		Close();
	}
	catch (CDBException* e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
		Close();
		brtn = FALSE;
	}
	return brtn;
}
