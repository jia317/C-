#include <iostream>
#include <Windows.h>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;

#if 0
// 类的大小
class A
{
public:
	void func1(){ }

private:
	int a;
	char b;
};

class B
{
public:
	void func2(){ }
};

class C{ };

int main()
{
	/*cout << "类A的大小为：" << sizeof(A) << endl;
	cout << "类B的大小为：" << sizeof(B) << endl;
	cout << "类C的大小为：" << sizeof(C) << endl;*/

	//p = &x; // 编译器会将上面两个声明当成完全不同的两个类型，不能这样

	system("pause");
	return 0;
}
#endif

#if 0
// 结构体声明
// 1.带tag的结构体类型声明
struct student
{
	int id;
	char name[20];
	int age;
	char sex[5];
};

// 2. 匿名结构体类型声明
struct
{
	int a;
	char b;
	float c;
}x;

struct
{
	int a;
	char b;
	float c;
}a[20], *p;

// 结构体的自引用
struct Node
{
	int data;
	struct Node* n;
};

// typedef是用来进行类型定义的
typedef struct Node
{
	int data;
	Node* n; // 相当于struct Node* n;
}Node; // 这里的Node就相当于struct Node 

// 结构体变量的定义和初始化
// 1.声明类型的同时，定义变量
struct Point
{
	int x;
	int y;
}p1;

// 2.直接定义
struct Point p2;

// 初始化
// 1. 定义变量的同时初始化
struct Point p3 = { 1, 2 };

typedef struct stu // 类型声明
{
	char name[25];
	int age;
}stu;
stu s = { "jia", 21 }; // 初始化

// 2. 结构体嵌套初始化
// 声明的同时定义并初始化
struct Node
{
	int data;
	struct Point p;
	struct Node* next;
}n1 = { 10, {4, 5}, NULL };

// 定义时进行初始化
struct Node n2 = { 1, { 2, 3 }, NULL };
#endif

#if 0
// 结构体内存对齐
// 修改默认对齐数
//#pragma pack(1) // 修改默认对齐数为1字节
// vs默认对齐数为8
typedef struct S1 // sizeof(S1) = 12 最大对齐数 = 4
{
	char a; // 1 对齐数1
	int b; // 8 对齐数4
	long c; // 12 对齐数4
}S1;
typedef struct S2 // sizeof(S2) = 24 最大对齐数 = 8
{
	short a; // 2 对齐数2
	double b; // 16 对齐数8
	S1* s1; // 24 结构体整体大小对齐到最大对齐数的整数倍
}S2;
//#pragma pack() // 取消设置的默认对齐数，还原为默认(4)

// 计算某变量相对于首地址的偏移

// 结构体传参：传结构体地址
struct S
{
	int data[100];
	int num;
}s = { {1,2,3}, 7 };

// 传结构体
void Print1(struct S s)
{
	cout << s.data << endl;;
	cout << s.num << endl;
}

// 传结构体地址
void Print2(struct S* s)
{
	cout << s->data << endl;;
	cout << s->num << endl;
}

int main()
{

	//cout << "修改默认对齐数为1，struct S2的大小为：" << sizeof(struct S2) << endl;
	//cout << "取消设置的默认对齐数，struct A的大小为：" << sizeof(struct A) << endl;
	
	//Print1(s); // 传结构体
	//Print2(&s); // 传结构体地址

	cout << "sizeof(S1) = " << sizeof(S1) << endl;
	cout << "sizeof(S2) = " << sizeof(S2) << endl;

	cout << sizeof(float) << endl;
	system("pause");
	return 0;
}
#endif

// this指针
#if 0
class A
{
public:
	void PrintA()
	{
		cout << _a << endl;
	}

	void Show()
	{
		cout << "Show()" << endl;
	}
private:
	int _a;
};

int main()
{
	A* const p = NULL;
	p->PrintA();
	p->Show();

	system("pause");
	return 0;
}
#endif

// 验证类对象内存布局
#if 0
class Student
{
public:
	char _name[20];
	char _sex[3];
	int _age;

public:
	void InitStu(char name[], char sex[], int age)
	{
		strcpy(_name, name);
		strcpy(_sex, sex);
		_age = age;
	}

	void PrintStu()
	{
		cout << _name << "-" << _sex << "-" << _age << endl;
	}

};

int main()
{
	Student s1, s2, s3;
	s1.InitStu("jia", "女", 21);
	s2.InitStu("ha", "男", 22);
	s3.InitStu("der", "男", 18);

	s1.PrintStu();
	s2.PrintStu();
	s3.PrintStu();

	cout << sizeof(s1) << endl;

	system("pause");
	return 0;
}
#endif

// this指针的理解：将下边代码翻译成c语言代码
#if 0
class Car
{
public:
	void SetPrice(int price)
	{
		_price = price;
	}
	void GetPrice()
	{
		cout << _price << endl;
	}
private:
	int _price;
};

int main()
{
	Car c;
	c.SetPrice(100);
	c.GetPrice();

	system("pause");
	return 0;
}

// 改为C语言：成员变量用结构体保存，成员函数变成全局函数即可
struct Car
{
	int _price;
};

void SetPrice(struct Car* This, int price)
{
	This->_price = price;
}

void GetPrice(struct Car* This)
{
	cout << This->_price << endl;
}

int main()
{
	struct Car c;
	SetPrice(&c, 100);
	GetPrice(&c);

	system("pause");
	return 0;
}
#endif

// 测试this指针在哪存储
#if 0
class Person
{
public:
	void SetAge(int age)
	{
		_age = age;
		cout << _age << endl;
	}
private:
	char _name[20];
	int _age;
};

int main()
{
	//Person p;
	//p.SetAge(21);

	system("pause");
	return 0;
}
#endif

// 类的六个默认成员函数
// 1. 构造函数：只负责初始化对象
// 函数名和类名相同，无返回值，对象实例化时编译器自动调用对应的构造函数
// 如果用户不显式定义构造函数，编译器会默认生成一个构造函数
// 构造函数可以重载

#if 0
class Date
{
public:
	// 无参构造
	//Date(){ }

	// 带参构造
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	/*void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}*/

	// ---------------------------------------------------------

	Date()
	{
		_year = 2021;
		_month = 4;
		_day = 17;
	}

	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

void TestDate()
{
	Date d1; // 调用无参构造
	Date d2(2021,4,17); // 调用带参构造

	//Date d3(); // 这是一个函数声明，该函数无参，返回一个Date类型的对象
}

void TestDate2()
{
	Date d;
}

int main()
{
	/*Date d1, d2;
	d1.SetDate(2021, 4, 17);
	d1.Display();

	d2.SetDate(2021, 4, 18);
	d2.Display();*/

	//TestDate2();

	Date d;

	system("pause");
	return 0;
}
#endif

#if 0
// 不显式定义构造函数
// 编译器可能会生成默认构造函数
class Date
{
public:

private:
	int _year;
	int _month;
	int _day;
};
#endif

// 编译器默认生成构造函数的4种情况
// 1. 类中包含另一个类成员对象，且类成员对象的类中定义了默认构造函数
// Time类显式定义构造函数，Date类不显式定义构造函数
// Date类中包含一个Time类对象
class Time
{
public:
	/*Time()
	{
	cout << "Time()" << endl;
	_hour = 0;
	_min = 0;
	_sec = 0;
	}*/
private:
	int _hour;
	int _min;
	int _sec;
};

class Date
{
private:
	// 基本类型(内置类型)
	int _year;
	int _month;
	int _day;

	Time _t; // 自定义类型
};

// 2.基类定义了默认构造函数的派生类，创建派生类对象时
class Base
{
public:
	Base()
	{
		cout << "Base()" << endl;
	}
};

class Derived :public Base
{
public:
	int _d;
};


int main()
{
	//Date d;

	Derived d;
	system("pause");
	return 0;
}