#include <iostream>
#include <Windows.h>
using namespace std;

// 当一个类中包含另一个类对象成员时，且被包含的类对象的类中显式定义了构造函数
// 编译器将给这个类自动生成一个默认构造函数
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

// 1.构造函数可以重载
class Date
{
public:
	/*
	2. 默认构造函数只能有一个！
	无参构造函数、全缺省构造函数、未显式定义编译器自动生成的构造函数
	都叫默认构造函数，且默认构造函数只能有一个
	*/
	// 无参构造函数
	Date()
	{
		_year = 2021;
		_month = 4;
		_day = 18;
	}

	// 全缺省构造函数
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	// 底下这个构造函数和前面的构造函数形成了重载
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
	//Date d1; //  Date中定义了两个默认构造函数，创建该对象时函数调用存在二义性，会报错
	//d1.print();

	//Date d2(2000, 4, 21); // 调用有三个参数的构造函数
	//d2.print();

	system("pause");
	return 0;
}


