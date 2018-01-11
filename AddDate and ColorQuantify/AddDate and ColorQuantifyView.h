
// AddDate and ColorQuantifyView.h : interface of the CAddDateandColorQuantifyView class
//

#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "string.h"

using namespace cv;
using namespace std;

class CAddDateandColorQuantifyView : public CView
{
protected: // create from serialization only
	CAddDateandColorQuantifyView();
	DECLARE_DYNCREATE(CAddDateandColorQuantifyView)

private:
	Mat m_imgSrc;//Դͼ�����OpenCV��Mat����
	Mat m_imgDst;//Ŀ��ͼ�����OpenCV��Mat����
	unsigned char *m_pImgSrc;//��m_imgSrc����ȡͼ��λͼ���ݲ���֯��BGRA��ʽ��һ������4���ֽ�
	unsigned char *m_pImgDst;//��m_imgDst����ȡͼ��λͼ���ݲ���֯��BGRA��ʽ��һ������4���ֽ�
	CBitmap m_bitmap;//MFC��λͼ�࣬���ڽ�ͼ����ʾ����Ļ��
	unsigned char m_Palette[1024];//256ɫλͼ�ĵ�ɫ�����ݣ�ÿ����ɫ��4�ֽڣ��ֱ��ʾBRGAͨ��
	enum {AddData,ColorQuantify,Translate,Other} ProcessID;//��ǰ������ʶ

// Attributes
public:
	CAddDateandColorQuantifyDoc* GetDocument() const;

// Operations
public:
	uchar ComputeDulLinearLerp(float virRows, float virCols, int index);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CAddDateandColorQuantifyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnProcessTranslate();
	afx_msg void OnProcessHorizMirror();
	afx_msg void OnProcessVertmirror();
	afx_msg void OnProcessModifyscale();
	afx_msg void OnProcessModifyscale1();
	afx_msg void OnProcessRotate();
	afx_msg void OnProcessRotate1();
	afx_msg void OnProcessTranspose();
};

#ifndef _DEBUG  // debug version in AddDate and ColorQuantifyView.cpp
inline CAddDateandColorQuantifyDoc* CAddDateandColorQuantifyView::GetDocument() const
   { return reinterpret_cast<CAddDateandColorQuantifyDoc*>(m_pDocument); }
#endif

