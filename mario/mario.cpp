// mario.cpp : Defines the entry point for the application.
//
#include <windowsx.h>

#include "framework.h"
#include "mario.h"
#include "Engine.h"
#include "Setting.h"
#include "State.h"
#include "Menu.h"

#include <uxtheme.h>
#pragma comment (lib, "uxtheme.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND mainWindowHandle;							// mainWindowHandle

// Function Declaration
void MemoryBuffer(HWND, HDC);

// Initialize Engine
Engine* engine = new Engine();

// Initialize Game State
State* state = new State();

// Initialize Menu
Menu* menu = new Menu();

// Initialize Gdiplus
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

// Initialize Server Time
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

bool OnCreate(HWND, LPCREATESTRUCT);
void OnDestroy(HWND);
void OnPaint(HWND);
void OnCommand(HWND, int, HWND, UINT);
void OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);
void OnKeyUp(HWND hwnd, UINT vk, BOOL fUp, int cRepeat, UINT flags);

void DrawToDoubleBuffer(HDC, Gdiplus::Graphics*);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	// 
	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MARIO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MARIO));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// after amount of time
			// send a wm_paint message
		}
	}

	// Shut down Gdiplus
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MARIO));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MARIO);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	mainWindowHandle = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	// Disable maximize button
	SetWindowLong(mainWindowHandle, GWL_STYLE,
		GetWindowLong(mainWindowHandle, GWL_STYLE) & ~WS_MAXIMIZEBOX);

	if (!mainWindowHandle)
	{
		return FALSE;
	}
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	ShowWindow(mainWindowHandle, nCmdShow);
	UpdateWindow(mainWindowHandle);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_KEYDOWN, OnKeyDown);
		HANDLE_MSG(hWnd, WM_KEYUP, OnKeyUp);


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

bool OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	// Resize the window
	RECT rect1;
	GetWindowRect(hWnd, &rect1);
	RECT rect2;
	GetClientRect(hWnd, &rect2);

	SetWindowPos(
		hWnd,
		NULL,
		rect1.left,
		rect1.top,
		RESOLUTION_X + ((rect1.right - rect1.left) - (rect2.right - rect2.left)),
		RESOLUTION_Y + ((rect1.bottom - rect1.top) - (rect2.bottom - rect2.top)),
		NULL
	);

	return true;
}

void OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}

void OnPaint(HWND hWnd)
{
	// Initialize Paint
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);

	RECT rc;
	GetClientRect(hWnd, &rc);
	HDC memdc;
	auto hbuff = BeginBufferedPaint(hdc, &rc, BPBF_COMPATIBLEBITMAP, NULL, &memdc);

	MemoryBuffer(hWnd, memdc);
	EndBufferedPaint(hbuff, TRUE);

	EndPaint(hWnd, &ps);
	InvalidateRect(hWnd, nullptr, false);
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{

}

void OnKeyDown(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	if (state->getState() == 1)
		engine->KeyDown(vk);
	menu->KeyDown(vk, state);
	InvalidateRect(hwnd, nullptr, false);
}

void OnKeyUp(HWND hwnd, UINT vk, BOOL fUp, int cRepeat, UINT flags)
{
	if (state->getState() == 1)
		engine->KeyUp(vk, state);

	InvalidateRect(hwnd, nullptr, false);

}

void MemoryBuffer(HWND hwnd, HDC hdc)
{
	// Initialize main handle
	Gdiplus::Graphics graphics(hdc);

	// Initialize Double Buffer where we draw everything on Bitmap first
	Gdiplus::Bitmap* buffer = new Gdiplus::Bitmap(RESOLUTION_X, RESOLUTION_Y, PixelFormat32bppPARGB);
	Gdiplus::Graphics memGraphics(buffer);

	// Initialize Game Elapsed Time
	end = std::chrono::steady_clock::now();
	double delta = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
	begin = end;

	graphics.Clear(Gdiplus::Color(153, 255, 255));
	engine->Draw(memGraphics);

	// Check state of the game
	if (state->getState() == 0)
	{
		menu->CreateMenu(hwnd, memGraphics);
	}
	else if (state->getState() == 1)
	{ // without logic everything will be paused
		engine->Logic(delta, state);
	}
	else if (state->getState() == 2)
	{
		menu->CreateGameOverMenu(hwnd, memGraphics);

	}

	graphics.DrawImage(buffer, 0, 0);

	// Clean up
	delete buffer;
	buffer = nullptr;

	//InvalidateRect(hwnd, nullptr, 0);
}