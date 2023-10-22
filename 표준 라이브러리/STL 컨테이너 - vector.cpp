#include <iostream>
#include <vector>


void Vector_Container()
{
	// ���� �迭 �ڷᱸ�� vector
	std::vector<int> v;
	std::vector<int>::iterator itr;

	// push_back(��) : vector�� �ش� ���� �ִ� ��.
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);
	for (auto e : v)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	for (std::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
	{
		std::cout << *itr << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;

	// ������ ���� �������� �ִ� ���� ���� ��.
	v.pop_back();
	v.resize(100);

	// ���� �˰��� ��� ����
	sort(v.begin(), v.end());
}