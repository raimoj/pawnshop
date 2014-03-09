#if !defined(AFX_CUSTOMERINFO_H__3F24AD67_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_)
#define AFX_CUSTOMERINFO_H__3F24AD67_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomerInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomerInfo window

class CDBLoan;

class CCustomerInfo : public CWnd
{
// Construction
public:
	CCustomerInfo();
	CCustomerInfo(CDBLoan* pDBLoan, long lCustomerID);
	CCustomerInfo(const CCustomerInfo& customerinfo);

// Attributes
public:
	long m_lCustID;
	CString m_AS_Ptp;
	CString m_AS_KatuOs;
	CString m_AS_ENimet;
	CString m_AS_HTun;
	CString m_AS_Nimi;

	CDBLoan* m_pDBLoan;

// Operations // Implementation
public:
	BOOL CheckGender(CString sHtun);
	
	CString RemoveSpaces(CString sText);
	CString updateHTun(CString ht);
	CString GetHtun(CString sHtun, BOOL bRuotsHTun, int iSp = -1);
	//void print(int xPos, int yPos, bool bNote);
	void setCustomer(long lCustomerID);


	virtual ~CCustomerInfo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomerInfo)
	//}}AFX_VIRTUAL



	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomerInfo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_sTempHtun;

	BOOL NumberCheck(CString sChar, int iMin, int iMax);
	BOOL CheckChar(CString sChar, CString s);
	int CheckIdentityNumber(CString sHTun, BOOL bRuotsHTun, int isp);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMERINFO_H__3F24AD67_E4B2_11D3_8A37_0000E8C7E630__INCLUDED_)
