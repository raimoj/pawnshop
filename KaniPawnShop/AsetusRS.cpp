// AsetusRS.cpp : implementation file
//

#include "stdafx.h"
#include "Pantti.h"
#include "AsetusRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsetusRS

IMPLEMENT_DYNAMIC(CAsetusRS, CRecordset)

CAsetusRS::CAsetusRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAsetusRS)
	m_AT_Toimisto = _T("");
	m_AT_Katu = _T("");
	m_AT_Ptp = _T("");
	m_AT_Puh = _T("");
	m_AT_Fax = _T("");
	m_AT_LainaAika = 0;
	m_AT_LKorkoPr1 = 0.0;//_T("");
	m_AT_LRaja1 = 0.0;//_T("");
	m_AT_LKorkoPr2 = 0.0;
	m_AT_LRaja2 = 0.0;//_T("");
	m_AT_LKorkoPr3 = 0.0;
	m_AT_LRaja3 = 0.0;//_T("");
	m_AT_LKorkoPr4 = 0.0;
	m_AT_MyValmMaksuPr = 0.0;//_T("");
	m_AT_MyValmMaksuaikaEr = 0;
	m_AT_MyValmMaksuMin = 0;
	m_AT_ArvopapValMaksuPr = 0;
	m_AT_Lisakulut = 0.0;//_T("");
	m_AT_Kuittimaksu = 0.0;//_T("");
	m_AT_MuKirjemaksu = 0.0;//_T("");
	m_AT_HKMaksuPr = 0.0;//_T("");
	m_AT_HKPoMaksu = 0.0;//_T("");
	m_AT_HKKulut = 0.0;//_T("");
	m_AT_PostitusMaksu = 0.0;//_T("");
	m_AT_KuitinKatoaminen = 0.0;//_T("");
	m_AT_ToimenpideKieltoPv = 0;
	m_AT_SHVMaksuPr = 0.0;//_T("");
	m_AT_VakVarmMaksu = 0.0;//_T("");
	m_AT_SeurHKPv = 0;			// HUOM! Tämä pitää muistaa lisätä (date-tyyppi/initialisointi)!
	m_AT_HKEraPvRaja = 0;		// HUOM! Tämä pitää muistaa lisätä (date-tyyppi/initialisointi)!
	m_AT_MuKirjeRajaMk = 0.0;//_T("");
	m_AT_MuKirje1RajaPv = 0;
	m_AT_MuKirje2RajaPv = 0;
	m_AT_HKSiirtoRajaPv = 0;
	m_AT_YlijKuitAikaraja = 0;
	m_AT_YlijIlmMaksu = 0.0;//_T("");
	m_AT_LainYlijAlarajaMk = 0.0;//_T("");
	m_AT_OsakArvoOsuus = 0.0;//_T("");
	m_nFields = 38;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CAsetusRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}
*/
CString CAsetusRS::GetDefaultSQL()
{
	//return _T("[dbo].[ASETUS]");
	return _T("[ASETUS]");
}

void CAsetusRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAsetusRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[AT_Toimisto]"), m_AT_Toimisto);
	RFX_Text(pFX, _T("[AT_Katu]"), m_AT_Katu);
	RFX_Text(pFX, _T("[AT_Ptp]"), m_AT_Ptp);
	RFX_Text(pFX, _T("[AT_Puh]"), m_AT_Puh);
	RFX_Text(pFX, _T("[AT_Fax]"), m_AT_Fax);
	RFX_Long(pFX, _T("[AT_LainaAika]"), m_AT_LainaAika);
	RFX_Double(pFX, _T("[AT_LKorkoPr1]"), m_AT_LKorkoPr1);
	RFX_Double(pFX, _T("[AT_LRaja1]"), m_AT_LRaja1);
	RFX_Double(pFX, _T("[AT_LKorkoPr2]"), m_AT_LKorkoPr2);
	RFX_Double(pFX, _T("[AT_LRaja2]"), m_AT_LRaja2);
	RFX_Double(pFX, _T("[AT_LKorkoPr3]"), m_AT_LKorkoPr3);
	RFX_Double(pFX, _T("[AT_LRaja3]"), m_AT_LRaja3);
	RFX_Double(pFX, _T("[AT_LKorkoPr4]"), m_AT_LKorkoPr4);
	RFX_Double(pFX, _T("[AT_MyValmMaksuPr]"), m_AT_MyValmMaksuPr);
	RFX_Long(pFX, _T("[AT_MyValmMaksuaikaEr]"), m_AT_MyValmMaksuaikaEr);
	RFX_Double(pFX, _T("[AT_MyValmMaksuMin]"), m_AT_MyValmMaksuMin);
	RFX_Double(pFX, _T("[AT_ArvopapValMaksuPr]"), m_AT_ArvopapValMaksuPr);
	RFX_Double(pFX, _T("[AT_Lisakulut]"), m_AT_Lisakulut);
	RFX_Double(pFX, _T("[AT_Kuittimaksu]"), m_AT_Kuittimaksu);
	RFX_Double(pFX, _T("[AT_MuKirjemaksu]"), m_AT_MuKirjemaksu);
	RFX_Double(pFX, _T("[AT_HKMaksuPr]"), m_AT_HKMaksuPr);
	RFX_Double(pFX, _T("[AT_HKPoMaksu]"), m_AT_HKPoMaksu);
	RFX_Double(pFX, _T("[AT_HKKulut]"), m_AT_HKKulut);
	RFX_Double(pFX, _T("[AT_PostitusMaksu]"), m_AT_PostitusMaksu);
	RFX_Double(pFX, _T("[AT_KuitinKatoaminen]"), m_AT_KuitinKatoaminen);
	RFX_Long(pFX, _T("[AT_ToimpideKieltoPv]"), m_AT_ToimenpideKieltoPv);
	RFX_Double(pFX, _T("[AT_SHVMaksuPr]"), m_AT_SHVMaksuPr);
	RFX_Double(pFX, _T("[AT_VakVarmMaksu]"), m_AT_VakVarmMaksu);
	RFX_Date(pFX, _T("[AT_SeurHKPv]"), m_AT_SeurHKPv);
	RFX_Date(pFX, _T("[AT_HKEraPvRaja]"), m_AT_HKEraPvRaja);
	RFX_Double(pFX, _T("[AT_MuKirjeRajaMk]"), m_AT_MuKirjeRajaMk);
	RFX_Long(pFX, _T("[AT_MuKirje1RajaPv]"), m_AT_MuKirje1RajaPv);
	RFX_Long(pFX, _T("[AT_MuKirje2RajaPv]"), m_AT_MuKirje2RajaPv);
	RFX_Long(pFX, _T("[AT_HKSiirtoRajaPv]"), m_AT_HKSiirtoRajaPv);
	RFX_Long(pFX, _T("[AT_YlijKuitAikaraja]"), m_AT_YlijKuitAikaraja);
	RFX_Double(pFX, _T("[AT_YlijIlmMaksu]"), m_AT_YlijIlmMaksu);
	RFX_Double(pFX, _T("[AT_LainYlijAlarajaMk]"), m_AT_LainYlijAlarajaMk);
	RFX_Double(pFX, _T("[AT_OsakArvoOsuus]"), m_AT_OsakArvoOsuus);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAsetusRS diagnostics

#ifdef _DEBUG
void CAsetusRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CAsetusRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
