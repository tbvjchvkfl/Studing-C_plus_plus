#include <iostream>

using namespace std;

// �Լ� ����
void P_Function(int a, int input, int b);
void P_Function_1(int x, int input, int y);


int main()
{
	// �Լ� ȣ��
	P_Function(1, 1, 1);
	P_Function_1(2, 2, 2);
}


// �Լ� ����
void P_Function(int a, int input, int b)
{
	cout << "Test" << endl;
}

void P_Function_1(int x, int input, int y)
{
	cout << "Test1" << endl;
}
