프레임 워크 
- 
- 프레임 워크는 '뼈대' 혹은 '체계'를 뜻한다.
- 프로그래밍에서는 특정 운영체제나 특정 그래픽 라이브러리를 위한 응용 프로그램의 표준 구조를 구현한 클래스와 라이브러리를 ***애플리케이션 프레임 워크(Application Framework)*** 라고 부른다.

간단 용어 정리
- 
> ### Library
>  - 프로그램에서 자주 사용할 편리한 함수 및 기능들을 모아 둔 모듈이다.
>  - 쉽게 사용할 수 있도록 정의를 담은 헤더파일(.h)과 컴파일된 라이브러리(.lib) 형태로 제공된다.

> ### Application Programming Interface(API)
>   - 앱 개발을 위해 주로 운영체제에서 필요한 기능들을 제공하는 인터페이스이다.
>   - 앱과 하드웨어를 연결해주는 역할을 한다.

> ### Software Development Kit
>   - API와 거의 같은 의미이지만 개발을 도와주는 다양한 도구들을 제공하기도 한다.

> ### Framework
>   - 위와 같은 도구들을 모아 다양한 앱을 만들 수 있도록 ***앱의 기본 흐름*** 을 규정한다.
>   - 데이터에 사용할 파일 포멧 같은 경우도 프레임워크가 지정한 것을 사용해야한다.


Microsoft::WRL::ComPtr
- 
- ComPtr은 COM 오브젝트에 대한 스마트 포인터 기능이다. Microsoft에 의해 Windows8.x SDK 추가 되었다.
- Microsoft::WRL::ComPtr은 COM오브젝트에 대한 스마트 포인터 템플릿으로 Windows RunTime(WRT) C++ 프로그래밍 에서 사용할 수 있다.
- ComPtr은 std::shared_ptr와 같은 방식으로 내부에 참조 카운트를 가지고 있으며 참조 카운트가 0이 되면 해제되는 방식이다.
- 사용 시 ***#include <wrl.h>*** 나 ***#include<wrl/client.h>*** 를 추가해야한다.
- 일반적인 COM 객체는 팩토리 또는 헬퍼 함수를 통해서 생성되고, 매개변수로 인터페이스에 대한 포인터의 주소(**)를 넘겨주는 형태이다. ComPtr은 이런 특성을 GetAddressOf()메서드를 제공한다. 만약 ComPtr 오브젝트를 클래스 멤버로 사용하고 있고, 이미 초기화가 되어있는지 명확하지 않으면 안전하게 ReleaseAndGetAddressOf()메서드를 사용할 수 있다. 해제는 자동으로 이루어지지만 명시적으로 해제하고 싶다면 Reset()메서드를 사용한다.
- 메서드에 명시적으로 접근할 경우 Get()을 통해 포인터에 접근한다.
- 매개 변수로 사용 시에는 ***void func(const Microsoft::WRL::ComPTR<T>& param);*** 또는  ***void func(T* param);*** 과 같이 사용해야한다. -> ComPtr은 shared_ptr과 방식이 같으므로 그냥 포인터로 넘겨주면 참조 카운트가 증가해버리기 때문!!!

Inline Function (인라인 함수)
- 
함수를 호출할 때 호출스택을 사용하지 않고 바로 함수를 처리한다.
일반적으로 함수가 호출 될 때에는 함수 호출 -> 함수의 주소값을 스택에 저장 -> 매개변수를 스택에 저장 -> 함수 실행 순으로 진행되는데, 
함수의 타입 앞에 inline키워드를 붙이면 함수 호출 시 스택을 사용하지 않고 함수를 실행시킨다.

<예시>
<pre>
  <code>
    #include <iostream>
    inline int func (int a, int b)
    {
      return a+b;
    }
    int main()
    {
      int num{};
      num = func(5,2);
    }
  </code>
</pre>
위 예시 에서 func함수를 인라인 함수로 변경하면 아래와 같이 치환되어 들어간다.

<pre>
  <code>
    #include <iostream>
    int func (int a, int b)
    {
      return a+b;
    }
    int main()
    {
      int num{};
      
      // 인라인 함수 사용으로 인한 치환
      num = 5+2;
    }
  </code>
</pre>

인라인 함수를 사용한다고 해서 무조건 호출 스택을 사용하지 않는 것은 아니지만, 매개변수가 작거나, 가벼운 기능의 함수라면 스택을 사용하지 않고 매우 빠르게 동작할 수 있게 할 수 있다.

WM_CREATE
-
윈도우 프로시져 단계에서 애플리케이션이 CreateWindowEx 또는 CreateWindow 함수를 호출하여 창을 만들 때 발생하는 메시지이다.

Direct2D 리소스
-
하드웨어의 성능을 활용한 그리기 API는 CPU 중심의 리소스들과 CPU에서도 잘 실행되는 그리기 명령들을 가지고 있다. 하지만 그 중 일부만 하드웨어 가속을 지원하는데, 때문에 CPU의 리소스를 사용할 수 있어야한다.

Direct2D에서는 리소스를 크게 2가지로 구분한다.
- 장치 독립적인 리소스 (ID2D1Factory처럼 CPU에서 보관되는 리소스)
- 장치 의존적인 리소스 (ID2D1RenderTarget처럼 GPU에 보관되는 리소스)


장치 손실 (Device Lost)
-
하드웨어 가속 리소스는 빠르고 높은 품질의 결과물을 뽑아내는 만큼 CPU/RAM에 비해 매우 한정적인 GPU/V-RAM을 사용하다보니 리소스 부족 현상을 겪게 된다. 예를 들어 ALT + TAB으로 작업을 전환하거나 시스템 윈도우가 만들어질 때, 절전모드가 작동하거나 다른 앱이 실행되는 등의 현상이 발생하는데, 이를 장치 손실(Device Lost)라고 한다.

