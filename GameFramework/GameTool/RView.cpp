// RView.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "RView.h"
// --------------------- ENG
#include <GameScene.h>
// --------------------- LOG
// --------------------- TOOL
#include "LevelDesignView.h"


// RView
#include "Dlg0.h"
#include "Dlg1.h"
#include "Dlg2.h"
#include "Dlg3.h"
#include "Dlg4.h"

int RView::SelEntity = -1;
GameString RView::EntityName;

#define TAB_NUMBER_MIN 0
int TabCount = TAB_NUMBER_MIN;
#define TAB_NUMBER_MAX TabCount
#define TAB_NUMBER_PLUS_PLUS TabCount++

#define SAFE_DELETE(p) {if(p){delete p; p = NULL;}}

IMPLEMENT_DYNCREATE(RView, CFormView)

RView::RView()
	: CFormView(IDD_RView)
{
	/*dlg0 = NULL;
	dlg1 = NULL;
	dlg2 = NULL;
	dlg3 = NULL;*/
	m_pWndShow = nullptr;
}

RView::~RView()
{
	/*SAFE_DELETE(dlg0);
	SAFE_DELETE(dlg1);
	SAFE_DELETE(dlg2);
	SAFE_DELETE(dlg3);*/
	for (size_t i = 0; i < ArrDlg.size(); i++)
	{
		delete ArrDlg[i];
	}
}

void RView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtl);
}

BEGIN_MESSAGE_MAP(RView, CFormView)
	ON_WM_CREATE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &RView::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// RView 진단

#ifdef _DEBUG
void RView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void RView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// RView 메시지 처리기


int RView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	/* 
		0.Backdrops		1.Sprites		2.Layers		3.Collisions		4.Properties
	*/

	GameScene::Create<LevelDesignView>(L"MAP");
	GameScene::ChangeScene(L"MAP");

	return 0;
}


void RView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_TabCtl.DeleteAllItems();

	/* 
		CRect rect;
		dlg0 = new Dlg0;
		dlg0->Create(IDD_DLG0, &m_TabCtl);
		dlg0->GetWindowRect(&rect);
		dlg0->MoveWindow(10, 30, rect.Width(), rect.Height());
	*/
	CreateNewDlg<Dlg0>(IDD_DLG0);
	CreateNewDlg<Dlg1>(IDD_DLG1);
	CreateNewDlg<Dlg2>(IDD_DLG2);
	CreateNewDlg<Dlg3>(IDD_DLG3);
	CreateNewDlg<Dlg4>(IDD_DLG4);

	m_TabCtl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Backdrops");
	m_TabCtl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Sprites");
	m_TabCtl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Layers");
	m_TabCtl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Collisions");
	m_TabCtl.InsertItem(TAB_NUMBER_PLUS_PLUS, L"Properties");

}



void RView::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_pWndShow != NULL)
	{
		m_pWndShow->ShowWindow(SW_HIDE);
		m_pWndShow = NULL;
	}

	UpdateData(TRUE);

	int SIdx = m_TabCtl.GetCurSel();

	WCHAR ArrText[256];
	TCITEMW Item;
	Item.mask = TCIF_TEXT;
	Item.cchTextMax = 256;
	Item.pszText = ArrText;
	m_TabCtl.GetItem(SIdx, &Item);

	if (TAB_NUMBER_MIN > SIdx || TAB_NUMBER_MAX < SIdx)
	{
		return;
	}

	for (size_t i = 0; i < ArrDlg.size(); i++)
	{
		ArrDlg[i]->ShowWindow(SW_HIDE);
	}

	ArrDlg[SIdx]->ShowWindow(SW_SHOW);

	//GameScene::ChangeScene(ArrText);

	UpdateData(FALSE);

	*pResult = 0;
}
