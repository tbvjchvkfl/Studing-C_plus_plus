#include <iostream>
#include <regex> // regular expression

void Regular_Expression()
{
	std::cout << "이메일 : ";
	std::string email;
	std::cin >> email;


	// (\\w + [\\w\\.] *)@(\\w + [\\w\\.] *)\\.([A - Za - z] + )

	// 정규 표현식
	std::regex pattern("(\\w+[\\w\\.]*)@(\\w+[\\w\\.]*)\\.([A-Za-z]+)");

	// 로우 리터럴 버전
	std::regex pattern(R"(\w+[\w\.]*)@(\w+[\w\.]*)\.([A-Za-z]+)");
	if (std::regex_match(email, pattern))
	{
		std::cout << "올바른 메일 주소" << std::endl;
	}
	else
	{
		std::cout << "삑" << std::endl;
	}
}