#include<iostream>
#include<windows.h>
using namespace std;

// 列表初始化

#include<vector>
#include<map>
// 内置类型的列表初始化
#if 0
int main()
{
	// 内置类型变量
	int a1 = 10;
	int a2(10);
	int a3{ 10 };

	// 数组
	int arr1[5]{1, 2, 3, 4, 5};
	int arr2[]{1, 2, 3};

	// 动态数组，在C++98中不支持
	int* arr3 = new int[5]{1, 2, 3, 4, 5};

	// 标准容器
	vector<int> v{ 1, 2, 3, 4, 5 };
	map<string, string> m{ { "orange", "橙子" }, { "mango", "芒果" } };


	system("pause");
	return 0;
}
#endif

// 自定义类型的列表初始化
#if 0
class Point
{
public:
	Point(int x=0, int y=0)
		: _x(x)
		, _y(y)
	{}

private:
	int _x;
	int _y;
};

#include<initializer_list>
namespace jia
{
	template<class T>
	class vector
	{
		typedef T* iterator;
	public:
		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{ }

		vector(initializer_list<T> l)
			:_start(new T[l.size()])
			, _finish(_start)
		{
			for (auto& e : l)
				*_finish++ = e;

			_endofstorage = _finish;
		}

		vector<T>& operator=(initializer_list<T> l)
		{
			delete[] _start;
			for (auto& e : l)
				*_finish++ = e;

			return *this;
		}

		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstorage = nullptr;
			}
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
}


int main()
{
	// 标准库支持单个对象的列表初始化
	//Point p{ 1, 2 };

	// 多个对象想要支持列表初始化，需要给该类(模板类)添加一个带有initializer_list类型参数的构造函数即可
	jia::vector<int> v1{ 1, 2, 3 };

	/*
	如果没有提供列表格式的赋值
	1. 先用{4，5，6}调用列表初始化格式的构造函数创建一个临时对象
	2. 用临时对象给v1赋值
	3. 赋值完成后，临时对象就销毁了
	*/
	v1 = { 4, 5, 6 };

	system("pause");
	return 0;
}
#endif

/*
auto使用的前提是：必须要对auto声明的类型进行初始化，否则编译器无法推导出auto的实际变量
auto不能作为函数参数或者函数返回值
C++98中支持的RTTI(运行时类型识别)：
1）typeid：只能查看类型，不能用其结果定义类型
2）dynamic_cast：只能应用于含有虚函数的继承体系中
RTTI缺点：降低程序运行效率

decltype：根据表达式的实际类型推演定义变量时所用的类型
*/
#if 0
void* GetMemory(size_t size)
{
	cout << "调用GetMemory()" << endl;
	return malloc(size);
}

// C语言中的定义方式
// 定义与Getmemory函数类型相同的函数指针类型 --- 函数指针类型
typedef void* (*CF)(size_t size); // pF是一个类型
// 定义与Getmemory函数类型相同的函数指针类型 --- 函数指针变量
void* (*pFun)(size_t size); // pFun变量可以指向任意一个返回值为void*，参数列表为(size_t size)的函数

typedef decltype(&GetMemory) CPPF; // PF是一个类型
CPPF pf; // pf是函数指针类型的变量
/*
int arr[10]
arr：数组名，也是数组首元素地址
数组类型：去掉数组名就是数组类型 ---> int[10]

void* GetMemory(size_t size)
GetMemory：是函数名，也是函数入口地址
函数类型：去掉函数名就是函数类型void* _cdecl(size_t) 
函数指针类型：void* (*_cdecl)(size_t) 
函数指针变量：void* (*p_cdecl)(size_t)

decltype(GetMemory)：推演出来的是函数类型
decltype(&GetMemory)：推演出来的是函数指针类型

定义函数指针变量
decltype(&GetMemory) pf;
typedef decltype(&GetMemory) PF; PF pf;
*/

int main()
{
	int a = 10;
	double b = 3.14;
	auto c = a + b;

	// 推演表达式类型作为变量的定义类型
	decltype(a + b) d;
	cout << typeid(d).name() << endl;

	// 推演函数返回值类型
	// 如果直接在decltype之后跟函数名字，推导出来的是函数类型
	cout << typeid(decltype(GetMemory)).name() << endl;
	 // 如果在decltype之后跟的是函数调用，推导出来的是函数返回值类型 注意：在推到期间不会调用该函数
	cout << typeid(decltype(GetMemory(100))).name() << endl; // 函数返回值类型

	pFun = GetMemory; // pFun是函数指针变量，指向GetMemory函数
	pFun(10); // 相当于GetMemory(10)

	// 验证：
	cout << typeid(CF).name() << endl;
	cout << typeid(CPPF).name() << endl;

	// 在C语言中，数组名只有在sizeof和&之后，才代表数组本身
	// 数组名在decltype后数组名也表示数组本身
	int arr[10];
	cout << typeid(decltype(arr)).name() << endl;

	system("pause");
	return 0;
}
#endif
#if 0
template<class T1, class T2>
auto Add(const T1& left, const T2& right)->decltype(left+right) // auto是一个占位符
{
	return left + right;
}

int main()
{
	Add(1, 2.3);

	system("pause");
	return 0;
}
#endif 

// 右值引用
#if 0
int main()
{
	// C++98中的引用
	int a = 10;
	int& ra = a;

	// C++11中的右值引用
	int&& rra = 100;

	// 注意：右值引用不能直接引用左值
	//int&& rrb = a;
	system("pause");
	return 0;
}
#endif

#if 0
class A{};

A Get()
{
	A a;
	return a;
}


int& GetI()
{
	static int a = 1;
	return a;
} 

int main()
{
	int a = 10;
	int b = 20;

	const int c = 100;
	//int&& rrc = c; // c可以取地址，所以是左值

	// 如果表达式的运行结果是一个临时变量或对象，认为是右值
	int&& rr = a + b; // a+b的结果是一个临时变量
	A&& rr1 = Get(); // Get()返回一个临时对象

	//int&& rrb = GetI(); // a是一个全局变量，是左值

	// 如果表达式运行结果或单个变量是一个引用，则认为是左值
	int& ra = a;
	//int&& rra = ra; 

	system("pause");
	return 0;
}
#endif

// C++98：引用：可以引用左值，也可以引用右值
// C++11：右值引用：一般只能引用右值
#if 0
void TestRef98()
{
	// C++98 引用
	// 普通类型的引用
	int a = 10;
	int& ra = a; // 引用的是左值
	//int& rb = 10; // 普通类型的引用不能引用右值

	// const类型的引用
	// 在C++98中，const类型的引用实际是万能引用
	const int b = 100;
	const int& rb = b; // const类型引用可以引用左值
	const int& rc = 100; // const类型引用可以引用右值

}

int Get()
{
	int x;
	return x;
}

void TestRef11()
{
	int&& rra = 10;

	int a = 10;
	int b = 20;
	int&& rrb = a + b;

	// 以值的方式返回结果
	int&& rc = Get();

	//int&& rrd = a;
	int&& rre = move(a); // 引用左值的方式

	const int&& a = 100;
}
int main()
{
	TestRef98();
	TestRef11();

	system("pause");
	return 0;
}
#endif

#if 0
#pragma warning(disable:4996)
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			_str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(new char[strlen(s._str)+1])
	{
		strcpy(_str, s._str);
	}

	String(String&& s)
		:_str(s._str)
	{
		s._str = nullptr;
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* temp = new char[strlen(s._str) + 1];
			strcpy(temp, s._str);
			delete[] _str;
			_str = temp;
		}
		return *this;
	}

	String& operator=(String&& s)
	{
		delete[] _str;
		_str = s._str;
		s._str = nullptr;

		return *this;
	}

	String operator+(const String& s)const
	{
		char* temp = new char[strlen(s._str) + strlen(_str) + 1];
		strcpy(temp, _str);
		strcat(temp, s._str);

		String ret(temp);
		delete[] temp;
		return ret; // 返回值是ret的一份临时拷贝对象retCopy，ret是右值，调用移动构造
	}

	char& operator[](int index)
	{
		return _str[index];
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};

void TestString1()
{
	String s1 = "hello";
	String s2 = "world";

	String s3;
	/*
	在C++98中，s3 = s1 + s2有两步操作：
	1. 调用operator+函数将s1和s2字符串拼接起来，在operator+函数中，由于不能改变s1和s2，所以使用const修饰，所以要创建一个临时变量temp来保存s1和s2的拼接结果
	   返回时要返回一个string对象，所以要用temp的空间创建一个对象ret；但是ret是函数栈上的对象，出函数作用域要销毁，所以返回值要拷贝构造一个ret的临时对象retCopy
	   retCopy拷贝完成后，ret就会销毁，ret中的_str的资源要释放
	2. 调用赋值运算符重载函数，将retCopy赋值给s3，retCopy赋值结束后也要销毁，retCopy中的_str的资源也要释放
	3. 所以，在这种方式下，有三次开辟空间的过程，即ret,retCopy,s3，但是每个对象的资源都只有很短的生命周期，这种对象是将亡值，也就是右值，可以通过右值引用来提高程序运行效率
	4. 所以，想要通过资源转移的方式减少开辟资源的消耗

	C++11中的移动语义就可以解决上述问题
	移动构造和移动赋值运算符重载
	*/
	s3 = s1 + s2; // s1+s2的结果retCopy是右值，调用移动赋值
}

// move的误用
void TestString2()
{
	String s1 = "hello";
	String s2(move(s1));
	String s3(s2);

	/*
	s1是一个左值，将s1用move转换为右值，构造s2，会调用移动构造，将s1中的资源转移给s2，即s1._str==nullptr
	之后再使用s1访问资源就会出错
	*/
	//s1[0] = 'H';
}

class Person
{
public:
	Person(char* name, char* sex, int age)
		: _name(name)
		, _sex(sex)
		, _age(age)
	{}

	Person(const Person& p)
		: _name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{ }

#if 0
	/*
	p引用的是右值，但是p中的_name和_sex依旧是左值，会调用String类中拷贝构造
	但是p是一个将亡值，所以可以把p中的资源转移给this指向的对象
	所以要将_name和_sex转化为右值，让其调用String类中的运动构造
	*/
	Person(Person&& p)
		:_name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{ }
#endif

	// move的正确使用！
	Person(Person&& p)
		:_name(move(p._name))
		, _sex(move(p._sex))
		, _age(p._age)
	{ }

private:
	String _name;
	String _sex;
	int _age;
};

Person GetPerson()
{
	Person person("jia", "女", 21);
	return person; // person是一个将亡值，值返回要创建临时对象，调用Person中的移动构造
}

int main()
{
	TestString1();
	TestString2();

	GetPerson();

	system("pause");
	return 0;
}
#endif

// 完美转发---std::forward<T>的使用
#if 0
void Fun(int& x)
{
	cout << "lvalue ref" << endl;
}

void Fun(int&& x)
{
	cout << "rvalue ref" << endl;
}

void Fun(const int& x)
{
	cout << "const lvalue ref" << endl;
}

void Fun(const int&& x)
{
	cout << "const rvalue ref" << endl;
}

template<class T>
/*
PerfectForward为转发的函数模板，Fun为实际目标函数
完美转发：目标函数总希望将参数按照传递给转发函数的实际类型转给目标函数
即，函数模板在向目标函数传参时，
如果传递给函数模板的实参是左值，传递给目标函数的也是左值
如果传递给函数模板的实参是右值，传递给目标函数的也是右值
*/
void PerfectForward(T &&t)
{
	Fun(t); //
	//Fun(std::forward<T>(t));
}

int main()
{
	PerfectForward(10); // 普通右值引用

	int a;
	PerfectForward(a);
	PerfectForward(move(a));

	const int b = 7;
	PerfectForward(b);
	PerfectForward(move(b));

	system("pause");
	return 0;
}
#endif

// 右值引用给中间临时变量取别名
#if 0
#pragma warning(disable:4996)
class String
{
public:
	String(const char* str = "")
	{
		cout << "String():" << this << endl;
		if (nullptr == str)
			_str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String(String&& s)
		:_str(s._str)
	{
		cout << "String(&&):" << this << endl;
		s._str = nullptr;
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* temp = new char[strlen(s._str) + 1];
			strcpy(temp, s._str);
			delete[] _str;
			_str = temp;
		}
		return *this;
	}

	String& operator=(String&& s)
	{
		delete[] _str;
		_str = s._str;
		s._str = nullptr;

		return *this;
	}

	String operator+(const String& s)const
	{
		char* temp = new char[strlen(s._str) + strlen(_str) + 1];
		strcpy(temp, _str);
		strcat(temp, s._str);

		String ret(temp);
		delete[] temp;
		return ret; // 返回值是ret的一份临时拷贝对象retCopy，ret是右值，调用移动构造
	}

	char& operator[](int index)
	{
		return _str[index];
	}

	~String()
	{
		cout << "~String():" << this << endl;
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};

int main()
{
	String s1;
	String s2 = "hello";
	String s3 = "world";
	s1 = s2 + s3; // s2+s3的返回值retCopy在赋值结束后会销毁

	// s3和s4都是右值引用给中间临时变量取别名的写法
	String s4 = s2 + s3; // s2+s3的返回值retCopy在赋值结束后不会销毁，s4就是retCopy，延长了retCopy的生命周期
	String&& s5 = s2 + s3;

	system("pause");
	return 0;
}
#endif

/*
lambda表达式
应用场景：
1. 在比较中，自定义类型的元素比较，需要用户定义比较器，有两种方式：函数指针或者封装成类，在类中重载()
   如果每次比较逻辑不同，还要去实现多个类，特别是相同类的命名很麻烦，不能重复
2. C++98中，在一个函数中不能定义另一个函数，且函数中要用到的内部定义的函数出现次数较多，但是只在该函数中使用
lambda表达式结构
[捕获列表](参数列表)multable->返回值类型{函数体}
*/

#include<algorithm>
#include<functional>
// 在C++98中，如果想要对一个数据集合中的元素进行排序，可以使用std::sort方法
#if 0
int main()
{
	int arr[] = { 6, 4, 2, 1, 7, 5, 3 };

	std::sort(arr, arr + sizeof(arr) / sizeof(arr[0])); // 第三个参数不传，默认是升序排列
	// 如果需要降序，需要改变元素的比较规则
	std::sort(arr, arr + sizeof(arr) / sizeof(arr[0]),greater<int>());

	return 0;
}
#endif

#if 0
struct Goods
{
	string _name;
	double _price;
};

// 如果待排序元素为自定义类型，需要用户定义排序时的比较规则
// 两种方式：函数指针或封装类重载()
struct Compare
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price <= gr._price;
	}
};

int main()
{
	Goods gds[] = { { "苹果", 2.1 }, { "香蕉", 3 }, { "芒果", 5 } };
	//sort(gds, gds + sizeof(gds) / sizeof(gds[0]), Compare());

	// 采用lambda表达式
	sort(gds, gds + sizeof(gds) / sizeof(gds[0]), [](const Goods& gl, const Goods& gr)->bool{
		return gl._price >= gr._price;
	});

	system("pause");
	return 0;
}
#endif

#if 0
int main()
{
	int a = 10, b = 20;

	// lambda表达式实现相加
	auto ADD = [a,b](int left, int right)->int{ return left + right; };
	auto add = [a](int left, int right)mutable->int{ a += 2; return left + right; }; 

	cout << ADD(a, b) << endl;
	cout << add(a, b) << endl;
	cout << a << endl;

	// 以值的方式捕获父作用域中的变量，&a不相同，lambda表达式中的a是a的临时拷贝
	auto Add = [a](int left, int right)->int{ cout << &a << endl; return left + right; };
	Add(a, b);
	cout << &a << endl;

	// 以引用的方式捕获父作用域中的变量，&a相同
	auto Sub = [&a](int left, int right)->int{ a += 2; cout << &a << endl; return left - right; };
	Sub(a, b);
	cout << a << endl;
	cout << &a << endl;

	system("pause");
	return 0;
}
#endif

#if 0
class Date
{
public:
	void Test()
	{
		int a = 1, b = 2, c = 3;

		// 以值的方式捕获父作用域中所有变量，包括this指针
		auto l1 = [=]
		{
			cout << a << endl;
			cout << b << endl;
			cout << c << endl;

			cout << this << endl;
			this->_year = 2021;
			this->_month = 5;
			this->_day = 30;

			// 不能捕获父作用域中定义在lambda表达式后的变量
			//cout << d << endl;
		};
		int d;

		// 不能重复捕获
		/*auto l2 = [=, a]
		{
			cout << a << endl;
			cout << b << endl;
			cout << c << endl;

			cout << this << endl;
			this->_year = 2021;
			this->_month = 5;
			this->_day = 30;
		};*/
		

		// 以引用的方式捕获父作用域中所有变量，包括this指针
		int* pa = &a;
		auto l3 = [&]
		{
			a = b = c = 7;
			cout << a << endl;
			cout << b << endl;
			cout << c << endl;

			cout << this << endl;
			this->_year = 2021;
			this->_month = 5;
			this->_day = 30;

			//this = nullptr; // 不能修改this
			pa = &b;
		};
		l3();
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
		cout << this->_year << endl;
		cout << this->_month << endl;
		cout << this->_day << endl;

		// 不能重复引用捕获
		/*auto l4 = [&, &a]
		{
			a = 15;

			cout << this << endl;
			this->_year = 2021;
			this->_month = 5;
			this->_day = 30;
		};
		*/

		// 表示除了a以值的方式捕获其他父作用域中所有变量按照引用方式捕获
		auto l5 = [&,a]
		{
			cout << a << endl;
			cout << b << endl;
			cout << c << endl;

			cout << this << endl;
			this->_year = 2021;
			this->_month = 5;
			this->_day = 30;
		};


	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d;
	d.Test();

	system("pause");
	return 0;
}
#endif

// 在块作用域以外的lambda表达式的捕获列表必须为空
#if 0
int g_a = 7;
auto l= []{ };
//auto l = [g_a]{};
#endif

#if 0
void fun()
{
	int c = 20;
}

int main()
{
	int a = 7;

	if (true)
	{
		int b = 10;
		// l1的父作用域就是if的花括号
		auto l1 = [a]{
			cout << a << endl;
		};
	}
	
	// 只能捕获lambda表达式父作用域中的变量
	// 不能捕获其他块作用域的变量
	//auto l2 = [b]{ };
	// 不能捕获非全局作用域的变量
	//[c]{};
}
#endif

// lambda表达式在底层实现上也是仿函数的方式
#if 0
class Rate
{
public:
	Rate(double rate) : _rate(rate)
	{}
	double operator()(double money, int year)
	{
		return money * _rate * year;
	}
private:
	double _rate;
};
int main()
{
	// 函数对象
	double rate = 0.49;
	Rate r1(rate);
	r1(10000, 2);
	// lamber
	auto r2 = [=](double monty, int year)->double{return monty*rate*year; };
	r2(10000, 2);
	return 0;
}
#endif

// C语言中的类型转换
#if 0
int main()
{
	// C语言中的隐式类型转化可能会有中间变量
	double a = 12.34;
	//int& ra = a;
	/*
	引用必须两个变量类型一致，为了让ra引用a，只能用a的整数部分创建一个临时变量，让ra去引用临时变量
	由于临时变量不能取地址也不能修改，所以临时变量具有常性，所以引用时要加const
	*/
	const int& ra = a; 

	/*
	验证：ra引用的是临时变量，而不是a
	修改a的值，但是ra没有变，而且a和ra的地址也不同
	*/
	a = 23.45;
	cout << a << endl;    
	cout << ra << endl;
	cout << &a << endl;
	cout << &ra << endl;

	// 将a的地址按照int*类型的地址解析 不会创建临时变量
	// 即a的空间是8字节，pa只能访问4字节内容
	int* pa = (int*)&a;
	cout << &a << endl;
	cout << pa << endl;

	// 在C++中，const修饰的内容编译器认为是一个常量，而且具有宏替换的效果
	const int b = 7;
	int* pb = (int*)&b; // &b的类型是const int*，这里强转为int*，相当于去掉const
	*pb = 10;
	//b = 12; // 常量不能修改
	cout << b << endl; // 在编译时已经替换为7了，所以即使修改了b，打印结果依旧是7
	cout << *pb << endl;


	system("pause");
	return 0;
}
#endif

// static_cast、reinterpret_cast、const_cast的用法
#if 0
int main()
{
	double d = 12.34;
	int a = static_cast<int>(d);

	int* pd = reinterpret_cast<int*>(&d);

	// reinterpret_cast可以将一个指针转换为整数，再将整数转换为指针，转换之后的指针依旧可以拿到原指针的值
	int c = 10;
	int* pc = &c;
	cout << *pc << endl;
	int rc = reinterpret_cast<int>(pc);
	int* rpc = reinterpret_cast<int*>(rc);
	cout << *rpc << endl;

	// const_cast用来删除变量的const属性
	const int e = 7;
	int& re = const_cast<int&>(e);
	int* pe = const_cast<int*>(&e);



	system("pause");
	return 0;
}
#endif

// dynamic_cast的用法
#if 0
class B
{
public:
	virtual void f(){}
};

class D :public B
{
public:
	void TestD()
	{
		cout << "TestD()" << endl;
	}
};

void func(B* pb)
{
	// static_cast关闭或挂起了正常的类型检查，可能会出错
	D* pd1 = static_cast<D*>(pb);
	// dynamic_cast会先检查是否能够转化成功，能成功则转，否则返回0
	D* pd2 = dynamic_cast<D*>(pb);

	cout << "pd1:" << pd1 << endl;
	cout << "pd2:" << pd2 << endl;

	pd1->TestD();
	pd2->TestD();
}

int main()
{
	B b;
	D d;
	func(&b); // 基类指针指向基类对象
	func(&d);

	system("pause");
	return 0;
}
#endif

// explicit关键字
#if 0
class A
{
public:
	explicit A(int a)
	{
		cout << "A(int)" << endl;
	}

	A(const A& a)
	{
		cout << "A(const A&)" << endl;
	}

private:
	int _a;
};

int main()
{
	A a1(1);

	/*
	如果单参构造函数不加explicit
	1. 调用单参构造一个匿名对象
	2. 用匿名对象给a1赋值

	加了explicit关键字就不能这样赋值了
	*/
	//a1 = 1; 

	//A a2 = 1;

	system("pause");
	return 0;
}
#endif

// 线程库
#include<thread>

#if 0
void TFunc(int a)
{
	cout << a << endl;
	cout << "TFunc()" << endl;
}

class TF
{
public:
	void operator()()
	{
		cout << "TF" << endl;
	}
};

int main()
{
	thread t1; // 创建一个对象，但是实际上没有创建线程

	// 传函数指针
	thread t2(TFunc,7); // 第一个为线程要做的事，后边的是函数的参数

	// 仿函数：先创建对象，然后传递对象
	TF f;
	thread t3(f);

	// lambda表达式
	thread t4([](int a){
		cout << "Lambda" << endl;
		cout << a << endl;
	}, 12);


	system("pause");
	return 0;
}
#endif

// 线程函数的参数是以值拷贝的方式拷贝到线程栈空间的

#if 0
void ThreadFunc1(int& ra) // ra实际上引用的是实参a在函数调用栈中的拷贝，所以不能通过ra修改外部实参a的值
{
	cout << &ra << endl;
	ra += 10;
}

void ThreadFunc2(int* pa) // pa实际上引用的是&a在函数调用栈中的拷贝，但是拷贝中存放的就是a的地址，所以通过pa可以修改外部实参a的值
{
	cout << pa << endl;
	*pa += 10;
}

int main()
{
	int a = 7;
	cout << &a << endl;

	/*thread t1(ThreadFunc1, a);
	t1.join();
	cout << a << endl;*/

	/*thread t2(ThreadFunc2, &a);
	t2.join();
	cout << a << endl;*/

	// 如果一定要用引用方式，可以使用std::ref
	thread t3(ThreadFunc1, std::ref(a));
	t3.join();
	cout << a << endl;

	system("pause");
	return 0;
}
#endif