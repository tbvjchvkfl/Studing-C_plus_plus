#include <iostream>
#include <forward_list>

//-------------- Forward List --------------

void Forwardlist_Container()
{
	// 싱글 링크드 리스트와 같은 기능을 하는 Forwardlist
	std::forward_list<int> list{ 10, 11, 1, 2 };

	// 사용법은 vector와 비슷하지만
	// forwardlist에서는 push_front를 사용해서 자료구조에 값을 추가함.
	list.push_front(1);
	list.pop_front();

	list.sort();

	for (const auto& e : list)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}


//-------------- List --------------

void List_Container()
{
	// 더블 링크드 리스트와 같은 기능을 하는 list
	std::list<int> list{ 10, 11, 1, 2 };

	// 더블 링크드 리스트이므로 push_back, push_front 둘 다 사용가능함.
	list.push_front(1);
	list.push_back(2);
	list.pop_front();
	list.pop_back();

	list.sort();

	for (const int& e : list)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}