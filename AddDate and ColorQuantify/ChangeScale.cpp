// ChangeScale.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AddDate and ColorQuantify.h"
#include "ChangeScale.h"
#include "afxdialogex.h"


// ChangeScale �Ի���

IMPLEMENT_DYNAMIC(ChangeScale, CDialogEx)

ChangeScale::ChangeScale(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChangeScale::IDD, pParent)
	, InputScale(0)
{

}

ChangeScale::~ChangeScale()
{
}

void ChangeScale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, InputScale);
}


BEGIN_MESSAGE_MAP(ChangeScale, CDialogEx)
END_MESSAGE_MAP()


// ChangeScale ��Ϣ�������
