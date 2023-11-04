**Modern C++**
=======
**C++ 11, 14, 20버전에 추가된 신규 내용 및 기능들 정리**
* * *



**C++ 11 - 언어 변경 사항**
-----
### **- auto**  
- 컴파일러가 컴파일 타임에 타입을 특정할 수 있을 경우 타입을 auto로 간략하게 선언할 수 있다.
  <pre>
    <code>
      std::vector<int> v = {1,2,3};
      for(auto e : v)
        {
            std::cout << e << std::endl;
        }

       -> for문에서 사용한 변수 e의 타입은 int로 적용됨.
    </code>
  </pre>

### **- 유니폼 초기화**
  - C++에 존재하는 많은 데이터의 초기화 값을 설정할 때에 '{}'으로 동일한 표기를 할 수 있도록 변화됨.
<pre>
  <code>
    int x = 0;                               => int x {};
    int array[] = {1,2,3};                   => int array{1,2,3];
    int* p = nullptr;                        => int*p {};
    Structure* pStructure = new pStructure;  => Structure* pStructure = new pStructure{};
  </code>
</pre>

### **- 범위 기반 반복문**
  - STL의 순차적 컨테이너의 [begin, end) 순회를 편리하게 할 수 있도록 해주는 반복문
<pre>
  <code>
    std::map myMap;
    for(auto e : myMap)
    {
        std::cout << e.first<< e.second << std::endl;
    }
  </code>
</pre>

### **- 람다식 (Lambda Expression)**
- 익명 함수라는 뜻으로 함수를 이름 없이 정의하는 것을 의미한다.

<pre>
  <code>
    < Lambda Expression의 형태 >
    [Capture](Parameter)Mutable ->typename {body};

    < 사용 예시 >  
    [](int a, int b){return a + b;} // 매개변수 2개를 받는 익명 함수
    
    [](int a)-> int{return result;} // 매개변수 1개와 반환값이 있는 익명 함수
  </code>
</pre>
 > #### [] : 캡쳐절
 > ###### - 람다식에서 외부 변수 사용 유무를 설정하는 부분</br> * [] : 외부 변수 사용 불가 </br> * [=] : 외부 변수를 값으로 사용 </br> * [&] 외부 변수를 참조형으로 사용 

 > #### () : 파라미터
 > ###### - 람다식에서 사용될 매개변수를 정의하는 부분

 > #### mutable
 > ###### 람다식 내부에서 캡쳐한 변수의 값을 변경할 수 있도록 허용하는 키워드

 > #### throw
 > ###### - 예외 사항에 대한 내용

 > #### -> typename : 리턴 값
 > ###### - 람다식의 반환 값이 있는 경우 타입을 지정해주어야함.

 > #### {} : 함수 몸체
 > ###### - 람다식이 수행할 기능을 정의하는 부분

### **- 우측 값 참조**
- 
### **- 이동 생성자**
  - 객체의 값을 다른 객체로 옮기는 것.</br> - 값이 다른 객체로 옮겨가는 것으로 기존 값은 데이터가 유실됨.</br> - 이러한 이동은 원본값이 이름 없는 객체일 때만 발생한다.
<pre>
  <code>
    < 복사 생성자 >
      MyClass(const MyClass&)
    
    < 이동 생성자 >
    MyClass(MyClass&&)
  </code>
</pre>




C++14
[람다](https://github.com/tbvjchvkfl/Studing-C_plus_plus/edit/main/Mordern%20C%2B%2B/Read%20me.md)
