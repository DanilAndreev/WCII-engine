// WCIIRemake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

//Global variavles

//The main window class name
static TCHAR szWindowClass[] = _T("DesktopApp");

//The string that appears in the applicatio title bar
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

HINSTANCE hInst;

//Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);




int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return 1;
	}

	//Store instance handle in our global variable
	hInst = hInstance;


	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	HWND hwndButton = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"OK",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		10,         // y position 
		100,        // Button width
		100,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.




	if (!hWnd) {
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);
		return 1;
	}

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//for image
const int winx = 100;
const int winy = 500;
const int winbpp = 1;

BITMAPINFO m_bi;
char* buffer = 0;


void setbuffer()
{
	m_bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bi.bmiHeader.biWidth = winx;
	m_bi.bmiHeader.biHeight = winy;
	m_bi.bmiHeader.biPlanes = 1;
	m_bi.bmiHeader.biBitCount = 24;
	m_bi.bmiHeader.biCompression = BI_RGB;
	m_bi.bmiHeader.biSizeImage = 0;
	m_bi.bmiHeader.biXPelsPerMeter = 100;
	m_bi.bmiHeader.biYPelsPerMeter = 100;
	m_bi.bmiHeader.biClrUsed = 0;
	m_bi.bmiHeader.biClrImportant = 0;

	size_t paddedWidth = (winx * 3 + 3) & ~3;
	buffer = new char[paddedWidth * winy * winbpp];

	for (int y = 0; y < winy; ++y)
	{
		for (int x = 0; x < winx; ++x)
		{
			for (int z = 0; z < 3; ++z)
			{
				buffer[y * paddedWidth + x * winbpp + z] = z * x;
			}
		}
	}
}

//---------------------------


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop!");
	TCHAR textToType[2];
	textToType[0] = rand() % 20 + 80;
	textToType[1] = 0;
	int pos = 1;

//for image
	RECT client;
	DWORD result;
//---------------

	switch (message)
	{
		case WM_CREATE:
			setbuffer();
			InvalidateRect(hWnd, NULL, TRUE);

			break;
		case WM_LBUTTONDOWN:
			pos++;
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc,
				5, pos,
				greeting, _tcslen(greeting));
			EndPaint(hWnd, &ps);
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &client);
			result = StretchDIBits(hdc,
				0, 0,
				client.right, client.bottom,
				0, 0,
				winx, winy,
				buffer, &m_bi, DIB_RGB_COLORS, SRCCOPY);
			if (result != winy)
			{
				//Drawing failed
				DebugBreak();
			}

			//
			
			//TCHAR teststr[] = _T(a);
/*
			TextOut(hdc,
				5, 5,
				greeting, _tcslen(greeting));

			TextOut(hdc,
				5, 5,
				textToType, _tcslen(textToType));
*/
			//End application-specific layout section

			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}




