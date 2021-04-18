#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

// 1.普通命名空间
namespace N1
{
	int a=1;
	int Add(int left, int right)
	{
		return left + right;
	}
}

// 2. 命名空间可以嵌套
namespace N2
{
	int a=2, b=2;
	int Add(int left, int right)
	{
		return left + right;
	}

	namespace N3
	{
		int c=3, d=3;
		int Sub(int left, int right)
		{
			return left - right;
		}
	}
}

// 3. 同一个工程允许多个相同名称的命名空间，编译器最后会合成同一个命名空间
namespace N1
{
	int Mul(int left, int right)
	{
		return left*right;
	}
}

// 4. 命名空间的使用
namespace N
{
	int a = 10;
	int b = 20;
	int Add(int left, int right)
	{
		return left + right;
	}

	int Sub(int left, int right)
	{
		return left - right;
	}
}

#if 0
int main()
{
	// 命名空间中成员的使用
	// 1.加命名空间名称及作用域限定符
	printf("%d\n", N1::a);

	system("pause");
	return 0;
}
#endif

#if 0
// 2.使用using将命名空间中成员引入
using N2::a;
int main()
{
	printf("%d\n", a);
	printf("%d\n", N2::N3::c);

	system("pause");
	return 0;
}
#endif

#if 0
// 3.使用 using namespace 命名空间名称 引入
using namespace N;
int main()
{
	printf("%d\n", a);
	printf("%d\n", b);

	cout << "用N中的Add:" << Add(7, 8) << endl;
	cout << "用N1中的Add:" << N1::Add(a,b) << endl;

	system("pause");
	return 0;
}
#endif

#if 0
// 缺省参数
void TestFunc(int a = 0)
{
	cout << a << endl;
}

// 全缺省参数
void TestFunc1(int a = 1, int b = 2, int c = 3)
{
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
}

// 半缺省参数
// 半缺省参数必须从右往左给出，不能间隔着给
void TestFunc2(int a, int b = 2, int c = 3)
{
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
}
int main()
{
	//TestFunc();
	//TestFunc(10);

	//TestFunc1();
	//TestFunc1(7); // a=7,b、c采用默认值
	//TestFunc1(7, 8); // a=7, b=8, c采用默认值
	//TestFunc1(4, 5, 6);

	TestFunc2(1); // a=1, b=2, c=3
	TestFunc2(7, 8); // a=7, b=8, c=3
	TestFunc2(7, 8, 9); // a=7, b=8, c=9

	system("pause");
	return 0;
}
#endif

#if 0
// 函数重载
// 同一作用域 同名 参数列表(参数个数 或 参数类型 或 参数顺序)必须不同
int Add(int left, int right)
{
	return left + right;
}

int Add(int a, int b, int c)
{
	return a + b + c;
}

double Add(double a, double b)
{
	return a + b;
}

double Add(int a, double b)
{
	return a + b;
}

int main()
{
	cout << Add(1, 2) << endl;
	cout << Add(1, 2, 3) << endl;
	double ret = Add(1.0, 2.0);
	printf("%f\n", ret);
	cout << Add(1, 2.0) << endl;

	system("pause");
	return 0;
}
#endif

#if 0
#include "test.h"
int main()
{
	Add(1, 2);
	return 0;
}
#endif

// 引用
void TestRef()
{
	int a = 10;
	int b = 1;
	// 一个变量可以有多个引用
	int& ra = a;  // 引用在定义时必须初始化
	int& rra = a;

	// 下边三个地址一样，说明它们是同一个变量
	printf("%p:%d\n", &a, a);
	printf("%p:%d\n", &ra, ra);
	printf("%p:%d\n", &rra, rra);
}

// 引用一旦初始化就不能再引用其他实体
// 意思是，就算引用了其他实体，它的地址也并没有改变，始终指向初始化时引用的实体
void TestRef1()
{
	string s1 = "a";
	string s3 = "c";

	string& s2 = s1;
	s2 = s3;

	printf("%p\n", &s1);
	printf("%p\n", &s2);
	printf("%p\n", &s3);
}

void TestConstRef()
{
	const int a = 10;
	//int& ra = a; // 这种写法是错误的，因为a为常量
	const int& ra = a; // 正确写法

	//int& b = 7; //这种写法也是错误的，因为7是常量
	const int& b = 7; // 正确写法

	double c = 12.34;
	const int& rc = c; // 虽然可以通过编译，但是最好类型一致
	cout << "修改前rc=" << rc << endl;
	c = 56.78; // 这里改变了c的值，如果rc是c的引用，那么rc的值也应该变成56
	cout << "修改后rc=" << rc << endl; // 但是打印结果还是12，说明rc根本不是c的引用

}

// 引用做参数

// 值传参，会发生临时拷贝，交换的是临时拷贝
// 调用Swap1：交换结果无改变
void Swap1(int left, int right)
{
	int temp = left;
	left = right;
	right = temp;
}

// 引用传参，传入的是变量实体
// 调用Swap：结果交换了
void Swap(int& left, int& right)
{
	int temp = left;
	left = right;
	right = temp;
}

// 引用做返回值
// 
//int& Add(int left, int right) // 还没明白
//{
//	return left + right; 
//}

int& Add(int a, int b)
{
	int c = a + b;
	return c;
}

#if 0
int main()
{
	//TestRef();
	//TestRef1();
	//TestConstRef();

	//int a = 1, b = 7;
	//cout << "用swap1交换前a和b：" << a << "," << b << endl;
	//Swap1(a, b);
	//cout << "用swap1交换后a和b：" << a << "," << b << endl;
	//
	//a = 1, b = 7;
	//cout << "用swap交换前a和b：" << a << "," << b << endl;
	//Swap(a, b);
	//cout << "用swap交换后a和b：" << a << "," << b << endl;

	/*int& ret = Add(1, 2);
	Add(3, 4);
	printf("%d\n", ret);*/

	//cout << "Add(1,2):" << ret << endl; // 7

	system("pause");
	return 0;
}
#endif


// 引用和指针
void Swap_p(int* left, int* right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}

void Swap_r(int& left, int& right)
{
	int temp = left;
	left = right;
	right = temp;
}

#if 0
int main()
{
	//int a = 10;

	//int& ra = a; // ra就是a
	//ra = 20; // 改ra就相当于改a

	//int* pa = &a; // pa是指向a的变量，pa中保存的是a的地址
	//*pa = 20; // pa解引用

	int a = 10;
	int b = 20;

	Swap_p(&a, &b);   // 调用int*
	Swap_r(a, b);     // 调用int&

	int* pa = &a;
	*pa = 100;

	int& ra = a;
	ra = 100;
	
	system("pause");
	return 0;
}
#endif

#if 0
int main()
{
	int a = 10;
	int& ra = a;

	int* p = &a;
	// 访问实体的方式
	cout << ra << endl; // 引用访问实体由编译器处理
	cout << *p << endl; // 指针访问实体需要显式解引用

	int b = 20;
	p = &b; // 指针可以在任何时候指向任何一个同类型实体

	char c = 'a';
	char& rc = c;
	char* pc = &c;

	rc++; // 引用自加 = 引用实体的值+1
	pc++; // 指针自加 = 指针向后偏移一个类型的大小
	cout << rc << endl;
	cout << pc << endl;
	cout << sizeof(rc) << endl; // sizeof(引用) = 引用类型的大小
	cout << sizeof(pc) << endl; // sizeof(指针) = 指针中存储的变量的地址所占字节个数(32位平台下占4字节)

	// 有多级指针
	int*p1;
	int** p2;
	int*** p3;

	int d = 10;
	int& rd = d;
	// 没有多级引用
	//int&& rrd = d;
	//int&&& rrrd = d;

	// C++11中提出的右值引用
	const int&& rrd = 10;
	
	system("pause");
	return 0;
}
#endif

// auto的使用
int Func()
{
	return 10;
}
int TestAuto()
{
	int a = 10;
	auto b = a;
	auto c = 'a';
	auto d = Func();

	cout << typeid(b).name() << endl; // int
	cout << typeid(c).name() << endl; // char 
	cout << typeid(d).name() << endl; // int

	return 0;
}

// auto不能作为函数的参数
//void TestAuto1(auto a) // 错误示范
//{ }

// auto不能直接用来声明数组
//void TestAuto2() // 错误示范
//{ 
//	int a[] = { 1, 2, 3 };
//	auto b[] = { 4, 5, 6 };
//}

#if 0
int main()
{
	//TestAuto();

	// auto与指针和引用结合起来使用
	int x = 10;
	// 用auto声明指针类型时，用auto和auto*没有任何区别
	auto a = &x;
	auto* b = &x;

	// 用auto声明引用类型时必须加&
	int& rx = x;
	auto& c = rx;

	cout << typeid(a).name() << endl; // int*
	cout << typeid(b).name() << endl; // int*
	cout << typeid(c).name() << endl; // int

	*a = 20;
	cout << x << endl; // 20
	*b = 30;
	cout << x << endl; // 30
	c = 40;
	cout << x << endl; // 40

	// 在同一行声明多个变量时，这些变量必须是相同类型，否则编译器会报错
	// 因为编译器只对第一个类型进行推导，然后用推导出来的类型定义其他变量
	auto a = 1, b = 2; // 正确写法
	//auto c = 3, d = 4.0; // 报错
	
	system("pause");
	return 0;
}
#endif

#if 0
// auto和范围for(C++11)
// 范围for的括号由":"范围两部分，第一部分是范围内用于迭代的变量，第二部分表示被迭代的范围
void TestFor()
{
	int array[] = { 1, 2, 3, 4, 5 };
	// 给array中每个元素乘2
	for (auto& e : array) // 注意：auto = int，e相当于是array中单个元素的别名
	{
		e *= 2;
		cout << typeid(e).name() << endl; // int
	}
	
	for (auto e : array) // auto a = auto* a
	{
		cout << e << " ";
		cout << typeid(e).name() << endl; // int
	}
}

int main()
{
	TestFor();

	system("pause");
	return 0;
}
#endif

// 宏
#if 0
#define MAX 10

int main()
{
	const int a = 10;
	int b = 20;

	int* pa = (int*)&a;
	*pa = 100;

	printf("%d\n", MAX);
	printf("%d\n", a);
	printf("%d\n", b);

	cout << a << endl;
	cout << *pa << endl;

	return 0;
}
#endif

// 宏函数的定义及使用
#if 0
#define SQUARE(x) x*x

int main()
{
	int a = 5;

	cout << SQUARE(a) << endl;
	cout << SQUARE(a+1) << endl; // 11

	system("pause");
	return 0;
}

#define MAX(a,b) (a>b ? a:b)

int main()
{
	int a = 10;
	int b = 20;

	// MAX(++b, a)
	// -> ++b>a ? ++b : a
	// -> 21>10 ? 22 : 10
	cout << MAX(++b, a) << endl; //22

	system("pause");
	return 0;
}
#endif

// 内联函数
inline int fun(int left, int right)
{
	return left + right;
}

int main()
{
	int ret = Add(1, 2);
	return 0;
}