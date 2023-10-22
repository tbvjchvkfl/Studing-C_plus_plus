#include <iostream>
#include <set>
#include <unordered_set>

void Set_Container()
{
	// ���� �Ǿ��ִ� ������.
	// �����͵��� �ڵ����� ������.


	// ������ ������ ���ĵǾ��ִ� ��.
	std::set<int>s;
	s.insert(1);
	s.insert(9);
	s.insert(6);
	s.insert(4);


	// ���� ��� �ݺ����� �Ǹ� iterator�� �ִٴ� ��
	for (int e : s)
	{
		std::cout << e << std::endl;
	}


	// ������ ������ ���ĵǾ����� ���� ��.
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