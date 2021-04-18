#include <iostream>
using namespace std;

// this指针能否为空？
class A
{
public:
	/*
	在编译器中下边的成员函数是这样的
	void func(A* const this)
	{
	this->_t = 10;
	cout << this << endl;
	}
	*/
	void func()
	{
		_t = 10; // 成员函数中访问成员变量或者调用成员函数，如果this指针为空，肯定崩溃
		cout << this << endl;
	}

	int _t;
};
int main()
{
	A a1, a2, a3;

	// 调用成员函数的两种方式
	// 1. 对象.成员函数
	a1.func(); // call A::func(&a1)

	// 2. 指向对象的指针->成员函数
	A* pa1 = &a2;
	pa1->func(); // call A::func(pa1)

	A* pa2 = &a3;
	pa2 = nullptr;
	pa2->func(); // call A::func(nullptr)

	system("pause");
	return 0;
}