#include <windows.h>
#include <fstream>
#include <vector>
#include <wincodec.h>
#include "D2DFramework.h"

#pragma comment (lib, "WindowsCodecs.lib")

class ImageExample : public D2DFramework
{
	Microsoft::WRL::ComPtr<IWICImagingFactory> mspWICFactory;
	Microsoft::WRL::ComPtr<ID2D1Bitmap>mspBitmap;

private:
	HRESULT LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap);
	HRESULT LoadWIC(LPCWSTR filename, ID2D1Bitmap** ppBitmap);

protected:
	virtual HRESULT CreateDeviceResources() override;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"ImageExample", UINT w = 1024, UINT h = 768) override;
	void Render() override;
	void Release() override;
};



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpcmdLine, _In_ int nShowcmd)
{
	try
	{
		ImageExample myFramework;

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



HRESULT ImageExample::LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
	// 파일 열기
	std::ifstream file;
	file.open(filename, std::ios::binary);

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	file.read(reinterpret_cast<char*>(&bfh), sizeof(BITMAPFILEHEADER));
	file.read(reinterpret_cast<char*>(&bih), sizeof(BITMAPINFOHEADER));

	if (bfh.bfType != 0x4D42)
	{
		return E_FAIL;
	}
	if (bih.biBitCount != 32)
	{
		return E_FAIL;
	}

	// biSizeImage : 픽셀들의 전체 크기 (바이트 수)
	std::vector<char> pixels(bih.biSizeImage);

	file.seekg(bfh.bfOffBits);

	int pitch = bih.biWidth * (bih.biBitCount / 8);
	//file.read(&pixels[0], bih.biSizeImage);
	/*for (int y = bih.biHeight - 1; y >= 0; y--)
	{
		file.read(&pixels[y * pitch], pitch);
	}*/

	int index{};
	for (int y = bih.biHeight - 1; y >= 0; y--)
	{
		index = y * pitch;
		for (int x = 0; x < bih.biWidth; x++)
		{
			char r{}, g{}, b{}, a{};
			file.read(&b, 1);
			file.read(&g, 1);
			file.read(&r, 1);
			file.read(&a, 1);

			if (r == 30 && g == -57 /*199*/ && b == -6 /*250*/)
			{
				r = g = b = a = 0;
			}
			pixels[index++] = b;
			pixels[index++] = g;
			pixels[index++] = r;
			pixels[index++] = a;
		}
	}

	file.close();

	HRESULT hr = mspRenderTarget->CreateBitmap(D2D1::SizeU(bih.biWidth, bih.biHeight), D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)), ppBitmap);
	ThrowIfFailed(hr);

	(*ppBitmap)->CopyFromMemory(nullptr, &pixels[0], pitch);

	return S_OK;
}

HRESULT ImageExample::LoadWIC(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
	Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
	HRESULT hr;

	// 디코더 생성
	hr = mspWICFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, decoder.GetAddressOf()/*디코더 생성*/);
	ThrowIfFailed(hr);

	// 디코더에서 그림 해석 
	// 그림 1장을 가져옴
	Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
	hr = decoder->GetFrame(0, frame.GetAddressOf());
	ThrowIfFailed(hr);

	// 가져온 그림을 BGRA순서로 변경
	Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
	hr = mspWICFactory->CreateFormatConverter(converter.GetAddressOf());
	ThrowIfFailed(hr);

	hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom);
	ThrowIfFailed(hr);


	// 그림 파일을 생성
	hr = mspRenderTarget->CreateBitmapFromWicBitmap(converter.Get(), ppBitmap);
	ThrowIfFailed(hr);

	return S_OK;
}

HRESULT ImageExample::CreateDeviceResources()
{
	D2DFramework::CreateDeviceResources();

	//BMP를 사용하는 경우
	/*HRESULT hr = LoadBMP(L"Images/32.bmp", mspBitmap.ReleaseAndGetAddressOf());
	ThrowIfFailed(hr);*/


	// WIC를 사용하는 경우
	HRESULT hr = LoadWIC(L"Images/32.bmp", mspBitmap.ReleaseAndGetAddressOf());
	ThrowIfFailed(hr);

	return S_OK;
}

HRESULT ImageExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
{
	HRESULT hr = CoInitialize(nullptr);
	hr = ::CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(mspWICFactory.GetAddressOf()));

	ThrowIfFailed(hr);
	D2DFramework::Initialize(hInstance, title, w, h);

	return S_OK;
}

void ImageExample::Render()
{
	mspRenderTarget->BeginDraw();
	mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	mspRenderTarget->DrawBitmap(mspBitmap.Get());

	HRESULT hr = mspRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
	ThrowIfFailed(hr);
}

void ImageExample::Release()
{
	D2DFramework::Release();

	mspBitmap.Reset();
	mspWICFactory.Reset();

	CoUninitialize();
}

// WIC를 사용해서 Direct2D로 이미지를 가져오는 방식

// 1. 디코더를 생성
// 2. 프레임을 획득
// 3. Converter로 데이터를 변환 ( 픽셀포멧 BGRA )
// 4. 위 데이터로 IBITMAP 생성