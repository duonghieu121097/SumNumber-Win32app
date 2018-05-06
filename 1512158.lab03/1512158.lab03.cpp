// 1512158.lab03.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include <windowsx.h>
#include "1512158.lab03.h"
#include <string>
#include <iostream>
#define MAX_LOADSTRING 100
using namespace std;

void OnPaint(HWND hwnd);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
int Oncalculate(HWND hwnd);

HWND hJapan;
HWND hSing;
HWND hResult;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY1512158LAB03, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1512158LAB03));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MY1512158LAB03));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY1512158LAB03);
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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 50, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
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
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
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

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	// Parse the menu selections:
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hwnd);
		break;
	case ID_BUTTON:
		Oncalculate(hwnd);
		break;
	}
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	// TODO: Add any drawing code that uses hdc here...

	EndPaint(hwnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	
	CreateWindow(L"STATIC", L"Nhập giá ở singapore (SGD): ", WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER
		, 350, 150, 180, 40, hwnd, NULL, hInst, NULL);
	hSing = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL
		, 550, 150, 100, 40, hwnd, NULL, hInst, NULL);
	CreateWindow(L"STATIC", L"Nhập giá ở Nhật Bản (JPY): ", WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER
		, 350, 100, 180, 40, hwnd, NULL, hInst, NULL);
	hJapan = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL
		, 550, 100, 100, 40, hwnd, NULL, hInst, NULL);
	CreateWindow(L"BUTTON", L"Khảo sát", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
		, 500, 200, 100, 40, hwnd, (HMENU)ID_BUTTON, hInst, NULL);
	hResult = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_CENTER
		, 400, 270, 300, 40, hwnd, NULL, hInst, NULL);
	return true;
}
int Oncalculate(HWND hwnd)
{
	int japan, sing, s1, s2;
	WCHAR* buffer1 = NULL;
	WCHAR* buffer2 = NULL;
	s1 = GetWindowTextLength(hJapan);
	s2 = GetWindowTextLength(hSing);
	buffer1 = new WCHAR[s1];
	buffer2 = new WCHAR[s2];
	GetWindowText(hJapan, buffer1, s1);
	GetWindowText(hSing, buffer2, s2);
	japan = _wtoi(buffer1);
	sing = _wtoi(buffer2);
	float JPY_USD = japan * 0.00893;
	float SGD_USD = sing * 0.73666;
	if (JPY_USD < SGD_USD) 
	{
		SetWindowText(hResult, L"Bạn nên mua ở Nhật Bản");
	}
	if (JPY_USD > SGD_USD)
	{
		SetWindowText(hResult, L"Bạn nên mua ở Singapore");
	}
	if (JPY_USD == SGD_USD) 
	{
		SetWindowText(hResult, L"Giá bằng nhau ở hai nơi");
	}
	return japan;
}