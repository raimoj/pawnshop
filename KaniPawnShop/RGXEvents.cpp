// RGXEventRows.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXEvents.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGXEvents

CRGXEvents::CRGXEvents()
{
	m_lCurrentLoanEventNr = 0;
}

CRGXEvents::CRGXEvents(CDlgTapahtumat* pCDlgEvents)
{
	m_pCDlgEvents = pCDlgEvents;
	m_lCurrentLoanEventNr = 0;
}

CRGXEvents::~CRGXEvents()
{
}


BEGIN_MESSAGE_MAP(CRGXEvents, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXEvents)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRGXEvents message handlers


BOOL CRGXEvents::OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt)
{
	long lEventNr = 0;
	//TRACE("OnLButtonClickedRowCol!\n");
	SetReadOnly(FALSE);
	SetStyleRange(CGXRange(1, 0, GetRowCount(), 12),
						CGXStyle().SetFont(CGXFont()./*SetSize(14).*/SetBold(FALSE))
						);
	SetStyleRange(CGXRange(nRow, 0, nRow, 12),
								CGXStyle().SetFont(CGXFont()./*SetSize(14).*/SetBold(TRUE))
								);

	SetReadOnly(TRUE);


	if (nRow >= 1)
	{
		//TRACE("Valittu rivi %d\n", nRow);
		m_lCurrentLoanEventNr = atol(GetValueRowCol(nRow,17));
		
		GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
							(LONG) GetSafeHwnd());
	}
	return TRUE;
}

