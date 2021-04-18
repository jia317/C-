#include <assert.h>
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
#pragma warning(disable:4996)

// 析构函数
// 1. 类中在堆上申请了空间
typedef int DataType;
class SeqList
{
public:
	SeqList(int capacity = 10)
	{
		_pData = (DataType*)malloc(capacity*sizeof(DataType));
		assert(_pData);

		_size = 0;
		_capacity = capacity;
	}

	~SeqList()
	{
		if (_pData)
		{
			free(_pData);
			*_pData = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
private:
	DataType* _pData;
	DataType _size;
	DataType _capacity;
};

// 类中包含自定义类型成员
class String
{
public:
	String(const char* str = "jia")
	{
		_str = (char*)malloc(strlen(str) + 1);
		strcpy(_str, str);
	}

	~String()
	{
		cout << "~String()" << endl;
		free(_str);
	}
private:
	char* _str;
};

class Person
{
private:
	string _name;
	int _age;
};

//int main()
//{
//	//SeqList s;
//
//	Person s;
//
//	system("pause");
//	return 0;
//}

#if 0
fstream fout("destructor.txt", ios::app); // 要不然看不到析构函数中的输出语句

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		fout << "~A()" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}
	~B()
	{
		fout << "~B()" << endl;
	}
};

int main()
{
	A a;
	B b;

	system("pause");
	return 0;
}
#endif

// 析构函数调用时机
// 情况2：delete 指向对象的指针时，
//   或者delete 指向对象的基类类型的指针，而基类析构函数是虚函数
#if 0
fstream fout("destructor_case3.txt", ios::app);

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}

	virtual ~A()
	{
		fout << "~A()" << endl;
	}

private:
	int _a;
};

class B :public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}

	~B()
	{
		fout << "~B()" << endl;
	}
};

//void Test()
//{
//	A *a = new A(10); // 动态申请一个类A类型大小的空间并初始化为10
//	delete a;
//}
#endif

// 情况3：对象A是类B的成员，B的析构函数调用时，会去调用A的析构函数
#if 0
fstream fout("destructor_case4.txt", ios::app);

class A
{
public:
	A()
	{
		fout << "A()" << endl;
	}
	~A()
	{
		fout << "~A()" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		fout << "B()" << endl;
	}
	~B()
	{
		fout << "~B()" << endl;
	}

private:
	A a;
};

int main()
{
	//A a; // 创建一个基类对象a
	//B b; // 创建一个派生类对象b

	//A* pa1 = &a; // 指向基类对象的基类指针pa1
	//A* pa2 = &b; // 指向派生类对象的基类指针pa2

	//A* pa = new B(); // 基类指针pa指向new出来的派生类对象
	//delete pa;
	//B* pb = new B(); // 

	B b;

	system("pause");
	return 0;
}
#endif

#if 0
// 拷贝构造函数
// 没有显式定义拷贝构造函数，编译器会生成默认拷贝构造函数
class Date
{
public:
	Date(int year = 2021, int month = 4, int day = 18)
	{
		_year = year;
		_month = month;
		_day = day;
	}

private:
	int _year;
	int _month;
	int _day;
};

void Test1()
{
	Date d1;

	Date d2 = d1; // 这是初始化！！不是赋值
	Date d3(d2); // 这种写法和上边一样
}

// 调用拷贝构造函数的三种情况
class Point
{
public:
	Point(int x = 0, int y = 0)
		:_x(x)
		, _y(y)
	{ }

	~Point(){ };

	Point(const Point &p);

	int getX()const
	{
		return _x;
	}

	int getY()const
	{
		return _y;
	}
private:
	int _x;
	int _y;
};

Point::Point(const Point &p)
{
	_x = p._x;
	_y = p._y;
	cout << "Calling the copy constructor" << endl;
}

// 2. 函数参数为类对象时
void func1(const Point& p) // 类类型对象形参实例化时要调用拷贝构造函数，复制一份实参
{
	cout << p.getX() << endl;
}

// 3. 函数返回值为类对象时
Point func2()
{
	Point a(1, 2);
	return a;
}

int main()
{
	//Test1();
	Point p1(7, 2);
	// 1. 用一个对象初始化同类的另一个对象
	Point p2(p1); // 调用拷贝构造函数
	cout << "x = " << p2.getX() << "," << "y = " << p2.getY() << endl;

	func1(p2); // p1对象作为实参传递

	p2 = func2();
	cout << "x = " << p2.getX() << "," << "y = " << p2.getY() << endl;

	system("pause");
	return 0;
}
#endif

//定义一个Point类
class Point{
public:
	Point(int xx = 0, int yy = 0) :x(xx), y(yy){}     //构造函数
	~Point(){ };                              //析构函数
	Point(const Point &p);                //复制构造函数
	int getX()const{ return x; }
	int getY()const { return y; }
private:
	int x, y;//私有成员

};

Point::Point(const Point &p)
{
	x = p.x;
	y = p.y;
	cout << "Calling the copy constructor" << endl;

}
//形参作为Point类对象的函数
void fun1(Point p)
{
	cout << p.getX() << endl;

}

//返回类的对象
Point fun2()
{
	Point a(1, 2);
	return a;
}

int main()
{
	Point a(4);    //第一个对象A,该过程利用了重载，后面的y默认为0

	Point b(a);      //此时调用copy构造函数；情况1，用a初始化b，第一次调用copy构造函数
	cout << b.getX() << endl;

	fun1(b);  //此时调用copy构造函数；类的对象在函数中为实参，第二次调用copy构造函数

	b = fun2();//此时调用copy构造函数；函数返回值为类的对象，第三次调用copy构造函数
	cout << b.getX() << endl;

	system("pause");
	return 0;
}