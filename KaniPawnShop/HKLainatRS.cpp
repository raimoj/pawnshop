// HKLainatRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "HKLainatRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHKLainatRS

IMPLEMENT_DYNAMIC(CHKLainatRS, CRecordset)

CHKLainatRS::CHKLainatRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CHKLainatRS)
	m_HKL_LA_Nr = 0;
	m_HKL_VNr = 0;
	m_HKL_AsID = 0;
	m_HKL_AsHTun = _T("");
	m_HKL_HK_Nr = 0;
	m_HKL_PoistettuHKsta = 0;	// (HUOM ! Tämä pitää muistaa lisätä !)
	m_HKL_LainanNimi = _T("");
	m_HKL_LainanTuoteryhma = _T("");
	m_HKL_EraPv = 0;
	m_HKL_Laina = 0.0;
	m_HKL_KorotKulut = 0.0;
	m_HKL_HKkulut = 0.0;
	m_HKL_Pohjahinta = 0.0;
	m_HKL_Myyntihinta = 0.0;
	m_HKL_Ylij_Alij = 0.0;
	m_HKL_OstajanNimi = _T("");
	m_HKL_MyyntiPv = 0;
	m_HKL_Kuittaus = FALSE;
	m_HKL_KuittausAika = 0;
	m_HKL_KirjeNr = 0;
	m_HKL_KirjePv = 0;
	m_HKL_YlijMaksuPv = 0;
	m_HKL_YlijKuittausPv = 0;
	m_HKL_Huom = _T("");
	//m_HKL_ts = 0;
	m_nFields = 24;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CHKLainatRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CHKLainatRS::GetDefaultSQL()
{
	//return _T("[dbo].[HKLAINAT]");
	return _T("[HKLAINAT]");
}

void CHKLainatRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CHKLainatRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[HKL_LA_Nr]"), m_HKL_LA_Nr);
	RFX_Long(pFX, _T("[HKL_VNr]"), m_HKL_VNr);
	RFX_Long(pFX, _T("[HKL_AsID]"), m_HKL_AsID);
	RFX_Text(pFX, _T("[HKL_AsHTun]"), m_HKL_AsHTun);
	RFX_Long(pFX, _T("[HKL_HK_Nr]"), m_HKL_HK_Nr);

	RFX_Date(pFX, _T("[HKL_PoistettuHKsta]"), m_HKL_PoistettuHKsta);
	RFX_Text(pFX, _T("[HKL_LainanNimi]"), m_HKL_LainanNimi);
	RFX_Text(pFX, _T("[HKL_LainanTuoteryhma]"), m_HKL_LainanTuoteryhma);
	RFX_Date(pFX, _T("[HKL_EraPv]"), m_HKL_EraPv);
	RFX_Double(pFX, _T("[HKL_Laina]"), m_HKL_Laina);
	RFX_Double(pFX, _T("[HKL_KorotKulut]"), m_HKL_KorotKulut);
	RFX_Double(pFX, _T("[HKL_HKkulut]"), m_HKL_HKkulut);
	RFX_Double(pFX, _T("[HKL_Pohjahinta]"), m_HKL_Pohjahinta);

	RFX_Double(pFX, _T("[HKL_Myyntihinta]"), m_HKL_Myyntihinta);
	RFX_Double(pFX, _T("[HKL_Ylij_Alij]"), m_HKL_Ylij_Alij);
	RFX_Text(pFX, _T("[HKL_OstajanNimi]"), m_HKL_OstajanNimi);
	RFX_Date(pFX, _T("[HKL_MyyntiPv]"), m_HKL_MyyntiPv);
	RFX_Bool(pFX, _T("[HKL_Kuittaus]"), m_HKL_Kuittaus);
	RFX_Date(pFX, _T("[HKL_KuittausAika]"), m_HKL_KuittausAika);
	RFX_Long(pFX, _T("[HKL_KirjeNr]"), m_HKL_KirjeNr);
	RFX_Date(pFX, _T("[HKL_KirjePv]"), m_HKL_KirjePv);
	RFX_Date(pFX, _T("[HKL_YlijMaksuPv]"), m_HKL_YlijMaksuPv);
	RFX_Date(pFX, _T("[HKL_YlijKuittausPv]"), m_HKL_YlijKuittausPv);
	RFX_Text(pFX, _T("[HKL_Huom]"), m_HKL_Huom);
	//RFX_Date(pFX, _T("[HKL_ts]"), m_HKL_ts);//RFX_Binary(pFX, _T("[HKL_ts]"), m_HKL_ts);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CHKLainatRS diagnostics

#ifdef _DEBUG
void CHKLainatRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CHKLainatRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG

