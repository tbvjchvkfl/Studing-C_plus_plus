

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
	ID2D1Bitmap* mpBitmap;

	float mX;
	float mY;
	float mOpacity;

public:
	Actor() = delete;
	Actor(D2DFramework* pFramework, LPCWSTR filename);
	Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity = 1.0f);

	virtual ~Actor();

private:
	void Draw(float x, float y, float opacity);

public:
	virtual void Draw();
};

// ------------ BitmapManager.h ------------

#pragma once
#include <wrl/client.h> // Comptr
#include <d2d1.h>
#include <wincodec.h>
#include <map>
#include "com_exception.h"

// 아래 클래스 구조가 Singleton Pattern의 기본!!!
// Singleont Pattern은 instance화를 할 수 없음.


// final 키워드 = 클래스가 최종이다!!!
// final 키워드가 붙으면 상속이 불가능함.
class BitmapManager final
{
public:
	static BitmapManager& Instance()
	{
		static BitmapManager instance;
		return instance;
	}

private:
	BitmapManager() {}
	BitmapManager(const BitmapManager&) {}
	void operator=(const BitmapManager&) {}

public:
	~BitmapManager() {}

	////////////////////////////////

private:
	ID2D1HwndRenderTarget* mpRenderTarget{};
	Microsoft::WRL::ComPtr<IWICImagingFactory> mspWICFactory{};

	std::map < std::wstring, Microsoft::WRL::ComPtr<ID2D1Bitmap>> mBitmapResources;

private:
	HRESULT LoadWICBitmap(std::wstring filenmame, ID2D1Bitmap** ppBitmap);

public:
	HRESULT Initialize(ID2D1HwndRenderTarget* pRT);
	void Release();

	ID2D1Bitmap* LoadBitmap(std::wstring filename);
};

// ------------ D2DFramework.h ------------

#pragma once
#include <d2d1.h>
#include <wrl/client.h>
#include "com_exception.h"
#include "BitmapManager.h"


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

public:
	inline ID2D1HwndRenderTarget* GetRenderTarget()
	{
		return mspRenderTarget.Get();
	}
	inline ID2D1Factory* GetD2DFactory()
	{
		return mspD2DFactory.Get();
	}
};




// ------------ Com_Exceiption.h ------------

#pragma once
#include <exception>
#include <winerror.h>
#include <stdio.h>
#include <string>

// Com_Exceiption
class com_exception : public std::exception
{
private:
	HRESULT result;
	std::string description;

public:
	com_exception(HRESULT hr) : result(hr), description() {}
	com_exception(HRESULT hr, std::string msg) : result(hr), description(msg) {}
	virtual const char* what() const override
	{
		static char str[512]{};
		sprintf_s(str, "Failed with HRESULT : %08X\n%s\n", result, description.c_str());
		return str;
	}
};

// inline 함수 : 호출 스택을 쓰지 않으려고 함.
// 스택을 사용하지 않고 register에 데이터를 잠시 옮겨놓는 것.
// 호출 스택을 무조건 사용하지 않는 것은 아님.
// 매개 변수가 작거나, 가벼운 기능의 함수라면 매우 빠르게 동작할 수 있게 할 수 있음.
// 표기법 : inline / type / 함수 이름 / (매개변수) 
inline void ThrowIfFailed(HRESULT hr, std::string msg = "")
{
	if (FAILED(hr))
	{
		throw com_exception(hr, msg);
	}
}


// ------------ WinMain.cpp ------------

#include <windows.h>
#include "D2DFramework.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpcmdLine, _In_ int nShowcmd)
{
	try
	{
		D2DFramework myFramework;

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

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename) : mpFramework(pFramework), mpBitmap(), mX(), mY(), mOpacity(1.0f)
{
	mpBitmap = BitmapManager::Instance().LoadBitmap(filename);
}

Actor::Actor(D2DFramework* pFramework, LPCWSTR filename, float x, float y, float opacity) : Actor(pFramework, filename)
{
	mX = x;
	mY = y;
	mOpacity = opacity;
}

Actor::~Actor()
{
}

void Actor::Draw(float x, float y, float opacity)
{
	auto pRT = mpFramework->GetRenderTarget();
	if (pRT == nullptr)
	{
		return;
	}

	auto size{ mpBitmap->GetPixelSize() };
	D2D1_RECT_F rect{ x,y,static_cast<float>(x + size.width), static_cast<float>(y + size.height) };

	pRT->DrawBitmap(mpBitmap, rect, opacity);
}

void Actor::Draw()
{
	// 외부에서 매개변수를 사용하기 때문에 사용자가 커스텀이 가능함.
	Draw(mX, mY, mOpacity);
}


// ------------ BitmapManager.cpp ------------

#include "BitmapManager.h"

#pragma comment(lib, "WindowsCodecs.lib")

using namespace std;
using namespace Microsoft::WRL;


HRESULT BitmapManager::LoadWICBitmap(wstring filename, ID2D1Bitmap** ppBitmap)
{
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
	HRESULT hr;

	auto pWICFactory = mspWICFactory.Get();

	if (pWICFactory == nullptr)
	{
		return E_FAIL;
	}

	hr = pWICFactory->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, decoder.GetAddressOf());
	ThrowIfFailed(hr);


	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode>frame;
	ThrowIfFailed(decoder->GetFrame(0, frame.GetAddressOf()));

	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	ThrowIfFailed(pWICFactory->CreateFormatConverter(converter.GetAddressOf()));

	hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom);
	ThrowIfFailed(hr);

	auto pRT = mpRenderTarget;
	if (pRT == nullptr)
	{
		return E_FAIL;
	}
	hr = pRT->CreateBitmapFromWicBitmap(converter.Get(), ppBitmap);
	ThrowIfFailed(hr);

	return S_OK;
}

HRESULT BitmapManager::Initialize(ID2D1HwndRenderTarget* pRT)
{
	if (pRT == nullptr) // if(!pRT)랑 같은 의미!!! 헷갈리지 말 것!!!
	{
		return E_FAIL;
	}

	mpRenderTarget = pRT;

	HRESULT hr = ::CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(mspWICFactory.GetAddressOf()));
	ThrowIfFailed(hr, "WICFactory Create Failed");

	return hr;
}

void BitmapManager::Release()
{
	mBitmapResources.clear();

	mspWICFactory.Reset();
}

ID2D1Bitmap* BitmapManager::LoadBitmap(wstring filename)
{
	if (!mspWICFactory)
	{
		ThrowIfFailed(E_FAIL, "WICFactory must not null");
		return nullptr;
	}

	auto result = mBitmapResources.insert({ filename, nullptr });

	if (result.second == true)
	{
		auto spBitmap = ComPtr<ID2D1Bitmap>();
		LoadWICBitmap(filename, spBitmap.GetAddressOf());
		result.first->second = spBitmap;
	}

	return result.first->second.Get();
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
	HRESULT hr;


	// 범위 해결연산자를 사용할 때 왼쪽부분을 표기하지 않으면 전역에 (global)과 같음.
	// MyClass::CoCreate() -> MyClass에 CoCreate라는 함수가 포함되어있다.
	// ::CoCreate() -> 전역에 있는 CoCreate 함수

	// 기본 버전
	/*if (FAILED(hr))
	{
		ShowError(L"Failed to Create Factory");
		return hr;
	}*/

	// inline 함수를 활용한 버전
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
	ThrowIfFailed(InitD2D(mHwnd), "Failed To InitD2D");


	HRESULT hr = BitmapManager::Instance().Initialize(mspRenderTarget.Get());
	ThrowIfFailed(hr, "Failed To BitmapManager Initialize");

	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);

	return S_OK;
}

void D2DFramework::Release()
{
	BitmapManager::Instance().Release();
	mspRenderTarget.Reset();
	mspD2DFactory.Reset();

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

