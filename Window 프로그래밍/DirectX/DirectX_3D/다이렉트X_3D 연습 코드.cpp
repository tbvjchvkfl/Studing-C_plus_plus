// ------------ DrawTriangle.h ------------

#pragma once

#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "D3DFramework.h"


class DrawTriangle : public D3DFramework
{
	struct VERTEX
	{
		FLOAT x, y, z;
		FLOAT color[4];
	};

	struct MatrixBuffer
	{
		DirectX::XMMATRIX world;
	};

	Microsoft::WRL::ComPtr<ID3D11InputLayout> mspInputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mspVertexBuffer;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> mspVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mspPixelShader;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> mspTexture; // resource
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mspTextureView;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> mspSamplerState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> mspBlendState;

	Microsoft::WRL::ComPtr<ID3D11Buffer> mspConstantBuffer;

	float mX, mY;
	float mRotationZ;
	DirectX::XMMATRIX mWorld;

public:
	void Initialize(HINSTANCE hInstance, int width = 800, int height = 600) override;
	void Destroy() override;

private:
	void InitTriangle();
	void InitPipeline();

	HRESULT CreateTextureFromBMP();

protected:
	void Update(float delta) override;
	void Render() override;

};




// ------------ D3DFramework.h ------------

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <string>
#include "Timer.h"
#include "Input.h"

class D3DFramework
{
	const std::wstring CLASSNAME{ L"D2DWindowClass" };
	const std::wstring TITLE{ L"Direct3D Example" };

protected:
	int mScreenWidth{ 800 };
	int mScreenHeight{ 800 };
	bool mMinimized{ false };
	bool mMaximized{ false };
	bool mResizing{ false };
	bool mPaused{ false };

	HWND mHwnd{};
	HINSTANCE mInstance{};

	// 타이머
	MyUtil::Timer mTimer;

	// input
	MyUtil::Input mInput;

	// FPS 표시용
	std::wstring mTitleText{};




	// interface DirectX Graphics Infrastructure
	Microsoft::WRL::ComPtr<IDXGISwapChain> mspSwapChain{};
	Microsoft::WRL::ComPtr<ID3D11Device> mspDevice{};
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mspDeviceContext{};

	Microsoft::WRL::ComPtr<ID3D11Texture2D> mspRenderTarget{};
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mspRenderTargetView{};

	Microsoft::WRL::ComPtr<ID3D11Texture2D> mspDepthStencil{};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mspDepthStencilView{};

private:
	void InitWindow(HINSTANCE hInstance);
	void InitD3D();

	// FPS 표시용 함수 
	void CalculateFPS();

protected:
	void OnResize();
	void RenderFrame();
	virtual void Render();
	virtual void Update(float delta);

public:
	virtual void Initialize(HINSTANCE hInstance, int width = 800, int height = 600);
	virtual void Destroy();
	void GameLoop();

public:
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);



// ------------ Input.h ------------

#pragma once
#include <array>

namespace MyUtil
{
	class Input
	{
	private:
		std::array<bool, 256> mKeys;
		int mCursorX, mCursorY;

	public:
		void Initailize();

		void SetKeyDown(unsigned int key);
		void SetKeyUp(unsigned int key);
		void SetCursor(int x, int y);

		bool IsKeyDown(unsigned int key);
		void GetCursor(int& x, int& y);
	};
}


// ------------ Timer.h ------------

#pragma once

namespace MyUtil
{
	class Timer
	{
	private:
		double mdDeltaTime;
		float mfScale;
		bool mbStopped;

		double mdSecondsPerCount;
		long long mllBaseTime;
		long long mllPausedTime;
		long long mllStopTime;
		long long mllPrevTime;
		long long mllCurrTime;

	public:
		Timer();

	public:
		void Start();
		void Stop();
		void Resume();
		void Update();

		float TotalTime() const;
		float DeltaTime() const;
		void SetScale(float scale);
	};
}



// ------------ WinMain.cpp ------------

#include "DrawTriangle.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCMDLine, _In_ int nShowCmd)
{

	DrawTriangle framework;
	framework.Initialize(hInstance);

	framework.GameLoop();

	framework.Destroy();
	
	return 0;
}

// ------------ D3DFramework.cpp ------------

#include <sstream>
#include "D3DFramework.h"

#pragma comment (lib, "d3d11.lib")


void D3DFramework::InitWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc{};

	mInstance = hInstance;
	mTitleText = TITLE;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = CLASSNAME.c_str();
	wc.hInstance = mInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Faild to register window class!", L"Error", MB_OK);
		return;
	}

	RECT wr{ 0,0,mScreenWidth, mScreenHeight };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	mHwnd = CreateWindowEx(
		NULL,
		CLASSNAME.c_str(),
		mTitleText.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (mHwnd == NULL)
	{
		MessageBox(NULL, L"Failed to create window!", L"Error", MB_OK);
		return;
	}

	SetWindowLongPtr(mHwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(mHwnd, SW_SHOW);
	SetForegroundWindow(mHwnd);
	SetFocus(mHwnd);
	UpdateWindow(mHwnd);
}

void D3DFramework::InitD3D()
{
	// 유니폼 초기화를 하지 않을 경우 아래 ZeroMemory를 필수적으로 해주어야함.
	DXGI_SWAP_CHAIN_DESC scd{};
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1; // back buffer count
	scd.BufferDesc.Width = mScreenWidth;
	scd.BufferDesc.Height = mScreenHeight;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = mHwnd;
	scd.SampleDesc.Count = 1; // MSAA : Multi Sampling Anti-Aliasing
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.Windowed = TRUE;

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		mspSwapChain.ReleaseAndGetAddressOf(),
		mspDevice.ReleaseAndGetAddressOf(),
		nullptr,
		mspDeviceContext.ReleaseAndGetAddressOf());

	OnResize();
}

void D3DFramework::CalculateFPS()
{
	static int frameCount{ 0 };
	static float timeElapsed{ 0.0f };

	frameCount++;

	if (mTimer.TotalTime() - timeElapsed >= 1.0f)
	{
		// 1초에 몇번 걸리는지
		float fps = (float)frameCount;

		// 프레임 1개 그릴 때 얼마나 걸리는지
		float mspf = 1000.0f / fps;

		std::wostringstream oss;
		oss.precision(6);
		oss << mTitleText << L" - " << L"FPS : " << fps << ", FrameTime : " << mspf << L"ms";

		// 윈도우 제목 변경
		SetWindowText(mHwnd, oss.str().c_str());

		frameCount = 0;
		timeElapsed += 1.0f;
	}
}

void D3DFramework::OnResize()
{
	ID3D11RenderTargetView* nullViews[]{ nullptr };
	mspDeviceContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);

	mspRenderTargetView.Reset();
	mspDepthStencilView.Reset();
	mspRenderTarget.Reset();
	mspDepthStencil.Reset();
	mspDeviceContext->Flush();

	mspSwapChain->ResizeBuffers(0, mScreenWidth, mScreenHeight, DXGI_FORMAT_UNKNOWN, 0);

	mspSwapChain->GetBuffer(0, IID_PPV_ARGS(mspRenderTarget.ReleaseAndGetAddressOf()));
	mspDevice->CreateRenderTargetView(mspRenderTarget.Get(), nullptr, mspRenderTargetView.ReleaseAndGetAddressOf());

	// Depth Stencil Resource - Texture
	CD3D11_TEXTURE2D_DESC td(
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		mScreenWidth,
		mScreenHeight,
		1,
		1,
		D3D11_BIND_DEPTH_STENCIL
	);

	mspDevice->CreateTexture2D(&td, nullptr, mspDepthStencil.ReleaseAndGetAddressOf());

	// Depth Stencil View
	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvd(D3D11_DSV_DIMENSION_TEXTURE2D);
	mspDevice->CreateDepthStencilView(mspDepthStencil.Get(), &dsvd, mspDepthStencilView.ReleaseAndGetAddressOf());

	// 파이프라인 설정
	mspDeviceContext->OMSetRenderTargets(1,
		mspRenderTargetView.GetAddressOf(),
		mspDepthStencilView.Get());

	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<FLOAT>(mScreenWidth), static_cast<FLOAT>(mScreenHeight));
	mspDeviceContext->RSSetViewports(1, &viewport);
}

void D3DFramework::RenderFrame()
{
	float bg[4]{ 0.0f, 0.2f, 0.4f, 1.0f };

	mspDeviceContext->ClearRenderTargetView(mspRenderTargetView.Get(), bg);
	mspDeviceContext->ClearDepthStencilView(mspDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	Render();
	mspSwapChain->Present(0, 0);

}

void D3DFramework::Render()
{
}

void D3DFramework::Update(float delta)
{
}

void D3DFramework::Initialize(HINSTANCE hInstance, int width, int height)
{
	mScreenWidth = width;
	mScreenHeight = height;
	mPaused = false;

	InitWindow(hInstance);
	InitD3D();
}

void D3DFramework::Destroy()
{
	mspSwapChain->SetFullscreenState(FALSE, nullptr);

	mspDepthStencilView.Reset();
	mspDepthStencil.Reset();
	mspRenderTargetView.Reset();
	mspRenderTarget.Reset();

	mspSwapChain.Reset();
	mspDevice.Reset();
	mspDeviceContext.Reset();

	DestroyWindow(mHwnd);
	UnregisterClass(CLASSNAME.c_str(), mInstance);
}

void D3DFramework::GameLoop()
{
	mTimer.Start();
	mInput.Initailize();

	MSG msg{};
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
			mTimer.Update();

			if (mPaused)
			{
				Sleep(100);
			}
			else
			{
				CalculateFPS();
				Update(mTimer.DeltaTime());
				RenderFrame();
			}
		}
	}
}

LRESULT D3DFramework::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		mInput.SetKeyDown(static_cast<unsigned int> (wParam));
		break;

	case WM_KEYUP:
		mInput.SetKeyUp(static_cast<unsigned int> (wParam));
		break;

	case WM_LBUTTONDOWN:
		mInput.SetKeyDown(VK_LBUTTON);
		break;

	case WM_LBUTTONUP:
		mInput.SetKeyUp(VK_LBUTTON);
		break;

	case WM_MOUSEMOVE:
		mInput.SetCursor(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			mPaused = true;
			mTimer.Stop();
		}
		else
		{
			mPaused = false;
			mTimer.Resume();
		}
		break;

	case WM_PAINT:
		if (mResizing)
		{
			RenderFrame();
		}
		else
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
		}
		break;

	case WM_ERASEBKGND:
		return 1;
		break;

	case WM_ENTERSIZEMOVE:
		mPaused = true;
		mResizing = true;
		mTimer.Stop();
		break;

	case WM_SIZE:
		mScreenWidth = LOWORD(lParam);
		mScreenHeight = HIWORD(lParam);

		if (!mspDevice)
		{
			break;
		}

		if (wParam == SIZE_MINIMIZED)
		{
			if (!mPaused)
			{
				mTimer.Stop();
			}
			mPaused = true;

			mMinimized = true;
			mMaximized = false;
		}
		else if (wParam == SIZE_MAXIMIZED)
		{
			mTimer.Resume();
			mPaused = false;

			mMaximized = true;
			mMinimized = false;
			OnResize();
		}
		else if (wParam == SIZE_RESTORED)
		{
			if (mMinimized)
			{
				mPaused = false;
				mTimer.Resume();

				mMinimized = false;
				OnResize();
			}
			else if (mMaximized)
			{
				mPaused = false;
				mTimer.Resume();

				mMaximized = false;
				OnResize();
			}
			else if (mResizing)
			{

			}
			else
			{
				mPaused = false;
				mTimer.Resume();

				OnResize();
			}
		}
		break;

	case WM_GETMINMAXINFO:
		reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.x = 640;
		reinterpret_cast<MINMAXINFO*>(lParam)->ptMinTrackSize.y = 480;
		break;

	case WM_EXITSIZEMOVE:
		mPaused = false;
		mResizing = false;
		mTimer.Resume();
		OnResize();
		break;

	case WM_MENUCHAR:

		// 전체 화면에서 창모드로 돌아갈 때 소리가 안나게 막아주는 코드
		return MAKELRESULT(0, MNC_CLOSE);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto pFramework = reinterpret_cast<D3DFramework*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	return pFramework->MessageHandler(hwnd, message, wParam, lParam);
}




// ------------ DrawTriangle.cpp ------------

#include <fstream>
#include <vector>
#include "DrawTriangle.h"

#pragma comment (lib, "d3dcompiler.lib")

void DrawTriangle::Initialize(HINSTANCE hInstance, int width, int height)
{
	D3DFramework::Initialize(hInstance, width, height);

	InitTriangle();
	InitPipeline();
	CreateTextureFromBMP();
}

void DrawTriangle::Destroy()
{
	mspTextureView.Reset();
	mspTexture.Reset();
	mspInputLayout.Reset();
	mspBlendState.Reset();
	mspSamplerState.Reset();
	mspVertexBuffer.Reset();
	mspPixelShader.Reset();
	mspVertexShader.Reset();

	D3DFramework::Destroy();
}

void DrawTriangle::InitTriangle()
{
	// 배열의 형태로 만들었을 때

	/*VERTEX vertices[]{
		{ -0.5f,  0.5f, 0.0f, {1.0f, 0.0f, 0.0f, 1.0f}},
		{ 0.5f, 0.5f, 0.0f, {0.0f, 1.0f, 0.0f, 1.0f}},
		{-0.5f, -0.5f, 0.0f, {0.0f, 0.0f, 1.0f, 1.0f}},
		{ 0.5f, -0.5f, 0.0f, {1.0f, 0.0f, 1.0f, 1.0f}}
	};*/

	VERTEX vertices[]{
		{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f},
		{ 0.5f, 0.5f, 0.0f, 1.0f, 0.0f},
		{-0.5f, -0.5f, 0.0f, 0.0f, 1.0f},
		{ 0.5f, -0.5f, 0.0f, 1.0f, 1.0f}
	};

	CD3D11_BUFFER_DESC bd(
		// sizeof(VERTEX)*3, 삼각형 만들기
		sizeof(VERTEX) * 4,
		D3D11_BIND_VERTEX_BUFFER,
		D3D11_USAGE_DYNAMIC,
		D3D10_CPU_ACCESS_WRITE);

	mspDevice->CreateBuffer(&bd, nullptr, mspVertexBuffer.ReleaseAndGetAddressOf());

	D3D11_MAPPED_SUBRESOURCE ms;
	mspDeviceContext->Map(
		mspVertexBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&ms
	);

	memcpy(ms.pData, vertices, sizeof(vertices));
	mspDeviceContext->Unmap(mspVertexBuffer.Get(), 0);

	float border[4]{ 0.0f, 0.0f, 0.0f, 0.0f };
	CD3D11_SAMPLER_DESC sd(
		/*D3D11_FILTER_MIN_MAG_MIP_LINEAR,*/
		D3D11_FILTER_MIN_MAG_MIP_POINT,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		0.0f,
		1,
		D3D11_COMPARISON_ALWAYS,
		border,
		0,
		1
	);
	mspDevice->CreateSamplerState(&sd, mspSamplerState.ReleaseAndGetAddressOf());

	D3D11_BLEND_DESC blendDesc{};
	ZeroMemory(&blendDesc, sizeof(CD3D11_BLEND_DESC));
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	mspDevice->CreateBlendState(&blendDesc, mspBlendState.ReleaseAndGetAddressOf());

	bd = CD3D11_BUFFER_DESC(
		sizeof(MatrixBuffer),
		D3D11_BIND_CONSTANT_BUFFER,
		D3D11_USAGE_DEFAULT
	);
	mspDevice->CreateBuffer(&bd, nullptr, mspConstantBuffer.ReleaseAndGetAddressOf());

	mX = mY = 0.0f;
	mRotationZ = 0.0f;
}

void DrawTriangle::InitPipeline()
{
	// Binary Large Object
	Microsoft::WRL::ComPtr<ID3DBlob> spVS;
	Microsoft::WRL::ComPtr<ID3DBlob> spPS;

	// Vertex Shader ver.
	D3DCompileFromFile(
		L"VertexShader.hlsl",
		0,
		0,
		"main",
		"vs_4_0_level_9_3",
		0,
		0,
		spVS.GetAddressOf(),
		nullptr
	);

	// Pixel Shader ver.
	D3DCompileFromFile(
		L"PixelShader.hlsl",
		0,
		0,
		"main",
		"ps_4_0_level_9_3",
		0,
		0,
		spPS.GetAddressOf(),
		nullptr
	);

	mspDevice->CreateVertexShader(spVS->GetBufferPointer(), spVS->GetBufferSize(), nullptr, mspVertexShader.ReleaseAndGetAddressOf());
	mspDevice->CreatePixelShader(spPS->GetBufferPointer(), spPS->GetBufferSize(), nullptr, mspPixelShader.ReleaseAndGetAddressOf());

	mspDeviceContext->VSSetShader(mspVertexShader.Get(), nullptr, 0);
	mspDeviceContext->PSSetShader(mspPixelShader.Get(), nullptr, 0);

	D3D11_INPUT_ELEMENT_DESC ied[]
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	mspDevice->CreateInputLayout(ied, 2, spVS->GetBufferPointer(), spVS->GetBufferSize(), mspInputLayout.ReleaseAndGetAddressOf());
	mspDeviceContext->IASetInputLayout(mspInputLayout.Get());

	mspDeviceContext->VSSetConstantBuffers(0, 1, mspConstantBuffer.GetAddressOf());
}

HRESULT DrawTriangle::CreateTextureFromBMP()
{
	std::ifstream ifs;
	ifs.open("Textures/Cat.bmp", std::ifstream::binary);

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	ifs.read(reinterpret_cast<char*>(&bfh), sizeof(BITMAPFILEHEADER));
	ifs.read(reinterpret_cast<char*>(&bih), sizeof(BITMAPINFOHEADER));

	std::vector<char> pixels(bih.biSizeImage);
	ifs.seekg(bfh.bfOffBits);
	int pitch = bih.biWidth * (bih.biBitCount / 8);

	char r{}, g{}, b{}, a{};
	int index{};
	for (int y = bih.biHeight - 1; y >= 0; y--)
	{
		// 후에 추가된 코드
		index = y * pitch;
		for (int x = 0; x < bih.biWidth; x++)
		{
			ifs.read(&b, 1);
			ifs.read(&g, 1);
			ifs.read(&r, 1);
			ifs.read(&a, 1);

			if (static_cast<unsigned char>(r) == 30 && static_cast<unsigned char>(g) == 199 && static_cast<unsigned char>(b) == 250)
			{
				pixels[index] = pixels[index + 1] = pixels[index + 2] = pixels[index + 3] = 0;
			}
			else
			{
				pixels[index] = b;
				pixels[index + 1] = g;
				pixels[index + 2] = r;
				pixels[index + 3] = a;
			}

			index += 4;
		}


		// 한줄씩 읽어오는 코드
		// ifs.read(&pixels[y * pitch], pitch);
	}

	ifs.close();

	CD3D11_TEXTURE2D_DESC td(
		DXGI_FORMAT_B8G8R8A8_UNORM,
		bih.biWidth,
		bih.biHeight,
		1,
		1
	);

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &pixels[0];
	initData.SysMemPitch = pitch;
	initData.SysMemSlicePitch = 0;
	mspDevice->CreateTexture2D(&td, &initData, mspTexture.ReleaseAndGetAddressOf());

	CD3D11_SHADER_RESOURCE_VIEW_DESC srvd(
		D3D11_SRV_DIMENSION_TEXTURE2D,
		td.Format,
		0, 1
	);
	mspDevice->CreateShaderResourceView(mspTexture.Get(), &srvd, mspTextureView.ReleaseAndGetAddressOf());

	return S_OK;
}

void DrawTriangle::Update(float delta)
{
	if (mInput.IsKeyDown('Q'))
	{
		mRotationZ += DirectX::XM_PI * delta; // radian, time-base
	}
	else if (mInput.IsKeyDown('E'))
	{
		mRotationZ -= DirectX::XM_PI * delta;
	}

	if (mInput.IsKeyDown(VK_UP) || mInput.IsKeyDown('W'))
	{
		mY += 1.0f * delta;
	}
	else if (mInput.IsKeyDown(VK_DOWN) || mInput.IsKeyDown('S'))
	{
		mY -= 1.0f * delta;
	}

	if (mInput.IsKeyDown(VK_LEFT))
	{
		mX -= 1.0f * delta;
	}
	else if (mInput.IsKeyDown(VK_RIGHT))
	{
		mX += 1.0f * delta;
	}

	if (mInput.IsKeyDown('1'))
	{
		mTimer.SetScale(1.0f);
	}
	else if (mInput.IsKeyDown('2'))
	{
		mTimer.SetScale(2.0f);
	}
	else if (mInput.IsKeyDown('3'))
	{
		mTimer.SetScale(3.0f);
	}

	mWorld = DirectX::XMMatrixIdentity();
	mWorld *= DirectX::XMMatrixRotationZ(mRotationZ);
	mWorld *= DirectX::XMMatrixTranslation(mX, mY, 0.0f);

	if (mInput.IsKeyDown(VK_SPACE))
	{
		mRotationZ = 0.0f;
		mX, mY = 0.0f;
		OutputDebugStringW(L"스페이스\n");
	}
}

void DrawTriangle::Render()
{
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;



	mspDeviceContext->IASetVertexBuffers(0, 1, mspVertexBuffer.GetAddressOf(), &stride, &offset);

	// 삼각형 만들기
	/*mspDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mspDeviceContext->Draw(3, 0);*/

	// 사각형 만들기
	mspDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// PixelShader를 직접 만든 버전
	mspDeviceContext->PSSetSamplers(0, 1, mspSamplerState.GetAddressOf());

	// 그림 그리기
	mspDeviceContext->PSSetShaderResources(0, 1, mspTextureView.GetAddressOf());
	mspDeviceContext->OMSetBlendState(mspBlendState.Get(), nullptr, 0xffffffff);

	MatrixBuffer mb;
	mb.world = DirectX::XMMatrixTranspose(mWorld);
	mspDeviceContext->UpdateSubresource(mspConstantBuffer.Get(), 0, nullptr, &mb, 0, 0);

	mspDeviceContext->Draw(4, 0);


}

// ------------ Input.cpp ------------

#include "Input.h"

using namespace MyUtil;

void Input::Initailize()
{
	mKeys.fill(false);
	mCursorX = mCursorY = 0;
}

void Input::SetKeyDown(unsigned int key)
{
	mKeys[key] = true;
}

void Input::SetKeyUp(unsigned int key)
{
	mKeys[key] = false;
}

void Input::SetCursor(int x, int y)
{
	mCursorX = x;
	mCursorY = y;
}

bool Input::IsKeyDown(unsigned int key)
{
	return mKeys[key];
}

void Input::GetCursor(int& x, int& y)
{
	x = mCursorX;
	y = mCursorY;
}

// ------------ Timer.cpp ------------

#include <Windows.h>
#include "Timer.h"

using namespace MyUtil;

Timer::Timer() : mdDeltaTime{ -1.0 }, mfScale{ 1.0f }, mbStopped{ false }, mdSecondsPerCount{ 0.0 }, mllBaseTime{ 0 }, mllPausedTime{ 0 }, mllStopTime{ 0 }, mllPrevTime{ 0 }, mllCurrTime{ 0 }
{
	long long countsPerSec;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec));

	mdSecondsPerCount = 1.0 / static_cast<double>(countsPerSec);
}

void Timer::Start()
{
	long long currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mllBaseTime = currTime;
	mllPrevTime = currTime;
	mllStopTime = 0;
	mbStopped = false;
}

void Timer::Stop()
{
	if (!mbStopped)
	{
		long long currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		mllStopTime = currTime;
		mbStopped = true;
	}
}

void Timer::Resume()
{
	if (mbStopped)
	{
		long long currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mllPausedTime += (currTime - mllStopTime);
		mllPrevTime = currTime;
		mllStopTime = 0;
		mbStopped = false;
	}
}

void Timer::Update()
{
	if (mbStopped)
	{
		mdDeltaTime = 0.0;
		return;
	}
	long long currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mllCurrTime = currTime;

	mdDeltaTime = (mllCurrTime - mllPrevTime) * mdSecondsPerCount;

	mllPrevTime = mllCurrTime;


	if (mdDeltaTime < 0.0)
	{
		mdDeltaTime = 0.0;
	}
}

float Timer::TotalTime() const
{
	if (mbStopped)
	{
		return static_cast<float>((mllStopTime - mllBaseTime - mllPausedTime) * mdSecondsPerCount);
	}
	else
	{
		return static_cast<float>((mllCurrTime - mllBaseTime - mllPausedTime) * mdSecondsPerCount);
	}
}

float Timer::DeltaTime() const
{
	return static_cast<float>(mdDeltaTime * mfScale);
}

void Timer::SetScale(float scale)
{
	mfScale = scale;
}
