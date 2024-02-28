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
매개변수는 다음과 같다.
|타입|매개변수|설명|
|---|---|---|
|ID3D11Resource*|pResource|Depth-Stencil에 사용될 리소스 포인터이다.|
|const D3D11_DEPTH_STENCIL_VIEW_DESC*|pDesc|Depth-Stencil View에 대한 설명 구조체 포인터이다.|
|ID3D11DepthStencilView**|ppDepthDSTencilView|생성된 Depth-Stencil View Interface에 대한 포인터이다.|


ID3D11DeviceContext::OMSetRenderTargets()
-
렌더 타겟과 깊이-스텐실 버퍼를 바인딩하는 함수이다.
매개 변수는 다음과 같다.
|타입|변수|설명|
|---|---|---|
|UINT|NumViews|렌더 타겟의 숫자이다.</br>여러개의 렌더 타겟이 있다면 렌더 타겟의 개수를 넣고 다음 인자에 배열을 넘겨주어야한다.|
|ID3D11RenderTargetView* const*|ppRenderTargetViews|뷰의 배열의 포인터를 넘겨주어야한다. 렌더 타겟 뷰의 숫자가 1개면 해당 뷰의 **를 넘겨준다.|
|ID3D11DepthStencilView*|pDepthStencilView|Depth-Stencil View의 포인터를 넘겨준다.|

ID3D11DeviceContext::RSSetViewports()
-
뷰포트를 바인딩하는 함수이다.
RS는 Rasterrizer Stage의 약자로 3차원 공간의 정보를 2차원 이미지로 변환시킨다는 의미이다.
매개변수는 UINT(뷰포트의 개수)타입과 const D3D11_VIEWPORT*(뷰포트의 배열 포인터) 타입의 데이터를 넣어주면 된다.

ID3D11DeviceContext::ClearRenderTargetView()
-
렌더 타겟을 초기화한다.
첫번째 매개변수에는 렌더타겟 뷰에 대한 포인터를 두번째인자에는 지울 색상에 대한 const FLOAT[4]타입을 넣어주면 된다.

ID3D11DeviceContext::ClearDepthStencilView()
-
깊이-스텐실 리소스를 지운다.
매개변수는 다음과 같다.
|타입|변수|설명|
|---|---|---|
|ID3D11DepthStencilView*|pDepthStencilView|지울 Depth-Stencil View Interface에 대한 포인터이다.|
|UINT|ClearFlags|지울 플래그로 어떤 리소스를 지울지 지정할 수 있다. OR연산으로 여러개를 지정하는 것도 가능하다.|
|FLOAT|Depth|Depth Buffer를 지운다.|
|UINT8|Stencil|Stencil Buffer를 지운다.|

IDXGISwapChain::Present()
-
스왑체인을 이용해 화면에 그리는 것으로 SWAP/FLIP과 같은 의미이다.
매개변수는 다음과 같다.
|타입|변수|설명|
|---|---|---|
|UINT|SyncInterval|화면에 보여줄 프레임을 Vertical Blank Interval과 어떻게 동기화 하느냐라는 뜻으로 0일 경우 즉시 화면에 표시, 1~4라면 주사율 중 n번째 Vblank신호에 동기화 한다. Vblank란 디스플레이가 화면을 그리고 난 후 다시 그리기 위해 초기 지점으로 돌아가는 시간을 의미한다.|
|UINT|Flags|프레젠테이션 옵션을 지정한다.|

IDXGISwapChain::SetFullscreenState()
-
현재 만들어진 윈도우를 전체 화면 또는 창모드로 지정할 수 있다.
매개변수로 BOOL타입 변수와 IDXGIOutput* 가 있는데, BOOL 타입 변수로 전체화면/창모드를 지정할 수 있고, IDXGIOutput* 변수로 출력 타겟을 지정할 수있다.(창모드로 설정했을 경우 무조건 NULL을 넘겨주어야한다.)

ID3D11DeviceContext::Flush()
-
명령큐의 모든 명령을 GPU로 보낸다. CPU와 GPU는 물리적으로 분리되어 있는 하드웨어 이므로 명령들을 CPU에 쌓아두었다가 GPU가 가져가는 방식을 취한다. 이 때, CPU/GPU의 속도 차이로 인해 코드가 실행되는 시점에서 아직 처리되지 않은 명령이 남아있는 경우가 있는데, 이 와 같은 경우로 인해 처리되지 못한 명령들을 즉시 GPU에 적용한다.

IDXGISwapChain::ResizeBuffers()
-
백버퍼의 크기를 재설정 한다.
매개 변수는 다음과 같다.
|타입|변수|설명|
|---|---|---|
|UINT|BufferCount|스왑체인의 버퍼 개수(FrontBuffer와 BackBuffer를 모두 포함한 개수)이다. 0을 지정하면 기존에 있던 버퍼 개수를 유지한다.|
|UINT|Width|후면 버퍼의 가로 크기이다.|
|UINT|Height|후면 버퍼의 세로 크기이다.|
|DXGI_FORMAT|NweFormat|변경할 포멧을 지정한다. DXGI_FORMAT_UNKNOWN으로 설명하면 기존 포멧을 유지한다.|
|UINT|SwapChainFlags|스왑체인의 추가 옵션이다. 특별한 설정이 필요없으면 0을 입력하면 된다.|


윈도우 메세지 정리
-

> #### WM_SIZE
> - 윈도우의 크기가 변경될 때 마다 전달된다. 사이즈 변경에는 다음과 같은 특이사항이 있는데, 이 정보들이 wParam으로 전달된다.</br>
>   - SIZE_MINIMIZED : 최소화 되어서 트레이로 내려간다.</br>
>   - SIZE_MAXIMIZED : 최대화 됩니다.</br>
>   - SIZE_RESTORED : 최소화, 최대화가 아닌 상태에서 윈도우 크기가 변경되면 들어온다.

> #### WMENTERSIZEMOVE
> - 사용자가 윈도 테두리를 드래그 해서 사이즈를 조절하려고 할 때 발생한다.

> #### WM_EXITSIZEMOVE
> - 사용자가 윈도우 테두리를 놓으면(Released) 한번 발생한다.

> #### WM_MENUCHAR
> - 메뉴의 단축키가 눌렸는지를 확인하는 메시지이다.

> #### WM_GETMINMAXINFO
> - 사이즈나 위치가 변경되기 직전에 전달되는 메시지이다. 이를 통해 윈도우가 너무 크거나 작아지지 않도록 예외처리를 할 수 있다.

ID3D11Device::CreateBuffer()
-
D3D11_BUFFER_DESC에서 생성한 Description으로 버퍼를 생성한다.
|타입|매개변수|설명|
|---|---|---|
|const D3D11_BUFFER_DESC*|pDesc|버퍼를 설명하는 구조체에 대한 포인터이다.|
|const D3D11_SUBRESOURCE_DATA*|pInitialData|초기 데이터를 저장한 구조체 포인터이다. null을 넘겨주면 미정 상태로 남게되며 사용하기 전 직접 데이터를 채워넣어야 한다.|
|ID3D11Buffer**|ppBuffer|생성한 버퍼 인터페이스의 포인터이다.|

ID3D11DeviceContext::Map()
-
넘겨준 리소스를 매핑하여 매핑된 서브 리소스 구조체를 봔환한다.
|타입|변수|설명|
|---|---|---|
|ID3D11Resource*|pResource|매핑할 리소스이다. 버텍스 버퍼를 넘겨준다.|
|UINT|Subresource|서브 리소스의 인덱스이다.|
|D3D11_MAP|MapType|매핑 방식을 지정한다. 사용자가 지정한 값을 사용하고 이전 값은 버린다. 주로 DYNAMIC버퍼에 사용되며 CPU가 값을 사용하게된다.|
|UINT|MapFlags|추가 옵션으로 GPU가 바빠서 대기하고 있을 때 CPU의 작업을 지정한다.|
|D3D11_MAPPED_SUBRESOURCE*|pMappedResource|매핑된 리소스의 구조체를 돌려준다.|

ID3D11DeviceContext::Unmap()
-
매핑한 리소스를 GPU가 읽어갈 수 있도록 해준다.
첫번째 인자에는 ID3D11Resource*타입의 해제할 ID3D11Resource 인터페이스의 포인터를 두번째 인자에는 UINT타입의 해제될 서브 리소스를 넘겨준다.

D3DCompiileFromFile()
-
셰이더를 컴파일할 때 사용하는 함수이다.
|타입|변수|설명|
|---|---|---|
|LPCWSTR|pFiileName|컴파일 할 HLSL파일 이름을 지정한다.|
|const D3D_SHADER_MACRO*|pDefiines|C에서 #define과 같이 HLSL의 매크로 목록을 넘겨준다.|
|ID3DInclude*|pInclude|HLSL헤더 파일을 지정한다. HLSL코드에 #include와 같은 명령을 사용하면 컴파일 에러가 발생하기 때문에 헤더를 이 곳에서 넘겨주어야 한다. 넘겨줄 헤더가 없을 땐 NULL.|
|LPCSTR|pEntrypoint|엔트리 포인트를 지정한다.(main, Winmain)|
|LPCSTR|pTarget|셰이더 코드의 버전을 지정한다. |
|UINT|Flags1|추가 컴파일 옵션이다.|
|UINT|Falgs2|추가 컴파일 옵션이다.|
|ID3DBlob**|ppCode|컴파일 성공한 바이너리 코드를 돌려준다.|
|ID3DBlob**|ppErrorMsgs|에러 메시지를 담고 있는 블롭니다. 성공하면 NULL을 반환한다.|

ID3D11Device::CreateVertexShader()</br>ID3D11Device::CreatePixelShader()
-
블롭에서 각각 셰이더들의 인터페이스를 구한다.
|타입|변수|설명|
|---|---|---|
|const void*|pShaderBytecode|컴파일된 셰이더코드를 넘겨준다. ID3DBlob의 GetBufferPointer를 호출하면 버퍼의 포인터를 구할 수 있다.|
|SIZE_T|BytecodeLength|컴파일된 셰이더 코드의 바이트 크기를 넘겨준다.|
|ID3D11ClassLiinkage*|pClassLiinkage|#pragma comment("lib", "D3D11.lib")와 같은 기능으로 외부에서 정의되고 구현된 함수등을 함께 사용할 때 "Link"를 해줘야 하는데 이러한 것들을 지정한다.|
|ID3D11VertexShader**/ID3D11PiixelShader**|ppVertexShader/ppPixelShader|생성된 셰이더 인터페이스를 반환한다.|

ID3D11DeviceContext::VSSetShader()</br>ID3D11DeviceContext::PSSetShader()
-
파이프라인에서 VertexShader와 PixelShader 스테이지에 각 Shader들을 지정한다.
|타입|변수|설명|
|---|---|---|
|ID3D11VertexShader*/ID3D11PixelShader*|pVertexShader/pPixelShader|설정할 셰이더 포인터를 넘겨준다. NULL을 넘겨줄 경우 Shader가 비활성화된다.|
|ID3D11ClassInstance*const|ppClassInstance|클래스 인터페이스의 배열을 넘겨준다.|
|UINT|NumClassInstance|클래스 인스턴스의 개수를 지정한다.|


D3D11_INPUT_ELEMENT_DESC
-
InputAssembler에 값을 넘겨주기 위해서는 입력값이 어떤식으로 구성되어 있는지를 알려줘야한다. 이를 입력 레이아웃이라고 부르는데, 이를 이용하여 셰이더 코드에서 각각의 입력이 어떤형태로 구성되어 있는지 판단한다.
