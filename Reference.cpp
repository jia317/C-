#include<iostream>
#include<Windows.h>
using namespace std;

#if 0
void TestRef()
{
	const int a = 10;
	//int& ra = a; // 这种写法是错误的，因为a为常量
	const int& ra = a; // 正确写法

	//int& b = 7; //这种写法也是错误的，因为7是常量，不能通过编译
	const int& b = 7; // 正确写法

	double c = 12.34;
	const int& rc = c; // 虽然可以通过编译，但是最好类型一致
	cout << "修改前rc=" << rc << endl;
	c = 56.78; // 这里改变了c的值，如果rc是c的引用，那么rc的值也应该变成56
	cout << "修改后rc=" << rc << endl;
}

int main()
{
	/*int a = 10;
	const int& ra = a;
	a = 17;
	cout << "ra = " << ra << endl;

	double b = 12.34;
	const int& rb = b;
	b = 56.78;
	cout << "rb = " << rb << endl;*/

	TestRef();

	system("pause");
	return 0;
}
#endif

// 引用的使用场景
// 1. 简化代码
// 例1：
#if 0
struct A
{
	int x;
	int y;

	struct B
	{
		int i;
		int j;
	};

	B b;
};

// 例2：交换int*类型的指针函数
// C语言
void Swap(int** l,int** r)
{
	int temp = *l;
	*l = *r;
	*r = temp;
}

void Swap(int& pa, int& pb)
{
	int temp = pa;
	pa = pb;
	pb = temp;
}
int main()
{
	//A a;
	//a.b.i = 12;

	//// 假设之后会经常用到a.b.i这个变量，那么每一次使用都要写很长的变量名
	//// 如果不用引用
	//a.b.i = 10;

	//// 用引用
	//int &ri = a.b.i;
	//ri = 22;
	//cout << "ri = " << ri << endl;

	const int a = 10;
	int b;
	int* pa = (int*)&a;
	int* pb = &b;
	Swap(&pa, &pb);
	Swap(pa, pb);

	system("pause");
	return 0;
}
#endif

#if 0
// 2. 引用类型作为函数形参
// C语言Swap
void Swap(int* l, int* r)
{
	int temp = *l;
	*l = *r;
	*r = temp;
}

// C++引用传参
void Swap(int& l, int& r)
{
	int temp = l;
	l = r;
	r = temp;
}

// 如果不想通过形参来改变外部实参，可以用const类型引用作为形参类型
void Print(const int& x)
{
	cout << x << endl;
}

int main()
{
	int a = 3;
	int b = 8;

	Swap(&a, &b);
	Swap(a, b);

	system("pause");
	return 0;
}
#endif

int main()
{
	const int a = 10;
	int* pa = (int*)&a;

	*pa = 100;

	/*
	在C++中，被const修饰的变量一般称为常量，该常量具有宏替换的效果
	这里的宏替换是在编译阶段，在所有使用const常量的地方用常量的值替换该常量
	注意：除&常量外
	*/
	cout << a << endl; // 在编译阶段进行了替换，相当于cout<<10<<endl;
	cout << *pa << endl;
	cout << *&a << endl; // 10

	system("pause");
	return 0;
}

// 这个main函数按照C语言测试，将文件后缀改为.c
// 测试在C语言中，const修饰的变量仍旧是变量，只不过不能修改
// 但是在C++中，被const修饰的变量一般称为常量，该常量具有宏替换的效果
#if 0
int main()
{
	const int a = 10;
	int array[a]; // 在C语言中会报错，因为数组开辟int类型的变量的个数必须是常量(就是方括号中的值)

	system("pause");
	return 0;
}
#endif
