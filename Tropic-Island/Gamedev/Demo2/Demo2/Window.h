#pragma once
#include <Windows.h>
#include <gl\GLU.h>
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"glu32.lib")
#include <atlstr.h>
#include <windowsx.h>
#include <string>
#if DBAPI_ == 1
	#include "DataBaseConnection.h"
#endif
#include <iostream>
class Window
{
public:
	Window();
	static GLvoid Update();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static GLvoid KillWindow();
	static GLboolean CreateWindow_(wchar_t *title, GLint width, GLint height, GLint bits, GLboolean fullscreenflag);
	static GLvoid Show();
	~Window();
	static PMSG msg_;
	static LPARAM lparam_;
	static WPARAM wparam_;
	static HGLRC hrc;
	static HDC hdc;
	static HWND hwnd,hwnd2;
	static HINSTANCE hinstance;
	static GLboolean fullscreen;
	static int x, y;

	static HWND edit1, edit2;

	static TCHAR pszTextBuff[500];
	static TCHAR Buff1[500];
	static bool offline,enablesound;
	static std::string login, pass;
	//static bool connect;
#if DBAPI_ == 1
	static DataBaseConnection *db;
#endif
	static HMENU hMenu, hSubMenu;
};