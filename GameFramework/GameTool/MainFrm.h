
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame() noexcept;
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CChildView		m_wndView;
	CSplitterWnd	m_SWnd;

protected:
	CToolBar m_wndToolBar;


// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnUpdateFrameMenu(HMENU hMenuAlt);

	afx_msg void OnIdrToolbar();
	afx_msg void OnUpdateIdrToolbar(CCmdUI* pCmdUI);
	afx_msg void OnButtonDraw();
	afx_msg void OnUpdateButtonDraw(CCmdUI* pCmdUI);
	afx_msg void OnButtonPickobj();
	afx_msg void OnUpdateButtonPickobj(CCmdUI* pCmdUI);
	afx_msg void OnButtonPaintCol();
	afx_msg void OnUpdateButtonPaintCol(CCmdUI* pCmdUI);
	afx_msg void OnButtonBringForward();
	afx_msg void OnUpdateButtonBringForward(CCmdUI* pCmdUI);
	afx_msg void OnButtonBringBack();
	afx_msg void OnUpdateButtonBringBack(CCmdUI* pCmdUI);
};


