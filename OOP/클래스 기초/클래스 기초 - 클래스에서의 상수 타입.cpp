#include<iostream>



class Grid
{
	int x;
	int y;

public:
	// ��ǥ ���� �Լ�
	void PrintCoordinate();

	// �������� ������ ��ǥ������ �Ÿ��� ���ϴ� �Լ�
	double Distance() const;

	void Setter(int a, int b);
};
int main()
{
	Point p1;
	p1.Set(2, 3);
	p1.Print();
	std::cout << p1.Distance();
}




void Grid::Setter(int a, int b)

{	
	x = a;
	y = b;
}

void Grid::PrintCoordinate()
{
	//std::cin >> x >> y;
	std::cout << "���õ� ��ǥ" << std::endl;
	std::cout << "(" << x << ", " << y << ")" << std::endl;
}

double Grid::Distance() const
{
	std::cout << "�������� ������ ��ǥ������ �Ÿ�" << std::endl;
	std::cout << sqrt(x * x + y * y) << std::endl;
	return sqrt(x * x + y * y);
}

// �ػ�� Ÿ���� ������ ����

// ��� ����
const int LENGTH{ 10 };

// ��� �Ű����� : �Ű������� ���� �ٲ� �� ����.
void Print(const int* x)
{

}

// ��� ��ȯ ��
const int* DoSomethinh()
{

}

// ��� ��� �Լ� : �ش� Ŭ������ ��� �������� ������ �� ����.
class MyClass
{
	int GetCount() const;
};