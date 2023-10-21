#pragma once
class NPoint2D
{
	int mX;
	int mY;

public:
	NPoint2D();
	NPoint2D(int x, int y);
	void Print();

	// 해당 함수에 friend를 사용하여 
	// operator + 함수가 NPoint2D클래스의 친구가 됨.
	// 그러므로, 해당 함수는 NPoint2D 클래스의 private에 접근이 가능해짐.
	friend NPoint2D operator + (NPoint2D x, NPoint2D y);

	friend NPoint2D operator++(NPoint2D arg1);

	friend const NPoint2D& operator++(NPoint2D& arg1, int V);

	friend std::ostream& operator<<(std::ostream& os, NPoint2D pt);

	// 멤버 함수 버전의 연산자 오버로딩

	// 전위 연산자
	NPoint2D operator - (const NPoint2D& op)
	{
		return NPoint2D(mX - op.mX, mY - op.mY);
	}
	

	// 전위 연산자
	NPoint2D operator--()
	{
		mX--;
		mY--;
		return *this;
	}

	// 후위 연산자
	NPoint2D operator--(int v)
	{
		NPoint2D temp(mX, mY);

		mX--;
		mY--;
		return temp;
	}

	// [] 연산자 오버로딩
	int& operator[] (int index)
	{
		switch (index)
		{
		case 0:
		{
			return mX;
		}
		break;
		case 1:
		{
			return mY;
		}
		break;
		default:
		{
			std::cerr << "Index error" << std::endl;
		}
		break;
		}
	}

	operator double()
	{
		return sqrt(mX * mX + mY * mY);
	}

	void operator() (int x, int y)
	{
		mX = x;
		mY = y;
	}


};

// 연산자 오버로딩

// NPoint2D를 반환하는 operator +  함수
// 해당 함수는 전역 함수임.
// 전역 함수 버전의 연산자 오버로딩
NPoint2D operator + (NPoint2D x, NPoint2D y);


// 단항 연산자 오버로딩

// 전위 연산자
NPoint2D operator++(NPoint2D arg1);


// 후위 연산자
const NPoint2D& operator++(NPoint2D& arg1, int V);

// 스트림 연산자 오버로딩
std::ostream& operator<<(std::ostream& os, NPoint2D pt);