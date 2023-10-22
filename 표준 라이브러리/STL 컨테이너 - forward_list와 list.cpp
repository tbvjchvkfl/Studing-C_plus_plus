#include <iostream>
#include <forward_list>

//-------------- Forward List --------------

void Forwardlist_Container()
{
	// �̱� ��ũ�� ����Ʈ�� ���� ����� �ϴ� Forwardlist
	std::forward_list<int> list{ 10, 11, 1, 2 };

	// ������ vector�� ���������
	// forwardlist������ push_front�� ����ؼ� �ڷᱸ���� ���� �߰���.
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
	// ���� ��ũ�� ����Ʈ�� ���� ����� �ϴ� list
	std::list<int> list{ 10, 11, 1, 2 };

	// ���� ��ũ�� ����Ʈ�̹Ƿ� push_back, push_front �� �� ��밡����.
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