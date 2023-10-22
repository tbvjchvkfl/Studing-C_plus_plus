#include<iostream>

class Computer
{
public:
	int mPrice{};
	int mColor{};

private:
	int mPower{};
	char mMainboard{};

private:
	void PowerInfo()
	{
		std::cout << "파워는 " << mPower << "입니다." << std::endl;
	}

public:
	void PriceInfo()
	{
		std::cout << "가격은 " << mPrice << "입니다." << std::endl;
		PowerInfo();
	}
};

int main()
{
	// Instantiate ( 인스턴스 화 ) = 클래스의 오브젝트 화

	Computer myComputer;

	// 인스턴스에서 호출한 함수는 *의 형태로 넘어감.
	// call by reference
	// 자기 자신을 참조할 땐 this를 사용함.
	myComputer.PriceInfo();
}