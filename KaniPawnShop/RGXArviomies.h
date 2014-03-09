#if !defined(AFX_RGXARVIOMIES_H__E28C28FA_3B89_11D3_89F5_0000E8C7E630__INCLUDED_)
#define AFX_RGXARVIOMIES_H__E28C28FA_3B89_11D3_89F5_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXArviomies.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CRGXArviomies window

class CRGXArviomies : public /*CWnd*/CGXGridWnd
{
// Construction
public:
	CRGXArviomies();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXArviomies)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRGXArviomies();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXArviomies)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt);




private:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXARVIOMIES_H__E28C28FA_3B89_11D3_89F5_0000E8C7E630__INCLUDED_)
