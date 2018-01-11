#pragma once


// RotateDialog 对话框

class RotateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(RotateDialog)

public:
	RotateDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RotateDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float RotateAngle;
};
