#pragma once


// ChangeScale �Ի���

class ChangeScale : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeScale)

public:
	ChangeScale(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChangeScale();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString InputString;
	float InputScale;
};
