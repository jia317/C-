#include <iostream>
#include <Windows.h>
using namespace std;

// ��һ�����а�����һ��������Աʱ���ұ�������������������ʽ�����˹��캯��
// ����������������Զ�����һ��Ĭ�Ϲ��캯��
#if 0
class Time
{
public:
	Time()
	{
		_h = 1;
		_m = 1;
		_s = 1;
	}
private:
	int _h;
	int _m;
	int _s;
};

class Date
{
public:
	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;

	Time t;
};
#endif

// 1.���캯����������
class Date
{
public:
	/*
	2. Ĭ�Ϲ��캯��ֻ����һ����
	�޲ι��캯����ȫȱʡ���캯����δ��ʽ����������Զ����ɵĹ��캯��
	����Ĭ�Ϲ��캯������Ĭ�Ϲ��캯��ֻ����һ��
	*/
	// �޲ι��캯��
	Date()
	{
		_year = 2021;
		_month = 4;
		_day = 18;
	}

	// ȫȱʡ���캯��
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	// ����������캯����ǰ��Ĺ��캯���γ�������
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	//Date d1; //  Date�ж���������Ĭ�Ϲ��캯���������ö���ʱ�������ô��ڶ����ԣ��ᱨ��
	//d1.print();

	//Date d2(2000, 4, 21); // ���������������Ĺ��캯��
	//d2.print();

	system("pause");
	return 0;
}


