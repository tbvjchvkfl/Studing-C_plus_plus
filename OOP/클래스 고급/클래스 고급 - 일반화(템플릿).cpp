#include <iostream>
#include "MyClass.h"


// template
// 일반화
// template <typename name>
// 내가 만든 name이라는 타입으로 여러 타입들의 함수를 일반화해서 사용할 수 있음.
// tempalte은 선언한 후 바로 아래 있는 함수 1개에만 적용됨. ( 1개의 template은 1개의 함수와 쌍을 이루어야함. )
// 아래 예시 참고

template <typename T>
T Sum(T x, T y)
{
	T sum;
	sum = x + y;

	return sum;
}


template <typename T>
T Sort(T array[], T left, T right)
{
	int i = left;
	int j = right;
	int pivot = array[(left + right) / 2];

	while (i <= j)
	{
		while (array[i] < pivot)
		{
			i++;
		}
		while (array[j] > pivot)
		{
			j--;
		}
		if (i <= j)
		{
			int& LX = array[i];
			int& RY = array[j];
			int temp = LX;
			LX = RY;
			RY = temp;
			i++;
			j--;
		}
	}

	if (left < j)
	{
		Sort(array, left, j);
	}
	if (i < right)
	{
		Sort(array, i, right);
	}

	return 0;
}

template <typename T>
T Print(T array[], T x)
{
	for (int a = 0; a <= x; a++)
	{
		std::cout << array[a];
	}
	return 0;
}

//// 클래스를 template으로 일반화 시킬 때
//template <typename T>
//class Myclass
//{
//	T mValue;
//public:
//	void Function(T arg);
//};
//
//// 함수의 선언과 정의를 분리할 경우
//template <typename T>
//void Myclass<T>::Function(T arg)
//{
//	T temp = arg;
//	temp += arg;
//}


int main()
{
	// 암시적 표기법
	std::cout << Sum(1, 1) << std::endl;
	std::cout << Sum(1.0f, 1.0f) << std::endl;
	std::cout << Sum('A', 'B') << std::endl;


	// 명시적 표기법
	std::cout << Sum<int>(1, 1) << std::endl;
	std::cout << Sum<float>(1.1f, 1.1f) << std::endl;



	int ARRAY[]{ 1,5,7,6,2 };

	Sort<int>(ARRAY, 0, 4);
	Print<int>(ARRAY, 4);

	MyClass<int> c1;
	c1.Function(10);

}