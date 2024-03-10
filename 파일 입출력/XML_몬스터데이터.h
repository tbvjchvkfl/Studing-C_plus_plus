#pragma once
#include <string>
#include <vector>
#include "tinyxml2.h"

struct Status
{
	int mLevel{};
	int mHP{};
	int mMP{};
};

struct Item
{
	std::string mName{};
	int mGold;
};

class Monster2
{
private:
	std::string mName{};
	Status mStatus{};
	std::vector<Item>mDropItems{};

public:
	void SetName(std::string name) { mName = name; }
	void SetStatus(const Status status) { mStatus = status; }
	void AddDropItem(const Item& item) { mDropItems.push_back(item); }

	std::string GetName() const { return mName; }

	// 리턴 타입을 참조형으로 사용할 경우 const를 사용할 수 없음.
	Status& GetStatus() { return mStatus; }
	std::vector<Item>& GetDropItems() { return mDropItems; }
};

void SaveXML(std::string path, std::vector<Monster2>& monsters)
{
	using namespace tinyxml2;

	tinyxml2::XMLDocument doc;

	XMLDeclaration* decl = doc.NewDeclaration(R"(xml version = "1.0" encoding = "EUC-KR")");
	doc.LinkEndChild(decl);

	XMLElement* root = doc.NewElement("monsters");

	for (auto& monster : monsters)
	{
		auto monElement = doc.NewElement("monster");
		monElement->SetAttribute("name", monster.GetName().c_str());

		auto statusElement = doc.NewElement("status");

		Status status = monster.GetStatus();
		statusElement->SetAttribute("level", status.mLevel);
		statusElement->SetAttribute("hp", status.mHP);
		statusElement->SetAttribute("mp", status.mMP);
		monElement->LinkEndChild(statusElement);
		//root->LinkEndChild(monElement);

		auto itemsElement = doc.NewElement("items");
		for (auto& item : monster.GetDropItems())
		{
			auto itemElement = doc.NewElement("item");
			itemElement->SetAttribute("name", item.mName.c_str());
			itemElement->SetAttribute("gold", item.mGold);
			itemsElement->LinkEndChild(itemElement);
		}
		monElement->LinkEndChild(itemsElement);
		root->LinkEndChild(monElement);
	}
	doc.LinkEndChild(root);
	doc.SaveFile(path.c_str());
}

void LoadXML(std::string path, std::vector<Monster2>& monsters)
{
	using namespace tinyxml2;

	XMLDocument doc;

	doc.LoadFile(path.c_str());

	auto root = doc.FirstChildElement("monsters");
	for (auto monElement = root->FirstChildElement(); monElement != nullptr; monElement = monElement->NextSiblingElement())
	{
		Monster2 monster;
		monster.SetName(monElement->Attribute("name"));

		auto statusElement = monElement->FirstChildElement("status");
		Status status;
		status.mLevel = statusElement->IntAttribute("level");
		status.mHP = statusElement->IntAttribute("hp");
		status.mMP = statusElement->IntAttribute("mp");
		monster.SetStatus(status);

		auto itemsElement = monElement->FirstChildElement("items");
		for (auto itemElement = itemsElement->FirstChildElement(); itemElement != nullptr; itemElement = itemElement->NextSiblingElement())
		{
			Item item;
			item.mName = itemElement->Attribute("name");
			item.mName = itemElement->Attribute("gold");
			monster.AddDropItem(item);
		}
		monsters.push_back(monster);
	}
}

void TinyXML()
{
	std::vector<Monster2> monsters;

	Monster2 m;
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

	SaveXML("Data/monsters.xml", monsters);

	monsters.clear();

	LoadXML("Data/monsters.xml", monsters);
}