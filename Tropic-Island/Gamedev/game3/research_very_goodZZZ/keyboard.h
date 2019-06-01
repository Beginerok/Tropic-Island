/*
This is si in off
*/
#include <Windows.h>
#include <gl\GLU.h>
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"glu32.lib")
class Keyboard
{
public:
	Keyboard();
	static GLvoid Update();
	static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
	static GLvoid KillWindow();
	static GLboolean CreateWindow_(wchar_t *title,GLint width,GLint height,GLint bits,GLboolean fullscreenflag);
	static GLvoid Show();
	~Keyboard();
	static PMSG msg_;
	static LPARAM lparam_;
	static WPARAM wparam_;
	static HGLRC hrc;
	static HDC hdc;
	static HWND hwnd;
	static HINSTANCE hinstance;
	static GLboolean fullscreen;
	static int x,y;
};
