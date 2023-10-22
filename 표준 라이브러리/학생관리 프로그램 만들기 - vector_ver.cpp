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
	std::cout << "��ȣ, �̸�, ���� : ";
	Student newStudent;
	if (std::cin >> newStudent.mNumber >> newStudent.mName >> newStudent.mScore)
	{
		/*for (const auto& e : v)
		{
			if (e.mNumber == newStudent.mNumber)
			{
				std::cout << "�ߺ��� ��ȣ�Դϴ�." << std::endl;
				return;
			}
		}
		v.push_back(newStudent);
		*/
		auto itr = std::find_if(v.begin(), v.end(), [&](const auto& e) {return e.mNumber == newStudent.mNumber; });
		if (itr != v.end())
		{
			std::cout << "�ߺ��� ��ȣ�Դϴ�." << std::endl;
			return;
		}
		v.push_back(newStudent);
	}
	else
	{
		std::cout << "�߸��� �Է��Դϴ�." << std::endl;
	}
}

void RemoveStudent(std::vector<Student>& v)
{
	std::cout << "������ ��ȣ�� �Է��ϼ��� : ";
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
		std::cout << "��ȣ�� �Է����ּ���" << std::endl;
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

	std::cout << "���� : " << total << ", ��� : " << total / v.size() << std::endl;
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
	// {��ȣ, �̸�, ����}
	// 1. �߰�
	// 2. ����(��ȣ��)
	// 3. ���
	// 4. ���, ����
	// 5. ��� �̻��� �л� ���
	// 6. ���� 
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

		std::cout << "1. �л� �߰�" << std::endl;
		std::cout << "2. �л� ����(��ȣ)" << std::endl;
		std::cout << "3. ��ü �л� ���" << std::endl;
		std::cout << "4. ���� �� ���" << std::endl;
		std::cout << "5. ��� �̻��� ���" << std::endl;
		std::cout << "6. ����" << std::endl;
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
			std::cerr << "�߸��� ����Դϴ�." << std::endl;
		}
		break;
		}
	}
}