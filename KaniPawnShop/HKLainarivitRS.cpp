// HKLainarivitRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "HKLainarivitRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHKLainarivitRS

IMPLEMENT_DYNAMIC(CHKLainarivitRS, CRecordset)

CHKLainarivitRS::CHKLainarivitRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CHKLainarivitRS)
	m_HLR_ID = 0;//_T("");
	m_HLR_HKL_LA_Nr = 0;
	m_HLR_RiviNr = 0;
	m_HLR_TuNr = _T("");
	m_HLR_Maara = 0;
	m_HLR_Yks = _T("");
	m_HLR_YksPaino = 0;//_T("");
	m_HLR_SiirtoMyymalaan = FALSE;
	m_HLR_EiListoille = FALSE;
	m_HLR_Kuvaus = _T("");
	m_HLR_Huom = _T("");
	m_HLR_Laina = 0;//_T("");
	m_HLR_Varasto = _T("");
	m_HLR_KorotKulut = 0;//_T("");
	m_HLR_HKkulut = 0;//_T("");
	m_HLR_Pohjahinta = 0;//_T("");
	m_HLR_KorkeinTarjous = 0;//_T("");
	m_HLR_TarjoajanNimi = _T("");
	m_HLR_MyyntiRaja = 0;//_T("");
	m_HLR_Myyntihinta = 0;//_T("");
	m_HLR_OstajanNimi = _T("");
	m_HLR_MyyntiHuom = _T("");
	m_HLR_MyyntiPv = 0;			// Tämä pitää muistaa lisätä !
	m_nFields = 21;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CHKLainarivitRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CHKLainarivitRS::GetDefaultSQL()
{
	//return _T("[dbo].[HKLAINARIVIT]");
	return _T("[HKLAINARIVIT]");
}

void CHKLainarivitRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CHKLainarivitRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[HLR_ID]"), m_HLR_ID);
	RFX_Long(pFX, _T("[HLR_HKL_LA_Nr]"), m_HLR_HKL_LA_Nr);
	RFX_Long(pFX, _T("[HLR_RiviNr]"), m_HLR_RiviNr);
	RFX_Text(pFX, _T("[HLR_TuNr]"), m_HLR_TuNr);
	RFX_Long(pFX, _T("[HLR_Maara]"), m_HLR_Maara);
	RFX_Text(pFX, _T("[HLR_Yks]"), m_HLR_Yks);
	RFX_Double(pFX, _T("[HLR_YksPaino]"), m_HLR_YksPaino);
	RFX_Bool(pFX, _T("[HLR_SiirtoMyymalaan]"), m_HLR_SiirtoMyymalaan);
	RFX_Bool(pFX, _T("[HLR_EiListoille]"), m_HLR_EiListoille);
	RFX_Text(pFX, _T("[HLR_Kuvaus]"), m_HLR_Kuvaus);
	//RFX_Text(pFX, _T("[HLR_Huom]"), m_HLR_Huom);
	RFX_Double(pFX, _T("[HLR_Laina]"), m_HLR_Laina);
	//RFX_Text(pFX, _T("[HLR_Varasto]"), m_HLR_Varasto);
	RFX_Double(pFX, _T("[HLR_KorotKulut]"), m_HLR_KorotKulut);
	RFX_Double(pFX, _T("[HLR_HKkulut]"), m_HLR_HKkulut);
	RFX_Double(pFX, _T("[HLR_Pohjahinta]"), m_HLR_Pohjahinta);
	RFX_Double(pFX, _T("[HLR_KorkeinTarjous]"), m_HLR_KorkeinTarjous);
	RFX_Text(pFX, _T("[HLR_TarjoajanNimi]"), m_HLR_TarjoajanNimi);
	RFX_Double(pFX, _T("[HLR_MyyntiRaja]"), m_HLR_MyyntiRaja);
	RFX_Double(pFX, _T("[HLR_Myyntihinta]"), m_HLR_Myyntihinta);
	RFX_Text(pFX, _T("[HLR_OstajanNimi]"), m_HLR_OstajanNimi);
	RFX_Text(pFX, _T("[HLR_MyyntiHuom]"), m_HLR_MyyntiHuom);
	RFX_Date(pFX, _T("[HLR_MyyntiPv]"), m_HLR_MyyntiPv);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CHKLainarivitRS diagnostics

#ifdef _DEBUG
void CHKLainarivitRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CHKLainarivitRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG


