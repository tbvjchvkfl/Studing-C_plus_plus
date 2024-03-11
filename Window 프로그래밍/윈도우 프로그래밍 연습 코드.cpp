#include <windows.h>
#include <sstream>
#include <gdiplus.h>

#pragma comment (lib, "Gdiplus.lib")

const wchar_t gClassName[] = L"MyWindowClass";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	MessageBox(nullptr, L"Hello World", L"MyWindow", MB_ICONEXCLAMATION | MB_OK);

	Gdiplus::GdiplusStartupInput gpsi;
	ULONG_PTR gdiToken;
	Gdiplus::GdiplusStartup(&gdiToken, &gpsi, nullptr);

	// 1. ������ Ŭ���� ���
	WNDCLASSEX wc;

	// *** important ***
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to register", L"Error", MB_OK);
		return 0;
	}

	// 2. �����츦 ����
	HWND hwnd;
	hwnd = CreateWindowEx(
		0,
		gClassName,
		L"Hello Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
	{
		MessageBox(nullptr, L"Failed to create", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	// 3. ������ �޽��� ó��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiToken);
	return msg.wParam;
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);


	// Gdi Code
	/*HPEN redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HBRUSH hatchBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0));
	SelectObject(hdc, redPen);
	SelectObject(hdc, hatchBrush);
	Rectangle(hdc, 0, 0, 100, 100);
	DeleteObject(hatchBrush);*/


	// Gdiplus Code
	Gdiplus::Pen redPen(Gdiplus::Color(255, 0, 0));
	Gdiplus::HatchBrush hatchBrush(Gdiplus::HatchStyle::HatchStyleCross, Gdiplus::Color(255, 0, 0));
	Gdiplus::Image image(L"image.jpg");

	Gdiplus::Graphics graphics(hdc);
	// graphics.DrawRectangle(&redPen, 0, 0, 100, 100);
	graphics.DrawImage(&image, 0, 0, 640, 480);
	EndPaint(hwnd, &ps);
}
// 4. ������ ���ν��� �ۼ�
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			OnPaint(hwnd);
		}
		break;
		case WM_KEYDOWN:
		{
			std::ostringstream oss;
			oss << "Virtual Keycode = " << wParam << std::endl;
			OutputDebugStringA(oss.str().c_str());
		}
		break;
		case WM_LBUTTONDOWN:
		{
			HDC hdc;

			// GetDC ���� ReleaseDC�� ����� �޸� ������ ����. 
			hdc = GetDC(hwnd);
			Rectangle(hdc, 0, 0, 100, 100);
			ReleaseDC(hwnd, hdc);

			// *** C++ ��� ��Ÿ�� ***
			std::ostringstream oss;
			oss << "x : " << LOWORD(lParam) << ", y : " << HIWORD(lParam) << std::endl;
			OutputDebugStringA(oss.str().c_str());
			

			// *** C��� ��Ÿ�� ***
			//int x = lParam;
			//int y = lParam;
			//// ����� �� outputstring �Լ�
			//OutputDebugStringA("Hello\n");
		}
		break;
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		}
		break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
			break;
	}
}