// LainaRS2.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "LainaRS2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLainaRS2

IMPLEMENT_DYNAMIC(CLainaRS2, CRecordset)

CLainaRS2::CLainaRS2(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLainaRS2)
	m_LA_Nr = 0;
	
	m_LA_AS_ID = 0;
	m_LA_LainanNimi = _T("");
	m_LA_TR_Ryhma = _T("");
	m_LA_AS_HTun = _T("");

	m_LA_AlkupPv = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_Pv = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_EraPv = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_Tila = _T("");
	m_LA_VakSumma = 0.0;//_T("");
	m_LA_Laina = 0.0;//_T("");
	m_LA_Korko = 0.0;
	m_LA_Kielto = _T("");
	m_LA_KieltoRajaPv = 0;			// HUOM ! Tämä pitää muistaa lisätä !

	m_LA_SaVakMaksuPr = 0.0;//_T("");
	m_LA_YlimSaMaksu = 0.0;//_T("");

	m_LA_KuitinKatoaminen = FALSE;
	m_LA_KuitinKatoamisMaksu = 0.0;//_T("");
	m_LA_MuistKirjeMaksu1 = 0.0;//_T("");
	m_LA_MuistKirjeMaksu2 = 0.0;//_T("");
	m_LA_VakVarmMaksu = 0.0;//_T("");
	m_LA_PostitusMaksu = 0.0;//_T("");

	m_LA_HkPoistomaksu = 0;
	m_LA_MyValmKorvaus = 0;
	m_LA_ArvopapValMaksu = 0;

	m_LA_Alennus = 0.0;//_T("");


	m_LA_Liitteet = _T("");
	m_LA_Huom = _T("");
	m_LA_EiMuistutusta = FALSE;
	m_LA_MuistHuom = _T("");
	m_LA_OdotusPv = 0;				// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_MuistKirje1 = 0;			// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_MuistKirje2 = 0;			// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_HuutokPv = 0;				// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_YlijKirjePv = 0;			// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_Aika = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_LA_Varasto = _T("");
	//m_LA_ts = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_nFields = 37;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CLainaRS2::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CLainaRS2::GetDefaultSQL()
{
	//return _T("[dbo].[LAINAPERU]");
	return _T("[LAINAPERU]");
}

void CLainaRS2::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLainaRS2)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[LA_Nr]"), m_LA_Nr);
	
	RFX_Long(pFX, _T("[LA_AS_ID]"), m_LA_AS_ID);
	RFX_Text(pFX, _T("[LA_AS_HTun]"), m_LA_AS_HTun);
	RFX_Text(pFX, _T("[LA_LainanNimi]"), m_LA_LainanNimi);
	RFX_Text(pFX, _T("[LA_TR_Ryhma]"), m_LA_TR_Ryhma);

	RFX_Date(pFX, _T("[LA_AlkupPv]"), m_LA_AlkupPv);
	RFX_Date(pFX, _T("[LA_Pv]"), m_LA_Pv);
	RFX_Date(pFX, _T("[LA_EraPv]"), m_LA_EraPv);
	RFX_Text(pFX, _T("[LA_Tila]"), m_LA_Tila);
	RFX_Double(pFX, _T("[LA_VakSumma]"), m_LA_VakSumma);
	RFX_Double(pFX, _T("[LA_Laina]"), m_LA_Laina);
	RFX_Double(pFX, _T("[LA_Korko]"), m_LA_Korko);
	RFX_Text(pFX, _T("[LA_Kielto]"), m_LA_Kielto);
	RFX_Date(pFX, _T("[LA_KieltoRajaPv]"), m_LA_KieltoRajaPv);

	RFX_Double(pFX, _T("[LA_SaVakMaksuPr]"), m_LA_SaVakMaksuPr);
	RFX_Double(pFX, _T("[LA_YlimSaMaksu]"), m_LA_YlimSaMaksu);

	RFX_Bool(pFX, _T("[LA_KuitinKatoaminen]"), m_LA_KuitinKatoaminen);
	RFX_Double(pFX, _T("[LA_KuitinKatoamisMaksu]"), m_LA_KuitinKatoamisMaksu);
	RFX_Double(pFX, _T("[LA_MuistKirjeMaksu1]"), m_LA_MuistKirjeMaksu1);
	RFX_Double(pFX, _T("[LA_MuistKirjeMaksu2]"), m_LA_MuistKirjeMaksu2);
	RFX_Double(pFX, _T("[LA_VakVarmMaksu]"), m_LA_VakVarmMaksu);
	RFX_Double(pFX, _T("[LA_PostitusMaksu]"), m_LA_PostitusMaksu);

	RFX_Double(pFX, _T("[LA_HkPoistomaksu]"), m_LA_HkPoistomaksu);
	RFX_Double(pFX, _T("[LA_MyValmKorvaus]"), m_LA_MyValmKorvaus);
	RFX_Double(pFX, _T("[LA_ArvopapValMaksu]"), m_LA_ArvopapValMaksu);

	RFX_Double(pFX, _T("[LA_Alennus]"), m_LA_Alennus);

	RFX_Text(pFX, _T("[LA_Liitteet]"), m_LA_Liitteet);
	RFX_Text(pFX, _T("[LA_Huom]"), m_LA_Huom);
	RFX_Bool(pFX, _T("[LA_EiMuistutusta]"), m_LA_EiMuistutusta);
	RFX_Text(pFX, _T("[LA_MuistHuom]"), m_LA_MuistHuom);
	RFX_Date(pFX, _T("[LA_OdotusPv]"), m_LA_OdotusPv);
	RFX_Date(pFX, _T("[LA_MuistKirje1]"), m_LA_MuistKirje1);
	RFX_Date(pFX, _T("[LA_MuistKirje2]"), m_LA_MuistKirje2);
	RFX_Date(pFX, _T("[LA_HuutokPv]"), m_LA_HuutokPv);
	RFX_Date(pFX, _T("[LA_YlijKirjePv]"), m_LA_YlijKirjePv);
	RFX_Date(pFX, _T("[LA_Aika]"), m_LA_Aika);
	RFX_Text(pFX, _T("[LA_Varasto]"), m_LA_Varasto);
	//RFX_Date(pFX, _T("[LA_ts]"), m_LA_ts);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLainaRS2 diagnostics

#ifdef _DEBUG
void CLainaRS2::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CLainaRS2::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
