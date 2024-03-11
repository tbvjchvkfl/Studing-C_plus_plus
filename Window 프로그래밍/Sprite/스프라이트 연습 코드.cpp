// ------------ Actor.h ------------

#pragma once
#include "D2DFramework.h"

class Actor
{
protected:

	// 선택 사항
	// ID2D1Factory와 IWICImagingFactory 2개를 사용하느냐
	// vs
	// Framework 하나만 사용하느냐

	/*ID2D1Factory* pD2DFactory;
	IWICImagingFactory* pWICFactory;*/


	D2DFramework* mpFramework;

	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspBitmap;

	float mX;
	float mY;
	float mOpacity;

public:
	Actor() = delete;
	Actor(D2DFramework* pFramework, LPCWSTR filename);
	Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity = 1.0f);

	virtual ~Actor();

private:
	HRESULT LoadWICImage(LPCWSTR filename);
	void Draw(float x, float y, float opacity);

public:
	virtual void Draw();
};

// ------------ ActorExample.h ------------

#pragma once
#include <memory>
#include "D2DFramework.h"
#include "Actor.h"

class ActorExample : public D2DFramework
{
	std::unique_ptr<Actor> mspBackground;
	std::unique_ptr<Actor> mspBug;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"ActorExmple", UINT width = 1024, UINT Height = 768) override;
	virtual void Release() override;
	virtual void Render() override;
};

// ------------ D2DFramework.h ------------

#pragma once
#include <wincodec.h>
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
	Microsoft::WRL::ComPtr<IWICImagingFactory> mspWICFactory{};
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

public:
	inline ID2D1HwndRenderTarget* GetRenderTarget()
	{
		return mspRenderTarget.Get();
	}
	inline IWICImagingFactory* GetWICFactory()
	{
		return mspWICFactory.Get();
	}
	inline ID2D1Factory* GetD2DFactory()
	{
		return mspD2DFactory.Get();
	}
};



// ------------ Winmain.cpp ------------
#include <windows.h>
#include "ActorExample.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpcmdLine, _In_ int nShowcmd)
{
	try
	{
		ActorExample myFramework;

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

// ------------ Actor.cpp ------------

#include "Actor.h"

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename) : mpFramework(pFramework), mspBitmap(), mX(), mY(), mOpacity(1.0f)
{
	LoadWICImage(filename);
}

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity) : Actor(pFramework, filename)
{
	mX = x;
	mY = y;
	mOpacity = opacity;
}

Actor::~Actor()
{
	mspBitmap.Reset();
}

HRESULT Actor::LoadWICImage(LPCWSTR filename)
{
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
	HRESULT hr;

	if (mpFramework == nullptr)
	{
		return E_FAIL;
	}

	auto pWICFactory = mpFramework->GetWICFactory();

	if (pWICFactory == nullptr)
	{
		return E_FAIL;
	}

	hr = pWICFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, decoder.GetAddressOf());
	ThrowIfFailed(hr);


	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode>frame;
	ThrowIfFailed(decoder->GetFrame(0, frame.GetAddressOf()));

	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	ThrowIfFailed(pWICFactory->CreateFormatConverter(converter.GetAddressOf()));

	hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom);
	ThrowIfFailed(hr);

	auto pRT = mpFramework->GetRenderTarget();
	if (pRT == nullptr)
	{
		return E_FAIL;
	}
	hr = pRT->CreateBitmapFromWicBitmap(converter.Get(), mspBitmap.GetAddressOf());
	ThrowIfFailed(hr);

	return S_OK;
}

void Actor::Draw(float x, float y, float opacity)
{
	auto pRT = mpFramework->GetRenderTarget();
	if (pRT == nullptr)
	{
		return;
	}

	auto size{ mspBitmap->GetPixelSize() };
	D2D1_RECT_F rect{ x,y,static_cast<float>(x + size.width), static_cast<float>(y + size.height) };

	pRT->DrawBitmap(mspBitmap.Get(), rect, opacity);
}

void Actor::Draw()
{
	// 외부에서 매개변수를 사용하기 때문에 사용자가 커스텀이 가능함.
	Draw(mX, mY, mOpacity);
}

// ------------ ActorExample.cpp ------------

#include <vector>
#include "ActorExample.h"

std::vector<std::unique_ptr<Actor>> bugs;

HRESULT ActorExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT width, UINT height)
{
    HRESULT hr;

    hr = D2DFramework::Initialize(hInstance, title, width, height);
    ThrowIfFailed(hr);

    mspBackground = std::make_unique<Actor>(this, L"Images/back1.png", 0.0f, 0.0f, 1.0f);

    // 여러마리
    /*for (int i = 0; i < 20; i++)
    {
        bugs.push_back(std::make_unique<Actor>(this, L"Images/bug1_1.png", 0.0f + i* 20.0f, 100.0f));
    }*/
   
    // 한 마리만 만들 떄는 이렇게
    mspBug = std::make_unique<Actor>(this, L"Images/bug1_1.png", 100.0f, 100.0f);

    return S_OK;
}

void ActorExample::Release()
{
    // unique_ptr를 사용했으므로 생성한 순서대로 해제를 해주어야함.
    //bugs.clear();

    mspBug.reset();
    mspBackground.reset();

    D2DFramework::Release();
}

void ActorExample::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    mspBackground->Draw();
    mspBug->Draw();

    /*for (auto& bugs : bugs)
    {
        bugs->Draw();
    }*/

    

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}


// ------------ D2DFramework.cpp ------------

#include "D2DFramework.h"

#pragma comment (lib, "d2d1.lib")
#pragma commnet (lib, "WindowsCodecs.lib")

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
	HRESULT hr;


	// 범위 해결연산자를 사용할 때 왼쪽부분을 표기하지 않으면 전역에 (global)과 같음.
	// MyClass::CoCreate() -> MyClass에 CoCreate라는 함수가 포함되어있다.
	// ::CoCreate() -> 전역에 있는 CoCreate 함수

	hr = ::CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(mspWICFactory.GetAddressOf()));
	// 기본 버전
	/*if (FAILED(hr))
	{
		ShowError(L"Failed to Create Factory");
		return hr;
	}*/

	// inline 함수를 활용한 버전
	ThrowIfFailed(hr);

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mspD2DFactory.GetAddressOf());
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
	// CoInitialize와 CoUninitialize는 하나의 쌍으로 존재해야 함.
	ThrowIfFailed(CoInitialize(nullptr));

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
	mspWICFactory.Reset();

	CoUninitialize();
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
