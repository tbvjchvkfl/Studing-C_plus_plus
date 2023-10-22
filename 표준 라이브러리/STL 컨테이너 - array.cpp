#include <iostream>
#include <array>

void Array_Container()
{
	// array 컨테이너 사용법
	// array<type_name, array_size> struct_name;
	std::array<int, 4> myArray{ 1, 2, 3, 4 };

	// 범위 기반 반복문 사용 가능
	for (const auto& e : myArray)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	// Iterator(반복자)를 통해 첫번째 원소부터 순회
	for (std::array<int, 4>::iterator itr = myArray.begin(); itr != myArray.end(); ++itr)
	{
		std::cout << *itr << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < myArray.size(); ++i)
	{
		std::cout << myArray[i] << " ";
	}
	std::cout << std::endl;
}