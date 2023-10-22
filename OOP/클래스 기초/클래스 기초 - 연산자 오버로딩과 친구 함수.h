#pragma once
class NPoint2D
{
	int mX;
	int mY;

public:
	NPoint2D();
	NPoint2D(int x, int y);
	void Print();

	// �ش� �Լ��� friend�� ����Ͽ� 
	// operator + �Լ��� NPoint2DŬ������ ģ���� ��.
	// �׷��Ƿ�, �ش� �Լ��� NPoint2D Ŭ������ private�� ������ ��������.
	friend NPoint2D operator + (NPoint2D x, NPoint2D y);

	friend NPoint2D operator++(NPoint2D arg1);

	friend const NPoint2D& operator++(NPoint2D& arg1, int V);

	friend std::ostream& operator<<(std::ostream& os, NPoint2D pt);

	// ��� �Լ� ������ ������ �����ε�

	// ���� ������
	NPoint2D operator - (const NPoint2D& op)
	{
		return NPoint2D(mX - op.mX, mY - op.mY);
	}
	

	// ���� ������
	NPoint2D operator--()
	{
		mX--;
		mY--;
		return *this;
	}

	// ���� ������
	NPoint2D operator--(int v)
	{
		NPoint2D temp(mX, mY);

		mX--;
		mY--;
		return temp;
	}

	// [] ������ �����ε�
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

// ������ �����ε�

// NPoint2D�� ��ȯ�ϴ� operator +  �Լ�
// �ش� �Լ��� ���� �Լ���.
// ���� �Լ� ������ ������ �����ε�
NPoint2D operator + (NPoint2D x, NPoint2D y);


// ���� ������ �����ε�

// ���� ������
NPoint2D operator++(NPoint2D arg1);


// ���� ������
const NPoint2D& operator++(NPoint2D& arg1, int V);

// ��Ʈ�� ������ �����ε�
std::ostream& operator<<(std::ostream& os, NPoint2D pt);