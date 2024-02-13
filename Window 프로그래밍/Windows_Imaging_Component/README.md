Windows Imaging Component
-
WIC는 마이크로 소프트에서 이미지를 인코딩, 디코딩 등의 처리하기 위해 추가한 low-level API이다.
BMP, GIF, JPEG, PNG등의 포멧들을 읽고 쓸 수 있다.
Windows Vista와 함께 개발되어 이후 버전부터는 추가 설치를 통해 사용이 가능하다.

WIC Initialize
-
WIC는 COM기반이라 초기화를 해주어야 한다.
DirectX와는 다르게 WIC는 윈도우 전용 환경이므로 COM을 완벽히 적용해야 한다.
***CoInitialize()*** 함수를 사용하여 초기화하고, ***CoUnInitialize()*** 를 사용하여 COM 환경을 해제한다.

WIC Decoder
-
WIC를 이용하여 파일을 읽어올 때에는 몇가지 과정이 필요하다.
그 중 첫번째가 디코더를 생성하는 것인데, 디코더 생성은 WICFactory에 ***CreateDecoderFromFilename()*** 함수를 통해 생성한다.

##### <실습 코드 중 일부>
<pre>
  <code>
    HRESULT ImageExample::LoadWICImage(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
    {
      Microsoft::WRL::ComPtr<IWICBitmapDecoder> bimapDecoder;
      HRESULT hr{};

      // 디코더 생성
      hr = mspWICFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, BimapDecoder.GetAddressOf());
      ThrowIfFailed(hr);
    }
  </code>
</pre>

> ### HRESULT IWICImaginFactory::CreateDecoderFromFilename()
> - WIC 디코더를 만드는 함수로 매개변수는 다음과 같다.

|매개변수|이름|설명|
|---|---|---|
|LPCWSTR|wzFilename|null-terminated wide char string|
|const GUID|*pguidVendor|Globally Unique Identifider(중복 되지 않는 고유한 난수)</br>고유의 포멧을 가진 회사별 고유의 디코더를 지정한다.|
|DWORD|dwDesiredAccess|읽기/쓰기/읽기&쓰기 등의 파일 접근 방식을 지정한다.|
|WICDecodeOptions|metadataOptions|메타 데이터 옵션이다.</br>데이터를 설명하기 위한 데이터로 gif처럼 여러장의 이미지가 모여있는 데이터처럼 픽셀 데이터에 대한 추가 데이터가 있는 경우 캐시를 할 것인지, 바로 로딩할 것인지를 결정한다.|
|IWICBitmapDecoder|**ppIDecoder|생성된 디코더를 담을 포인터의 주소이다.|

WIC Frame
-
WIC를 이용하여 파일을 읽어올 때 디코더를 생성했다면 다음은 디코더에서 프레임을 획득해야한다.

##### <실습 코드 중 일부>
<pre>
  <code>
    HRESULT ImageExample::LoadWICImage(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
    {
      Microsoft::WRL::ComPtr<IWICBitmapDecoder> bimapDecoder;
      HRESULT hr{};

      // 디코더 생성
      hr = mspWICFactory->CreateDecoderFromFilename(filename, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, BimapDecoder.GetAddressOf());
      ThrowIfFailed(hr);

      //프레임 획득
      Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
      ThrowIfFailed(bitmapDecoder->GetFrame(0, frame.GetAddressOf()));

      return S_OK;
    }
  </code>
</pre>

> HRESULT IWICBitmapFrameDecode::GetFrame()
> - 생성된 디코더에서 프레임을 가져오는 함수이다.
> - 매개변수는 다음과 같다.

|매개변수|이름|설명|
|---|---|----|
|UINT|index|가져올 프레임 번호를 저장한다.|
|IWICBitmapFrameDecode|**ppIBitmapFrame|디코딩된 프레임을 담을 포인터의 주소이다.|

WIC Converter
-
위 과정을 통해 프레임까지 획득했다면 이제 컨버터를 사용해 데이터를 변환하는 작업을 해주어야한다.

##### <실습 코드 중 일부>
<pre>
  <code>
    HRESULT ImageExample::LoadWICImage(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
    {
      // 포멧 컨버터
      Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
      ThrowIfFailed(mspWICFactory->CreateFormatConverter(converter.GetAddressOf()));

      hr = converter->Initialize(frame.Get(), GUID_WICPixelFromat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom);
      ThrowIfFailed(hr);
    }
  </code>
</pre>

> ### HRESULT IWICImagingFactory::CreateFormatConverter()
> - 컨버터를 생성하는 함수로 매개변수에 컨버터를 담을 포인터의 주소를 넘겨준다.

> ### HRESULT IWICFormatConverter::Initialize()
> - 컨버터를 초기화하는 함수이다.
> - 매개변수는 다음과 같다.

|매개변수|이름|설명|
|---|---|---|
|IWICBitmapSource|*pISource|변환할 비트맵을 지정한다.|
|REFWICPixelFormatGUID|dstFormat|변환 후의 픽셀 포멧을 지정한다.|
|WIFCBitmapDitherType|dither|디더링 타입을 지정한다.|
|IWICPalette|*pIPalette|변환에 적용할 때 사용할 색상 팔레트를 지정한다.|
|double|alphaThresholdPercent|알파값의 임계점을 지정한다.|
|WICBitmapPaletteType|paletteTranslate|변환에 사용할 팔레트 타입을 지정한다.|
