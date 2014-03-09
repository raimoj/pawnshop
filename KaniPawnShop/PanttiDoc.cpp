// PanttiDoc.cpp : implementation of the CPanttiDoc class
//

#include "stdafx.h"
#include "Pantti.h"

#include "PanttiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPanttiDoc

IMPLEMENT_DYNCREATE(CPanttiDoc, CDocument)

BEGIN_MESSAGE_MAP(CPanttiDoc, CDocument)
	//{{AFX_MSG_MAP(CPanttiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanttiDoc construction/destruction

CPanttiDoc::CPanttiDoc()
{
}

CPanttiDoc::~CPanttiDoc()
{
}

BOOL CPanttiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPanttiDoc serialization

void CPanttiDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPanttiDoc diagnostics

#ifdef _DEBUG
void CPanttiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPanttiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPanttiDoc commands




