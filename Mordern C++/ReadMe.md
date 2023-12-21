**Modern C++**
=======
**C++ 11, 14, 20버전에 추가된 신규 내용 및 기능들 정리**
* * *



**C++ 11 - 언어 변경 사항**
-----
## **- auto**  
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
<pre>
  <code>
    < 기존 swap 함수 >                       < 우측 값 참조를 적용 시킨 버전 ></우측>
      template < class T >                  template < class T >
        swap(T& a, T& b)                     swap(T&& a, T&& b)
        {                                    {
          T tmp(a);                              T tmp(a);
          a = b;                                 a = b;
          b = tmp;                               b = tmp;
        }                                    }
  </code>
</pre>
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

**C++ STL 변경 사항**
------

### **- 스마트 포인터**
- 기존의 포인터에서 메모리 해제까지 자동으로 수행되는 포인터
> #### std::unique_ptr    [<코드 링크 (Click)>](https://github.com/tbvjchvkfl/Studing-C_plus_plus/blob/main/Mordern%20C%2B%2B/%EC%8A%A4%EB%A7%88%ED%8A%B8%20%ED%8F%AC%EC%9D%B8%ED%84%B0.cpp)
> ###### - 엄격한 소유권 관리를 수행하는 스마트 포인터</br> - 포인터를 저장하고 있는 객체를 소유함.</br> - 복사 생성자, 복사 배정은 지원하지 않음.( 이동 생성자 & 이동 배정은 가능 )


> #### std::shared_ptr [<코드 링크 (Click)>](https://github.com/tbvjchvkfl/Studing-C_plus_plus/blob/main/Mordern%20C%2B%2B/%EC%8A%A4%EB%A7%88%ED%8A%B8%20%ED%8F%AC%EC%9D%B8%ED%84%B0.cpp)
> ###### - 내부에 참조 카운트가 존재하여 사용될 때마다 카운트가 올라가고, 파괴될 때 카운트가 0이 되며 메모리를 해제함.

>#### std::weak_ptr
>###### - shared_ptr을 가리키는 용도로 추가되었다.</br> - shared_ptr의 참조 카운트를 증가시키지 않는다.

> ##### < 포인터 멤버 함수 >
> ###### - unique_ptr::reset()     : 새로운 포인터 지정</br> - unique_ptr::get()       : 현재 포인터를 반환</br> - unique_ptr::release()   : 현재 포인터를 해제

## **- std::tuple**
- std::pair처럼 N개의 원소로 이루어진 집합
<pre>
  <code>
    #include < tuple >
      int main()
      {
          std::tuple<int, std::string, std::string> students;
          students = std::make_tuple(1, "번 학생 : ", "이승민");
          std::cout << "Student Num :" << std::get<0>(students) << std::endl;
          std::cout << "Student Num :" << std::get<0>(students) << std::endl;
          std::cout << "Student Num :" << std::get<0>(students) << std::endl;
      }
  </code>
</pre>
> #### < tuple의 생성 및 접근 법 >
> ###### - std::make_tuple : 튜플 객체를 만들어준다.</br>- std::get< types >(tuple-object) : 튜플 객체의 원소에 접근한다.

### **- 정규 표현식** [<코드 링크 (Click)>](https://github.com/tbvjchvkfl/Studing-C_plus_plus/blob/main/Mordern%20C%2B%2B/%EC%A0%95%EA%B7%9C%20%ED%91%9C%ED%98%84%EC%8B%9D.cpp)
- 특정한 규칙을 갖는 문자열의 집합을 표현하는데 사용하는 형식 언어
<pre>
  <code>
    \"([^\"]*)\"
  </code>
</pre>
> #### \" ....\"
> ###### - 정규표현식이 시작되는 부분.

> #### ( ....* )
> ###### - (  ) : Capture Group으로 또 하나의 패턴을 지정할 때 사용. </br> - * : 0번 이상 반복 된다는 뜻. 해당 패턴이 나타나는 모든 것을 찾는다.

> #### [ ... ]
> ###### - 문자 클래스로 대괄호 안에 있는 내용을 찾는다.

> #### ^\
> ###### - 위 [   ] 안에 들어가는 조건이다.</br> - ^는 Not을 의미하며, 위 식의 조건은 "가 아닌 모든 문자들을 의미한다.

