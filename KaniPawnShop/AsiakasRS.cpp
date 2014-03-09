// AsiakasRS.cpp : implementation file
//

#include "stdafx.h"
#include "Pantti.h"
#include "AsiakasRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsiakasRS

IMPLEMENT_DYNAMIC(CAsiakasRS, CRecordset)

CAsiakasRS::CAsiakasRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAsiakasRS)
	m_AS_ID = 0;
	m_AS_HTun = _T("");
	m_AS_RuotsHTun = FALSE;
	m_AS_Sp = FALSE;
	m_AS_Nimi = _T("");
	m_AS_ENimet = _T("");
	m_AS_KatuOs = _T("");
	m_AS_Ptp = _T("");
	m_AS_Puh = _T("");
	m_AS_Huom = _T("");
	m_AS_Kielto = 0;
	m_AS_Ylij = 0.0;//_T("");
	m_AS_Alij = 0.0;//_T("");
	m_AS_KieltoAika = 0;			// HUOM! Tämä pitää muistaa lisätä!
	m_AS_MuistEsto = 0;
	m_AS_AsSuhtAlku = 0;	// HUOM! Tämä pitää muistaa lisätä!
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CAsiakasRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}*/

CString CAsiakasRS::GetDefaultSQL()
{
	//return _T("[dbo].[ASIAKAS]");
	return _T("[ASIAKAS]");
}

void CAsiakasRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAsiakasRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[AS_ID]"), m_AS_ID);
	RFX_Text(pFX, _T("[AS_HTun]"), m_AS_HTun);
	RFX_Bool(pFX, _T("[AS_RuotsHTun]"), m_AS_RuotsHTun);
	RFX_Bool(pFX, _T("[AS_Sp]"), m_AS_Sp);
	RFX_Text(pFX, _T("[AS_Nimi]"), m_AS_Nimi);
	RFX_Text(pFX, _T("[AS_ENimet]"), m_AS_ENimet);
	RFX_Text(pFX, _T("[AS_KatuOs]"), m_AS_KatuOs);
	RFX_Text(pFX, _T("[AS_Ptp]"), m_AS_Ptp);
	RFX_Text(pFX, _T("[AS_Puh]"), m_AS_Puh);
	RFX_Text(pFX, _T("[AS_Huom]"), m_AS_Huom);
	RFX_Long(pFX, _T("[AS_Kielto]"), m_AS_Kielto);
	RFX_Double(pFX, _T("[AS_Ylij]"), m_AS_Ylij);
	RFX_Double(pFX, _T("[AS_Alij]"), m_AS_Alij);
	RFX_Date(pFX, _T("[AS_KieltoAika]"), m_AS_KieltoAika);
	RFX_Long(pFX, _T("[AS_MuistEsto]"), m_AS_MuistEsto);
	RFX_Date(pFX, _T("[AS_AsSuhtAlku]"), m_AS_AsSuhtAlku);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAsiakasRS diagnostics

#ifdef _DEBUG
void CAsiakasRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CAsiakasRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
