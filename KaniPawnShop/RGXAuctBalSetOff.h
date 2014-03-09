#if !defined(AFX_RGXAUCTBALSETOFF_H__20A9B2A3_DBC9_11D3_8A37_0000E8C7E630__INCLUDED_)
#define AFX_RGXAUCTBALSETOFF_H__20A9B2A3_DBC9_11D3_8A37_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXAuctBalSetOff.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXAuctBalSetOff window

class CRGXAuctBalSetOff : public /*CWnd*/ CGXGridWnd
{
// Construction
public:
	CRGXAuctBalSetOff();
	CRGXAuctBalSetOff(CAuctionCtrl* pActl);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXAuctBalSetOff)
	//}}AFX_VIRTUAL

// Implementation
public:
	void clear();
	void showLetter(long lLetterNr);
	virtual ~CRGXAuctBalSetOff();
	void initColumns();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXAuctBalSetOff)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CAuctionCtrl* m_pActl;
	BOOL OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXAUCTBALSETOFF_H__20A9B2A3_DBC9_11D3_8A37_0000E8C7E630__INCLUDED_)
