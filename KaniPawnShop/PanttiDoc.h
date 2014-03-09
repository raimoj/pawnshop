// PanttiDoc.h : interface of the CPanttiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANTTIDOC_H__BAF87A8D_D921_11D2_89C2_0000E8C7E630__INCLUDED_)
#define AFX_PANTTIDOC_H__BAF87A8D_D921_11D2_89C2_0000E8C7E630__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPanttiDoc : public CDocument
{
protected: // create from serialization only
	CPanttiDoc();
	DECLARE_DYNCREATE(CPanttiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanttiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CPanttiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPanttiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANTTIDOC_H__BAF87A8D_D921_11D2_89C2_0000E8C7E630__INCLUDED_)
