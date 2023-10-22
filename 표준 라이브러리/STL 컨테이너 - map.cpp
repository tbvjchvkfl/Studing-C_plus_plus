#include <iostream>
#include <map>
#include <unordered_map>

void Map_Container()
{
	// --------- Map ---------
	// - 모든 키 값은 정렬되어있음.
	// - 중복된 키 값을 허용하지 않음.

	std::map<int, int> isMap;
	// map에 값을 넣는 방법 : 배열 표기법을 이용해서 키 값을 정하고 해당 키에 값을 대입한다.
	for (int i = 0; i < 5; i++)
	{
		isMap[i] = i + 1;
	}

	std::map<int, std::string> toMap;
	// map에 값을 넣는 방법 : insert 함수를 사용해서 pair를 만든 후 값을 넣는다.
	toMap.insert(std::make_pair<int, std::string>(1, "1초라도 안보이면"));
	toMap.insert(std::make_pair<int, std::string>(2, "2렇게 초조한데"));
	toMap.insert(std::make_pair<int, std::string>(3, "3초는 어떻게 기다려"));


	std::map<std::string, std::string> myMap;
	// insert함수를 사용할 때 pair를 만들지 않고도 값을 넣을 수 있다.
	myMap.insert({ "+", "더하기연산자이면서 이항 연산자입니다." });
	myMap.insert({ ">>", "비트 시프트 연산자입니다." });
	myMap.insert({ "new", "동적 메모리 할당 연산자입니다. delete 주의하세요." });

	std::cout << myMap["+"] << std::endl;
	myMap["-"] = "빼기 연산자입니다.";

	// map에서 값을 제거하는 방법 : erase함수를 사용할 것.
	myMap.erase("-");

	for (auto e : myMap)
	{
		std::cout << e.first << e.second << std::endl;
	}



	// ※ Unorded_map
	//	- map의 자동 정렬 기능으로 인해 성능 저하가 발생할 수 있음.
	//	- map보다 더 빠르다는 장점을 가지고 있는 unorded_map을 사용하면 시간복잡도를 더욱 줄일 수 있음.
}