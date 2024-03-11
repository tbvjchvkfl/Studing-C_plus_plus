
// ------------ BitmapExample.h ------------

#pragma once
#include "D2DFramework.h"
#include <memory>

const int BITMAP_WIDTH = 1024;
const int BITMAP_HEIGHT = 768;

const int BITMAP_BYTECOUNT = 4;

class BitmapExample : public D2DFramework
{
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspFrameBuffer;
	std::unique_ptr<UINT8[]> mspBackBuffer;

protected:
	virtual HRESULT CreateDeviceResources() override;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"BitmapExample", UINT w = BITMAP_WIDTH, UINT h = BITMAP_HEIGHT) override;
	virtual void Render() override;

	void DrawPixel(int x, int y, D2D1::ColorF color);
	void DrawRectangle(int left, int top, int w, int h, D2D1::ColorF color);
	void ClearBuffer(D2D1::ColorF color);
	void PresentBuffer();
};

// ------------ D2DFramework.h ------------

#pragma once
#include <d2d1.h>
#include <wrl/client.h>
#include <exception>
#include <stdio.h>

// COM Exception
class com_exception : public std::exception
{
private:
	HRESULT result;

public:
	com_exception(HRESULT hr) : result(hr) {}
	virtual const char* what() const override
	{
		static char str[64]{};
		sprintf_s(str, "Failed with HRESULT : %08X", result);
		return str;
	}
};

// inline 함수 : 호출 스택을 쓰지 않으려고 함.
// 스택을 사용하지 않고 register에 데이터를 잠시 옮겨놓는 것.
// 호출 스택을 무조건 사용하지 않는 것은 아님.
// 매개 변수가 작거나, 가벼운 기능의 함수라면 매우 빠르게 동작할 수 있게 할 수 있음.
// 표기법 : inline / type / 함수 이름 / (매개변수) 
inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw com_exception(hr);
	}
}

class D2DFramework
{
private:
	const LPCWSTR gClassName{ L"MyWindowClass" };

protected:
	HWND mHwnd{};

protected:
	Microsoft::WRL::ComPtr<ID2D1Factory> mspD2DFactory{};
	Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> mspRenderTarget{};

protected:
	HRESULT InitWindow(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework", UINT w = 1024, UINT h = 768);
	virtual HRESULT InitD2D(HWND hwnd);
	virtual HRESULT CreateDeviceResources();

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"D2DFramework", UINT w = 1024, UINT h = 768);

	virtual void Release();
	virtual int GameLoop();
	virtual void Render();

	void ShowError(LPCWSTR msg, LPCWSTR title = L"Error");

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};




// ------------ WinMain.cpp ------------

#include <windows.h>
#include "BitmapExample.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpcmdLine, _In_ int nShowcmd)
{
	try
	{
		BitmapExample myFramework;

		myFramework.Initialize(hInstance, L"Framework", 1024, 768);

		int ret = myFramework.GameLoop();

		myFramework.Release();

		return ret;
	}
	catch (const com_exception& e)
	{
		OutputDebugStringA(e.what());
		MessageBoxA(nullptr, e.what(), "Error", MB_OK);
	}
}

// ------------ BitmapExample.cpp ------------

#include "BitmapExample.h"

HRESULT BitmapExample::CreateDeviceResources()
{
    D2DFramework::CreateDeviceResources();
    HRESULT hr = mspRenderTarget->CreateBitmap(
        D2D1::SizeU(BITMAP_WIDTH, BITMAP_HEIGHT),
        D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)),
        mspFrameBuffer.ReleaseAndGetAddressOf());
    ThrowIfFailed(hr);
    return S_OK;
}

HRESULT BitmapExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
{
    D2DFramework::Initialize(hInstance, title, w, h);

    mspBackBuffer = std::make_unique<UINT8[]>(BITMAP_WIDTH * BITMAP_HEIGHT * BITMAP_BYTECOUNT);

    return S_OK;
}

void BitmapExample::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    ClearBuffer(D2D1::ColorF(D2D1::ColorF::Aquamarine));

    DrawRectangle(0, 0, 100, 100, D2D1::ColorF::Red);
    DrawRectangle(50, 50, 100, 100, D2D1::ColorF(D2D1::ColorF::AntiqueWhite, 0.8f));

    PresentBuffer();
    mspRenderTarget->DrawBitmap(mspFrameBuffer.Get());


    // 그리기
    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void BitmapExample::DrawPixel(int x, int y, D2D1::ColorF color)
{
    int pitch = BITMAP_WIDTH * BITMAP_BYTECOUNT;
    int i = y * pitch + x * BITMAP_BYTECOUNT; // 2차원의 공간을 1차원의 배열화 하는 것.

    // alpha 값 넣기
    float inverse = 1.0f - color.a;

    mspBackBuffer[i] = mspBackBuffer[i] * inverse + static_cast<UINT8> (color.r * 255 * color.a);
    mspBackBuffer[i + 1] = mspBackBuffer[i + 1] * inverse + static_cast<UINT8> (color.g * 255 * color.a);
    mspBackBuffer[i + 2] = mspBackBuffer[i + 2] * inverse + static_cast<UINT8> (color.b * 255 * color.a);
    mspBackBuffer[i + 3] = mspBackBuffer[i + 3] * inverse + static_cast<UINT8> (color.a * 255 * color.a);

}

void BitmapExample::DrawRectangle(int left, int top, int w, int h, D2D1::ColorF color)
{
    for (int x = 0; x < w; ++x)
    {
        for (int y = 0; y < h; ++y)
        {
            DrawPixel(left + x, top + y, color);
        }
    }
}

void BitmapExample::ClearBuffer(D2D1::ColorF color)
{
    UINT8* p = &mspBackBuffer[0];
    for (int i = 0; i < BITMAP_WIDTH * BITMAP_HEIGHT; i++)
    {
        *p++ = static_cast<UINT8>(color.r * 255); // R
        *p++ = static_cast<UINT8>(color.g * 255); // G
        *p++ = static_cast<UINT8>(color.b * 255); // B
        *p++ = static_cast<UINT8>(color.a * 255); // A
    }
}

void BitmapExample::PresentBuffer()
{
    // back -> front
    // 후면 버퍼에 있는 내용을 전방으로 옮기는 용도로 만든 함수.

    // &mspBackBuffer[0]는 mspBackBuffer.get()과 같음.
    mspFrameBuffer->CopyFromMemory(nullptr, &mspBackBuffer[0], BITMAP_WIDTH * BITMAP_BYTECOUNT);
}

// ------------ D2DFramework.cpp ------------

#include "D2DFramework.h"

#pragma comment (lib, "d2d1.lib")

HRESULT D2DFramework::InitWindow(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
{
	HWND hwnd;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = gClassName;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = D2DFramework::WndProc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	if (!RegisterClassEx(&wc))
	{
		return E_FAIL;
	}

	RECT wr = { 0,0,static_cast<LONG>(w),static_cast<LONG>(h) };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	hwnd = CreateWindowEx(0, gClassName, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, hInstance, NULL);

	if (hwnd == nullptr)
	{
		return E_FAIL;
	}
	mHwnd = hwnd;

	SetWindowLongPtr(mHwnd, GWLP_USERDATA, reinterpret_cast <LONG_PTR> (this));

	return S_OK;
}

HRESULT D2DFramework::InitD2D(HWND hwnd)
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mspD2DFactory.GetAddressOf());
	// 기본 버전
	/*if (FAILED(hr))
	{
		ShowError(L"Failed to Create Factory");
		return hr;
	}*/

	// inline 함수를 활용한 버전
	ThrowIfFailed(hr);


	hr = CreateDeviceResources();
	return hr;
}

HRESULT D2DFramework::CreateDeviceResources()
{
	RECT wr;
	GetClientRect(mHwnd, &wr);
	HRESULT hr;
	hr = mspD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(mHwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)), mspRenderTarget.GetAddressOf());

	// 기본 버전
	/*if (FAILED(hr))
	{
		ShowError(L"Failed to Create HWNDRenderTarget!");
		return hr;
	}*/


	// inline 함수를 활용한 버전
	ThrowIfFailed(hr);
	return S_OK;
}

HRESULT D2DFramework::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
{
	ThrowIfFailed(InitWindow(hInstance, title, w, h));
	ThrowIfFailed(InitD2D(mHwnd));

	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);

	return S_OK;
}

void D2DFramework::Release()
{
	mspRenderTarget.Reset();
	mspD2DFactory.Reset();
}

int D2DFramework::GameLoop()
{
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
			Render();
		}
	}
	return static_cast<int>(msg.wParam);
}

void D2DFramework::Render()
{
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
	HRESULT hr = mspRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}

void D2DFramework::ShowError(LPCWSTR msg, LPCWSTR title)
{
	MessageBox(nullptr, msg, title, MB_OK);
}

LRESULT D2DFramework::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// pFramwork의 포인터로 접근하는 방식을 사용할 수 있음.
	D2DFramework* pFramwork = reinterpret_cast<D2DFramework*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (message)
	{
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
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	}
	return 0;
}
