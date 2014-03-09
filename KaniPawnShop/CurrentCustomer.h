#if !defined(AFX_CURRENTCUSTOMER_H__5BD242E3_6F69_11EF_8A68_0000E8C7E630__INCLUDED_)
#define AFX_CURRENTCUSTOMER_H__5BD242E3_6F69_11EF_8A68_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CurrentCustomer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCurrentCustomer window

class CCurrentCustomer : public /*CWnd*/ CAsiakasRS
{
// Construction
public:
	CCurrentCustomer();
	CCurrentCustomer(long lCustomerID);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurrentCustomer)
	//}}AFX_VIRTUAL

// Implementation
public:
	long getCurrentCustomerID();
	BOOL isCustomerSelected();
	void setCurrentCustomerID(long lCustomerID);
	virtual ~CCurrentCustomer();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCurrentCustomer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
private:
	bool m_bSelectedOK;
	long m_lCustomerID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURRENTCUSTOMER_H__5BD242E3_6F69_11EF_8A68_0000E8C7E630__INCLUDED_)
