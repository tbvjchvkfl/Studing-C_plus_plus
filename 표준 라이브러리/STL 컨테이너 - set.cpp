#include <iostream>
#include <set>
#include <unordered_set>

void Set_Container()
{
	// 정렬 되어있는 형태임.
	// 데이터들을 자동으로 정렬함.


	// 고유한 값들이 정렬되어있는 것.
	std::set<int>s;
	s.insert(1);
	s.insert(9);
	s.insert(6);
	s.insert(4);


	// 범위 기반 반복문이 되면 iterator가 있다는 뜻
	for (int e : s)
	{
		std::cout << e << std::endl;
	}


	// 고유한 값들이 정렬되어있지 않은 것.
	std::unordered_set <int> us;

	us.insert(1);
	us.insert(8);
	us.insert(4);
	us.insert(3);

	for (int e : us)
	{
		std::cout << e << std::endl;
	}

}