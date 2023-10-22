#include <iostream>
#include "MyClass.h"


// template
// �Ϲ�ȭ
// template <typename name>
// ���� ���� name�̶�� Ÿ������ ���� Ÿ�Ե��� �Լ��� �Ϲ�ȭ�ؼ� ����� �� ����.
// tempalte�� ������ �� �ٷ� �Ʒ� �ִ� �Լ� 1������ �����. ( 1���� template�� 1���� �Լ��� ���� �̷�����. )
// �Ʒ� ���� ����

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

//// Ŭ������ template���� �Ϲ�ȭ ��ų ��
//template <typename T>
//class Myclass
//{
//	T mValue;
//public:
//	void Function(T arg);
//};
//
//// �Լ��� ����� ���Ǹ� �и��� ���
//template <typename T>
//void Myclass<T>::Function(T arg)
//{
//	T temp = arg;
//	temp += arg;
//}


int main()
{
	// �Ͻ��� ǥ���
	std::cout << Sum(1, 1) << std::endl;
	std::cout << Sum(1.0f, 1.0f) << std::endl;
	std::cout << Sum('A', 'B') << std::endl;


	// ����� ǥ���
	std::cout << Sum<int>(1, 1) << std::endl;
	std::cout << Sum<float>(1.1f, 1.1f) << std::endl;



	int ARRAY[]{ 1,5,7,6,2 };

	Sort<int>(ARRAY, 0, 4);
	Print<int>(ARRAY, 4);

	MyClass<int> c1;
	c1.Function(10);

}