Window 프로그래밍 기초
- 
윈도우 프로그래밍은 메인 함수가 기존의 CPP에서의 메인 함수와 다른 형태를 보인다. 이는 마이크로 소프트에서 요구하는 기능들을 사용해야 하기 때문인데, 각 요구 사항들은 다음과 같다.
<pre>
  <code>
    #include &ltWindows.h&gt
    int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _in_ int nShowCmd)
    {
      MessageBox(nullptr, L"Hello World!", L"SimlpleWindow", MB_ICONEXCLAMATION | MB_OK);
      return 0;
    }
  </code>
</pre>

> ### #include <windows.h>
- 윈도우 프로그래밍 헤더
- 윈도우 프로그래밍을 하기 위해 필수적으로 포함해야된다.

> #### int WINAPI WinMain(&#95;In&#95; HINSTANCE hInstance, &#95;In&#95;opt&#95; HINSTANCE hPrevInstance, &#95;In&#95; LPSTR lpCmdLine, &#95;in&#95; int nShowCmd)
- main() 함수의 윈도우 버전
- 윈도우 프로그래밍은 대부분 마이크로 소프트에서 요구하는 기능들을 사용해야하기 때문에 C&#43;&#43;에서는 볼 수 없었던 용어가 등장한다.
- 용어 설명은 아래 표 참고

|용어 설명|내용|
|------|---|
| WINAPI | Windows Application Programming Interface의 약자로 Window OS가 앱을 위해 준비한 기능이라는 뜻이며, WINAPI가 붙은 함수가 운영체제에 의해 관리되는 시스템 함수라는 의미이다. |
| &#95;In&#95; / &#95;In&#95;opt | 윈도우 프로그래밍에서는 매개 변수 앞에 접두어가 붙는다. 이러한 접두어를 SAL(Source code Annotation Language) 즉, 소스 코드 주석 언어라고 부르는데, 포인터와 같은 변수들은 입/출력 구분이 애매하여 용도를 명시하는 기능으로 사용된다.</br> *&#95;In&#95; : 입력 ,  &#95;Out&#95; : 출력 ,  &#95;Inout&#95; : 입출력 , &#95;In&#95;opt&#95; : 선택적 파라미터 |
| HINSTANCE | Handle of Instance의 약자이다. 핸들은 _포인터_이며, 인스턴스는 우리가 만드는 앱의 실행 버전으로 볼 수 있다. 클래스처럼 윈도우 앱들은 하나의 프로그램을 여러개 실행해서 여러개의 인스턴스를 만들 수 있다. |
| LPSTR | Long Pointer to Null-Terminated String의 약자로 윈도우에서 사용하는 8비트 아스키 문자열에 대한 타입을 뜻 한다. C&#43;&#43;에서의 char&#42;와 동일하며, typedef CHAR&#42; LPSTR로 정의 되어 있다. |

- 해당 함수는 모든 윈도우 프로그램의 진입점으로 윈도우 앱이 실행되면 OS가 바로 Winmain함수로 진입해서 프로그램이 실행된다.
- 위 Winmain함수의 매개 변수들은 다음과 같은 기능을 한다.

| 매개 변수 | 내용 |
|----------|------|
| &#95;In&#95; HINSTACNE hInstance | OS가 실행시킨 앱의 현재 인스턴스 핸들 |
| &#95;In&#95;opt&#95; HINSTANCE hPrevInstance | 이전 인스턴스의 핸들. 항상NULL이다.|
| &#95;In&#95;LPSTR lpCmdLine | 명령줄(command line)을 뜻한다. 해당 프로그램을 콘솔창에서 실행시킬 때, 실행 파일 뒤에 추가 명령을 넣을 수 있다. |
| &#95;In&#95; int nShowCmd | 처음 앱을 실행할 때 일반 윈도우로 표시할지, 전체 화면이나 최소화 화면으로 표시할지에 대한 값. |

> #### MessageBox(HWND hwnd, LPCWSTR lpText, LPCWSTR lpCation, UINT uType)
- 화면에 메시지 박스를 하나 보여주는 함수.

| 매개 변수 | 사용 형태 | 내용 |
|----------|------|------|
| HWND hwnd | nullptr | Handle of Window의 약자로 메세지 박스를 소유할 부모 윈도우를 지정하는 용도로 사용됨. nullptr일 경우 운영체제가 메세지 박스를 제어하고, 특정 윈도우를 지정할 경우엔 해당 윈도우의 HWND를 넣으면 됨.| 
| LPCWSTR lpText | L"Hello World" | Long Pointer Constant WCHAR STRing의 약자로 메세지 박스에 표시될 내용을 전달받는다. 확장 문자열에 대한 상수 포인터이기 때문에 L""접두어를 사용하여 표시할 메세지를 입력한다. |
| LPCWSTR lpCaption | L"Simple Window" | 메세지 박스 제목 표시줄에 표시될 내용. |
| UINT uType | MB_ICONEXCLAMATION / MB_OK | 메세지 박스의 형태를 지정한다. 여러가지 형태로 커스텀할 수 있다. 위에서 사용한 형태는 느낌표 아이콘(MB_ICONEXCLAMATION)과 '확인'버튼(MB_OK)이다. |

---

윈도우 프로그래밍 기본
- 
- 윈도우 앱을 만들기 위해서는 반드시 다음과 같은 과정이 필요하다.
1. 윈도우 클래스 등록
2. 윈도우 생성
3. 윈도우 메세지 처리
4. 윈도우 프로시져 작성

<pre>
  <code>
    #include &ltwindows.h&gt

    const wchar_t gClassName[] = L"MyWindowClass";
    LRESULT CALLBACK windowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lParam);

    int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
    {
      // 윈도우 클래스 등록
      HWND hwnd;
      WNDCLASSEX wc;

      ZeroMemory(&wc, sizeof(WNDCLASSEX));

      wc.style = CS_HREDRAW | CS_VREDRAW;
      wc.lpszClassName = gClassName;
      wc.hInstance = hInstance;
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
      wc.lpfnWndProc = WindowProc;
      wc.cbSize = sizeof(WNDCLASSEX);

      if(!RegisterClassEx(&wc))
      {
        MessageBox(nullptr, L"Failed to register window class!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
      }

      // 윈도우 생성
      hwnd = CreateWindowEx(NULL, gClassName, L"Hello Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

      if (hwnd == nullptr)
      {
        MessageBox(nullptr, L"Failed to create window class!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
      }

      ShowWindow(hwnd, nShowCmd);
      UpdateWindow(hwnd);

      // 윈도우 메세지 처리
      MSG msg;
      while (GetMessage(&msg, NULL, 0, 0))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
      return static_cast<int>(msg.wParam);
    }
        
    //윈도우 프로시져 작성
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch(message)
        {
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
  </code>
</pre>

### - 윈도우 클래스 등록
> #### WNDCLASSEX wc;
- Window Class Extra의 약자로 윈도우 클래스의 정보를 담고 있는 구조체이다.
- EX가 붙어있으면 최신 버전이라는 뜻으로 추가 정보들을 담고 있다.

> #### ZeroMemory( &wc, sizeof(WNDCLASSEX));
- 해당 메모리를 0으로 초기화하는 함수이다.
- 첫 번째 파라미터는 초기화할 메모리의 포인터, 두 번째는 초기화할 메모리의 크기이다.
- 마이크로 소프트에서 제공하는 Wrapper 함수로 memset이라는 C++함수를 사용하기 편하게 지정한 것이다.

> #### if(!RegisterClassEx(&wc))
- 윈도우 클래스를 등록하는 함수이다.
- WNDCLASSEX 구조체를 매개변수로 받는다.
- 성공하면 클래스의 ATOM이라는 운영체제에서 고유한 값(정수)을 반환하며, 실패하면 0을 반환한다. 
