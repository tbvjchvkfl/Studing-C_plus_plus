#include <iostream>


using namespace std;

// 원소 6개짜리 배열과 정수 타입 변수 2개를 매게변수로 가진 정수 타입의 함수 선언
int F_Add(int array[6], int a, int b);

// 요건 배열의 마지막 원소부터 첫번째 원소까지 더하는 함수^^
int RF_Add(int Rarray[6], int a);

int main()
{
	// 매게 변수로 사용할 임의의 배열을 선언하고, 
	int Arr[6] = { 0,1,2,3,4,5 };

	// F_Add라는 함수를 호출한다.
	cout << Arr[0] << ", " << Arr[1] << ", " << Arr[2] << ", " << Arr[3] << ", " << Arr[4] << ", " << Arr[5] << " = " << F_Add(Arr, 0, 5) << endl;

	int RArr[6] = { 0,1,2,3,4,5 };
	//요건 배열의 마지막 원소부터 첫번 째 원소까지 더하는 함수 ^^
	cout << RArr[5] << ", " << RArr[4] << ", " << RArr[3] << ", " << RArr[2] << ", " << RArr[1] << ", " << RArr[0] << " = " << RF_Add(RArr, 5) << endl;
}


// int a 는 배열의 첫번째 원소를 의미하는 용도로 사용 즉, 시작 지점
// int b 는 배열의 마지막 원소를 의미하는 용도로 사용 즉, 마지막 지점
// 
int F_Add(int array[6], int a, int b)
{
	// 재귀되게 사용할 것이기 때문에 Stack overflow를 방지하기 위해서 시작 지점과 끝나는 지점의 값이 같아질 경우 배열의 마지막 값을 리턴하여 재귀가 끝날 수 있게 해줌.
	if (a == b)
	{
		return array[a];
	}

	// 그렇지 않을 경우 배열의 첫번째 원소부터 마지막 원소까지의 값을 합하는 재귀 함수를 호출한다.
	return array[a] + F_Add(array, a + 1, b);
}

// 요건 배열의 마지막 원소부터 첫번째 원소까지 더하는 함수^^
int RF_Add(int Rarray[6], int a)
{
	if (a <= 0)
	{
		return Rarray[0];
	}

	return Rarray[a] + RF_Add(Rarray, a - 1);
}