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
		std::cout << "�Ŀ��� " << mPower << "�Դϴ�." << std::endl;
	}

public:
	void PriceInfo()
	{
		std::cout << "������ " << mPrice << "�Դϴ�." << std::endl;
		PowerInfo();
	}
};

int main()
{
	// Instantiate ( �ν��Ͻ� ȭ ) = Ŭ������ ������Ʈ ȭ

	Computer myComputer;

	// �ν��Ͻ����� ȣ���� �Լ��� *�� ���·� �Ѿ.
	// call by reference
	// �ڱ� �ڽ��� ������ �� this�� �����.
	myComputer.PriceInfo();
}