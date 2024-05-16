#pragma once
#include "afxdialogex.h"


// Dlg0 대화 상자

class Dlg0 : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg0)

public:
	Dlg0(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Dlg0();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG0 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CCheckListBox m_ChkList;

	afx_msg void OnLbnSelchangeBdViewLayerList();
	afx_msg void OnCbnSelchangeNewBdNameCombo();
	afx_msg void OnBnClickedBdUpdateBtn();
};
