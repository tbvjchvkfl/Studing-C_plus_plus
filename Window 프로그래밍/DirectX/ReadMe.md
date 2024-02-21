DirectX 2D 프로그래밍 기초
- 
Microsoft에서 제공하는 멀티미디어 종합 라이브러리로 하드웨어에 직접 접근한다는 의미로 Direct라는 용어가 붙었다.
하드 웨어의 성능을 100% 발휘할 수 있게 하여, 높은 품질의 3차원 그래픽을 만들 수 있게 해준다.

> ### DirectX 구성 요소
- Direct2D : 2D 그래픽 표현 API
- Direct3D : 3D 그래픽 표현 API

Direct2D
- 
Derect2D를 사용하기 위해서는 Direct2D 기본 세팅을 해야 한다.

<Direct2D 기본 세팅>
<pre>
  <code>
    #include &ltwindows.h&gt
    #include &ltd2d1.h&gt

    #pragma comment (lib, "d2d1.lib")

    const wchar_t gClassName[] = L"MyWindowClass";
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    ID2D1Factory* gpD2DFactory{};            //Direct2D 전역 변수
    ID2D1HwndRenderTarget* gpRenderTarget{}; //Direct2D 전역 변수
  </code>
</pre>
> #### #include <d2d1.h>
> - Direct2D를 사용하기 위해서는 <d2d1.h>라는 헤더(Windows7에서 시작한 기본 버전)를 포함해주어야한다.

> #### #pragma comment (lib, "d2d1.lib")
> - 위 Direct2D 헤더 파일과 함께 "d2d1.lib"라이브러리를 포함시켜 줘야 한다.

> #### ID2D1Factory* gpD2DFactory{}; </br> ID2D1HwndRenderTarget* gpRenderTarget{};
> - Direct2D 오브젝트들은 프로그램의 시작 ~ 종료까지 관리할 필요가 있다.
> - 예제 용으로 전역변수로 선언했으나, 클래스에 넣어서 사용하는게 더 효율적.
</br>
</br>

Direct2D를 위한 기본 세팅이 끝났다면 Direct2D를 생성해야한다.</br>
Direct2D는 Window를 만들 때의 규칙처럼 다음의 규칙을 따른다.



> ### Direct2D 생성 규칙
> 1. Direct2D Factory 생성
> 2. 렌더 타겟 생성
> 3. 그리기
> 4. 리소스 해제

Direct2D Factory 생성
- 

<pre>
  <code>
    int WINAPI WinMain(_In_HISTANCE hInstance, _In_opt_ HINSTANCE hPrevIstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
    {
      // 1. Direct2D Factory 생성
      HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THERADED, &gpD2DFactory); 
    
      if(FAILED(hr))
      {
        MessageBox(nullptr, L"Failed to create D2D Factory!", L"Error", MB_ICONEXCLAMTION | MB_OK);
        return 0;
      }
    }
    ...
  </code>
</pre>

> ### HRESULT hr = D2D1CreateFactory(__in D2D1_FACTORY_TYPE factoryType, __out Factory **ppIFactory);
> - D2D 팩토리를 생성한다.</br>파라미터의 값은 다음과 같다.

|파라미터| 설명|
|--- |---|
|factoryType| 스레드 형태를 지정하는 열거형 매개변수로 둘 중 하나를 선택해야한다.</br>D2D1_FACTORY_TYPE_SINGLE_THREADED : 단일 스레드</br>D2D1FACTORY_TYPE_MULTI_THREADED : 다중 스레드|
|ppIFactory|생성된 D2D Factory의 포인터에 대한 주소. COM 객체의 함수 호출이 일어난다.|


렌더 타겟 생성
- 
Rendering할 대상을 생성하는 작업이다. 메모리, 파일 등의 대상을 지정할 수 있다.

<pre>
  <code>
    // 2. 렌더 타겟 생성
    GetClientRect(hwnd, &wr);
    hr = gpD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd,D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)), &gpRenderTarget);
    if(FAILED(hr))
      {
        MessageBox(nullptr, L"Failed to create D2D RenderTarget!", L"Error", MB_ICONEXCLAMTION | MB_OK);
        return 0;
      }
  </code>
</pre>

> ### BOOL GetClientRect(HWND hwnd, LPRECT lpRect)
> - 윈도우 핸들로부터 윈도우의 클라이언트 영역을 구해온다.
> - 파라미터는 아래 표 참고

|파라미터|설명|
|---|---|
|hwnd|역역을 구할 윈도우 핸들이다.|
|lpRect|RECT에 대한 포인터이다. left,top멤버는 0이고 right, bottom멤버에 너비, 높이를 지정해서 반환한다.|

> #### HRESULT CreateHwndRenderTarget(&#95;In&#95; CONST D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties, &#95;In&#95; CONST D2D1_HWND_RENDER_TARGET_PROPERTIES *hwndRenderTargetProperties, &#95;COM_Outptr_ID2D1HwndRenderTarget **hwndRenderTarget)
> - 윈도우 핸들에서 렌더타겟을 생성한다. (윈도우 내부에 그래픽을 그리는 것.)

|파라미터|설명|
|---|---|
|renderTargetProperties|렌더 타겟의 특성을 지정한다.</br>D2D1_RENDER_TARGET_PROPERTIES 구조체|
|hwndRenderTargetProperties|윈도우 핸들의 고유 특성</br>D2D1_HWND_RENDERTARGET_PROPERTIES 구조체|
|hwndRenderTarget|생성된 렌더타겟 인터페이스에 대한 포인터의 주소이다.|

> - 위 표에서의 각 구조체는 다음과 같다.

|구조체|설명|
|---|---|
|D2D1RENDER_TARGET_PROPERTIES|---|
|D2D1_RENDER_TARGET_TYPE type;|열거형으로 아래 중 하나를 사용할 수 있다.</br>D2D1_RENDER_TARGET_TYPE_DEFAULT : 가능하면 GPU를 사용한다.</br>D2D_RENDER_TARGET_TYPE_SOFTWARE : CPU를 사용해 렌더링 한다.</br>D2D1_RENDER_TARGET_TYPE_HARDWARE : GPU를 사용해 렌더링한다.|
|D2D1_PIXEL_FORMAT pixelFormat;|화면의 픽셀 하나가 어떤 형태인지를 지정하는 역할로 색상과 투명도를 지정할 수있다.|
|FLOAT dpiX;|가로 dpi|
|FLOAT dpiY;|세로 dpi|
|D2D1_RENDER_TARGET_USAGE usage;|렌더타겟의 용도에 대해 지정한다.</br>D2D1_RENDER_TARGET_USAGE_NONE : GDI호환은 되지않음</br>D2D1_RENDER_TARGET_USAGE_FORCE_BITMAP_REMOTING : BITMAP으로 내부에서 그린 후 원격 클라이언트에 보내는 용도</br>D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE : GDI호환|
|D2D1FEATURE_LEVEL minLevel;|DirectX최소 요구 사항을 지정한다.</br>D2D1_FEATURE_LEVEL_DEFAULT : 특별한 제한을 두지 않음</br>D2D1_FEATURE_LEVEL_9 : DirectX9 호환</br>D2D1_FEATURE_LEVEL_10 : DirectX10 호환|
|D2D1_HWND_RENDER_TARGET_PROPERTIES|---|
|HWND hwnd; | 윈도우 핸들|
|D2D1_SIZE_U pixelSize;|렌더 타겟의 크기</br>Size<UINT32>로 너비와 높이를 지정한다.|
|D2D1_PRESENT_OPTIONS presentOptions;|PRESENT 옵션(렌더링된 이미지를 사용자에게 보여줄 때의 옵션을 지정)|

그리기
-
<pre>
  <code>
    void OnPaint(HWND hwnd)
    {
      HDC hdc;
      PAINTSTRUCT ps;
      hdc = BeginPaint(hwnd, &ps);

      // 3. 그리기
      gpRenderTarget->BeginDraw();
      gpRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
      gpRenderTarget->EndDraw();

      EndPaint(hwnd, &ps);
    }
  </code>
</pre>

> ### gpRenderTarget->BeginDraw();</br>gpRenderTarget->EndDraw();
> - 렌더 타겟에 그릴 준비를 한다. GDI와 처럼 시작과 끝을 지정하면, gpRenderTarget내부에서 필요한 작업들을 수행한다.

> ### gpRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));
> - Clear() 메서드는 렌더 타겟의 화면을 특정 색상으로 지우는 기능을 한다.</br>ColorF는 기존의 COLORREF와 달리 0.0f~1.0f로 범위를 표현한다.(ColorF(red, green, blue, alpha)순)

메모리 해제
- 
<pre>
  <code>
    int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
    {
      MSG msg;
      while(GetMessage(&mgs, NULL, 0, 0))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }

      // 4. 메모리 해제
      if(gpRenderTarget != nullptr)
      {
        gpRenderTarget->Release();
        gpRenderTarget = nullptr;
      }
      if(gpD2DFactory != nullptr)
      {
        gpD2DFactory->Release();
        gpD2DFactory = nullptr;
      }
      return (int)msg.wParam;
    }
  </code>
</pre>

> ### if(gpRenderTarget != nullptr)
> - 인터페이스가 nullptr이 아닌지 확인

> ### gpRenderTarget->Release();
> - 인터페이스의 Release를 호출

> ### gpRenderTarget = nullptr;
> - 인터페이스를 초기화

COM (Component Object Model)
- 
- 프로그래밍 기법 중 하나로 재사용이 가능한 ***컴포넌트***를 만들어 배포를 쉽게 해준다.
> COM의 특성
> - COM 오브젝트는 인터페이스에 의해 실행되는 ***클래스*** 또는 ***클래스 집합***이다.
> - 인터페이스는 ***가상함수***의 집합니다.
> - 인터페이스는 IDirect3DDevice처럼 'I' 접두어가 붙는다.
> - 각 오브젝트 및 인터페이스는 고유의 ID 값을 갖는다.(IID_ 접두어가 붙는 것들)
> - C++ 객체와 같은 방식으로 생성할 수 없다.
>   - DirectX API의 헬퍼 함수들을 사용함.
>   - 객체의 수명도 COM 방식이 따로 존재함.
>   - 사용 후에는 반드시 Release()함수를 호출해야함.
> - COM 오브젝트의 멤버함수들은 결과 코드를 나타내는 HRESULT를 반환한다.
>   - 32비트 정수로 성공/ 실패 여부 및 기타 정보를 나타냄.
>   - Winerror.h에 정의되어있음.
>   - 성공은 S_, 실패는 E_로 시작한다.(S_OK, E_FAIL)

