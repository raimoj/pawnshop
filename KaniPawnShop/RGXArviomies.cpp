// RGXArviomies.cpp : implementation file
//

#include "stdafx.h"
#include "pantti.h"
#include "RGXArviomies.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CRGXArviomies

CRGXArviomies::CRGXArviomies()
{
}

CRGXArviomies::~CRGXArviomies()
{
}


BEGIN_MESSAGE_MAP(CRGXArviomies, /*CWnd*/CGXGridWnd)
	//{{AFX_MSG_MAP(CRGXArviomies)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CRGXArviomies::OnLButtonClickedRowCol(ROWCOL nRow,
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


/////////////////////////////////////////////////////////////////////////////
// CRGXArviomies message handlers
