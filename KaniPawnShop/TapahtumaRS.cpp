// TapahtumaRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "TapahtumaRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTapahtumaRS

IMPLEMENT_DYNAMIC(CTapahtumaRS, CRecordset)

CTapahtumaRS::CTapahtumaRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTapahtumaRS)
	m_TP_Tap = 0;//_T("");
	m_TP_LA_Nr = 0;
	m_TP_KS_Tunnus = 0;
	m_TP_Varmennus = _T("");
	m_TP_Aika = 0;			// HUOM ! Tämä pitää muistaa lisätä !
	m_TP_AM_Nimikirjaimet = _T("");
		m_TP_Summa = 0;
	m_TP_VakSumma = 0;//_T("");
	m_TP_VanhaLaina = 0;//_T("");
	m_TP_UusiLaina = 0;//_T("");
//	m_TP_Muutos = 0; //MUUTOS
		m_TP_Korot = 0;
		m_TP_SHVMaksut = 0;
		m_TP_Toimitusmaksut = 0;
		m_TP_AlePyor = 0;
	m_TP_Maksettava = 0;//_T("");
	m_TP_Tyyppi = _T("");
		m_TP_Alijaama = 0;
		m_TP_Ylijaama = 0;
	m_TP_Selitys = _T("");
	m_TP_Huom = _T("");
	m_nFields = 20;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CTapahtumaRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=");
}*/

CString CTapahtumaRS::GetDefaultSQL()
{
	//return _T("[dbo].[TAPAHTUMA]");
	return _T("[TAPAHTUMA]");
}

void CTapahtumaRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTapahtumaRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TP_Tap]"), m_TP_Tap);
	RFX_Long(pFX, _T("[TP_LA_Nr]"), m_TP_LA_Nr);
	RFX_Long(pFX, _T("[TP_KS_Tunnus]"), m_TP_KS_Tunnus);
	RFX_Text(pFX, _T("[TP_Varmennus]"), m_TP_Varmennus);
	RFX_Date(pFX, _T("[TP_Aika]"), m_TP_Aika);
	RFX_Text(pFX, _T("[TP_AM_Nimikirjaimet]"), m_TP_AM_Nimikirjaimet);
		RFX_Double(pFX, _T("[TP_Summa]"), m_TP_Summa);
	RFX_Double(pFX, _T("[TP_VakSumma]"), m_TP_VakSumma);
	RFX_Double(pFX, _T("[TP_VanhaLaina]"), m_TP_VanhaLaina);
	RFX_Double(pFX, _T("[TP_UusiLaina]"), m_TP_UusiLaina);
//	RFX_Double(pFX, _T("[TP_Muutos]"), m_TP_Muutos);   //MUUTOS
		RFX_Double(pFX, _T("[TP_Korot]"), m_TP_Korot);
		RFX_Double(pFX, _T("[TP_SHVMaksut]"), m_TP_SHVMaksut);
		RFX_Double(pFX, _T("[TP_Toimitusmaksut]"), m_TP_Toimitusmaksut);
		RFX_Double(pFX, _T("[TP_AlePyor]"), m_TP_AlePyor);
	RFX_Double(pFX, _T("[TP_Maksettava]"), m_TP_Maksettava);
	RFX_Text(pFX, _T("[TP_Tyyppi]"), m_TP_Tyyppi);
		RFX_Double(pFX, _T("[TP_Alijaama]"), m_TP_Alijaama);
		RFX_Double(pFX, _T("[TP_Ylijaama]"), m_TP_Ylijaama);
	RFX_Text(pFX, _T("[TP_Selitys]"), m_TP_Selitys);
	RFX_Text(pFX, _T("[TP_Huom]"), m_TP_Huom);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTapahtumaRS diagnostics

#ifdef _DEBUG
void CTapahtumaRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CTapahtumaRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
