Winddow 프로그래밍 기초
- 

<pre>
  <code>
    #include <Windows.h>
    int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _in_ int nShowCmd)
    {
      MessageBox(nullptr, L"Hello World!", L"SimlpleWindow", MB_ICONEXCLAMATION | MB_OK);
      return 0;
    }
  </code>
</pre>
