#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Student
{
public:
	int			mNumber;
	std::string mName;
	int			mScore;

public:
	void Print() const
	{
		std::cout << "[" << mNumber << "]" << mName << " : " << mScore << std::endl;
	}
};

void AddStudent(std::vector<Student>& v)
{
	std::cout << "번호, 이름, 점수 : ";
	Student newStudent;
	if (std::cin >> newStudent.mNumber >> newStudent.mName >> newStudent.mScore)
	{
		/*for (const auto& e : v)
		{
			if (e.mNumber == newStudent.mNumber)
			{
				std::cout << "중복된 번호입니다." << std::endl;
				return;
			}
		}
		v.push_back(newStudent);
		*/
		auto itr = std::find_if(v.begin(), v.end(), [&](const auto& e) {return e.mNumber == newStudent.mNumber; });
		if (itr != v.end())
		{
			std::cout << "중복된 번호입니다." << std::endl;
			return;
		}
		v.push_back(newStudent);
	}
	else
	{
		std::cout << "잘못된 입력입니다." << std::endl;
	}
}

void RemoveStudent(std::vector<Student>& v)
{
	std::cout << "삭제할 번호를 입력하세요 : ";
	int number;
	std::cin >> number;
	if (std::cin >> number)
	{
		/*for (auto itr = v.begin(); itr != v.end(); itr++)
		{
			if (itr->mNumber == number)
			{
				v.erase(itr);
				return;
			}
		}*/

		// erase-remove idiom
		v.erase(std::remove_if(v.begin(), v.end(), [&](auto& e) {return e.mNumber == number; }));
	}
	else
	{
		std::cout << "번호를 입력해주세요" << std::endl;
	}
}

void PrintStudents(const std::vector<Student>& v)
{
	/*for (const auto& e : v)
	{
		e.Print();
	}*/
	std::for_each(v.begin(), v.end(), [&](const auto& e) {e.Print(); });
}

void PrintAverage(const std::vector<Student>& v)
{
	int total{};
	/*for (const auto& e : v)
	{
		total += e.mScore;
	}*/
	total = std::accumulate(v.begin(), v.end(), 0, [](int accum, const auto& e) {return accum += e.mScore; });

	std::cout << "총점 : " << total << ", 평균 : " << total / v.size() << std::endl;
}

void PrintOverAverage(const std::vector<Student>& v)
{
	int total{};
	for (const auto& e : v)
	{
		total += e.mScore;
	}

	int average = total / v.size();

	for (const auto& e : v)
	{
		if (e.mScore >= average)
		{
			e.Print();
		}
	}

	std::for_each(v.begin(), v.end(), [&](const auto& e) {if (e.mScore >= average) { e.Print(); }});
}

int main()
{
	// {번호, 이름, 점수}
	// 1. 추가
	// 2. 제거(번호로)
	// 3. 출력
	// 4. 평균, 총점
	// 5. 평균 이상의 학생 목록
	// 6. 종료 
	std::vector<Student> students_v
	{
		{1, "Kim", 80},
		{ 2, "Lee", 20 },
		{ 3, " Park", 40 },
		{ 4, "Choi", 30 }
	};
	bool isQuit{ false };

	while (!isQuit)
	{

		std::cout << "1. 학생 추가" << std::endl;
		std::cout << "2. 학생 제거(번호)" << std::endl;
		std::cout << "3. 전체 학생 출력" << std::endl;
		std::cout << "4. 총점 및 평균" << std::endl;
		std::cout << "5. 평균 이상의 목록" << std::endl;
		std::cout << "6. 종료" << std::endl;
		std::cout << ">";
		int command{};
		std::cin >> command;
		switch (command)
		{
		case 1:
		{
			AddStudent(students_v);
		}
		break;
		case 2:
		{
			RemoveStudent(students_v);
		}
		break;
		case 3:
		{
			PrintStudents(students_v);
		}
		break;
		case 4:
		{
			PrintAverage(students_v);
		}
		break;
		case 5:
		{
			PrintOverAverage(students_v);
		}
		break;
		case 6:
		{
			isQuit = true;
		}
		break;
		default:
		{
			std::cerr << "잘못된 명령입니다." << std::endl;
		}
		break;
		}
	}
}