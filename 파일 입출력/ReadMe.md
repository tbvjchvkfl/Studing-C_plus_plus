
**파일 입출력**
-


입출력 스트림
- 
- 컴퓨터가 처리해야할 데이터들이 한꺼번에 많이 몰렸을 경우 컴퓨가 느려지는 현상을 병목 현상이라고한다.</br> 많은 데이터가 몰리게되면 스트림에서 버퍼로 데이터들을 조금씩 꺼내어 출력될 수 있게 하는 스트리밍( 버퍼링 )이라는 아이디어가 등장했는데, std::cin, std::cout 등이 해당된다.
- C++에서는 ios_base와 ios를 기반 클래스로 하고 있고, 기반 클래스를 상속 받아 입력( istream )과 출력( ostream )으로 구분되고,</br> 다시 문자열( istringstream / ostingstream )과 파일( ifilestream / ofilestream )로 구분되어 파생되어있다.</br>덕분에, cin과 cout이 모든 스트림에 적용이 가능하다.

파일 처리
- 
- 컴퓨터는 용량이 큰 데이터들을 보조기억 장치에 저장하는데, 이는 다음과 같은 특성이있다.
  #### - 비 휘발성 : 전원이 꺼져도 데이터가 남아있음.
  #### - 순차 접근 : 처음 부터 순서대로 데이터에 접근한다.
- 위 특성 중 '순차 접근'으로 인하여 마치 배열과 같은 형로 메모리가 할당된다.
  
< 코드 예시 >

<pre>
  <code>
  #include &lt;iostream&gt;
  #include &lt;fstream&gt;
  bool LoadFile(const char* filename)
  {
    std::ifstream ist(filename);
    if(!ist)
    { 
      std::cerr << filename << "파일을 찾을 수 없습니다. << std::endl;
      return false;
    }
    char ch;
    wile(ist>>ch;)
    {
        std::cout << ch;
    }
    
    ist.close();
    return true;
  }
  </code>
</pre>
