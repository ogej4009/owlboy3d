
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "GameTool.h"

#include "MainFrm.h"
#include "LView.h"
#include "RView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CTLCOLOR()
	ON_COMMAND(IDR_TOOLBAR, &CMainFrame::OnIdrToolbar)
	ON_UPDATE_COMMAND_UI(IDR_TOOLBAR, &CMainFrame::OnUpdateIdrToolbar)
	ON_COMMAND(ID_BUTTON_DRAW, &CMainFrame::OnButtonDraw)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DRAW, &CMainFrame::OnUpdateButtonDraw)
	ON_COMMAND(ID_BUTTON_PICKOBJ, &CMainFrame::OnButtonPickobj)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PICKOBJ, &CMainFrame::OnUpdateButtonPickobj)
	ON_COMMAND(ID_BUTTON_PAINT_COL, &CMainFrame::OnButtonPaintCol)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PAINT_COL, &CMainFrame::OnUpdateButtonPaintCol)
	ON_COMMAND(ID_BUTTON_BRING_FORWARD, &CMainFrame::OnButtonBringForward)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_BRING_FORWARD, &CMainFrame::OnUpdateButtonBringForward)
	ON_COMMAND(ID_BUTTON_BRING_BACK, &CMainFrame::OnButtonBringBack)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_BRING_BACK, &CMainFrame::OnUpdateButtonBringBack)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 프레임의 클라이언트 영역을 차지하는 뷰를 만듭니다.
	/*if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("뷰 창을 만들지 못했습니다.\n");
		return -1;
	}*/

	RECT NewRect = { 0, 0, 1280 + 517 + 50, 720 + 24 };
	AdjustWindowRect(&NewRect, GetStyle(), FALSE);
	SetWindowPos(nullptr, 0, 0, NewRect.right - NewRect.left, NewRect.bottom - NewRect.top, SWP_NOMOVE | SWP_NOZORDER);

	m_SWnd.CreateStatic(this, 1, 2);
	m_SWnd.CreateView(0, 0, RUNTIME_CLASS(LView), SIZE{ 1280, 720 }, nullptr);
	m_SWnd.CreateView(0, 1, RUNTIME_CLASS(RView), SIZE{ 200, 720 }, nullptr);

	/////////////////////////////////////////////////////////////// 

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar/*, AFX_IDW_DOCKBAR_TOP, CRect(0, 0, 0, 0)*/);



	



	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	/*cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		;*/

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 뷰 창으로 포커스를 이동합니다.
	// m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 뷰에서 첫째 크랙이 해당 명령에 나타나도록 합니다.
	/*if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;*/

	// 그렇지 않으면 기본 처리합니다.
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



HBRUSH CMainFrame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFrameWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG)
	{
		pDC->SetBkColor(RGB(255, 0, 0));
	}
	hbr = CreateSolidBrush(RGB(255, 0, 0));
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CMainFrame::OnUpdateFrameMenu(HMENU hMenuAlt)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CFrameWnd::OnUpdateFrameMenu(hMenuAlt);
}


void CMainFrame::OnIdrToolbar()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnUpdateIdrToolbar(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnButtonDraw()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnUpdateButtonDraw(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnButtonPickobj()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnUpdateButtonPickobj(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnButtonPaintCol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnUpdateButtonPaintCol(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnButtonBringForward()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnUpdateButtonBringForward(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OnButtonBringBack()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMainFrame::OnUpdateButtonBringBack(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(TRUE);
}
