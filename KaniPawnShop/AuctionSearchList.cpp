// AuctionSearchList.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "AuctionSearchList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuctionSearchList

//IMPLEMENT_DYNAMIC(CAuctionSearchList, CRRecordset)

CAuctionSearchList::CAuctionSearchList(/*CDatabase* pdb*/CDB* pCDB)
	//: CRRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAuctionSearchList)
	//}}AFX_FIELD_INIT
	//m_nDefaultType = snapshot;
	m_pCDB = pCDB;
}

/*
CString CAuctionSearchList::GetDefaultConnect()
{
	return _T("ODBC;DSN=");
}

CString CAuctionSearchList::GetDefaultSQL()
{
	return _T("");
}

void CAuctionSearchList::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAuctionSearchList)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP
}
*/
/////////////////////////////////////////////////////////////////////////////
// CAuctionSearchList diagnostics

#ifdef _DEBUG
void CAuctionSearchList::AssertValid() const
{
	//CRRecordset::AssertValid();
}

void CAuctionSearchList::Dump(CDumpContext& dc) const
{
	//CRRecordset::Dump(dc);
}
#endif //_DEBUG

void CAuctionSearchList::moveLoansToAuction()
{

}
