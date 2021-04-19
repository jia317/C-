#include <iostream>
#include <Windows.h> 
#pragma warning(disable:4996)
using namespace std;

// 拷贝构造函数调用场景
// 拷贝构造函数的参数为什么要加const
// 拷贝构造函数的参数为什么要传引用
/*
编译器默认生成的拷贝构造函数的拷贝方式，浅拷贝(按字节拷贝)
什么时候必须定义拷贝构造函数？自定义类型时，自己写和编译器自动生成的一样 
涉及到资源管理时就会出问题 析构函数同一个空间释放两次
*/

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

	// 拷贝构造函数
	/*Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}*/
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2021, 4, 19);
	Date d2(d1);

	system("pause");
	return 0;
}
#endif

#if 0
class String
{
public:
	// 构造函数
	String(const char* str = "jia")
	{
		/*
		strlen：用来计算字符串长度，不包含\0
		sizeof：用来计算类型大小
		*/
		// 从堆上开辟能保存字符串大小的一段空间，并将这段空间的首地址传给_str
		_str = (char*)malloc(strlen(str) + 1);
		// 将str字符串中的字符一个一个拷贝到_str指向的空间中
		strcpy(_str, str);
	}

	// 拷贝构造函数
	String(const String& s)
	{
		_str = (char*)malloc(strlen(s._str)+1);
		strcpy(_str, s._str);
	}

	// 析构函数
	~String()
	{
		cout << "~String()" << endl;
		free(_str);
		_str = nullptr;
	}
private:
	char* _str;
};

// 当TestString函数执行完，s1、s2就要被销毁，这样可以看到销毁时调用析构函数的结果
// 如果直接写到main函数中，要return之后，对象才会被销毁，看不到调用析构函数的结果，需要将输出定向到文件中
void TestString()
{
	String s1("hello");
	String s2(s1);
}
int main()
{
	TestString();

	system("pause");
	return 0;
}
#endif

// 赋值运算符重载
#if 0
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		cout << "Constructor" << endl;
		_year = year;
		_month = month;
		_day = day;
	}

	// 写这个拷贝构造只是为了验证d2和d4调用了拷贝构造函数，打印两次
	/*Date(const Date& d)
	{
		cout << "Copy_Constructor" << endl;
	}*/

	/*Date& operator+(int days)
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}*/
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2021, 4, 19); // 调用构造函数
	Date d3; // 调用构造函数

	/*
	1. 区分调用拷贝构造函数和赋值运算符重载
	拷贝构造函数：是用已经存在的对象初始化新创建的对象
	赋值运算符重载：是用已经存在的对象给另一个已经存在的对象赋值
	*/
	Date d2 = d1; // 调用拷贝构造函数
	Date d4(d3); // 调用拷贝构造函数

	d3 = d1; // 调用赋值运算符重载

	system("pause");
	return 0;
}
#endif

/*
2. 未显式定义赋值运算符重载，编译器会自动生成
但是，当我们用一个对象给另一个对象赋值后，被赋值的对象原来的空间就被覆盖了
如果涉及到资源管理，在调用析构函数时就无法释放这段空间，导致内存泄漏
*/
#if 0
class String
{
public:
	// 构造函数
	String(const char* str = "jia")
	{
		/*
		strlen：用来计算字符串长度，不包含\0
		sizeof：用来计算类型大小
		*/
		// 从堆上开辟能保存字符串大小的一段空间，并将这段空间的首地址传给_str
		_str = (char*)malloc(strlen(str) + 1);
		// 将str字符串中的字符一个一个拷贝到_str指向的空间中
		strcpy(_str, str);
	}

	// 拷贝构造函数
	String(const String& s)
	{
		_str = (char*)malloc(strlen(s._str) + 1);
		strcpy(_str, s._str);
	}

	// 析构函数
	~String()
	{
		cout << "~String()" << endl;
		free(_str);
		_str = nullptr;
	}
private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	String s2(s1);
	
	String s3;
	s3 = s1;
}
int main()
{
	TestString();

	system("pause");
	return 0;
}
#endif

// 操作符重载
// 1. 运算符重载的参数必须有一个类类型或自定义类型的参数
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	/*Date& operator+(int days)
	{
	Date temp(*this);
	temp._day += days;
	return temp;
	}*/

	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	/*
	为什么要进行运算符重载？
	对于自定义类型，编译器不知道如何进行运算符操作
	对该运算符重载，就是告诉编译器针对该类型的对象如何进行该种操作符的操作
	*/
	// < 运算符的重载
	bool operator<(const Date& d)
	{
		if ((_year<d._year)||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day))
		{
				return true;
		}
		return false;
	}

	bool operator==(const Date& d)
	{
		if (_year == d._year &&
			_month == d._month &&
			_day == d._day)
		{
			return true;
		}
		return false;
	}

	/* 
	如果运算符重载在类中，那该运算符重载函数是类的成员函数
	成员函数中有隐含的参数this指针
	*/
	// !=的重载很好的说明了类中运算符重载函数的参数中有隐含的this指针
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	/*
	下边的+运算符重载存在的问题：
	1. 不含类类型或自定义参数
	2. 参数只有内置类型的参数，会引发无限递归调用这个运算符重载函数
	*/
	/*int operator+(int a, int b)
	{
		return a + b;
	}*/

	// 没整明白！！
	/*enum Data
	{THREE}; 
	int operator+(Data a, int b)
	{
		return a + b;
	}*/
	 
	/*

	*/
	// 用引用返回，返回对象生命周期必须比函数生命周期长
	Date& operator+(int days)
	{
		_day += days;
		return *this;
	}

	Date operator+=(int days)
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1;
	Date d2(2000, 8, 2);

	if (d1 < d2)
	{
		cout << "d1 < d2" << endl;
	}
	else
	{
		cout << "d1 >= d2" << endl;
	}

	d2 = d1 + 2; // 调用+运算符重载
	d1 += 2; // 调用+=运算符重载

	system("pause");
	return 0;
}
