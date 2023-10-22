#include <iostream>

class Character
{
protected:
	int mHP;

public:
	Character() : mHP{ 100 } {}
	virtual ~Character(){}
	
public:
	// 순수 가상함수
	// 부모에 만든 가상함수의 정의를 자식에 !!!필수적으로!!! 해주어야함.
	virtual void Attack() const{}
	virtual void Dead() const {}
};

class Warrior : public Character
{
public:
	Warrior() {}
	~Warrior() {}

public:
	void Attack() const override
	{
		std::cout << "전사는 칼을 휘둘렀다." << std::endl;
	}

	void Dead() const override
	{
		std::cout << "전사가 사망했다" << std::endl;
	}

	void DoubleSlash() const
	{
		std::cout << "전사는 칼을 두번 휘둘렀다." << std::endl;
	}
};

class MyClass
{
public:
	int MyMemberFunction(float x)
	{
		std::cout << "멤버함수 호출" << std::endl;
		return 0;
	}

	static float MyStaticFunction(int x)
	{
		std::cout << "정적함수 호출" << std::endl;
		return 0.0f;
	}
};

using FPtr = int (MyClass::*)(float);
using FPtr2 = float (*)(int);
int main()
{
	Character* p = new Warrior;
	p->Attack();
	
	// ((Warrior*)p)->DoubleSlash();
	// static_cast<Warrior*>(p);
	
	// 왠만하면 dynamic_cast를 사용해서 형변환 할 것.
	// 안전하니까!!!
	Warrior* wp = dynamic_cast<Warrior*>(p);
	if (wp)
	{
		wp->DoubleSlash();
	}
	else
	{
		std::cerr << "Warrior type expected" << std::endl;
	}

	delete p;

	MyClass c;
	FPtr ptr = &MyClass::MyMemberFunction;
	(c.*ptr)(1.1f);

	FPtr2 ptr2 = &MyClass::MyStaticFunction;
	(*ptr2)(1);
}