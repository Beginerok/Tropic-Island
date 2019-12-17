#include "Window.h"

PMSG Window::msg_;
GLboolean Window::fullscreen;
LPARAM Window::lparam_;
WPARAM Window::wparam_;
HGLRC Window::hrc;
HDC Window::hdc;
HWND Window::hwnd;
HINSTANCE Window::hinstance;
int Window::x, Window::y;
HWND Window::edit1, Window::edit2;

TCHAR Window::pszTextBuff[500];
TCHAR Window::Buff1[500];
Window::Window()
{
	msg_ = new MSG();
}
GLvoid Window::KillWindow()
{
	if (fullscreen)
	{
		ChangeDisplaySettings(0, 0);
		ShowCursor(true);
	}
	if (hrc)
	{
		if (!wglMakeCurrent(0, 0))
		{
			MessageBox(0, L"Release failed 1", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hrc))
		{
			MessageBox(0, L"Release failed 2", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
	}
	if (hdc && !ReleaseDC(hwnd, hdc))
	{
		MessageBox(0, L"Release failed 3", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}
	if (!UnregisterClass(L"My Window", hinstance))
	{
	}
	return;
}
GLboolean Window::CreateWindow_(wchar_t *title, GLint width, GLint height, GLint bits, GLboolean fullscreenflag)
{
	PWNDCLASS wc = new WNDCLASS();
	hinstance = GetModuleHandle(0);
	wc->style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc->lpfnWndProc = (WNDPROC)WndProc;
	wc->cbClsExtra = 0;
	wc->cbWndExtra = 0;
	wc->hInstance = hinstance;
	wc->hIcon = LoadIcon(0, IDI_WINLOGO);
	wc->hCursor = LoadCursor(0, IDC_ARROW);
	wc->hbrBackground = 0;
	wc->lpszMenuName = 0;
	wc->lpszClassName = L"My Window";
	if (!RegisterClass(wc))
	{
		MessageBox(0, L"Failed reg crea", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	fullscreen = fullscreenflag;
	if (fullscreen)
	{
		PDEVMODE dmscreensettings = new DEVMODE();
		memset(dmscreensettings, 0, sizeof(dmscreensettings));
		dmscreensettings->dmSize = sizeof(dmscreensettings);
		dmscreensettings->dmPelsWidth = width;
		dmscreensettings->dmPelsHeight = height;
		dmscreensettings->dmBitsPerPel = bits;
		dmscreensettings->dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if (ChangeDisplaySettings(dmscreensettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(0, L"Not support fulscreen", L"HINT", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
				fullscreen = false;
			else
			{
				MessageBox(0, L"Prog close", L"ERROR", MB_OK | MB_ICONSTOP);
				return false;
			}
		}
	}
	DWORD dwexstyle, dwstyle;
	if (fullscreen)
	{
		dwexstyle = WS_EX_APPWINDOW;
		dwstyle = WS_POPUP;
		ShowCursor(true);
	}
	else
	{
		dwexstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwstyle = WS_OVERLAPPED;
	}
	PRECT windowrect = new RECT();
	windowrect->left = (long)0;
	windowrect->right = (long)width + 0;
	windowrect->top = (long)0;
	windowrect->bottom = (long)height + 0;
	AdjustWindowRectEx(windowrect, dwstyle, false, dwexstyle);
	int menuheight = 0, menuwidth = 0;
	if (!fullscreenflag)
	{
		menuheight = 40;
		menuwidth = 20;
	}
	if (!(hwnd = CreateWindowEx(dwexstyle, L"My Window", title, 
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwstyle,
		0, 0, windowrect->right - windowrect->left + menuwidth, 
		windowrect->bottom - windowrect->top + menuheight, 0, 0, hinstance, 0)))
	{
		KillWindow();
		MessageBox(0, L"Create w error", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	HWND button = CreateWindowEx(
		BS_PUSHBUTTON,
		L"BUTTON",
		L"OK",
		WS_CHILD | WS_VISIBLE,
		250,
		150,
		70,
		30,
		hwnd,
		(HMENU)1001,
		hinstance,
		NULL
	);
	HWND RADIOBUTTON1 = CreateWindowEx(
		BS_PUSHBUTTON,
		L"BUTTON",
		L"OFFLINE",
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		350,
		150,
		70,
		30,
		hwnd,
		(HMENU)1002,
		hinstance,
		NULL
	);
	HWND RADIOBUTTON2 = CreateWindowEx(
		BS_PUSHBUTTON,
		L"BUTTON",
		L"ONLINE",
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		450,
		150,
		70,
		30,
		hwnd,
		(HMENU)1003,
		hinstance,
		NULL
	);
	edit1 = CreateWindowEx(/*DT_EDITCONTROL*/0L,L"Edit", L"E-mail",
		WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 10, 200,
		30, hwnd, (HMENU)1004, hinstance, NULL);

	edit2 = CreateWindowEx(/*DT_EDITCONTROL*/0L, L"Edit", L"password",
		WS_VISIBLE | WS_CHILD , 300, 50, 200,
		30, hwnd, (HMENU)1005, hinstance, NULL); 
	GLuint pixelformat;
	PPIXELFORMATDESCRIPTOR pfd = new PIXELFORMATDESCRIPTOR();
	pfd->nSize = sizeof(PPIXELFORMATDESCRIPTOR);
	pfd->nVersion = 1;
	pfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd->iPixelType = PFD_TYPE_RGBA;
	pfd->cColorBits = bits;
	pfd->cRedBits = 0;
	pfd->cRedShift = 0;
	pfd->cGreenBits = 0;
	pfd->cGreenShift = 0;
	pfd->cBlueBits = 0;
	pfd->cBlueShift = 0;
	pfd->cAlphaBits = 0;
	pfd->cAlphaShift = 0;
	pfd->cAccumBits = 0;
	pfd->cAccumRedBits = 0;
	pfd->cAccumGreenBits = 0;
	pfd->cAccumBlueBits = 0;
	pfd->cAccumAlphaBits = 0;
	pfd->cDepthBits = 32;
	pfd->cStencilBits = 0;
	pfd->cAuxBuffers = 0;
	pfd->iLayerType = PFD_MAIN_PLANE;
	pfd->bReserved = 0;
	pfd->dwLayerMask = 0;
	pfd->dwVisibleMask = 0;
	pfd->dwDamageMask = 0;
	if (!(hdc = GetDC(hwnd)))
	{
		KillWindow();
		MessageBox(0, L"can't create dc", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (!(pixelformat = ChoosePixelFormat(hdc, pfd)))
	{
		KillWindow();
		MessageBox(0,L"can't pixelf", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (!SetPixelFormat(hdc, pixelformat, pfd))
	{
		KillWindow();
		MessageBox(0, L"can't setpixel", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (!(hrc = wglCreateContext(hdc)))
	{
		KillWindow();
		MessageBox(0, L"can't context",L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if (!wglMakeCurrent(hdc, hrc))
	{
		KillWindow();
		MessageBox(0, L"can't context cur", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	return true;
}
GLvoid Window::Show()
{
	SwapBuffers(hdc);
}
GLvoid Window::Update()
{
	if (PeekMessage(msg_, 0, 0, 0, PM_REMOVE) && msg_->message != WM_QUIT)
	{
		TranslateMessage(msg_);
		DispatchMessage(msg_);
	}
	return;
}
Window::~Window()
{
	//19.09.2017 21:22 no work in vs2010
	//delete msg_;
}
#include <iostream>
LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		msg_->message = umsg;
	case WM_LBUTTONDOWN:
	{
		x = LOWORD(lparam);
		y = HIWORD(lparam);
		lparam_ = lparam;
		//if((x>x1)&&(x<x2)&&(y>y1)&&(y<y2))
		{
			//char* dst = new char[4];
			//MessageBox(hwnd,itoa(y,dst,10)/*"����������, � ����� �� �����������!"*/, "Yes-s-s!", MB_OK|MB_ICONINFORMATION);
			//delete dst;
		}

		break;
	}
	case WM_RBUTTONDOWN:
	{
		x = LOWORD(lparam);
		y = HIWORD(lparam);
		lparam_ = lparam;
		//if((x>x1)&&(x<x2)&&(y>y1)&&(y<y2))
		{
			//char *dst = new char[4];
			//MessageBox(hwnd, itoa(x,dst,10)/*"����������, � ����� �� �����������!"*/, "Yes-s-s!", MB_OK|MB_ICONINFORMATION);
			//delete dst;
		}

		break;
	}
	case WM_ACTIVATE:
	{
		return 0;
	}
	case WM_SYSCOMMAND:
	{
		switch (wparam)
		{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
	{
		wparam_ = wparam;
		return 0;
	}
	case WM_KEYUP:
	{
		wparam_ = wparam;
		return 0;
	}
	case WM_SIZE:
	{
		lparam_ = lparam;
		return 0;
	}
	case WM_COMMAND: 
	{
		if (wparam == 1001)
		{
			/*
			GetWindowText(*edit1, *login, count);
			GetWindowText(*edit2, *pass, count);
			std::cout << CW2A(*login)<<std::endl;
			std::cout << CW2A(*pass) << std::endl;
			*/
			//Edit_SetText(edit1, TEXT("91797 w7f9a789wf evckavolw4koar"));
			//SetWindowText(edit1, L"Text");
			//GetWindowText(edit1, login,count);
			//Edit_GetText(edit1, login, count);
			int cch;
			//static TCHAR pszTextBuff[500];
			cch = SendMessage(edit1, WM_GETTEXT, 500, (LPARAM)pszTextBuff);
			cch = SendMessage(edit2, WM_GETTEXT, 500, (LPARAM)Buff1);
			if (cch == 0)
				;//	MessageBox(hwnd, TEXT("������� �����"), TEXT("������ Edit"), MB_OK);
			else
			{
				//TCHAR Buff1[500] = { 0 };
				/*
				SYSTEMTIME st; GetSystemTime(&st);
				wsprintf(Buff1, TEXT("����� : %d � %d ��� %d ���\n"),
					st.wHour + 3, st.wMinute, st.wSecond);
				lstrcat(Buff1, __TEXT("����� � ������: "));
				*/
				//lstrcat(Buff1, pszTextBuff);
				//MessageBox(hwnd, Buff1, TEXT("���������� ������"), MB_OK);
				std::wcout << pszTextBuff << std::endl;
				std::wcout << Buff1 << std::endl;
			}
		}
		if (wparam == 1002)
			std::cout << "ofline!";
		if (wparam == 1003)
			std::cout << "online!";
		if (wparam == 1004)
			std::cout << "editlogin!";
		if (wparam == 1005)
			std::cout << "editpass!";

		break;
	}
	}
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

