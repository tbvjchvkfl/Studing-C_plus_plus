#include <iostream>
#include <string>

void String_Container()
{
	// string = ���ڸ� ���ҷ� ����ִ� �ڷᱸ��
	// std::string name;
	std::string str = "abc";

	for (auto e : str)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	// str�̶�� string �ڷᱸ���� "d"��� ���ͷ��� ���̴°�.(�̾� ���̱�)
	str.append("d");
	for (std::string::iterator itr = str.begin(); itr != str.end(); ++itr)
	{
		std::cout << *itr << " ";
	}
	std::cout << std::endl;

	for (char i = 0; i < str.size(); i++)
	{
		std::cout << str[i] << " ";
	}
	std::cout << std::endl;

	// C++ ��Ÿ���� ���ڿ��� C ��Ÿ�Ϸ� �����ϴ� ��.
	const char* a{};
	a = str.c_str();

	std::string countstr = "123";

	// ���ڿ��� ���������� ��ȯ ����
	int x{};
	x = std::stoi(countstr);

	// ������ ���ڿ��� ��ȯ ����
	std::string anotherstr;
	anotherstr = std::to_string(x);
}