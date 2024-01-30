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
