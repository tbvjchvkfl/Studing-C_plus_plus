#include<iostream>

using namespace std;

int* Ex4(int Array[], int count);

int main()
{
	
}

int* Ex4(int array[], int count)
{
	// pNew라는 이름의 포인터 변수 선언
	// 해당 변수에 배열의 형태로 매게 변수 count의 값 만큼 int 타입의 변수를 선언함. -> 선언된 변수는 n개
	int* pNew = new int[count];

	// 매게 변수 i를 위 함수 포인터의 매게 변수 int count의 값보다 작게 반복해서 더해줌.
	// int 타입의 변수가 1개 선언됨.   선언된 변수 n +1
	for (int i = 0; i < count; ++i) 
	{
		pNew[i] = array[i];
	}

	delete[] pNew;


	return 0;
}

// C에서 malloc과 calloc의 개념이 C++에서는 new ~ delete로 사용됨. 

/* <포인터 변수 하나만 선언할 때 표기법.>
    
	int* pointer = nullptr;

	int* pointer = new int;

	~~~

	delete pointer;

	<포인터 변수를 배열의 형태로 선언할 때 표기법>

	int* pointer = new int [];

	delete[] pointer;
*/


