#if !defined(AFX_RGXDESKLOGROWS_H__5308A3A4_A5FB_11D5_8AC1_0000E8C7E630__INCLUDED_)
#define AFX_RGXDESKLOGROWS_H__5308A3A4_A5FB_11D5_8AC1_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXDeskLogRows.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXDeskLogRows window

class CRGXDeskLogRows : public /*CWnd*/ CGXGridWnd
{
// Construction
public:
	CRGXDeskLogRows();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXDeskLogRows)
	//}}AFX_VIRTUAL
private:
// Attributes
	CKassalokiRS* m_pKLRS;

	
// Implementation
public:
	void fillGrid(CTime date = NULL, long desk = -1);
	void initGrid();
	virtual ~CRGXDeskLogRows();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXDeskLogRows)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt);

private:
	long m_loanNr;
	void clear();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXDESKLOGROWS_H__5308A3A4_A5FB_11D5_8AC1_0000E8C7E630__INCLUDED_)
