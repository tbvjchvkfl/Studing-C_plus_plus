#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>

class Student
{
public:
	int			mNumber;
	std::string mName;
	int			mScore;
};

std::ostream& operator<< (std::ostream& os, const Student& s)
{
	os << "[" << s.mNumber << "]" << s.mName << " : " << s.mScore << std::endl;

	return os;
}

void AddStudent(std::map<int, Student>& m)
{

	std::cout << "��ȣ, �̸�, ���� ������ �Է��ϼ���" << std::endl;

	Student newStudent;
	if (std::cin >> newStudent.mNumber >> newStudent.mName >> newStudent.mScore)
	{
		auto result = m.insert({ newStudent.mNumber, newStudent });
		if (!result.second)
		{
			std::cout << "�ߺ��� �л� ��ȣ�Դϴ�." << std::endl;
			return;
		}
	}
	else
	{
		std::cerr << "�߸��� �Է��Դϴ�." << std::endl;
	}
}

void RemoveStudent(std::map<int, Student>& m)
{
	std::cout << "������ ��ȣ�� �Է��ϼ��� : ";
	int number;
	if (std::cin >> number)
	{
		m.erase(number);
	}
	else
	{
		std::cout << "�߸��� �Է��Դϴ�.";
	}
	std::cout << std::endl;
}

void PrintStudents(const std::map<int, Student>& m)
{
	for (const auto& e : m)
	{
		std::cout << e.second << std::endl;
	}
}

void PrintAverage(const std::map<int, Student>& m)
{
	int total{};
	total = std::accumulate(m.begin(), m.end(), 0, [&](int accum, const auto& pair) {accum += pair.second.mScore; });

	std::cout << "���� : " << total << ", ��� : " << total / m.size() << std::endl;
}

void PrintOverAverage(const std::map<int, Student>& m)
{
	int average{};
	average = std::accumulate(m.begin(), m.end(), 0, [&](int accum, const auto& pair) {accum += pair.second.mScore; });

	average /= m.size();

	std::for_each(m.begin(), m.end(), [&](const auto& pair) {if (pair.second.mScore >= average) { std::cout << pair.second << std::endl; }});
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
	std::map<int, Student> students_m
	{
		{ 1, {1, "Kim", 80 }},
		{ 2, {2, "Lee", 20 }},
		{ 3, {3, " Park", 40 }},
		{ 4, {4, "Choi", 30 }}
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
			AddStudent(students_m);
		}
		break;
		case 2:
		{
			RemoveStudent(students_m);
		}
		break;
		case 3:
		{
			PrintStudents(students_m);
		}
		break;
		case 4:
		{
			PrintAverage(students_m);
		}
		break;
		case 5:
		{
			PrintOverAverage(students_m);
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