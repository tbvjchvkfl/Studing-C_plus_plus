#include <iostream>

// C++에서는 모든 멤버가 public인 클래스는 구조체와 동일함.

struct Mystruct
{
	// 각 멤버변수별로 별도 초기화 작업을 해줘도 됨.
	int x;
	int y;
};

class aMyClass
{
	int x;
	int y;

public:
	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};


class mMyClass
{
public:
	mMyClass()
	{
		std::cout << "[생성자]" << std::endl;
	}

	~mMyClass()
	{
		std::cout << "[소멸자]" << std::endl;
	}
};


class Monster
{
private:
	int mHealth;
	int mLevel;

public:
	// Default Constructor
	// 기본 생성자 ( 매개 변수가 없음 )
	Monster()
	{
		mHealth = 1;
		mLevel = 1;
	}


	// 멤버 초기화 리스트
	// 정의 그대로 초기화하고 싶을 때 사용
	Monster(int level = 0, int health = 0) : mHealth{ level }, mLevel{ health }
	{

	}
	Monster(int level = 0, int health = 0) : mHealth(level), mLevel(health)
	{
		mLevel = level;
		mHealth = health;
	}


	// 생성자는 함수의 오버로딩이 가능함.
	// 오버로딩 - 이름이 같고 매개변수가 다른 함수를 만드는 것.
	Monster(int Level)
	{
		mLevel = Level;
		mHealth = 0;
	}

	void Print()
	{
		std::cout << "Health : " << mHealth << std::endl;
		std::cout << "Level : " << mLevel << std::endl;
	}
};

class MyClass
{
public:
	int mX;
	int mY;

	MyClass(int x, int y)
	{
		mX = x;
		mY = y;
	}
};

int main()
{
	// 구조체를 초기화하는 것
	// 구조체에 있는 모든 멤버 변수들을 초기화 해줌.
	Mystruct s1{};

	std::cout << s1.x << ", " << s1.y << std::endl;





	std::cout << "-------- Start ------------" << std::endl;

	mMyClass c1;

	std::cout << "---------- end --------------" << std::endl;


	// 기본 생성자가 아닌 매개변수가 있는 생성자를 사용했을 경우
	// 클래스를 인스턴스화할 때 함수처럼 'Monster m1()' <- 이런식으로 표기해줘야함.
	Monster m1(1,0);
	m1.Print();

	
	MyClass m1{ 1, 2 };

}



// 생성자, 소멸자
// 인스턴스가 만들어지고 사라질때에만 영향이 있음. 동적할당이랑 관련 없음.

// **** 소멸은 생성의 역순!!! 중요!!!