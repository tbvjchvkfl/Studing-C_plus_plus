

**파일 입출력**
-


입출력 스트림
- 
- 컴퓨터가 처리해야할 데이터들이 한꺼번에 많이 몰렸을 경우 컴퓨가 느려지는 현상을 병목 현상이라고한다.</br> 많은 데이터가 몰리게되면 스트림에서 버퍼로 데이터들을 조금씩 꺼내어 출력될 수 있게 하는 스트리밍( 버퍼링 )이라는 아이디어가 등장했는데, std::cin, std::cout 등이 해당된다.
- C++에서는 ios_base와 ios를 기반 클래스로 하고 있고, 기반 클래스를 상속 받아 입력( istream )과 출력( ostream )으로 구분되고,</br> 다시 문자열( istringstream / ostingstream )과 파일( ifilestream / ofilestream )로 구분되어 파생되어있다.</br>덕분에, cin과 cout이 모든 스트림에 적용이 가능하다.

파일 처리
- 
  ## - File Stream
  - **파일 스트림을 사용하는 순서 : 파일 스트림 객체 생성 -> 파일 작업 -> 파일 닫기**
    - ##### 파일 스트림 객체 생성 : 읽기/쓰기 모드를 지정하여 객체를 생성한다. 주로 생성자에서 파일을 지정하거나, 빈 객체를 생성한 후 open()멤버 함수로 연다.
    - ##### 파일 작업 : 스트림 객체에서 데이터를 꺼내오거나 집어넣는 작업을 진행한다.
    - ##### 파일 닫기 : close()멤버 함수를 호출하여 작업이 끝난 파일은 닫아준다. 해당 작업을 하지 않을 경우 해당 파일을 다시 열 수 없다.

<pre>
  <code>
    < 파일 스트림 사용 전체 코드 예시 >
    
    ---SIMPLERDATA---
    Wolf,1,1,1
    Demon,5,5,5
    slime,4,4,4
    -----------------
    
    #inlcude &ltiostream&gt
    #inlcude &ltfstream&gt
    
    bool LoadFile(const std::string& filename, std::vector<Monster>& monsters)
    {
    	std::ifstream ifs;
    	ifs.exceptions(std::ifstream::badbit || std::ifstream::failbit);
    
    	try
    	{
    		ifs.open(filename);
    
    		std::string line;
    		std::getline(ifs, line);
    
    		while (!ifs.eof())
    		{
    			Monster m;
    			m.ReadText(ifs);
    			monsters.push_back(m);
    		}
    		ifs.close();
    	}
    	catch (std::ifstream::failure e)
    	{
    		std::cerr << std::endl << e.code() << " : " << e.what() << std::endl;
    		ifs.close();
    		return false;
    	}
    	return true;
    }
  int main()
  {
    LoadFile("C:/Programmer/cpp/FileSystem/Data/SimpleData.txt"); // 절대 경로 표기법
    LoadFile("Data/SimpleData.txt"); // 상대 경로 표기법
  }
  </code>
</pre>
> ### std::ifstream 인스턴스와 생성자
 - 기본 인스턴스 생성 : std::ifstream filestream;</br></br>- 기본 생성자 : std::ifstream filestream(); -> 파일과 연동되어 있지 않은 빈 객체</br> - 이동 생성자 : std::ifstream filestream(filename&&); </br>- 파일 연동법 : std::ifstream(const char* filename, ios_base_openmode = ios_base::in); -> 파일 연동 시 플래그를 통해 여러개를 지정할 수 있음.

|ios_base_openmode|설명|
|------|---|
|std::ifstream::in|input.</br>기본값으로 파일을 읽기 위해 연다.|
|std::ifstream::out|output.</br>파일을 저장하기 위해 연다.|
|std::ifstream::binary|binary.</br>텍스트 형태가 아닌 바이너리 데이터로 접근.|
|std::ifstream::ate|at end.</br>파일의 가장 끝에서부터 시작.|
|std::ifstream::app|append.</br>기존의 데이터에 이어 붙임. 출력은 파일의 가장 뒤에서부터 이루어짐.|
|std::ifstream::trunc|truncate.</br>기존 내용 전부 삭제.|


 ### - 에러 체크
 - 파일 스트림 객체는 마지막으로 수행한 파일 처리에 대한 결과를 error state flag로 기록해둠.
 - error state flag는 아래 멤버 함수를 통해 확인할 수 있다.
   ##### - good() : 연산 성공</br> - fail() : 예상치 못한 처리 </br> - eof() : 파일의 끝에 도착 ( end of file의 약자로 파일의 끝에 도달했음을 알림 )</br> - bad() : 심각한 오류

|상태|내용|good()|eof()|fail()|bad()|
|----|----|-----|----|----|----|
|goodbit|정상|true||||
|eofbit|파일의 끝에서 연산 시도||true|||
|failbit|논리적인 오류|||true||
|badbit|심각한 입/출력 오류|||true|true|

<pre>
  <code>
    bool LoadFile(const char* filename)
    {
        std::ifstream ist(filename);
        if(!ist.good())
        {
            std::cerr << filename << "파일을 찾을 수 없습니다." << std::endl;
            return false;
        }
        if(!ist.bad())
        {
            std::cerr << "파일이 손상되었습니다." << std::endl;
            ist.close();
            return false;
        }
        if(!ist.fail())
        {
            std::cerr << "잘못된 파일 포멧입니다." << std::endl;
            ist.close();
            return false;
        }
    }
  </code>
</pre>

- exception 멤버 함수
  - 위 내용을 iostream에서는 exception함수를 통해 일반화 할 수 있음.
  - exception 멤버 함수는 지정 한 에러 상태를 탐지해 자동적으로 예외를 발생시켜준다.
<pre>
  <code>
    boll LoadFile(const char* filename)
    {
      std::ifstream ist;
      ist.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      try
      {
        ist.open(filename);
        char ch;
        while(ist.get(ch))
        {
          std::cout << ch;
        }
        ist.close();
     }
     catch(std::ifstream::failure e)
     {
        std::cerr << "파일 연산 도중 예외가 발생했습니다. : " << e. what() << std::endl;
        ist.close();
        return false;                                          
     }
   }                                              
  </code>
</pre>

## - CSV
 - 쉼표로 구분되어있는 파일 형식
 - 추후 테이블 데이터를 읽어 올 때 CSV형식으로 읽어오면 쉽게 읽어올 수 있음.

### - 바이너리 데이터
 - 컴퓨터 메모리에 저장되어 있는 그대로를 파일로 저장하여 암호화 하는 것.
 - 바이너리 데이터를 읽거나 쓸 때에는 기본적으로 char*로 변환하여 사용한다. ( char 배열로 만들어 바이트의 집합으로 사용해야함. )


