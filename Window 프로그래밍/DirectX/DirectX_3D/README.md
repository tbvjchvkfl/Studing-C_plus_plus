Direct3D
-
DirectX로 3D 어플리케이션을 만들 때에도 2D때와 같이 순서가 존재한다.

#### [Direct3D 단계]
1. 디바이스 생성
2. 스왑체인 생성
3. 후면 버퍼를 렌더 타겟으로 지정 (렌더 타겟 뷰 생성)
4. 깊이 스텐실 버퍼(Depth-Stencil Buffer) 생성(깊이-버퍼 뷰 생성)
5. 뷰포트를 지정
6. 화면에 그리기
7. 렌더 타겟 지우기
8. Depth-stencil 지우기
9. 실제 그리기
10. 스왑(플립)

##### ※ 해당 문서에서는 DirectX 3D를 공부하고 실습하며 새롭게 배웠던 용어나 기능들에 대한 내용을 정리했다.

#define WIN32_LEAN_AND_MEAN
-
Window 프로그래밍을 할 때 컴파일 속도를 빨라지게 해주는 매크로이다.
Windows API에는 상당히 많은 것들이 정의 되어있어 컴파일 속도가 느려지기 마련인데, LEAN(간결하고)하고 MEAN(평균적인)한 함수들만 사용하겠다는 의미이다.

SetForegroundWindow()
- 
윈도우를 최상단으로 올리고 활성상태로 만들어준다. (작업 표시줄에 내려가 있을 때 클릭하여 올라오는 것과 동일)

SetFocus()
-
지정된 Window에 키보드 포커스를 지정한다. 매개변수로 키보드 입력을 받을 Window의 핸들을 넘겨준다.

IDXGISwapChain
-
Front Buffer와 Back Buffer를 서로 교환하여 각 페이지를 넘길 때 화면이 부드럽게 렌더링되는 것 처럼 보이도록 하기 위한 버퍼들의 모음.

ID3D11Device
-
디바이스란 그래픽 카드를 의미한다. 디스플레이 어댑터라고 표기하기도 한다.

ID3D11DeviceContext
-
디바이스와 연관된 정보라는 뜻이다.
Device Context는 그래픽카드의 GPU와 비디오 메모리 제어 등의 정보를 가지는데, 이를 이용하여 3D화면을 2D로 렌더링 하는 것의 여부와 어떻게 렌더링 될 것 인지도 정할 수 있다.

D3D11CreateDeviceAndSwapChain()
-
디바이스, 디바이스 컨텍스트 스왑 체인 오브젝트를 생성해주는 함수이다.
해당 함수는 HRESULT라는 데이터형을 반환한다.
매개변수는 아래와 같다.
|타입|매개변수|설명|
|---|---|---|
|IDXGIAdapter*|pAdapter|Direct3D에서 사용할 그래픽 카드를 지정한다.|
|D3D_DRIVER_TYPE|DriverType|하드웨어 또는 소프트웨어 렌더링을 사용할 것인지를 지정한다.|
|HMODULE|Software|소프트웨어 렌더링 구동기를 지정한다.|
|UINT|Flags|Direct3D를 어떻게 실행할 것인지에 대한 플래그를 지정한다.|
|const D3D_FEATURE_LEVEL*|pFeatuerLevels|기능 수준을 지정한다.(DirectX 11과 같은 버전을 말함) 기능 수준은 배열로 되어있어 배열의 포인터를 넘겨주면 되지만, Direct3D11을 사용하는 경우 0을 주면 된다.|
|UINT|FeaturesLevels|위 항목과 동일|
|UINT|SDKVersion|사용할 DirectX SDK의 버전을 명시한다.|
|const DXGI_SWAP_CHAIN_DESC*|pSwapChainDesc|스왑체인 구조체|
|IDXGISwapChain**|ppSwapChain|생성된 스왑체인 포인터를 돌려준다. ***반환값이 포인터***이므로 반드시 메모리를 해제해주어야한다.|
|ID3D11Device**|ppDevice|생성된 디바이스의 포인터를 돌려준다. ***반환값은 포인터***|
|D3D_FEATURE_LEVEL*|PFeatureLevel|기능 수준 배열을 반환한다.|
|ID3D11DeviceContext**|ppImmediateContext|생성된 디바이스 컨텍스트의 포인터를 돌려준다. ***반환값은 포인터***|

Resource & Resource View
-
Resource 와 Resource View는 각 데이터의 묶음과 그 데이터 묶음에 대한 설명서라고 볼 수 있다.
리소스는 단순한 메모리의 집합으로 매우 다양한 곳에서 사용할 수 있기 때문에 범용적인 형태가 되어야하는데, DirectX에서 사용되는 리소스는 ID3D11Texture1D, ID3D11Texture2D, ID3D11Texture3D, ID3D11Buffer가 있다.
상황에 따라 다양한 Interface를 해석해서 뷰로 만들 수 있다.

ID3D11Texture2D
-
ID3D11Resource 인터페이스를 상속하며, 2D 이미지 데이터를 저장하고 해당 데이터에 대한 접근을 제공한다.
RenderTarget, Depth-Stencil과 같은 데이터도 ID3D11Texture2D에 포함되어있다. ID3D11Texture2D는 비트맵과 같은 구조다.

ID3D11RenderTargetView
-
Direct3D의 Resource Interface 중 하나로 RenderTarget에 대한 뷰이다.
파이프라인 Stage 중 Output Merger에 속해있다.
RenderTargetView를 생성할 때에는 HRESULT ID3D11Device::CreateRenderTargetView()라는 함수를 사용한다.


ID3D11DepthStencilView
-
Direct3D의 Resource Interface 중 하나로 Depth-Stencil Buffer에 대한 뷰이다.
RenderTargetView와 마찬가지로 파이프라인 Stage 중 Output Merger에 속해있다.
HRESULT ID3D11Device::CreateDepthStencilView()함수를 통해 생성할 수 있다.

IDXGISwapChain::GetBuffer()
-
스왑체인의 버퍼를 가져오는 함수이다.
매개변수는 다음과 같다.
|타입|변수|설명|
|UINT|Buffer|버퍼 인덱스로 0기준이다.|
|REFIID|riid|인터페이스의 타입이다.|
|void **|ppSurface|버퍼로 사용될 인터페이스의 포인터이다.|

ID3D11Device::CreateRenderTargetView()
-
렌더타겟 뷰를 생성하는 함수이다.
CreateRenderTargetView의 매개변수는 다음과 같다.
|타입|매개 변수|설명|
|---|---|---|
|ID3D11Resource*|pResource|렌더 타겟에 대한 포인터이다. D3D11_BIND_RENDER_TARGET 플래그가 설정되어있어야한다.|
|const D3D11_RENDER_TARGET_VIEW_DESC*|pDesc|렌더 타겟 뷰에 대한 설명 구조체 포인터이다. NULL을 지정하면 밉맵 레벨0의 모든 리소스에 접근 가능한 뷰가 생성된다.|
|ID3D11RenderTargetView**|ppRTView|생성된 렌더 타겟 뷰 인터페이스에 대한 포인터이다.|

ID3D11Device::CreateTexture2D()
-
2D 텍스쳐를 생성한다.
해당 함수의 매개변수는 다음과 같다.
|타입|매개변수|설명|
|---|---|---|
|const D3D11_TEXTURE2D_DESC*|pDesc|텍스쳐의 설정을 넘겨줄 구조체 포인터이다.|
|const D3D11_SUBRESOURCE_DATA*|pInitialData|초기값을 지정한다. 리소스의 부분집합인 서브 리소스 데이터 형태로 넘겨주며, NULL인 경우 미정 상태로 생성된다.|
|ID3D11Texture2D**|ppTexture2D|생성된 텍스쳐 인터페이스의 포인터이다.|

ID3D11Device::CreateDepthStencilView()
-
Depth-Stencil View를 생성하는 함수이다.



ID3D11DeviceContext::OMSetRenderTargets()
-

ID3D11DeviceContext::RSSetViewports()
-

ID3D11DeviceContext::ClearRenderTargetView()
-

ID3D11DeviceContext::ClearDepthStencilView()
-

IDXGISwapChain::Present()
-
