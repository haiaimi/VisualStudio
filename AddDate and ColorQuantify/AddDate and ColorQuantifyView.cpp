
// AddDate and ColorQuantifyView.cpp : implementation of the CAddDateandColorQuantifyView class
//

#include "stdafx.h"
#include "DlgAddData.h"
#include "ChangeScale.h"
#include "TranslateDialog.h"
#include "RotateDialog.h"
#include "math.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AddDate and ColorQuantify.h"
#endif

#include "AddDate and ColorQuantifyDoc.h"
#include "AddDate and ColorQuantifyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAddDateandColorQuantifyView

IMPLEMENT_DYNCREATE(CAddDateandColorQuantifyView, CView)

BEGIN_MESSAGE_MAP(CAddDateandColorQuantifyView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CAddDateandColorQuantifyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CAddDateandColorQuantifyView::OnFileOpen)
	//ON_COMMAND(ID_PROCESS_ADDDATE, &CAddDateandColorQuantifyView::OnProcessAdddate)
	ON_COMMAND(ID_FILE_SAVE, &CAddDateandColorQuantifyView::OnFileSave)
	//ON_COMMAND(ID_PROCESS_COLORQUANTIFY, &CAddDateandColorQuantifyView::OnProcessColorquantify)
	ON_COMMAND(ID_PROCESS_TRANSLATE, &CAddDateandColorQuantifyView::OnProcessTranslate)
	ON_COMMAND(ID_PROCESS_HOR, &CAddDateandColorQuantifyView::OnProcessHorizMirror)
	ON_COMMAND(ID_PROCESS_VERTMIRROR, &CAddDateandColorQuantifyView::OnProcessVertmirror)
	ON_COMMAND(ID_PROCESS_MODIFYSCALE, &CAddDateandColorQuantifyView::OnProcessModifyscale)
	ON_COMMAND(ID_PROCESS_MODIFYSCALEDOUBLELERP, &CAddDateandColorQuantifyView::OnProcessModifyscale1)
	ON_COMMAND(ID_PROCESS_ROTATEWITHCLOSELERP, &CAddDateandColorQuantifyView::OnProcessRotate)
	ON_COMMAND(ID_PROCESS_ROTATEWITHDOUBLELERP, &CAddDateandColorQuantifyView::OnProcessRotate1)
	ON_COMMAND(ID_PROCESS_TRANSPOSE, &CAddDateandColorQuantifyView::OnProcessTranspose)
END_MESSAGE_MAP()

// CAddDateandColorQuantifyView construction/destruction

CAddDateandColorQuantifyView::CAddDateandColorQuantifyView()
{
	// TODO: add construction code here
	m_pImgSrc = NULL;
	m_pImgDst = NULL;
	ProcessID = Other;
	int i;
	//����һ����ɫ����ɫ�ı�������ʾ����ɫ֮��Ĺ�ϵ����(��ŵ�λ����ǰ��������Ϊ0,1,2��������7)��
	//0λ��1λ��ʾB������ǰ��λ��B����������λ��Ϊ0��
	//2λ��3λ��4λ��ʾG������ǰ��λ��G����������λ��Ϊ0��
	//5λ��6λ��7λ��ʾR������ǰ��λ��R����������λ��Ϊ0��
	for(i=0;i<256;i++)
	{
		m_Palette[i*4] = i & 0xc0;
		m_Palette[i*4+1] = (i & 0x38)<<2;
		m_Palette[i*4+2] = (i & 0x07)<<5;
		m_Palette[i*4+3] = 0;
	}
}

CAddDateandColorQuantifyView::~CAddDateandColorQuantifyView()
{
	if(!m_pImgSrc)//��ʾΪ������˿ռ�
		delete m_pImgSrc;//�ͷſռ�
	if(!m_pImgDst)//��ʾΪ������˿ռ�
		delete m_pImgDst;//�ͷſռ�
}

BOOL CAddDateandColorQuantifyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAddDateandColorQuantifyView drawing

void CAddDateandColorQuantifyView::OnDraw(CDC* pDC)
{
	CAddDateandColorQuantifyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(rect);
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);

	if(m_imgSrc.data)//���Դͼ������
	{
		// ��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
		m_bitmap.CreateCompatibleBitmap(pDC, m_imgSrc.cols,m_imgSrc.rows);
		//��Դͼ���λͼ���ݸ���CBitmap����
		m_bitmap.SetBitmapBits(m_imgSrc.cols*m_imgSrc.rows*4,m_pImgSrc);
		memDC.SelectObject(m_bitmap);
		//��CBitmap�����е�������ʾ����Ļ��
		pDC->BitBlt(0, 0, m_imgSrc.cols,m_imgSrc.rows, &memDC, 0, 0, SRCCOPY);
		m_bitmap.DeleteObject();
		
	}
	if(m_imgDst.data)
	{
		// ��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
		m_bitmap.CreateCompatibleBitmap(pDC, m_imgDst.cols,m_imgDst.rows);
		//��Ŀ��ͼ���λͼ���ݸ���CBitmap����
		m_bitmap.SetBitmapBits(m_imgDst.cols*m_imgDst.rows*4,m_pImgDst);
		memDC.SelectObject(m_bitmap);
		//��CBitmap�����е�������ʾ����Ļ��
		pDC->BitBlt(m_imgSrc.cols + 20, 0, m_imgDst.cols,m_imgDst.rows, &memDC, 0, 0, SRCCOPY);
		m_bitmap.DeleteObject();

	}
	memDC.DeleteDC();
}


// CAddDateandColorQuantifyView printing


void CAddDateandColorQuantifyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAddDateandColorQuantifyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAddDateandColorQuantifyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAddDateandColorQuantifyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CAddDateandColorQuantifyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAddDateandColorQuantifyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CAddDateandColorQuantifyView diagnostics

#ifdef _DEBUG
void CAddDateandColorQuantifyView::AssertValid() const
{
	CView::AssertValid();
}

void CAddDateandColorQuantifyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAddDateandColorQuantifyDoc* CAddDateandColorQuantifyView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAddDateandColorQuantifyDoc)));
	return (CAddDateandColorQuantifyDoc*)m_pDocument;
}
#endif //_DEBUG


// CAddDateandColorQuantifyView message handlers


void CAddDateandColorQuantifyView::OnFileOpen()
{
	// TODO: Add your command handler code here
	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL, 
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("JPG Files (*.jpg)|*.jpg|BMP Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"),
		NULL);
	//���ļ��Ի��򣬵õ��û�ѡ����ļ�·�����ļ���
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName(); //�ļ�����������FilePathName��
	}
	else
	{
		return;
	}
	string filePath = CT2A(FilePathName);
	m_imgSrc = imread(filePath,CV_LOAD_IMAGE_COLOR);//OpenCV����ͼ��
	//��ʼ��m_pImgSrc
	if(m_pImgSrc != NULL)
		delete m_pImgSrc;
	m_pImgSrc = new unsigned char[m_imgSrc.rows*m_imgSrc.cols*4];
	int i,j;
	//��m_imgSrc����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for(i=0;i<m_imgSrc.rows;i++)
	{
		for(j=0;j<m_imgSrc.cols;j++)
		{
			m_pImgSrc[i*m_imgSrc.cols*4 + j*4] = (m_imgSrc.data)[i*m_imgSrc.cols*3+j*3];
			m_pImgSrc[i*m_imgSrc.cols*4+j*4+1] = (m_imgSrc.data)[i*m_imgSrc.cols*3+j*3+1];
			m_pImgSrc[i*m_imgSrc.cols*4+j*4+2] = (m_imgSrc.data)[i*m_imgSrc.cols*3+j*3+2];
			m_pImgSrc[i*m_imgSrc.cols*4+j*4+3] = 0;
		}
	}
	//������ͼ�ػ���Ϣ��
	this->Invalidate(true);
}

void CAddDateandColorQuantifyView::OnFileSave()
{
	if (m_imgDst.data != NULL)
	{
		CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			(LPCTSTR)_TEXT("(*.jpg)|*.jpg|(*.bmp)|*.bmp|(*.png)|*.png||"),
			AfxGetMainWnd());    //�����ļ����Ϊ�Ի���
		CString FilePathName;
		if (dlg.DoModal() == IDOK)         //�ж��Ƿ���"����"��ť
		{
			FilePathName = dlg.GetPathName(); //����ļ�����·��
			switch (dlg.m_ofn.nFilterIndex)
			{
			case 1:
			{
					  if (FilePathName.Right(4) != _T(".jpg"))
						  FilePathName += _T(".jpg");
					  break;
			}
			case 2:
			{
					  if (FilePathName.Right(4) != _T(".bmp"))
						  FilePathName += _T(".bmp");
					  break;
			}
			case 3:
			{
					  if (FilePathName.Right(4) != _T(".png"))
						  FilePathName += _T(".png");
					  break;
			}
			}
		}
		else
		{
			return;
		}
		string filePath = CT2A(FilePathName);
		imwrite(filePath, m_imgDst);//����OpenCV��������ͼ��
	}

}

void CAddDateandColorQuantifyView::OnProcessTranslate()
{
	// TODO:  �ڴ���������������
	//��Ĭ��ƽ��x����50��y����50
	Invalidate(true);
	TranslateDialog TransDialog;
	TransDialog.DoModal();
	float TransX = TransDialog.TranslateX;
	float TransY = TransDialog.TranslateY;

	int delx = TransY;
	int dely = TransX;

	const int rows = m_imgSrc.rows;
	const int cols = m_imgSrc.cols;
	
	m_imgDst.create(rows, cols, m_imgSrc.type());

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int x = i - delx;
			int y = j - dely;
			if (x >= 0 && x < rows && y >= 0 && y < cols)
			{
				m_imgDst.data[i*cols * 3 + j * 3] = m_imgSrc.data[x*cols * 3 + y * 3];
				m_imgDst.data[i*cols * 3 + j * 3 + 1] = m_imgSrc.data[x*cols * 3 + y * 3 + 1];
				m_imgDst.data[i*cols * 3 + j * 3 + 2] = m_imgSrc.data[x*cols * 3 + y * 3 + 2];
			}
		}
	}

	//��ʼ��m_pImgDst
	if (m_pImgDst != NULL)
		delete m_pImgDst;

	m_pImgDst = new unsigned char[m_imgDst.rows*m_imgDst.cols * 4];
	//��m_imgDst����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 1] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 1];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 2] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 2];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 3] = 0;
		}
	}
	this->Invalidate(true);	//������ͼ�ػ���Ϣ��
}


void CAddDateandColorQuantifyView::OnProcessHorizMirror()
{
	// TODO:  �ڴ���������������
	int halfcols = m_imgSrc.cols / 2;
	int cols = m_imgSrc.cols;
	int rows = m_imgSrc.rows;

	m_imgSrc.copyTo(m_imgDst);

	for (int i = 0; i < rows; i++)
	{
		for (int j = halfcols; j < cols; j++)
		{
			m_imgDst.data[i*cols * 3 + j * 3] = m_imgSrc.data[i*cols * 3 + (cols - j) * 3];
			m_imgDst.data[i*cols * 3 + j * 3 + 1] = m_imgSrc.data[i*cols * 3 + (cols - j) * 3 + 1];
			m_imgDst.data[i*cols * 3 + j * 3 + 2] = m_imgSrc.data[i*cols * 3 + (cols - j) * 3 + 2];
		}
	}

	//��ʼ��m_pImgDst
	if (m_pImgDst != NULL)
		delete m_pImgDst;

	m_pImgDst = new unsigned char[m_imgDst.rows*m_imgDst.cols * 4];
	//��m_imgDst����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 1] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 1];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 2] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 2];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 3] = 0;
		}
	}
	this->Invalidate(true);	//������ͼ�ػ���Ϣ��

}


void CAddDateandColorQuantifyView::OnProcessVertmirror()
{
	// TODO:  �ڴ���������������
	int halfrows = m_imgSrc.rows / 2;
	int cols = m_imgSrc.cols;
	int rows = m_imgSrc.rows;

	m_imgSrc.copyTo(m_imgDst);

	for (int i = halfrows; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m_imgDst.data[i*cols * 3 + j * 3] = m_imgSrc.data[(rows - i)*cols * 3 + j * 3];
			m_imgDst.data[i*cols * 3 + j * 3 + 1] = m_imgSrc.data[(rows - i)*cols * 3 + j * 3 + 1];
			m_imgDst.data[i*cols * 3 + j * 3 + 2] = m_imgSrc.data[(rows - i)*cols * 3 + j * 3 + 2];
		}
	}

	//��ʼ��m_pImgDst
	if (m_pImgDst != NULL)
		delete m_pImgDst;

	m_pImgDst = new unsigned char[m_imgDst.rows*m_imgDst.cols * 4];
	//��m_imgDst����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 1] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 1];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 2] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 2];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 3] = 0;
		}
	}
	this->Invalidate(true);	//������ͼ�ػ���Ϣ��
}

//�����ֵ
void CAddDateandColorQuantifyView::OnProcessModifyscale()
{
	// TODO:  �ڴ���������������

	ChangeScale ScaleDialog;
	ScaleDialog.DoModal();
	float scale = ScaleDialog.InputScale;
	//��Ĭ�������������Ϊ2

	float xscale = scale;
	float yscale = scale;
	float xchange = 1 / xscale;
	float ychange = 1 / yscale;

	int DstRows = m_imgSrc.rows / xchange;
	int DstCols = m_imgSrc.cols / ychange;

	m_imgDst.create(DstRows, DstCols, m_imgSrc.type());

	for (int i = 0; i < DstRows; i++)
	{
		for (int j = 0; j < DstCols; j++)
		{
			int SrcRows = i / xscale + ychange / 2;
			int SrcCols = j / yscale + xchange / 2;

			//int SrcRows = i / xscale;
			//int SrcCols = j / yscale;
			
			if (SrcRows >= m_imgSrc.rows)
				SrcRows = m_imgSrc.rows;

			if (SrcCols >= m_imgSrc.cols)
				SrcCols = m_imgSrc.cols;

			m_imgDst.data[i*DstCols * 3 + j * 3] = m_imgSrc.data[SrcRows*m_imgSrc.cols * 3 + SrcCols * 3];
			m_imgDst.data[i*DstCols * 3 + j * 3 + 1] = m_imgSrc.data[SrcRows*m_imgSrc.cols * 3 + SrcCols * 3 + 1];
			m_imgDst.data[i*DstCols * 3 + j * 3 + 2] = m_imgSrc.data[SrcRows*m_imgSrc.cols * 3 + SrcCols * 3 + 2];
		}
	}


	//��ʼ��m_pImgDst
	if (m_pImgDst != NULL)
		delete m_pImgDst;

	m_pImgDst = new unsigned char[m_imgDst.rows*m_imgDst.cols * 4];
	//��m_imgDst����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (int i = 0; i < m_imgDst.rows; i++)
	{
		for (int j = 0; j < m_imgDst.cols; j++)
		{
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 1] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 1];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 2] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 2];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 3] = 0;
		}
	}
	this->Invalidate(true);	//������ͼ�ػ���Ϣ��

}

//˫��ֵ�㷨
void CAddDateandColorQuantifyView::OnProcessModifyscale1()
{
	// TODO:  �ڴ���������������
	//��Ĭ�������������Ϊ0.5


	ChangeScale ScaleDialog;
	ScaleDialog.DoModal();
	float scale = ScaleDialog.InputScale;

	float xscale = scale;
	float yscale = scale;
	float xchange = 1 / xscale;
	float ychange = 1 / yscale;

	int DstRows = m_imgSrc.rows / xchange;
	int DstCols = m_imgSrc.cols / ychange;

	m_imgDst.create(DstRows, DstCols, m_imgSrc.type());

	for (int i = 0; i < DstRows; i++)
	{
		for (int j = 0; j < DstCols; j++)
		{
			float SrcRows = i/xscale;
			float SrcCols = j/yscale;

			m_imgDst.data[i*DstCols * 3 + j * 3] = ComputeDulLinearLerp(SrcRows, SrcCols, 0);
			m_imgDst.data[i*DstCols * 3 + j * 3 + 1] = ComputeDulLinearLerp(SrcRows, SrcCols, 1);
			m_imgDst.data[i*DstCols * 3 + j * 3 + 2] = ComputeDulLinearLerp(SrcRows, SrcCols, 2);
		}
	}


	//��ʼ��m_pImgDst
	if (m_pImgDst != NULL)
		delete m_pImgDst;

	m_pImgDst = new unsigned char[m_imgDst.rows*m_imgDst.cols * 4];
	//��m_imgDst����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (int i = 0; i < m_imgDst.rows; i++)
	{
		for (int j = 0; j < m_imgDst.cols; j++)
		{
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 1] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 1];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 2] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 2];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 3] = 0;
		}
	}
	this->Invalidate(true);	//������ͼ�ػ���Ϣ��

}

//����˫���Բ�ֵ
uchar CAddDateandColorQuantifyView::ComputeDulLinearLerp(float virRows, float virCols,int index)
{
	uchar a = 0, b = 0, c = 0, d = 0;      //���Բ�ֵ���ĸ���
	int relRows = static_cast<int>(virRows);
	int relCols = static_cast<int>(virCols);

	int SrcCols = m_imgSrc.cols;
	int SrcRows = m_imgSrc.rows;

	float u = virRows - relRows;
	float v = virCols - relCols;

	if (relRows <= SrcRows && relCols <= SrcCols)
	{
		a = (1 - u)*(1 - v)*m_imgSrc.data[relRows*SrcCols * 3 + relCols * 3 + index];
	}

	if (relRows <= SrcRows && relCols + 1 <= SrcCols)
	{
		b = (1 - u)*v*m_imgSrc.data[relRows*SrcCols * 3 + (relCols + 1) * 3 + index];
	}

	if (relRows+1 <= SrcRows && relCols <= SrcCols)
	{
		c = u*(1 - v)*m_imgSrc.data[(relRows + 1)*SrcCols * 3 + relCols * 3 + index];
	}

	if (relRows+1 <= SrcRows && relCols+1 <= SrcCols)
	{
		d = u*v*m_imgSrc.data[(relRows + 1)*SrcCols * 3 + (relCols + 1) * 3 + index];
	}

	return a + b + c + d;
}
//�����ֵ
void CAddDateandColorQuantifyView::OnProcessRotate()
{
	// TODO:  �ڴ���������������

	RotateDialog RotDialog;
	RotDialog.DoModal();

	float RotateAngle = -RotDialog.RotateAngle;
	float angle = RotateAngle*CV_PI / 180.f;

	int SrcCols = m_imgSrc.cols;
	int SrcRows = m_imgSrc.rows;

	int DiagLine = sqrt(SrcCols*SrcCols + SrcRows*SrcRows);    //�Խ��߳���
	float DiagAngle = acosf((float)SrcCols / DiagLine);

	int AdjustRows = abs(DiagLine*sin(angle + DiagAngle));
	int AdjustCols = abs(DiagLine*cos(angle - DiagAngle));

	m_imgDst.create(DiagLine, DiagLine, m_imgSrc.type());

	for (int i = 0; i < DiagLine; i++)
	{
		for (int j = 0; j < DiagLine; j++)
		{
			//����ת�������,�õ���Ӧԭͼ�������
			int dstx = static_cast<int>((i - DiagLine / 2)*sin(-angle) + ((j - DiagLine / 2)*cos(-angle))) + SrcCols / 2;
			int dsty = static_cast<int>((i - DiagLine / 2)*cos(-angle) + (j - DiagLine / 2)*sin(angle)) + SrcRows / 2;
			
			if (dstx < SrcCols&&dstx >= 0 && dsty < SrcRows && dsty >= 0)
			{
				//m_imgDst.data[dsty*SrcCols * 3 + dstx * 3] = m_imgSrc.data[i*SrcCols * 3 + j * 3];
				//m_imgDst.data[dsty*SrcCols * 3 + dstx * 3 + 1] = m_imgSrc.data[i*SrcCols * 3 + j * 3 + 1];
				//m_imgDst.data[dsty*SrcCols * 3 + dstx * 3 + 2] = m_imgSrc.data[i*SrcCols * 3 + j * 3 + 2];

				m_imgDst.data[i*DiagLine * 3 + j * 3] = m_imgSrc.data[dsty*SrcCols * 3 + dstx * 3];
				m_imgDst.data[i*DiagLine * 3 + j * 3 + 1] = m_imgSrc.data[dsty*SrcCols * 3 + dstx * 3 + 1];
				m_imgDst.data[i*DiagLine * 3 + j * 3 + 2] = m_imgSrc.data[dsty*SrcCols * 3 + dstx * 3 + 2];
			}
		}
	}

	//��ʼ��m_pImgDst
	if (m_pImgDst != NULL)
		delete m_pImgDst;

	m_pImgDst = new unsigned char[m_imgDst.rows*m_imgDst.cols * 4];
	//��m_imgDst����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (int i = 0; i < m_imgDst.rows; i++)
	{
		for (int j = 0; j < m_imgDst.cols; j++)
		{
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 1] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 1];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 2] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 2];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 3] = 0;
		}
	}
	this->Invalidate(true);	//������ͼ�ػ���Ϣ��

}

//˫���Բ�ֵ
void CAddDateandColorQuantifyView::OnProcessRotate1()
{
	// TODO:  �ڴ���������������

	RotateDialog RotDialog;
	RotDialog.DoModal();

	float RotateAngle = -RotDialog.RotateAngle;
	float angle = RotateAngle*CV_PI / 180.f;

	int SrcCols = m_imgSrc.cols;
	int SrcRows = m_imgSrc.rows;

	int DiagLine = sqrt(SrcCols*SrcCols + SrcRows*SrcRows);    //�Խ��߳���
	float SrcColsf = static_cast<float>(SrcCols);
	float cos1 = SrcColsf / DiagLine;
	float DiagAngle = acosf(cos1);

	int AdjustRows = abs(DiagLine*sin(angle + angle));
	int AdjustCols = abs(DiagLine*cos(angle - angle));
	
	m_imgDst.create(DiagLine, DiagLine, m_imgSrc.type());
	for (int i = 0; i < DiagLine; i++)
	{
		for (int j = 0; j < DiagLine; j++)
		{
			//����ת�������,�õ���Ӧԭͼ�������
			float dstx = (i - DiagLine / 2)*sin(-angle) + (j - DiagLine / 2)*cos(-angle) + SrcCols / 2;
			float dsty = (i - DiagLine / 2)*cos(-angle) + (j - DiagLine / 2)*sin(angle) + SrcRows / 2;

			if (dstx < SrcCols&&dstx >= 0 && dsty < SrcRows && dsty >= 0)
			{
				//m_imgDst.data[dsty*SrcCols * 3 + dstx * 3] = m_imgSrc.data[i*SrcCols * 3 + j * 3];
				//m_imgDst.data[dsty*SrcCols * 3 + dstx * 3 + 1] = m_imgSrc.data[i*SrcCols * 3 + j * 3 + 1];
				//m_imgDst.data[dsty*SrcCols * 3 + dstx * 3 + 2] = m_imgSrc.data[i*SrcCols * 3 + j * 3 + 2];

				m_imgDst.data[i*DiagLine * 3 + j * 3] = ComputeDulLinearLerp(dsty, dstx, 0);
				m_imgDst.data[i*DiagLine * 3 + j * 3 + 1] = ComputeDulLinearLerp(dsty, dstx, 1);
				m_imgDst.data[i*DiagLine * 3 + j * 3 + 2] = ComputeDulLinearLerp(dsty, dstx, 2);
			}
		}
	}

	//��ʼ��m_pImgDst
	if (m_pImgDst != NULL)
		delete m_pImgDst;

	m_pImgDst = new unsigned char[m_imgDst.rows*m_imgDst.cols * 4];
	//��m_imgDst����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (int i = 0; i < m_imgDst.rows; i++)
	{
		for (int j = 0; j < m_imgDst.cols; j++)
		{
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 1] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 1];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 2] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 2];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 3] = 0;
		}
	}
	this->Invalidate(true);	//������ͼ�ػ���Ϣ��
}

//ͼ��ת��
void CAddDateandColorQuantifyView::OnProcessTranspose()
{
	// TODO:  �ڴ���������������
	int SrcRows = m_imgSrc.rows;
	int SrcCols = m_imgSrc.cols;

	int DstRows = SrcCols;
	int DstCols = SrcRows;
	m_imgDst.create(DstRows, DstCols, m_imgSrc.type());
	for (int i = 0; i < DstRows; i++)
	{
		for (int j = 0; j < DstCols; j++)
		{
			m_imgDst.data[i*DstCols * 3 + j * 3] = m_imgSrc.data[j*SrcCols * 3 + i * 3];
			m_imgDst.data[i*DstCols * 3 + j * 3 + 1] = m_imgSrc.data[j*SrcCols * 3 + i * 3 + 1];
			m_imgDst.data[i*DstCols * 3 + j * 3 + 2] = m_imgSrc.data[j*SrcCols * 3 + i * 3 + 2];
		}
	}

	//��ʼ��m_pImgDst
	if (m_pImgDst != NULL)
		delete m_pImgDst;

	m_pImgDst = new unsigned char[m_imgDst.rows*m_imgDst.cols * 4];
	//��m_imgDst����ȡλͼ���ݣ���ʽBGRA,һ������4�ֽ�
	for (int i = 0; i < m_imgDst.rows; i++)
	{
		for (int j = 0; j < m_imgDst.cols; j++)
		{
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 1] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 1];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 2] = (m_imgDst.data)[i*m_imgDst.cols * 3 + j * 3 + 2];
			m_pImgDst[i*m_imgDst.cols * 4 + j * 4 + 3] = 0;
		}
	}
	this->Invalidate(true);	//������ͼ�ػ���Ϣ��
}
