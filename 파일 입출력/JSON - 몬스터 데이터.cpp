#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>

using namespace rapidjson;

struct Status
{
	int mLevel{};
	int mHP{};
	int mMP{};
};

struct Item
{
	std::string mName{};
	int mGold{};
};

class Monster
{
private:
	std::string mName;
	Status mStatus;
	std::vector<Item> mItems;

public:
	void SetName(const std::string& name) { mName = name; }
	void SetStatus(const Status& status) { mStatus = status; }
	void AddDropItem(const Item& item) { mItems.push_back(item); }

	std::string& GetName() { return mName; }
	Status& GetStatus() { return mStatus; }
	std::vector<Item>& GetDropItems() { return mItems; }
};

bool SaveJson(const std::string& path, std::vector<Monster>& monsters)
{
	// rapidjson
	// Prettywriter를 stringbuffer에 사용
	StringBuffer sb;
	PrettyWriter<StringBuffer> writer(sb);

	// 중괄호 열기
	writer.StartObject();

	// 중괄호 사이에 내용
	// Key에 해당하는 내용은 무조건 Value가 있어야함.
		writer.Key("monsters");

		writer.StartArray();
			for (auto monster : monsters)
			{
				writer.StartObject();
				{
					writer.Key("name");
					writer.String(monster.GetName().c_str());

					writer.Key("status");
					writer.StartObject();
					{
						auto status = monster.GetStatus();
						writer.Key("level"); writer.Int(status.mLevel);
						writer.Key("hp"); writer.Int(status.mHP);
						writer.Key("mp"); writer.Int(status.mMP);
					}
					writer.EndObject();

					writer.Key("items");
					writer.StartArray();
					for (auto item : monster.GetDropItems())
					{
						writer.StartObject();
						writer.Key("name"); writer.String(item.mName.c_str());
						writer.Key("gold"); writer.Int(item.mGold);
						writer.EndObject();
					}
					writer.EndArray();
				}
				writer.EndObject();
			}
	writer.EndArray();
	// 중괄호 닫기
	writer.EndObject();

	std::ofstream ofs;
	// exceptions
	ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
	try
	{
		ofs.open(path);
		ofs << sb.GetString();
		ofs.close();
	}
	catch (std::ofstream::failure& e)
	{
		std::cerr << "invalid operation in SaveJson" << std::endl;
		std::cerr << e.what() << std::endl;
		ofs.close();
		return false;
	}
	return true;
}

bool LoadJson(const std::string& path, std::vector<Monster>& monsters)
{
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	std::stringstream ss;

	try
	{
		ifs.open(path);

		// rdbuf : read buffer
		// 파일 전체 내용을 가져오는 것.	////////    get, getline은 파일에 있는 내용을 1줄씩 가져오는 것.
		//ifs.rdbuf()
		ss << ifs.rdbuf();

		ifs.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "invalid operation in LoadJson" << std::endl;
		std::cerr << e.what() << std::endl;
		ifs.close();
		return false;
	}

	Document d;
	d.Parse(ss.str().c_str());

	for (auto& e1 : d["monsters"].GetArray())
	{
		//std::cout << e1["name"].GetString() << std::endl;
		Monster monster;
		monster.SetName(e1["name"].GetString());
		Status status;

		status.mLevel = e1["status"].GetObject()["level"].GetInt();
		status.mHP = e1["status"].GetObject()["hp"].GetInt();
		status.mMP = e1["status"].GetObject()["mp"].GetInt();
		monster.SetStatus(status);
		for (auto& itemObject : e1["items"].GetArray())
		{
			Item item;
			item.mName = itemObject["name"].GetString();
			item.mGold = itemObject["gold"].GetInt();
			monster.AddDropItem(item);
		}
		monsters.push_back(monster);
	}
	return true;
}

int main()
{
	std::vector<Monster> monsters;

	Monster m;
	m.SetName("슬라임");
	m.SetStatus({ 1,1,1 });
	m.AddDropItem({ "끈적한 젤리", 1 });
	monsters.push_back(m);

	m.GetDropItems().clear();
	m.SetName("늑대인간");
	m.SetStatus({ 5,5,5 });
	m.AddDropItem({ "발톱", 2 });
	m.AddDropItem({ "늑대가죽", 5 });
	monsters.push_back(m);

	m.GetDropItems().clear();
	m.SetName("악마");
	m.SetStatus({ 10,10,10 });
	m.AddDropItem({ "날개", 10 });
	m.AddDropItem({ "손톱", 5 });
	monsters.push_back(m);

	SaveJson("Data/monsters.json", monsters);

	monsters.clear();

	LoadJson("Data/monsters.json", monsters);
}