#include<iostream>
#include<Windows.h>
using namespace std;

// 不同数据在内存中的存放位置
#if 0
int globalVar = 1; 
static int staticGlobalVal = 1;
void Test()
{
	static int staticVar = 1; 
	int localVar = 1; 

	int num[] = { 1, 2, 3, 4 }; 
	char str[] = "abcd"; 
	char* p = "abcd"; 
	int* ptr1 = (int*)malloc(sizeof(int)* 4); 
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int)* 4);
	free(ptr1);
	free(ptr3);
}
#endif

// 探究C++为什么要创立自己的动态内存管理方式
/*
创建对象编译器会自动调用构造函数，销毁对象时编译器会自动调用析构函数
在堆上创建对象，不能用malloc
因为malloc不会调用构造函数，不调用构造函数说明对象创建失败；
所以malloc从堆上申请的空间就根本不是对象的空间，它只是一段和对象类型大小相等的堆空间而已
不能用free释放堆对象的空间
因为free不会调用析构函数，不调用析构函数就不能将对象中的资源清理干净 
*/
#if 0
class A
{
public:
	A(int a)
		:_a(a)
	{ 
		cout << "A()" << endl;
	}

	~A()
	{ 
		cout << "~A()" << endl;
	}
private:
	int _a;
};

int main()
{
	// 在栈上创建对象
	A a1(10);

	// 在堆上创建对象
	A* pa = (A*)malloc(sizeof(A));

	free(pa);

	system("pause");
	return 0;
}
#endif

// new和delete的用法
#if 0
int main()
{
	// 单个类型空间的申请
	int* p1 = new int;
	int* p2 = new int(10); // 申请1个int类型大小的空间，并初始化成10

	// 连续类型空间的申请
	int* p3 = new int[5]; // 申请5个int类型大小的连续空间
	int* p4 = new int[5]{ 1, 2, 3, 4, 5 }; // 申请5个int类型大小的连续空间，并初始化为1，2，3，4，5

	// 单个类型空间的释放
	delete p1;
	delete p2;

	// 连续空间的释放
	delete[] p3;
	delete[] p4;

	system("pause");
	return 0;
}
#endif

// 验证new会调用构造函数 delete会调用析构函数
#if 0
class Test
{
public:
	Test(int t = 7)
		:_t(t)
	{
		cout << "Test(int)" << this << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	int _t;
};

int main()
{
	Test* p1 = new Test(100);

	delete p1;

	system("pause");
	return 0;
}
#endif


// windows提供的api函数，用来进行简单的内存泄漏的检测
// 只需放在要检测的代码的最后即可
//_CrtDumpMemoryLeaks();

// 操作自定义类型
#if 0
class Test
{
public:
	Test(int t = 7)
		:_t(t)
	{
		cout << "Test(int)" << this << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	int _t;
};

int main()
{
	Test* p1 = new Test; // 在堆上创建一个Test类型的对象
	delete p1;

	Test* p2 = new Test(100); // 在在堆上创建一个Test类型的对象并将其中的成员变量初始化为100
	delete p2;

	Test* p3 = new Test[5]; // 在堆上创建5个Test类型的对象
	delete[] p3;	

	system("pause");
	return 0;
}
#endif

// 定位new表达式：在已分配的原始内存空间中调用构造函数初始化一个对象
#if 0
class Test
{
public:
	Test(int t = 7)
		:_t(t)
	{
		cout << "Test(int)" << this << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	int _t;
};

int main()
{
	Test* pt = (Test*)malloc(sizeof(Test)); // malloc申请的堆空间不是对象的空间
	
	new(pt)Test; // 定位new会调用构造函数
	/* 
	上边两行代码合起来相当于new
	new的实现原理：
	1. 申请堆空间
	2. 调用构造函数
	*/

	// 此时，pt指向的堆空间就是对象的空间了
	// 所以不能用free来释放空间，因为free不会调用析构函数
	// 所以这里手动调用析构函数

	/*
	下边两行代码合起来相当于delete
	delete的实现原理：
	1. 调用析构函数清理对象中的资源
	2. 释放空间
	*/
	pt->~Test();
	free(pt);


	system("pause");
	return 0;
}
#endif

