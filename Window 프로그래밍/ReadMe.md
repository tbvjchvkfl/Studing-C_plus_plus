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

> #include <windows.h>
> - 윈도우 프로그래밍 헤더

> int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _in_ int nShowCmd)
> - main() 함수의 윈도우 버전
>> WINAPI
>> - Window Application Programming Interface의 약자로 앱에서 사용할 수 있도록 운영체제가 제공하는 기능의 집합
