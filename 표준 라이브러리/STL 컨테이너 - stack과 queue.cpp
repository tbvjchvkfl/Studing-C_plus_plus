#include <iostream>
#include <stack>
#include <queue>

void StackAndQueue_Container()
{

	// ----------------- Stack ----------------
	std::stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);

	s.pop();

	/*while (!s.empty())
	{
		std::cout << s.top() << std::endl;
		s.pop();
	}*/


	std::stack<int> temp(s);

	while (!temp.empty())
	{
		std::cout << temp.top() << std::endl;
		temp.pop();
	}


	std::queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);




	// ---------------- Queue ----------------

	std::queue<int>temptation(q);

	while (!temptation.empty())
	{
		std::cout << temptation.front() << " ";
		temptation.pop();
	}
	std::cout << std::endl;



	// priority_queue는 queue에 들어가있음
	// #include <queue>만 해주면 됨.
	// 우선순위에 의해서 정렬되어 나옴.
	std::priority_queue<int> pq;
	pq.push(6);
	pq.push(3);
	pq.push(5);

	std::priority_queue<int>temp_1(pq);

	while (!temp_1.empty())
	{
		std::cout << temp_1.top() << " ";
		temp_1.pop();
	}
	std::cout << std::endl;


	struct App
	{
		int priority;
		std::string name;

		bool operator<(const App& app) const
		{
			return this->priority < app.priority;
		}
	};

	std::priority_queue<App> apppriority;
	apppriority.push({ 1, "notepad" });
	apppriority.push({ 5, "vscode" });
	apppriority.push({ 3, "lalala" });

	std::cout << apppriority.top().name << std::endl;
}
