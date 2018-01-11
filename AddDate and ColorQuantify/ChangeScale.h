#pragma once


// ChangeScale 对话框

class ChangeScale : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeScale)

public:
	ChangeScale(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChangeScale();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString InputString;
	float InputScale;
};
