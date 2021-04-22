#include<iostream>
#include<Windows.h>
using namespace std;

#if 0
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	~Date(){ }

	/*
	注意+重载和+=的重载
	+重载：不改变原对象
	+=重载：改变原对象
	*/
	Date operator+(/*Date* const this,*/int days) // 因为temp是临时对象，函数结束，临时变量就会销毁，传值返回会对temp拷贝构造一份临时变量
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}

	Date& operator+=(int days)
	{
		_day += days;
		return *this;
	}

	/* 
	赋值运算符重载正确姿势：
	1. 参数采用传引用方式，提高效率
	2. 返回值返回引用
	3. 如果是自己给自己赋值，不进行操作直接返回this指针
	4. 返回时，因为引用返回，返回值生命周期必须大于函数，所以返回this指针
	*/
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		
		return *this;
	}

	// 参数传值
	/*Date& operator=(const Date d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	 }*/

	// 传值返回
	/*Date operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	 }*/

	// 前置++
	Date& operator++()
	{
		_day++;
		return *this;
	}

	// 后置++
	/* 
	先使用，再++
	所以，返回的是++前的旧值，只能用临时变量保存旧值，再将该对象中的值++
	返回的是临时变量，函数结束临时变量要销毁，所以采用传值返回，给返回值生成一份临时拷贝
	返回的是临时拷贝

	参数中的int是为了构成函数重载，由编译器来传递
	*/
	Date operator++(int)
	{
		Date temp(*this);
		_day++;
		return temp;
	}

	// 前置--
	// 先--，再使用
	Date& operator--()
	{
		_day--;
		return *this;
	}

	// 后置--
	Date operator--(int)
	{
		Date temp(*this);
		_day--;
		return temp;
	}

	// &重载
	Date* operator&()
	{
		cout << this << endl;
		return this;
	}

	// 
	const Date* operator&()const
	{
		return this;
	}
private:
	int _year;
	int _month;
	int _day;
};

// 如果在类外实现运算符重载，没有this指针
// 类外不能访问类的私有成员
//Date operator-(const Date& d, int days)
//{
//	Date temp(d);
//	temp._day += days;
//	return temp;
//}
//Date& operator-=(Date& d, int days)
//{
//	d._day -= days;
//	return d;
//}

int main()
{
	Date d1(2021, 4, 21);
	Date d2(2021, 3, 17);

	/*d1.operator+(7);
	d2.operator+=(7);*/

	Date d3(2021, 4, 23);
	//d1 = d3;
	
	/*
	连续赋值，先用d3给d2赋值，再用d2给d1赋值
	也就是说，返回值应该返回调用赋值运算符的对象
	*/
	//d1 = d2 = d3;
	
	//d2 = d1++; // d2中是21 d1中是22
	//d2 = ++d1; // d2中是23 d1中是23

	&d2;

	const Date d4(2021, 4, 21);
	&d4;

	system("pause");
	return 0;
}

// d1=d2=d3 ---》 return *this
// const Date& d和Date& const d
#endif

#if 0
// const类型的成员函数 const修饰的其实是this指针
// this指针类型：类类型* const this
// 在const修饰的成员函数中：const 类类型* const this
// 即：this指针的指向和指向的空间中的内容都不能修改
// const修饰的成员函数中是不能修改成员变量的值的
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	~Date(){ }

	// 调用该函数的对象即this指向的对象和传参的对象都不改变 加const
	bool operator==(const Date& d)const
	{
		return _year == d._year &&
			_month == d._month &&
			_day == d._day;
	}

	void Print()const
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	const Date* operator&()const
	{
		return this;
	}

	
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2021, 4, 21);
	Date d2(2021, 4, 21);
	Date d3(2021, 4, 22);

	if (d1 == d2)
	{
		cout << "相同" << endl;
	}
	else
	{
		cout << "不同" << endl;
	}

	if (d1 == d3)
	{
		cout << "相同" << endl;
	}
	else
	{
		cout << "不同" << endl;
	}

	system("pause");
	return 0;
}
#endif

#if 0
// const成员
// 1. const对象不能调用非const成员函数
// 2. 非const对象可以调用const成员函数
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	~Date(){ }

	// 调用该函数的对象即this指向的对象和传参的对象都不改变 加const
	bool operator==(const Date& d)const
	{
		return _year == d._year &&
			_month == d._month &&
			_day == d._day;
	}

	void Print()const
	{

		cout << _year << "-" << _month << "-" << _day << endl;
	}

	const Date* operator&()const
	{
		return this;
	}

	Date* operator&()
	{
		cout << this << endl;
		return this;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	const Date d1(2021, 4, 21);
	Date d2(2021, 4, 22);

	&d1; // 调用const Date* operator&()const
	&d2; // 调用Date* operator&()
	
	d2.Print(); // 非const对象可以调用const成员函数

	system("pause");
	return 0;
}
#endif

class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
		:_year(year)
		, _month(month)
		, _day(day)
	{ 
		cout << "Date(int, int, int)" << this << endl;
	}

	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date& d)" << this << endl;
	}

	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_day = d._day;
			_month = d._month;
			_day = d._month;
		}

		cout << "operator" << this << endl;
		return *this;
	}

	~Date()
	{ 
		cout << "~Date()" << this << endl;
	}

	
private:
	int _year;
	int _month;
	int _day;
};

Date TestDate1(Date d)
{
	Date temp(d);
	temp = d;
	return temp;
}


Date& TestDate2(Date& d)
{
	Date temp(d);
	temp = d;
	return d;
}

Date TestDate3(Date d)
{
	return d;
}

void TestDate()
{
	Date d1(2021, 4, 21); // 调用构造
	Date d2(d1); // 拷贝构造

	// 测试调用TestDate1和调用TestDate2的打印结果

	//d2 = TestDate1(d1);
	
	/*
	调用经过：
	拷贝构造 -》 d
	拷贝构造 -》 temp
	赋值运算符重载 -》 temp = d
	拷贝构造 -》 值返回，返回值拷贝一份临时对象ret，只在赋值行有效
	析构函数 -》 temp
	析构函数 -》 d
	赋值运算符重载 -》 d2 = TestDate1(d1)
	析构函数 -》 ret
	*/

	//d2 = TestDate2(d1);

	/*
	调用经过：
	拷贝构造 -》 temp 
	赋值运算符重载 -》 temp = d
	析构函数 -》 temp
	赋值运算符重载 -》 d2 = TestDate2(d1)
	*/

	/*
	TestDate函数结束
	析构函数 -》 d2
	析构函数 -》 d1
	*/

	TestDate3(TestDate3(d1));

	/*
	拷贝构造 -》 d1的临时对象
	拷贝构造 -》 ret1的临时拷贝
	析构 -》 d1的临时对象

	拷贝构造 -》 ret1的临时拷贝的临时对象
	【拷贝构造 -》 ret2的临时拷贝】没有这条！编译器优化
	析构 -》 ret1的临时拷贝
	析构 -》 ret2的临时拷贝
	*/
}

void Test()
{
	TestDate1(Date d(2021, 4, 21));
}
int main()
{
	//TestDate();

	Test();

	system("pause");
	return 0;
}