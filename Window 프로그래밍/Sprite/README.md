Sprite
-
컴퓨터 그래픽에서 2D이미지 중 독립적으로 따로 움직이는 오브젝트를 ***스프라이트***라고 한다.
그러나, 요즘 게임에서는 수천개의 스프라이트를 그리기 때문에 효율적인 관리가 필요하다.

Singleton Pattern
-
싱글톤 패턴이란 디자인 패턴 중 하나로 하나의 관리자만 둔다는 개념이다.
클래스에서 생성자가 여러번 호출되더라도 실제로 생성되는 객체는 하나이고 이후에 또 다시 생성자가 호출되면 최초의 생성자가 생성한 객체를 리턴한다.

#### <싱글톤 패턴 적용 시 주의 사항>
- 스레드 동시성의 문제
  - 여러 클래스의 인스턴스에서 싱글톤 인스턴스에 접근하에 되면 동시성 문제가 발생할 수 있다.
- 앱 종료시까지 메모리에 상주
- 테스트가 어려움
  -  단위 테스트를 진행할 수 없음.
- 순환 종속 발생
  - A는 B의 싱글턴을 사용, B는 A의 인스턴스를 사용하는 경우가 발생하는데, OOP에서는 피하는 개념이다.
- 클래스 확장이 어려움
  - 싱글톤 패턴은 상속이 불가하다.

### [싱글톤 패턴의 기본 뼈대]
##### <코드 예시>
<pre>
  <code>
    class SingletonPattern final
    {
    public:
      static SingletonPattern& Instance()
      {
        static SingletonPattern instance;
        return instance;
      }
      
    private:
      SingletonPattern() {}                         // 기본 생성자
      SingletonPattern(const SingletonPattern&) {}  // 복사 생성자
      void operator=(const SingletonPattern&) {}    // 대입 연산자

    public:
      ~SingletonPattern() {}
      
    public:
      void GenericFunc(); //일반적인 함수
    }
  </code>
</pre>

Interpolation
-
보간. 즉, 도트형태로 찍힌 픽셀 이미지가 원형을 유지할 수 있게 해주는 그래픽 기법이다.
실제로 우리가 보는 이미지는 모눈종이에 찍은 점이지만 정확히 모눈종이에 중앙에 점이 찍히지 않는 경우도 발생하기 마련이다.
이러한 문제를 보완하기 위해 사용된다.

|종류|설명|
|---|---|
|Nearest-neighbor|가장 가까운 픽셀을 선택한다.|
|Linear|2개의 가까운 픽셀을 선택한 다음 선을 그리고 색상을 중간 값으로 만든다.|
|Bilinear|4개의 가까운 픽셀을 선택한 다음 각 픽셀의 평균 색상을 사용한다.|
|Trilinear|8개의 가까운 픽셀을 선택한 다음 평균 색상을 사용한다. 단, x,y,z 좌표 평면을 사용하므로 주로 3D에서 사용된다.|
|Cubic|16개의 픽셀을 선택하여 평균 색상을 사용한다.|
