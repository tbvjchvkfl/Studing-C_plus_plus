#include <windows.h>
#include <d2d1.h>
#include <cmath>

#pragma comment (lib, "d2d1.lib")

const wchar_t gClassName[] = L"SolitaireWindowClass";


// 1. Direct2D 팩토리 생성
// 2. 렌더 타겟 생성
// 3. 그리기 (렌더 타겟)
// 4. 리소스 해제


ID2D1Factory* gpD2DFactory{};
ID2D1HwndRenderTarget* gpRenderTarget{};

ID2D1SolidColorBrush* gpBrush{};
ID2D1RadialGradientBrush* gpRadialBrush{};



LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

// Test
// std::list<solitaire::Card> myDeck;

void OnPaint(HWND hwnd);
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpcmdLine, _In_ int nShowcmd)
{
	// D2D Factory
	// 모든 DirectX 함수는 HRESULT를 반환한다고 봐도 무방. (그 정도로 대부분 HRESULT를 반환하는 함수가 많음)

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &gpD2DFactory);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Failed to Create Factory", L"Error", MB_OK);
		return 0;
	}

	HWND hwnd;
	WNDCLASSEX wc;

	// 1단계 - 윈도우 클래스 등록
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(nullptr, L"Failed to register!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// 2단계 윈도우 생성
	RECT wr = { 0,0,1024,768 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	hwnd = CreateWindowEx(0, gClassName, L"Solitatire Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, hInstance, NULL);

	if (hwnd == nullptr)
	{
		MessageBox(nullptr, L"Failed to create!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	GetClientRect(hwnd, &wr);

	gpD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)), &gpRenderTarget);

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Failed to Create HWNDRenderTarget!", L"Error", MB_OK);
		return 0;
	}

	hr = gpRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGreen), &gpBrush);
	
	D2D1_GRADIENT_STOP stops[2]
	{
		{0.0f, D2D1::ColorF(D2D1::ColorF::Yellow)},
		{1.0f, D2D1::ColorF(D2D1::ColorF::Crimson)}
	};
	
	ID2D1GradientStopCollection* pGradientStops{};
	hr = gpRenderTarget->CreateGradientStopCollection(stops, 2, &pGradientStops);

	hr = gpRenderTarget->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(50.0f, 150.0f), D2D1::Point2F(0.0f, 0.0f), 50, 50), pGradientStops, &gpRadialBrush);

	if (pGradientStops != nullptr)
	{
		pGradientStops->Release();
		pGradientStops = nullptr;
	}

	ShowWindow(hwnd, nShowcmd);
	UpdateWindow(hwnd);

	/*MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		OnPaint(hwnd);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/

	// 게임에서 자주 사용되는 Message구조
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			OnPaint(hwnd);
		}
	}


	// 해제

	if (gpRadialBrush != nullptr)
	{
		gpRadialBrush->Release();
		gpRadialBrush = nullptr;
	}
	if (gpBrush != nullptr)
	{
		gpBrush->Release();
		gpBrush = nullptr;
	}
	if (gpRenderTarget != nullptr)
	{
		gpRenderTarget->Release();
		gpRenderTarget = nullptr;
	}
	if (gpD2DFactory != nullptr)
	{
		gpD2DFactory->Release();
		gpD2DFactory = nullptr;
	}
	
	

	if(gpBrush)
	
	return static_cast<int>(msg.wParam);
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	
	// RenderTarget에 그리기
	gpRenderTarget->BeginDraw();
	gpRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));


	gpRenderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f, 100.0f, 100.0f), gpBrush);

	gpBrush->SetColor(D2D1::ColorF(0.0f, 0.0f, 1.0f));
	
	gpRenderTarget->FillRectangle(D2D1::RectF(50.0f, 50.0f, 150.0f, 150.0f), gpBrush);

	static float angle = 0.0f;

	gpRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(75.0f+sinf(angle)*25,150.0f), 50.0f, 50.0f), gpRadialBrush);

	angle += 0.15f;

	gpRenderTarget->EndDraw();

	EndPaint(hwnd, &ps);
}

LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_LBUTTONUP:
	{
		//gLogic.OnClick(LOWORD(lparam), HIWORD(lparam));
	}
	break;
	case WM_PAINT:
	{
		OnPaint(hwnd);
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
	{
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	}
	return 0;
}

