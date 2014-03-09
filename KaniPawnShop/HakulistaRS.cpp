// HakulistaRS.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "HakulistaRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHakulistaRS

IMPLEMENT_DYNAMIC(CHakulistaRS, CRecordset)

CHakulistaRS::CHakulistaRS(CDatabase* pdb)
	: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CHakulistaRS)
	m_HA_LA_Nr = 0;
	m_HA_VNr = 0;
	m_HA_AsID = 0; //_T("");
	m_HA_AsHTun = _T("");
	m_HA_LainanNimi = _T("");
	m_HA_LainanTuoteryhma = _T("");
	m_HA_EraPv = 0;					// HUOM ! Tämä pitää muistaa lisätä !
	m_HA_Laina = 0.0; //_T("");
	m_HA_Varasto = _T("");
	m_HA_Liitteet = FALSE;
	m_HA_Huom = FALSE;
	m_HA_Odotus = FALSE;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


/*CString CHakulistaRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=Panttitietokanta");
}
*/

CString CHakulistaRS::GetDefaultSQL()
{
	//return _T("[dbo].[HAKULISTA]");
	return _T("[HAKULISTA]");
}

void CHakulistaRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CHakulistaRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[HA_LA_Nr]"), m_HA_LA_Nr);
	RFX_Long(pFX, _T("[HA_VNr]"), m_HA_VNr);
	RFX_Long(pFX, _T("[HA_AsID]"), m_HA_AsID);
	RFX_Text(pFX, _T("[HA_AsHTun]"), m_HA_AsHTun);
	RFX_Text(pFX, _T("[HA_LainanNimi]"), m_HA_LainanNimi);
	RFX_Text(pFX, _T("[HA_LainanTuoteryhma]"), m_HA_LainanTuoteryhma);
	RFX_Date(pFX, _T("[HA_EraPv]"), m_HA_EraPv);
	RFX_Double(pFX, _T("[HA_Laina]"), m_HA_Laina);
	RFX_Text(pFX, _T("[HA_Varasto]"), m_HA_Varasto);
	RFX_Bool(pFX, _T("[HA_Liitteet]"), m_HA_Liitteet);
	RFX_Bool(pFX, _T("[HA_Huom]"), m_HA_Huom);
	RFX_Bool(pFX, _T("[HA_Odotus]"), m_HA_Odotus);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CHakulistaRS diagnostics

#ifdef _DEBUG
void CHakulistaRS::AssertValid() const
{
	CRRecordset::AssertValid();
}

void CHakulistaRS::Dump(CDumpContext& dc) const
{
	CRRecordset::Dump(dc);
}
#endif //_DEBUG
