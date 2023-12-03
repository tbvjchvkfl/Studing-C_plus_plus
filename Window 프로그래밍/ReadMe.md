Winddow 프로그래밍 기초
- 

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

> #include <twindows.h>
> - 윈도우 프로그래밍 헤더

> int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _in_ int nShowCmd)
> - main() 함수의 윈도우 버전
>> WINAPI
>> - Window Application Programming Interface의 약자로 앱에서 사용할 수 있도록 운영체제가 제공하는 기능의 집합
