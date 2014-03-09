// RGXKassa.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXKassa.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGXKassa

CRGXKassa::CRGXKassa()
{
}

CRGXKassa::~CRGXKassa()
{
}


BEGIN_MESSAGE_MAP(CRGXKassa, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXKassa)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




/////////////////////////////////////////////////////////////////////////////
// CRGXKassa message handlers


BOOL CRGXKassa::OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt)
{
	TRACE("OnLButtonClickedRowCol!\n");
	/*GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID(),
							MAKELONG(m_hwnd, RJ_OG_PARENT_DLG));
	*/
	if (nRow >= 1)
	{
		GetParent()->SendMessage(WM_COMMAND,
							GetDlgCtrlID() | RJ_OG_PARENT_DLG << 16,
							(LONG) GetSafeHwnd());
	}
	return TRUE;
}
