#include <iostream>

// C++������ ��� ����� public�� Ŭ������ ����ü�� ������.

struct Mystruct
{
	// �� ����������� ���� �ʱ�ȭ �۾��� ���൵ ��.
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
		std::cout << "[������]" << std::endl;
	}

	~mMyClass()
	{
		std::cout << "[�Ҹ���]" << std::endl;
	}
};


class Monster
{
private:
	int mHealth;
	int mLevel;

public:
	// Default Constructor
	// �⺻ ������ ( �Ű� ������ ���� )
	Monster()
	{
		mHealth = 1;
		mLevel = 1;
	}


	// ��� �ʱ�ȭ ����Ʈ
	// ���� �״�� �ʱ�ȭ�ϰ� ���� �� ���
	Monster(int level = 0, int health = 0) : mHealth{ level }, mLevel{ health }
	{

	}
	Monster(int level = 0, int health = 0) : mHealth(level), mLevel(health)
	{
		mLevel = level;
		mHealth = health;
	}


	// �����ڴ� �Լ��� �����ε��� ������.
	// �����ε� - �̸��� ���� �Ű������� �ٸ� �Լ��� ����� ��.
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
	// ����ü�� �ʱ�ȭ�ϴ� ��
	// ����ü�� �ִ� ��� ��� �������� �ʱ�ȭ ����.
	Mystruct s1{};

	std::cout << s1.x << ", " << s1.y << std::endl;





	std::cout << "-------- Start ------------" << std::endl;

	mMyClass c1;

	std::cout << "---------- end --------------" << std::endl;


	// �⺻ �����ڰ� �ƴ� �Ű������� �ִ� �����ڸ� ������� ���
	// Ŭ������ �ν��Ͻ�ȭ�� �� �Լ�ó�� 'Monster m1()' <- �̷������� ǥ���������.
	Monster m1(1,0);
	m1.Print();

	
	MyClass m1{ 1, 2 };

}



// ������, �Ҹ���
// �ν��Ͻ��� ��������� ����������� ������ ����. �����Ҵ��̶� ���� ����.

// **** �Ҹ��� ������ ����!!! �߿�!!!