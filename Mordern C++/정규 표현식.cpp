#include <iostream>
#include <regex> // regular expression

void Regular_Expression()
{
	std::cout << "�̸��� : ";
	std::string email;
	std::cin >> email;


	// (\\w + [\\w\\.] *)@(\\w + [\\w\\.] *)\\.([A - Za - z] + )

	// ���� ǥ����
	std::regex pattern("(\\w+[\\w\\.]*)@(\\w+[\\w\\.]*)\\.([A-Za-z]+)");

	// �ο� ���ͷ� ����
	std::regex pattern(R"(\w+[\w\.]*)@(\w+[\w\.]*)\.([A-Za-z]+)");
	if (std::regex_match(email, pattern))
	{
		std::cout << "�ùٸ� ���� �ּ�" << std::endl;
	}
	else
	{
		std::cout << "��" << std::endl;
	}
}