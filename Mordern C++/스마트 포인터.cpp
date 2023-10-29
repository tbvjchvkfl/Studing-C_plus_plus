#pragma once
#include <iostream>

class Warrior
{
public:
	int mHealth;
	int mAttack;
};


//����Ʈ ������

// Unique Pointer
void Unique_ptr()
{
	// C++11
	std::unique_ptr<int> p{ new int };

	*p = 1;

	std::cout << *p << std::endl;


	// C++ 14
	std::unique_ptr<int>p2 = std::make_unique<int>();


	// make_unique���� �����ڸ� �״�� ����� �� ����.
	std::unique_ptr<Warrior>spWarrior = std::make_unique<Warrior>(100, 20);

	std::cout << spWarrior->mAttack << std::endl;

	spWarrior.release();	// delete p;					����⸸ �ϴ� ��
	spWarrior.reset();		// delete p; p = nullptr;		������� �ʱ�ȭ���� �ϴ� ��

	Warrior* ptr = spWarrior.get();		// �Ϲ� ������

}


// Shared Pointer
class Image
{

};

class Demon
{
public:
	int mHealth;
	int mAttack;

	std::shared_ptr<Image> mspImage;

	Demon(int h, int a, std::shared_ptr<Image> spImage) : mHealth{ h }, mAttack{ a }, mspImage{ spImage }
	{

	}
};

int SharedPointer()
{
	std::shared_ptr<Image> spImage = std::make_shared<Image>();
	{
		std::unique_ptr<Demon> spDemon = std::make_unique<Demon>(100, 10, spImage);
		{
			std::unique_ptr<Demon> spDemon2 = std::make_unique<Demon>(100, 10, spImage);
		}
	}
}