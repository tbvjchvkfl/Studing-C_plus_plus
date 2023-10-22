#include <iostream>
#include <map>
#include <unordered_map>

void Map_Container()
{
	// --------- Map ---------
	// - ��� Ű ���� ���ĵǾ�����.
	// - �ߺ��� Ű ���� ������� ����.

	std::map<int, int> isMap;
	// map�� ���� �ִ� ��� : �迭 ǥ����� �̿��ؼ� Ű ���� ���ϰ� �ش� Ű�� ���� �����Ѵ�.
	for (int i = 0; i < 5; i++)
	{
		isMap[i] = i + 1;
	}

	std::map<int, std::string> toMap;
	// map�� ���� �ִ� ��� : insert �Լ��� ����ؼ� pair�� ���� �� ���� �ִ´�.
	toMap.insert(std::make_pair<int, std::string>(1, "1�ʶ� �Ⱥ��̸�"));
	toMap.insert(std::make_pair<int, std::string>(2, "2���� �����ѵ�"));
	toMap.insert(std::make_pair<int, std::string>(3, "3�ʴ� ��� ��ٷ�"));


	std::map<std::string, std::string> myMap;
	// insert�Լ��� ����� �� pair�� ������ �ʰ� ���� ���� �� �ִ�.
	myMap.insert({ "+", "���ϱ⿬�����̸鼭 ���� �������Դϴ�." });
	myMap.insert({ ">>", "��Ʈ ����Ʈ �������Դϴ�." });
	myMap.insert({ "new", "���� �޸� �Ҵ� �������Դϴ�. delete �����ϼ���." });

	std::cout << myMap["+"] << std::endl;
	myMap["-"] = "���� �������Դϴ�.";

	// map���� ���� �����ϴ� ��� : erase�Լ��� ����� ��.
	myMap.erase("-");

	for (auto e : myMap)
	{
		std::cout << e.first << e.second << std::endl;
	}



	// �� Unorded_map
	//	- map�� �ڵ� ���� ������� ���� ���� ���ϰ� �߻��� �� ����.
	//	- map���� �� �����ٴ� ������ ������ �ִ� unorded_map�� ����ϸ� �ð����⵵�� ���� ���� �� ����.
}