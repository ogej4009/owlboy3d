#include "GameWin.h"
#include <Windows.h>
#include <assert.h>
//#include "GameSound.h"
#include "GameMovie.h" //// �߰��߽��ϴ�. 


#pragma region �޸� ���� �̽�
/*
	�޸��� ��Ŀ����
	������ �ڵ����� �����.
	������ ������ ������ �ִ�. �޸��� �����ֱ�(lifecycle)�� ������ �ִ�.
*/
#pragma endregion

GameWin::GameWinStarter GameWin::Starter = GameWin::GameWinStarter();
bool GameWin::IsProcess = true;

//////////////////////////////////////////////////////////// �߰��߽��ϴ�. 
void CALLBACK OnGraphEvent(HWND hwnd, long evCode, LONG_PTR param1, LONG_PTR param2)
{
	switch (evCode)
	{
	case EC_COMPLETE:
	case EC_USERABORT:
	{
		wchar_t ArrName[256];
		GetWindowText(hwnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);
		Ptr->GetMoviePlayer()->MovieStop();
		break;
	}
	case EC_ERRORABORT:
		// NotifyError(hwnd, L"Playback error.");
	{
		MSG_ASSERT_CODE(L"���� ����� ������ �ֽ��ϴ�.");
		wchar_t ArrName[256];
		GetWindowText(hwnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);
		Ptr->GetMoviePlayer()->MovieStop();
		break;
	}
	}
}


LRESULT CALLBACK GameWin::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	/////////////////////////////////// �߰� ����? 

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
		EndPaint(hWnd, &ps);
	}
	/*{
		wchar_t ArrName[256];
		GetWindowText(hWnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);

		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);

		if (nullptr != Ptr)
		{
			if (Ptr->MoviePlayer->State() != STATE_NO_GRAPH && Ptr->MoviePlayer->HasVideo())
			{
				Ptr->MoviePlayer->Repaint(hdc);
			}
			else
			{
				FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			}
		}

		EndPaint(hWnd, &ps);
	}*/

	break;
	case WM_CREATE:   //////// �߰��߽��ϴ�. 
	{
		wchar_t ArrName[256] = L"";
		// mfc�� HWndProc�� ������ �ȵȴ�. 
		GetWindowText(hWnd, ArrName, 256);
		break;
	}
	case WM_SETCURSOR:
	{
		// Turn off window cursor 
		SetCursor(NULL);
		ShowCursor(FALSE);
		return TRUE; // prevent Windows from setting cursor to window class cursor
	}
	break;

	/*case WM_DISPLAYCHANGE:
	{
		wchar_t ArrName[256];
		GetWindowText(hWnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);
		Ptr->MoviePlayer->DisplayModeChanged();
		break;
	}
	case WM_GRAPH_EVENT:
	{
		wchar_t ArrName[256];
		GetWindowTextW(hWnd, ArrName, 256);
		CPtr<GameWin> Ptr = GameWin::Find(ArrName);
		Ptr->MoviePlayer->HandleGraphEvent(OnGraphEvent);
		return 0;
	}*/

	case WM_DESTROY:
		IsProcess = false;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameWin::RegDef()
{
	GameDebug::LeckCheck();

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &GameWin::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = nullptr;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"DEF";
	wcex.hIconSm = nullptr;

	RegisterClassExW(&wcex);
}

void GameWin::WINMESSAGE(INITFUNC _Init, DEADTIME _CallBack)
{
#pragma region �޼������� 
	/*
		�⺻ �޽��� ����.
		������ �� GetMessage ������� �ʴ´�.
		����(synchronization) �Լ��� �޼����� �� ������ �����.
	*/
#pragma endregion
	if (nullptr != _Init)
	{
		_Init();
	}

	MSG msg;

	while (true == IsProcess)
	{
#pragma region �ȸ޼����Լ� == �񵿱��Լ� 
		/*
			PeekMessage �޼��� �Լ��� '�񵿱� �Լ�' �Դϴ�.
			PeekMessage �񵿱� �Լ��� �ٷ� ���ϵǴ� ����Դϴ�. �� ������ �ʴ´�.
			<�ɼ� ����>
			�޼����� ���İ��� �ʹ� ���� ���ͼ� �޼����� ���� ��� ��� ó���Ǵ°�?
			PM_NOREMOVE : �� ����� �� ó���Ѵ�.
			PM_REMOVE : �и��� �� ����� �о������.
			�ֱ��� ��ǻ�ͼ����� ó���� �ȵǴ� ���� ����.
			�޼����� ��� �����Լ��̴�.
			�޼����� �ִ� ��� ->  ���ǹ��� 0�̻��� ��(��)�� ����.
			�޼����� ���� ��� ->  0�� ����.
		*/
#pragma endregion
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (nullptr != _CallBack)
			{
				//GameSound::Update();
				GameDebug::DebugFrameUpdate();
				_CallBack();
			}
		}
	}

#pragma region ����Ÿ��
	/*
		'�޼���'�� ���� �ð��� ����Ÿ���̶�� �Ѵ�.
		������ ��κ� ����Ÿ�ӿ��� ���ư���. ������ ���⼭ ����Ǹ� �ȴ�.
		'�޼���'�� ������ ���ÿ� ���ư��ϱ� �ʹ� �������� �ʾƵ� �ȴ�.
		������� '�޼���'�� ���� �ð��� �� ����.
		��ģ���� ������ '�޼���'�� ������ ������ ������ �� �ִ�.
	*/
#pragma endregion
}

void GameWin::Create(const GameString& _WindowName, const GameString& _ClassName)
{
	CPtr<GameWin> NewWindow = CreateAndInsert(_WindowName, _ClassName);
}

void GameWin::Create(const GameString& _WindowName, HWND _HWnd)
{
	CPtr<GameWin> NewWindow = CreateAndInsert(_WindowName, _HWnd);
}

GameWin::GameWin(const GameString& _Name)
{
	Style = WS_OVERLAPPEDWINDOW;
	m_HWND = CreateWindowW(L"DEF", _Name, Style, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		nullptr, nullptr, nullptr, nullptr);	// ������ �ڵ��� �־�� HDC�� ���ü� �ִ�.

	if (!m_HWND)
	{
		assert(false);
	}

	m_HDC = GetDC(m_HWND);// �����쿡 ���𰡸� �׸��� �ִ� ����

	ShowWindow(m_HWND, SW_SHOW);
	UpdateWindow(m_HWND);
}

GameWin::GameWin(HWND _HWnd)
{
	m_HWND = _HWnd;
	if (!m_HWND)
	{
		assert(false);
	}
	m_HDC = GetDC(m_HWND);
	UpdateWindow(m_HWND);
}

GameWin::~GameWin()
{
	///////////////////// �߰��߽��ϴ�. 
	delete MoviePlayer;

}

void GameWin::Size(const CVector& _Size)
{
#pragma region ������ ������ �˱�
	/*
		������BAR�� �ְ�, �߰��� �¿� ���̵忡�� BAR�� �ִ�.
		�װ��� �˰� ũ�⸦ ����ؾ� �Ѵ�.
		GetClientRect(m_HWND, ) : (����BAR�������߰���)�������� ũ�⸦ ��� �Լ�
	*/
#pragma endregion

	m_Size = _Size;
	RECT Rect = { 0, 0, _Size.IX(), _Size.IY() };

	AdjustWindowRect(&Rect, Style, FALSE);
	SetWindowPos(m_HWND, nullptr, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOMOVE | SWP_NOZORDER);
}

CVector GameWin::MousePos()
{
#pragma region ���콺��ǥ�������� 
	/*
		���콺�� ��ġ�� ����ϴ� ���信�� �߿��� ����
		�����츶�� �� ���� ��ǥ ��ġ���� �ٸ��ٴ� ���̴�.
		�ػ󵵿� ���� �ȼ��� �������� �ٸ��� �����̴�.
		GetCursorPos()�� ���� ����Ϳ����� ���콺 ��ġ�� �� �� �ִ�.
		ScreenToClient(m_HWND, ���� �����ϴ� ������ �������� ������ش�.
	*/
#pragma endregion

	POINT P;
	GetCursorPos(&P);
	ScreenToClient(m_HWND, &P);
	return { (float)P.x, (float)P.y };
}

CMatrix GameWin::ViewPort()
{
	CMatrix Mat;
	Mat.VIEWPORT(0.0f, 0.0f, Size().X, Size().Y, 0.0f, 1.0f);
	return Mat;
}

CVector GameWin::MousePosVec3D()
{
	CVector Pos = MousePos();
	Pos.X -= m_Size.HX();
	Pos.Y -= m_Size.HY();
	Pos.Y *= -1.0f;
	return Pos;
}

CVector GameWin::WindowPosTo3DPos(CVector _WindowPos)
{
	return CVector::WindowPosTo3dPos(_WindowPos, m_Size);
}

#pragma region ��ü����
/*
	SOLID ��ü������ �ټ����� ���� ���� <�������̽� �и���Ģ>
	�������Լ��� ����� �װ͵��� �����ؼ� ���ο� ����� ������.
*/
#pragma endregion