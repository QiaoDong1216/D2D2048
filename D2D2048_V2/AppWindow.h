#pragma once
#include "Direct2dApp/Direct2dApp.h"
#include <iostream>
#include <shobjidl_core.h>
#include <string>
#include "Board.h"
#include "resource.h"
#pragma comment(lib, "Winmm.lib")

class AppWindow
{
public:
	AppWindow();
	~AppWindow();

	int Run(HINSTANCE hInstance);
	bool createWindow();
	void MessageLoop();
	void saveTo();
	float getFPS();
	void init(HWND hwnd);
	void Render();

	static DWORD WINAPI ThreadProc(
		LPVOID lpParameter
	);
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR  CALLBACK WindowDiglogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR  CALLBACK WindowDiglogAboutProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void Timerproc(HWND unnamedParam1, UINT unnamedParam2, UINT_PTR unnamedParam3, DWORD unnamedParam4);

private:
	bool Vertical_sync = true;
	bool Ai_Move = false;
	bool Animation_switch = true;

	static AppWindow* sInstance;
	app::Direct2dApp App;
	HINSTANCE hInstance;
	HWND m_hwnd;
	Board m_board;
	DWORD m_board_width;	// ���� ��
	DWORD m_board_height;	// ���� ��

	DIR m_Ai_Move = UP;
	Clock m_clock;
};
