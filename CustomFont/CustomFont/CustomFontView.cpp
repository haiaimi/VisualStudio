
// CustomFontView.cpp: CCustomFontView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CustomFont.h"
#endif

#include "CustomFontDoc.h"
#include "CustomFontView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCustomFontView

IMPLEMENT_DYNCREATE(CCustomFontView, CView)

BEGIN_MESSAGE_MAP(CCustomFontView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCustomFontView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CCustomFontView::OnRotateFont)
	ON_COMMAND(ID_32772, &CCustomFontView::OnMultiFontType)
	ON_COMMAND(ID_32773, &CCustomFontView::OnHollowFont)
END_MESSAGE_MAP()

// CCustomFontView 构造/析构
CCustomFontView::CCustomFontView()
{
	// TODO: 在此处添加构造代码

}

CCustomFontView::~CCustomFontView()
{
}

BOOL CCustomFontView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCustomFontView 绘图

void CCustomFontView::OnDraw(CDC* /*pDC*/)
{
	CCustomFontDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCustomFontView 打印


void CCustomFontView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCustomFontView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCustomFontView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCustomFontView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CCustomFontView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCustomFontView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCustomFontView 诊断

#ifdef _DEBUG
void CCustomFontView::AssertValid() const
{
	CView::AssertValid();
}

void CCustomFontView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCustomFontDoc* CCustomFontView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomFontDoc)));
	return (CCustomFontDoc*)m_pDocument;
}
#endif //_DEBUG


// CCustomFontView 消息处理程序


void CCustomFontView::OnRotateFont()
{
	// TODO: 在此添加命令处理程序代码
	CDC* pDC = GetDC();
	CFont m_font;
	pDC->SetBkMode(TRANSPARENT);
	CRect m_rect;
	GetClientRect(m_rect);
	pDC->FillRect(m_rect, NULL);
	pDC->SetViewportOrg(m_rect.Width() / 2, m_rect.Height() / 2);
	for (int i = 0; i < 360; i += 18)
	{
		m_font.CreateFont(-20, -20, i * 10, 0, 600, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_ROMAN, L"楷体");
		pDC->SelectObject(m_font);
		pDC->SetTextColor(RGB(255 - i, i * 255, i + 50));
		pDC->TextOut(0, 0, L"海哥大帅比");
		m_font.DeleteObject();
	}
}


void CCustomFontView::OnMultiFontType()
{
	// TODO: 在此添加命令处理程序代码

	CFontDialog fd;
	CDC* pDC = GetDC();
	CFont m_font;
	pDC->SetBkMode(TRANSPARENT);
	CRect m_rect;
	GetClientRect(m_rect);
	pDC->FillRect(m_rect, NULL);
	pDC->SetViewportOrg(m_rect.Width() / 2, m_rect.Height() / 2);

	if (fd.DoModal() == IDOK)
	{
		if (m_font.m_hObject)
			m_font.DeleteObject();

		m_font.CreateFontIndirectW(fd.m_cf.lpLogFont);
		pDC->SelectObject(m_font);
		pDC->SetTextColor(RGB(15, 15, 255));
		pDC->TextOutW(0, 0, L"海哥大帅比");
		m_font.DeleteObject();
	}
}


void CCustomFontView::OnHollowFont()
{
	// TODO: 在此添加命令处理程序代码

	CDC* pDC = GetDC();
	CRect m_rect;
	GetClientRect(m_rect);
	pDC->FillRect(m_rect, NULL);
	pDC->SetViewportOrg(m_rect.Width() / 2, m_rect.Height() / 2);

	CFont font;
	CFont *pOldFont;
	font.CreateFont(
		-50,                     
		-20,                         
		0,                         
		0,                         
		FW_BOLD,               
		FALSE,                     
		FALSE,                    
		0,                         
		DEFAULT_CHARSET,              
		OUT_DEFAULT_PRECIS,        
		CLIP_DEFAULT_PRECIS,      
		DEFAULT_QUALITY,           
		DEFAULT_PITCH | FF_SWISS,  
		_T("楷体"));                 

	pOldFont = pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);    //

	CPen pen(PS_SOLID, 1, RGB(0, 128, 255));
	pDC->SelectObject(&pen);
	pDC->BeginPath();
	pDC->TextOut(m_rect.top - 10, m_rect.left + 12, L"海哥大帅比");

	pDC->EndPath();
	int num = pDC->GetPath(NULL, NULL, 0);
	CPoint *pt = new CPoint[num];
	BYTE *type = new BYTE[num];
	num = pDC->GetPath(pt, type, num);
	CPoint pstart;
	for (int j = 0; j < num; j++)
	{
		switch (type[j])
		{
		case PT_MOVETO:
			pDC->MoveTo(pt[j]);
			pstart = pt[j];
			break;
		case PT_LINETO:
			pDC->LineTo(pt[j]);
			break;
		case PT_BEZIERTO:
			pDC->PolyBezierTo(pt + j, 3);      //绘制贝塞尔曲线
			j += 2;
			break;
		case PT_BEZIERTO | PT_CLOSEFIGURE:
			pt[j + 2] = pstart;
			pDC->PolyBezierTo(pt + j, 3);
			j += 2;
			break;
		case PT_LINETO | PT_CLOSEFIGURE:
			pDC->LineTo(pstart);
			break;
		}
		pDC->CloseFigure();
	}

	//清空
	font.DeleteObject();
	pen.DeleteObject();

	delete[] pt;
	delete[] type;
}
