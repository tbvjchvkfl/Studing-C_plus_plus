#include<iostream>

using namespace std;

int* Ex4(int Array[], int count);

int main()
{
	
}

int* Ex4(int array[], int count)
{
	// pNew��� �̸��� ������ ���� ����
	// �ش� ������ �迭�� ���·� �Ű� ���� count�� �� ��ŭ int Ÿ���� ������ ������. -> ����� ������ n��
	int* pNew = new int[count];

	// �Ű� ���� i�� �� �Լ� �������� �Ű� ���� int count�� ������ �۰� �ݺ��ؼ� ������.
	// int Ÿ���� ������ 1�� �����.   ����� ���� n +1
	for (int i = 0; i < count; ++i) 
	{
		pNew[i] = array[i];
	}

	delete[] pNew;


	return 0;
}

// C���� malloc�� calloc�� ������ C++������ new ~ delete�� ����. 

/* <������ ���� �ϳ��� ������ �� ǥ���.>
    
	int* pointer = nullptr;

	int* pointer = new int;

	~~~

	delete pointer;

	<������ ������ �迭�� ���·� ������ �� ǥ���>

	int* pointer = new int [];

	delete[] pointer;
*/


