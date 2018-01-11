
// AddDate and ColorQuantifyDoc.cpp : implementation of the CAddDateandColorQuantifyDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AddDate and ColorQuantify.h"
#endif

#include "AddDate and ColorQuantifyDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAddDateandColorQuantifyDoc

IMPLEMENT_DYNCREATE(CAddDateandColorQuantifyDoc, CDocument)

BEGIN_MESSAGE_MAP(CAddDateandColorQuantifyDoc, CDocument)
END_MESSAGE_MAP()


// CAddDateandColorQuantifyDoc construction/destruction

CAddDateandColorQuantifyDoc::CAddDateandColorQuantifyDoc()
{
	// TODO: add one-time construction code here

}

CAddDateandColorQuantifyDoc::~CAddDateandColorQuantifyDoc()
{
}

BOOL CAddDateandColorQuantifyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CAddDateandColorQuantifyDoc serialization

void CAddDateandColorQuantifyDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CAddDateandColorQuantifyDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CAddDateandColorQuantifyDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CAddDateandColorQuantifyDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CAddDateandColorQuantifyDoc diagnostics

#ifdef _DEBUG
void CAddDateandColorQuantifyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAddDateandColorQuantifyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAddDateandColorQuantifyDoc commands
