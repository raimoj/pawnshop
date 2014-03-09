#if !defined(AFX_RGXHKLAINARIVITGRID_H__B7BB8EA5_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_)
#define AFX_RGXHKLAINARIVITGRID_H__B7BB8EA5_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGXHkLainarivitGrid.h : header file
//

class CAuctionCtrl;

/////////////////////////////////////////////////////////////////////////////
// CRGXHkLainarivitGrid window

class CRGXHkLainarivitGrid : public /*CWnd*/CGXGridWnd
{
// Construction
public:
	CRGXHkLainarivitGrid();
	CRGXHkLainarivitGrid(CMC* pMC, CAuctionCtrl* pACtrl);

// Attributes
public:

	CFont f1;
	CFont f2;

// Operations
public:
	long m_lCurrentRow;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGXHkLainarivitGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	void updateOldValuesAfterSaving();
	void dialogIsClosing();
	long m_lCurrentLoanNr;

	void clearList();
	bool showLoanRows(long lLoanNbr); // return bool bEntirelySold
	void initColumns();
	virtual ~CRGXHkLainarivitGrid();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRGXHkLainarivitGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);


private:
	BOOL m_bHKLR_MyyntihintaNull;
	bool m_bRowSellingPriceChanged;
	bool m_bRowBasePriceChanged;
	bool m_bRowWeightChanged; // paino muuttunut

	bool needToBeSaved();
	CString m_sHLR_MyyntiHuom;
	double m_dHLR_Myyntihinta;
	double m_dHLR_Pohjahinta;
	CString m_sHLR_Kuvaus;
	double m_dHLR_Paino;
	CMC* m_pMC;
	CAuctionCtrl* m_pACtrl;
	CHKLainarivitRS* m_pHkLr;

	void resetValues();

protected:

	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow,
										ROWCOL nCol,
										UINT nFlags,
										CPoint pt);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGXHKLAINARIVITGRID_H__B7BB8EA5_B0C9_11D3_8A1F_0000E8C7E630__INCLUDED_)
