#include <iostream>
#include <string>

void String_Container()
{
	// string = 문자를 원소로 담고있는 자료구조
	// std::string name;
	std::string str = "abc";

	for (auto e : str)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;

	// str이라는 string 자료구조에 "d"라는 리터럴을 붙이는것.(이어 붙이기)
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

	// C++ 스타일의 문자열을 C 스타일로 변경하는 것.
	const char* a{};
	a = str.c_str();

	std::string countstr = "123";

	// 문자열을 정수형으로 변환 가능
	int x{};
	x = std::stoi(countstr);

	// 정수를 문자열로 변환 가능
	std::string anotherstr;
	anotherstr = std::to_string(x);
}