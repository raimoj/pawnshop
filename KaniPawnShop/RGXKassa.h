#if !defined(AFX_RGXKASSA_H__4DDEA09D_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_RGXKASSA_H__4DDEA09D_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXKassa.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXKassa window

class CRGXKassa : public /*CWnd*/CGXGridWnd
{
// Construction
public:
	CRGXKassa();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXKassa)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRGXKassa();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXKassa)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()



	BOOL OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt);


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXKASSA_H__4DDEA09D_3EBE_11D3_89F5_0000E8C7E630__INCLUDED_)
