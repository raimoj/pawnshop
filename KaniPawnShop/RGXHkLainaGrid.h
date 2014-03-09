#if !defined(AFX_RGXHKLAINAGRID_H__B7BB8EA4_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_)
#define AFX_RGXHKLAINAGRID_H__B7BB8EA4_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXHkLainaGrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGXHkLainaGrid window

class CRGXHkLainaGrid : public /*CWnd*/CGXGridWnd
{
// Construction
public:
	CRGXHkLainaGrid();
	CRGXHkLainaGrid(CMC* pMC, CAuctionCtrl* pACtrl);


// Attributes
public:

// Operations
public:

	CFont f1;
	CFont f2;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXHkLainaGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	void findLoan(long lLoanNr);
	long m_lCurrentLoanNr;

	void updateOldValuesAfterSaving();
	void dialogIsClosing();
	void showAuctionLoans(CString sSelectCondition);
	void initColumns();
	virtual ~CRGXHkLainaGrid();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXHkLainaGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);


private:
	BOOL m_bHKL_MyyntihintaNull;
	void resetValues();
	bool m_bLoanSellingPriceChanged;
	bool m_bLoanBasePriceChanged;
	long m_lCurrentRow;
	CMC* m_pMC;
	CAuctionCtrl* m_pACtrl;

	CString m_sHKL_LainanNimi;
	double m_dHKL_Pohjahinta;
	double m_dHKL_Myyntihinta;
	CString m_sHKL_Huom;
	CHKLainatRS* m_pHkL;

protected:

	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt);
	bool needToBeSaved();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXHKLAINAGRID_H__B7BB8EA4_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_)
