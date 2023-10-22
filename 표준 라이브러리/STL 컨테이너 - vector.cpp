#include <iostream>
#include <vector>


void Vector_Container()
{
	// 동적 배열 자료구조 vector
	std::vector<int> v;
	std::vector<int>::iterator itr;

	// push_back(값) : vector에 해당 값을 넣는 것.
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

	// 벡터의 가장 마지막에 있는 값을 뺴는 것.
	v.pop_back();
	v.resize(100);

	// 정렬 알고리즘 사용 가능
	sort(v.begin(), v.end());
}