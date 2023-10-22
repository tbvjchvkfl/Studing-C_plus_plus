#include <iostream>
#include <array>

void Array_Container()
{
	// array �����̳� ����
	// array<type_name, array_size> struct_name;
	std::array<int, 4> myArray{ 1, 2, 3, 4 };

	// ���� ��� �ݺ��� ��� ����
	for (const auto& e : myArray)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	// Iterator(�ݺ���)�� ���� ù��° ���Һ��� ��ȸ
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