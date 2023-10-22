#pragma once
class Animal
{
protected:
	int mAge;
	int mWeight;

public:
	Animal();
	Animal(int age, int weight);
	~Animal();

	int GetAge() const;
	int GetWeight() const;
	void SetAge(int age);
	void SetWeight(int weight);

	void Sound();
};

//			** ��� **
//			
//				ǥ��� = class "�ڽ� Ŭ���� �̸�" : [���� ������] "�θ� Ŭ���� �̸�"
// 
// 
//			 - ���� -
//			<�θ� Ŭ����>
//			class Parent
//			{
// 
//			};

//			<�ڽ� Ŭ����>
//			class Child : public Parnet
//			{
// 
//			};


class Cat : public Animal
{
public:
	enum BREED
	{
		KOREANSHORT,
		MUNCHKIN,
		RUSSIANBLUE,
		TURKISHANGORA
	};

private:
	BREED mBreed;

public:
	Cat();
	~Cat();

	Cat::BREED GetBreed() const;
	void SetBreed(Cat::BREED breed);

	void Grooming();
};

class Dog : public Animal
{
public:
	enum BREED
	{
		SHITZU,
		JINDOTGAE,
		HURSKY
	};

private:
	BREED mbreed;

public:
	Dog();
	~Dog();
	Dog::BREED GetBreed() const;
	void SetBreed(Dog::BREED breed);

	void Hawling();
};

