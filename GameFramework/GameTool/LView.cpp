// LView.cpp: 구현 파일
//

#include "pch.h"
#include "GameTool.h"
#include "LView.h"

#include <GameWin.h>
#include <GameDevice.h>
#include <GameUnity.h>

#pragma comment(lib, "GameBase.lib")
#pragma comment(lib, "GameEngine.lib")
#pragma comment(lib, "GameLogic.lib")
// LView

IMPLEMENT_DYNCREATE(LView, CFormView)

LView::LView()
	: CFormView(IDD_LView)
{

}

LView::~LView()
{
}

void LView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(LView, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// LView 진단

#ifdef _DEBUG
void LView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void LView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// LView 메시지 처리기


int LView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	new int();
	GameWin::Create(L"ToolWnd", m_hWnd);
	GameWin::MainObj()->Size({ 1280.0f, 720.0f });
	GameDevice::Create(L"ToolWnd");

	return 0;
}
