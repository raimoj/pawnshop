#if !defined(AFX_DBLOANEXPENSES_H__9C18A374_9209_11D3_8A1B_0000E8C7E630__INCLUDED_)
#define AFX_DBLOANEXPENSES_H__9C18A374_9209_11D3_8A1B_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBLoanExpenses.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBLoanExpenses window

class CDBLoanExpenses : public /*CWnd*/ CObject
{
// Construction
public:
	CDBLoanExpenses();

// Attributes
public:
	double m_dPyoristys;
	double m_dSHVMaksuYht;
	double m_dSHV_Mk_KK;
	int m_iSHVKorkokuukausia;
	double m_d_LA_KuitinKatoamismaksu;
	double m_dMaksettava;
	double m_dKorkoYht;
	double m_dViivastyskorkoYht;
	int m_iYlitysaikaPv;
	double m_dPaivakorko;
	double m_dKuukausikorkoYhtLainaAjalta;
	double m_dKuukausikorko;
	double m_d_LA_MuutKulut;
	double m_d_LA_Postitusmaksu;
	double m_d_LA_VakVarmMaksu;
	double m_d_LA_Muistutuskirjemaksu2;
	double m_d_LA_Muistutuskirjemaksu1;
	double m_d_LA_YlimSaMaksu;
	double m_d_LA_YlimSaMaksuPerKk;
	double m_d_AT_Kuittimaksu;
	double m_d_LA_SaVakMaksuPr;
	int m_iLoanMonthsDuringOfficialLoanPeriod;
	CTimeSpan m_tsTrueLoanPeriod;
	CTime m_tExpensesDate;

private:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBLoanExpenses)
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_iLoanMonthsDuringWholeLoanPeriod;
	double getKorkoMkEnnenErapaivaaYht();
	double getSHVKorkoMkPerKk();
	double getSHVKorkoMkPerPv();
	double getKorkoMkPerKk();
	double getKorkoMkPerPv();
	double getSHVKorkoPrPerKk();
	double getSHVKorkoPrPerPv();
	double getKorkoPrPerKk();
	double getKorkoPrPerPv();
	int getKorkoLainaKkErapvnJalkeen();
	int getSHVLainaKkErapvnJalkeen();
	int getLainaKkEnnenErapaivaa();
	int getLainaKkYht();
	int getLainaPvYht();
	CTime getExpensesTargetDate();
	int getLainaPvErapvnJalkeen();
	int getLainaPvEnnenErapaivaa();
	double getExtraStoringFee();
	double getExtraStoringFeePerKk();
	CDBLoan* m_pCDBLoanRef;
	virtual ~CDBLoanExpenses();

private:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDBLoanExpenses)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBLOANEXPENSES_H__9C18A374_9209_11D3_8A1B_0000E8C7E630__INCLUDED_)
