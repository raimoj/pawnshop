#if !defined(AFX_AUCTIONSEARCHLIST_H__951B158D_9F6E_11D3_8A1D_0000E8C7E630__INCLUDED_)
#define AFX_AUCTIONSEARCHLIST_H__951B158D_9F6E_11D3_8A1D_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AuctionSearchList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuctionSearchList recordset

class CAuctionSearchList : public /*CRRecordset*/CHakulistaRS
{
public:
	void moveLoansToAuction();
	CAuctionSearchList(/*CDatabase* pDatabase = NULL*/CDB* pCDB);
	//DECLARE_DYNAMIC(CAuctionSearchList)

// Field/Param Data
	//{{AFX_FIELD(CAuctionSearchList, CRRecordset)
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuctionSearchList)
	public:
	//virtual CString GetDefaultConnect();    // Default connection string
	//virtual CString GetDefaultSQL();    // Default SQL for Recordset
	//virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:
	CDB* m_pCDB;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUCTIONSEARCHLIST_H__951B158D_9F6E_11D3_8A1D_0000E8C7E630__INCLUDED_)
