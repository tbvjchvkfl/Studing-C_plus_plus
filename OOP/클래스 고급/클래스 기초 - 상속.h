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

//			** 상속 **
//			
//				표기법 = class "자식 클래스 이름" : [접근 제한자] "부모 클래스 이름"
// 
// 
//			 - 예시 -
//			<부모 클래스>
//			class Parent
//			{
// 
//			};

//			<자식 클래스>
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

