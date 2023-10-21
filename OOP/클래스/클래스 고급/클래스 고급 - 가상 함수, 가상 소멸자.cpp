#include <iostream>

class Character
{
protected:
	int mHP;

public:
	Character() : mHP{ 100 } {}
	virtual ~Character(){}
	
public:
	// ���� �����Լ�
	// �θ� ���� �����Լ��� ���Ǹ� �ڽĿ� !!!�ʼ�������!!! ���־����.
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
		std::cout << "����� Į�� �ֵѷ���." << std::endl;
	}

	void Dead() const override
	{
		std::cout << "���簡 ����ߴ�" << std::endl;
	}

	void DoubleSlash() const
	{
		std::cout << "����� Į�� �ι� �ֵѷ���." << std::endl;
	}
};

class MyClass
{
public:
	int MyMemberFunction(float x)
	{
		std::cout << "����Լ� ȣ��" << std::endl;
		return 0;
	}

	static float MyStaticFunction(int x)
	{
		std::cout << "�����Լ� ȣ��" << std::endl;
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
	
	// �ظ��ϸ� dynamic_cast�� ����ؼ� ����ȯ �� ��.
	// �����ϴϱ�!!!
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