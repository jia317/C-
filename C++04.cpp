#include<iostream>
using namespace std;

// 构造函数体内的函数体实际上是赋值，不是初始化
/*
初始化和赋值的区别：
初始化在对象生命周期只能有一次
赋值可以多次
*/

/*
必须在初始化列表进行初始化的成员
1. 引用成员变量
2. const成员变量
3. 自定义类型成员(该类没有默认构造函数)
*/
#if 0
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 22, int ref = 7, int x = 8 )
		// 用初始化列表才叫初始化
		:_year(year)
		, _month(month)
		, _day(day)
		, ra(ref)
		, a(x)
	{
		// 下边的语句都是赋值 不是初始化
		_year = year;
		_month = month;
		_day = day;
		//_day = day; // 没有报错，说明是赋值
	}

	Date(const Date& d)
		// 这里才是初始化
		:_year(d._year)
		, _month(d._month)
		,_day(d._day)
		, ra(d.ra)
		, a(d.a)
	{
		// 这是赋值
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

private:
	int _year;
	int _month;
	int _day;

	int& ra; // 引用成员变量必须在初始化列表进行初始化

	const int a; // const成员变量必须在初始化列表进行初始化
};
#endif

// 类中的自定义成员变量(该类没有默认构造函数)必须在初始化列表进行初始化
// 全缺省构造函数，无参构造函数和未显式定义编译器自动生成的构造函数都是默认构造函数
#if 0
class Time
{
public:
	// Time类中没有默认构造函数(因为我们显式定义了带有三个参数的构造函数)
	// Date类中的t初始化时要在Date类的初始化列表进行初始化
	Time(int hour, int min, int sec)
		:_hour(hour)
		, _min(min)
		, _sec(sec)
	{ }

private:
	int _hour;
	int _min;
	int _sec;
};

class Date
{
public:
	// 构造函数都有初始化列表
	// 用户没有写，编译器会补上，仍旧会执行初始化列表部分
	Date()
		// 用初始化列表才叫初始化
		:_year(2000)
		, _month(4)
		, _day(21)
		, t(11, 0, 0)
	{ }

	Date(int year, int month, int day)
		: _year(year)
		, _month(month)
		, _day(day)
		, t(11, 0, 0)
	{ }

	Date(const Date& d)
		// 这里才是初始化
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
		, t(d.t)
	{ }

private:
	int _year;
	int _month;
	int _day;

	Time t;
};

int main()
{
	Date d1;
	Date d2(2021, 4, 22);

	system("pause");
	return 0;
}
#endif

// 初始化成员变量的次序按照声明次序进行初始化，与初始化列表顺序无关
#if 0
class Time
{
public:
	// Time类中没有默认构造函数(因为我们显式定义了带有三个参数的构造函数)
	// Date类中的t初始化时要在Date类的初始化列表进行初始化
	Time(int hour, int min, int sec)
		:_min(min)
		,_hour(hour) 
		, _sec(sec)
	{ }

private:
	int _hour;
	int _min;
	int _sec;
};

int main()
{
	/*
	如果是按照初始化列表顺序进行初始化，那么
	min = 11   hour = 47   sec = 33
	但是，通过监视窗口看到的，仍旧是
	hour = 11    min = 47    sec = 33

	结论：初始化成员变量的顺序是成员变量的声明次序
	*/
	Time t(11, 47, 33);

	system("pause");
	return 0;
}
#endif

// 对于单个参数的构造函数，还具有类型转换的作用
// explicit关键字的作用：禁止单参构造函数的隐式转换
#if 0
class Date
{
public:
	// 单参的构造函数
	/*Date(int year)
		:_year(year)
		, _month(4)
		, _day(21)
	{
		cout << "Date(int)" << this << endl;
	}*/

	// 加上explicit关键字，单参构造函数就不会进行类型转换了
	explicit Date(int year)
		:_year(year)
		, _month(4)
		, _day(21)
	{
		cout << "Date(int)" << this << endl;
	}

	Date& operator=(const Date& d)
	{
		cout << this << "=" << &d << endl;

		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	~Date()
	{
		cout << "~Date() : " << this << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

// 验证单参构造函数的类型转化
void Test()
{
	Date d1(2021);

	/*
	先将2022作为实参传递给单参构造函数，创建一个临时对象
	再用这个临时对象给d1赋值
	*/
	d1 = 2022;
}
int main()
{
	Test();

	system("pause");
	return 0;
}
#endif

// static成员
/*
C语言中的static
1. static修饰函数：函数只能在声明的文件中使用
2. static修饰变量
   2.1 static修饰局部变量：延长生命周期，变成全局变量，生命周期追随程序
                           会记录上一次的值，在上一次修改的基础上修改
   2.2 static修饰全局变量：该变量只能在当前文件中使用
*/

#if 0
// 验证static修饰局部变量的记忆功能
void TestStatic2()
{
	/*
	如果是static修饰局部变量，那么调用三次TestStatic2()，打印结果为1 2 3 
	因为static修饰局部变量后，它的生命周期就追随程序，只有程序结束才销毁
	所以它会保留上一次修改的值，就像是有记忆功能一样

	如果是局部变量，调用三次TestStatic2()，打印结果为1 1 1
	因为局部变量在函数执行完就会被销毁，每次调用都是一个新的局部变量
	*/
	static int a = 0;
	int a = 0; 
	a++;
	cout << a << endl;
}
int main()
{
	TestStatic2();
	TestStatic2();
	TestStatic2();

	system("pause");
	return 0;
}
#endif

// C++中的static
// 构造函数、拷贝构造函数、赋值运算符重载、析构函数都不能被static修饰，否则就没this指针
/*
1. static修饰成员变量
   
2. static修饰成员函数
*/

// 一种场景：统计创建的对象个数
/*
思路：首先这个计数得是一个全局变量
缺陷：全局变量在任意位置可以修改

引出static关键字
被static修饰的成员供所有类对象所共享，是类的属性；不属于任何一个实例
所以用static int _count作为统计对象个数更安全
*/

//int _count = 0;
#if 0
class Date
{
public:
	Date(int year,int month,int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int,int,int)" << endl;
		_count++;
	}

	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date& d)" << endl;
		_count++;
	}

	~Date()
	{
		cout << "~Date() : " << this << endl;
		_count--;
	}

	// 静态成员函数
	// 静态成员函数不能被const修饰，因为const修饰成员函数实际上是修饰this指针，而在静态成员函数中没有this指针
	static int GetCount()
	{
		// 静态成员函数没有this指针
		//cout << this << endl; // 编译报错 

		/* 
		静态成员函数不能调用非静态成员函数

		Print是类的成员函数，打印时，通过this指针来访问成员变量
		而GetCount是静态成员函数，没有this指针，所以在Print函数中不能访问成员变量
		*/
		//Print(); // 编译报错

		// 静态成员函数中不能访问非静态成员变量
		//cout << _day << endl;

		return _count;
	}

	void Print()
	{
		// 非静态成员函数可以调用静态成员函数
		GetCount();
		cout << _year << _month << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;

	static int _count;
};
// 静态成员变量必须在类外进行初始化
int Date::_count = 0;
 
void TestDate()
{
	Date d1(2021, 2, 22);
	Date d2(2022, 2, 24);
}

// 静态成员为所有类对象所共享，不属于某个具体实例
void Test1()
{
	Date d1(2021, 2, 22);

	cout << sizeof(d1) << endl; // 12 三个int类型的成员变量的大小
}

// 类静态成员的访问方式
void Test2()
{
	Date d1(2021, 2, 22);
	/*
	1. 静态成员函数的调用方式：
	对象.静态成员函数
	类名::静态成员函数
	*/
	d1.GetCount();
	Date::GetCount();
	
	// 该静态成员_count为private，在类外不能访问
	//cout << d1._count <<endl;
	//cout << Date::_count <<endl;

}
int main()
{
	//TestDate();

	Test1();

	system("pause");
	return 0;
}
#endif

// <<的重载
#if 0
class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int,int,int)" << endl;
	}

	// 假如在类中进行<<重载
	/*
	<<操作需要两个操作数，类的非静态成员函数中第一个参数是隐藏的this指针，所以只要传一个ostream(cout类型)的参数即可
	*/
	// 但是，这种写法输出是反的
	// 为了让_cout变成第一个参数，只能将其重载在类外
	// 结论：<<只能在类外重载！！！
	/*void operator<<(ostream& _cout)
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}*/
private:
	int _year;
	int _month;
	int _day;
};
#endif

// 用来测试在类中重载<<
#if 0
int main() 
{
	Date d1(2021, 4, 22);

	// 说明需要两个操作数
	// 在类中重载之后，下面的代码仍不能执行
	//cout << d1;

	// 但是这样写可以
	//d1 << cout;
	// 说明我们在类中重载的<<达到的效果是相反的
	/*
	出现相反的情况的原因：
	因为d1是左操作数，cout是右操作数，相当于下边d1.operator<<(cout)的写法
	*/

	// 类中的成员函数必须通过对象来调用
	//d1.operator<<(cout);

	system("pause");
	return 0;
}
#endif

// <<重载的返回值类型是ostream
// 引用传参、引用返回都是为了提高函数调用效率
#if 0
ostream& operator<<(ostream& _cout, const Date& d)
{
	/* 因为不能在类外访问类的私有成员变量解决方法
	1. 在类中写一些public函数获取私有成员，在类外调用成员函数来访问
	2. 将类外定义的函数设置为友元函数就可以在该函数中访问类的私有成员了
	// 
	*/
	_cout << d._year << "-" << d._month << "-" << d._day ;
	return _cout;
}

// 用来测试在类外重载<<
int main()
{
	Date d1(2021, 4, 22);

	cout << d1;
	operator<<(cout, d1);

	// 探究<<重载函数的返回值
	/*
	连续<<
	先将"d1的日期是："输出到cout；再将d1输出到cout；再将endl输出到cout
	所以<<重载一定是有返回值的
	因为都要输出到cout，所以返回值类型也是ostream
	*/
	cout << "d1的日期是：" << d1 << endl;

	cout << d1 << 10;
	operator << (cout, d1) << 10;

	system("pause");
	return 0;
}
#endif

// 友元：为了解决类外不能访问类的私有成员
/*
1. 友元函数：可以直接访问类的私有成员，定义在类外，不属于任何类，但需要在类内声明，声明时加friend
1）友元函数可以直接访问类的保护成员和私有成员，但不是类的成员函数
2）友元函数不能被const修饰
3）友元函数可以在类的任何位置声明，不受类访问限定符限制
4）一个函数可以是多个类的友元函数
5）友元函数的调用与普通函数原理相同
*/

// 友元类
/*
1. 友元类的关系是单向的 
解释：比如类B是类A的友元类，那么类B可以访问类A中的私有成员，但是类A不能访问类B的私有成员
2. 友元关系不能传递
解释：B是A的友元类，C是B的友元类，但是在C中不能访问类A的私有成员
*/
#if 0
class Time
{
	friend class Date;
public:
	Time(int hour = 0, int min = 0, int sec = 0)
		:_hour(hour)
		, _min(min)
		, _sec(sec)
	{ }

private:
	int _hour;
	int _min;
	int _sec;
};

class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int,int,int)" << endl;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day;
		cout << _t._hour << "-" << _t._min << "-" << _t._sec;
	}
private:
	int _year;
	int _month;
	int _day;

	Time _t;
};
#endif

// 内部类
/*
1. 内部类是一个独立的类，它不属于外部类，不能用外部类对象去访问内部类
2. 内部类是外部类的友元类，内部类可以通过外部类对象来访问外部类中的所有成员
3. 内部类可以定义在外部类的public、protected、public
4. 内部类可以直接访问外部类的static、枚举成员，不需要外部类的对象/类名
5. sizeof(外部类)与内部类无关
*/
class DList
{
	struct DListNode // 内部类
	{
	public:
		DListNode(int x)
			:prev(nullptr)
			, next(nullptr)
			, data(x)
		{ }

		// 内部类可以用外部类对象访问外部类的所有成员
		void fun()
		{
			DList L;
			L._head; // 访问外部类的私有成员变量
			a = 10; // 访问外部类的static成员变量，不需要加外部类访问限定符或用外部类对象访问
			L.Fun(); // 访问外部类的成员函数
		}
	private:
		DListNode* prev;
		DListNode* next;
		int data;
	};

public:
	DList()
		:_head(nullptr)
	{ }

	void Fun()
	{

	}
private:
	DListNode* _head;
	static int a;
};

int DList:: a = 7; // 类中static成员变量必须在类外初始化

void Test()
{
	DList L;
	//L.data; // 不能用外部类对象访问内部类

	cout << sizeof(DList) << endl; // 4 只有一个指向DListNode类型对象的指针_head

}

int main()
{
	Test();

	system("pause");
	return 0;
}