// CurrentCustomer.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "CurrentCustomer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrentCustomer

CCurrentCustomer::CCurrentCustomer()
{
	m_bSelectedOK = FALSE;
}

CCurrentCustomer::CCurrentCustomer(long lCustomerID)
{
	m_bSelectedOK = FALSE;
}

CCurrentCustomer::~CCurrentCustomer()
{
}


//BEGIN_MESSAGE_MAP(CCurrentCustomer, CWnd)
	//{{AFX_MSG_MAP(CCurrentCustomer)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCurrentCustomer message handlers

void CCurrentCustomer::setCurrentCustomerID(long lCustomerID)
{
	if (lCustomerID <= 0)
	{
		this->m_bSelectedOK = FALSE;
		this->m_lCustomerID = 0;
	}
	else
	{
		this->m_bSelectedOK = TRUE;
		this->m_lCustomerID = lCustomerID;
	}
}

BOOL CCurrentCustomer::isCustomerSelected()
{
	return m_bSelectedOK;
}

long CCurrentCustomer::getCurrentCustomerID()
{
	if (m_bSelectedOK)
		return this->m_lCustomerID;
	else
		return 0;
}





