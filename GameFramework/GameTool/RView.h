#pragma once
#include <GameString.h>

// RView 폼 보기

class RView : public CFormView
{
	DECLARE_DYNCREATE(RView)

	static RView* ViewPtr;
	static int SelEntity;
	static GameString EntityName;

protected:
	RView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~RView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RView };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	/*Dlg0* dlg0;
	Dlg1* dlg1;
	Dlg2* dlg2;
	Dlg3* dlg3;*/
	template<typename T>
	void CreateNewDlg(unsigned int _Id)
	{
		T* NewDlg = new T();
		NewDlg->Create(_Id, &m_TabCtl);
		NewDlg->ShowWindow(SW_HIDE);
		NewDlg->SetBackgroundColor(RGB(153, 200, 240));
		//NewDlg->SetWindowPos(nullptr, 4, 20, 500, 500, 0);
		NewDlg->SetWindowPos(nullptr, 4, 20, 500, 600, 0);

		ArrDlg.push_back(NewDlg);
	}
	std::vector<CDialogEx*> ArrDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();

	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl m_TabCtl;
	CWnd* m_pWndShow;
};


