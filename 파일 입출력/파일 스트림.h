#pragma once
#include <iostream>

// 파일 스트림 헤더 파일
#include <fstream>


#include <sstream>
#include <vector>

struct Header
{
	int Version{ 1 };
	int ItemCount{};
};

class Monster
{
private:
	std::string mName{};
	int mLevel{};
	int mHP{};
	int mMP{};

public:
	// 기본 생성자 꼭 기억할 것
	Monster() = default;

	Monster(std::string name, int level, int hp, int mp) : mName{ name }, mLevel{ level }, mHP{ hp }, mMP{ mp }
	{
	}

	void SetName(std::string name) { mName = name; }
	void SetLevel(int level) { mLevel = level; }
	void SetHP(int hp) { mHP = hp; }
	void SetMP(int mp) { mMP = mp; }

	void ReadText(std::istream& is)
	{
		std::string line;

		try
		{
			std::getline(is, line, ',');
			mName = line;
			std::getline(is, line, ',');
			mLevel = std::stoi(line);
			std::getline(is, line, ',');
			mHP = std::stoi(line);
			std::getline(is, line);
			mMP = std::stoi(line);
		}
		catch (std::exception e)

		{
			std::cerr << "파일 구조가 올바르지 않습니다." << std::endl;
		}
	}
	void WriteText(std::ostream& os)
	{
		os << mName << "," << mLevel << "," << mHP << "," << mMP << std::endl;
	}

	void WriteBinary(std::ostream& os)
	{
		int nameLen = static_cast<int>(mName.size());
		os.write(reinterpret_cast<char*>(&nameLen), sizeof(int));
		os.write(mName.c_str(), nameLen);
		os.write(reinterpret_cast<char*>(&mLevel), sizeof(int));
		os.write(reinterpret_cast<char*>(&mHP), sizeof(int));
		os.write(reinterpret_cast<char*>(&mMP), sizeof(int));
	}

	void ReadBinary(std::istream& is)
	{
		int nameLen{};
		is.read(reinterpret_cast<char*>(&nameLen), sizeof(int));
		is.read(&mName[0], nameLen);
		is.read(reinterpret_cast<char*>(mLevel), sizeof(int));
		is.read(reinterpret_cast<char*>(mHP), sizeof(int));
		is.read(reinterpret_cast<char*>(mMP), sizeof(int));
	}

	friend std::ostream& operator << (std::ostream& os, Monster& m)
	{
		m.WriteText(os);
		return os;
	}

	friend std::istream& operator >> (std::istream& is, Monster& m)
	{
		m.ReadText(is);
		return is;
	}
};


bool LoadFile(const std::string& filename, std::vector<Monster>& monsters)
{


	std::ifstream ifs;
	//ifs.exceptions(std::ifstream::badbit || std::ifstream::failbit);

	try
	{
		ifs.open(filename);

		std::string line;
		std::getline(ifs, line);


		// delimiter
		// getline에서 delimiter를 만나면 읽기를 멈춤 
		while (!ifs.eof())
		{
			Monster m;
			m.ReadText(ifs);

			monsters.push_back(m);
		}
		ifs.close();
	}

	catch (std::ifstream::failure e)
	{
		std::cerr << std::endl << e.code() << " : " << e.what() << std::endl;
		ifs.close();
		return false;
	}



	//// file stream
	//std::ifstream ifs(filename);

	//// file operation
	//char ch;

	//while (ifs >> ch)
	//{
	//	std::cout << ch;
	//}

	//while (ifs.get(ch))
	//{
	//	std::cout << ch;
	//}
	//while (true)
	//{
	//	ifs.get(ch);

	//	if (ifs.eof())
	//	{
	//		if (ifs.eof())
	//		{
	//			std::cerr << "end of file!!" << std::endl;
	//			break;
	//		}

	//		if (ifs.fail())
	//		{
	//			std::cerr << "logical error!" << std::endl;
	//		}
	//		if (ifs.bad())
	//		{
	//			std::cerr << "fatal error!" << std::endl;
	//		}

	//	}
	//}
	///*char buffer[1024];
	//while(ifs.getline(buffer, 1024))
	//{
	//	std::cout << buffer;
	//}*/


	///*while (true)
	//{
	//	ifs >> ch;
	//	if (ifs.eof())
	//	{
	//		break;
	//	}
	//	std::cout << ch;
	//}*/

	//// close file
	//ifs.close();
	return true;
}

bool SaveFile(std::string filename, std::vector<Monster>& monsters)
{
	std::ofstream ofs;
	ofs.exceptions(std::ofstream::badbit);

	try
	{
		ofs.open(filename);

		ofs << "--- MONSTER DATA ---" << std::endl;

		for (auto& e : monsters)
		{
			e.WriteText(ofs);
		}

		ofs.close();
	}
	catch (std::ofstream::failure e)
	{
		std::cerr << std::endl << e.code() << " - " << e.what() << std::endl;
		ofs.close();
		return false;
	}
	return true;
}

bool SaveFileBinary(std::string filename, std::vector<Monster>& monsters)
{

	std::ofstream ostream;

	ostream.exceptions(std::ofstream::badbit);

	try
	{
		ostream.open(filename, std::ofstream::binary);

		Header header{ 1, static_cast<int>(monsters.size()) };
		ostream.write(reinterpret_cast<char*>(&header), sizeof(Header));

		for (auto& e : monsters)
		{
			e.WriteBinary(ostream);
		}

		ostream.close();
	}
	catch (std::ofstream::failure e)
	{
		std::cerr << std::endl << e.code() << " - " << e.what() << std::endl;
		ostream.close();
		return false;
	}
	return true;
}

bool LoadFileBinary(std::string filename, std::vector<Monster>& monsters)
{
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::badbit);

	try
	{
		ifs.open(filename, std::ifstream::binary);

		Header header;
		ifs.read(reinterpret_cast<char*>(&header), sizeof(Header));

		for (int i = 0; i < header.ItemCount; ++i)
		{
			Monster m;
			m.ReadBinary(ifs);
			monsters.push_back(m);
		}

		ifs.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << std::endl << e.code() << " - " << e.what() << std::endl;
		ifs.close();
		return false;
	}
	return true;
}

int File_Stream()
{
	// 경로 
	//path( directory or folder, file )

	// 절대 경로 표기법
	// LoadFile("C:/Programmer/cpp/FileSystem/Data/SimpleData.txt");

	// 상대 경로 표기법
	// LoadFile("Data/SimpleData.txt");


	std::vector<Monster> monsters;

	LoadFile("Data/SimpleData.txt", monsters);

	//for (const auto& e : monsters)
	//{
	//	std::cout << e << std::endl;
	//}

	monsters.push_back(Monster("ORC", 15, 15, 15));

	SaveFile("Data/SimpleData_copy.txt", monsters);


	////////////////////////

	SaveFileBinary("Data/SimpleData.bin", monsters);
	std::vector<Monster> v;
	LoadFileBinary("Data/SimpleData.bin", v);
	return 0;
}

