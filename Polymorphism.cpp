#include<iostream>
#include<Windows.h>
#include<string>
using namespace std;

// 包含纯虚函数的类称为抽象类
// 抽象类不能实例化对象 但是可以定义抽象类类型的指针
// 抽象类一定要被继承，而且在其后续的子类中要对纯虚函数进行重写
#if 0
class Car
{
public:
	// 纯虚函数：在函数前加上virtual关键字，后边加上=0
	virtual void Drive() = 0;
};

class Benz :public Car
{
public:
	virtual void Drive()
	{
		cout << "Benz-舒适" << endl;
	}
};

class BMW :public Car
{
public:
	virtual void Drive()
	{
		cout << "BMW-操纵" << endl;
	}
};

void TestCar()
{
	//Car c; // 抽象类不能实例化对象
	Car *pc; // 可以定义抽象类类型的指针

	Car *pBenz = new Benz;
	pBenz->Drive();
	delete pBenz;

	Car *pBMW = new BMW;
	pBMW->Drive();
	delete pBMW;
}
int main()
{
	TestCar();

	system("pause");
	return 0;
}
#endif

/*
含有虚函数的类，如果没有显式定义构造函数，编译器会生成默认的构造函数
*/
// 多态的原理
#if 0
class Base
{
public:
	void Test()
	{
		cout << "Test()" << endl;
	}

	virtual void Fun1()
	{
		cout << "Base::Fun1()" << endl;
	}

	virtual void Fun2()
	{
		cout << "Base::Fun2()" << endl;
	}

	int _b;
};

/*
基类和派生类各自拥有一个虚表
派生类会继承基类的虚表，但只是将基类虚表中的内容拷贝一份
*/
class Derived:public Base
{
public:
	int _d;
};

int main()
{
	/*
	含有虚函数的类的大小会多4个字节(在32位vs平台下)
	不管有多少虚函数，都只多4个字节，说明这四个字节的指针_vfptr是指向一块空间
	这块空间就是虚表的空间
	虚表中存放的是虚函数的地址
	虚函数的存放程序由虚函数的声明的先后次序决定
	*/
	cout << sizeof(Base) << endl;

	/*
	在内存窗口&b，在创建完对象后，前四个字节被填充
	说明虚表指针_vfptr是在构造函数中被填充的，因为创建对象时，只调用了构造函数
	*/
	Base b;

	Derived d;

	system("pause");
	return 0;
}
#endif

// 派生类中不重写基类虚函数，虚表中存放的是基类虚函数
// 派生类重写了基类虚函数，虚表中存放的是派生类重写的虚函数
#if 0
class Base
{
public:
	void Test()
	{
		cout << "Test()" << endl;
	}

	virtual void Fun1()
	{
		cout << "Base::Fun1()" << endl;
	}

	virtual void Fun2()
	{
		cout << "Base::Fun2()" << endl;
	}

	virtual void Fun3()
	{
		cout << "Base::Fun3()" << endl;
	}

	int _b;
};

/*
此时派生类虚函数表中存放的是
Derived::Fun1()
Base::Fun2()
Derived::Fun3()
*/
class Derived :public Base
{
public:
	virtual void Fun1() // 重写基类虚函数Fun1
	{
		cout << "Derived::Fun1()" << endl;
	}

	virtual void Fun3() // 重写基类虚函数Fun3
	{
		cout << "Derived::Fun1()" << endl;
	}
	int _d;
};

int main()
{
	Base b;
	Derived d;

	system("pause");
	return 0;
}
#endif

// 派生类中自己的虚函数放在哪？
/*
从监视窗口看不到派生类新增的虚函数
从内存窗口可以看到
*/
#if 0
class Base
{
public:
	void Test()
	{
		cout << "Test()" << endl;
	}

	virtual void Fun1()
	{
		cout << "Base::Fun1()" << endl;
	}

	virtual void Fun2()
	{
		cout << "Base::Fun2()" << endl;
	}

	virtual void Fun3()
	{
		cout << "Base::Fun3()" << endl;
	}

	int _b;
};

class Derived :public Base
{
public:
	virtual void Fun1() // 重写基类虚函数Fun1
	{
		cout << "Derived::Fun1()" << endl;
	}

	/*
	派生类虚表中的虚函数次序与派生类重写基类虚函数的顺序无关
	派生类新增的虚函数，按其声明次序，加在虚表后面
	*/
	virtual void Fun3() // 重写基类虚函数Fun3
	{
		cout << "Derived::Fun3()" << endl;
	}

	virtual void Fun2() // 重写基类虚函数Fun2
	{
		cout << "Derived::Fun2()" << endl;
	}

	

	virtual void Fun4() // 派生类自己的虚函数
	{
		cout << "Derived::Fun4()" << endl;
	}

	virtual void Fun5() // 派生类自己的虚函数
	{
		cout << "Derived::Fun5()" << endl;
	}

	int _d;
};

// 如何获取虚表地址？ 如何获取虚表中的每一项？
/*
1. 对象地址和虚表地址在数值上是相同的，可以通过&对象先拿到对象地址
2. &对象的类型是类类型* 要拿到前四个字节需要强转为int* 
   即 *(int*)(&对象名) 就是虚表地址的整型数字
3. 要将整型数字转化为指针类型 
   虚函数的类型为 void (*)(void)
   typedef void (*PVFT)(void) 将虚函数类型取一个类型名为PVFT
   再将整型数字转化为PVFT类型即可获取到虚函数地址
*/
typedef void(*PVFT)();
/*
区分带不带typedef时的PVFT
typedef void(*PVFT)(); 表示给void(*)()这个函数指针类型起了一个别名 叫PVFT
void(*PVFT)(); 表示定义了一个void(*)()这个函数指针类型的变量 变量名叫PVFT
*/
void GetVFT(Base& b, const string& str)
{
	//cout << hex << *(int*)(&b) << endl; // 这是一个整型数字，与虚表地址的数值相同而已，并不是虚表地址

	PVFT* pvf = (PVFT*)(*(int*)(&b)); // 将其强转为PVFT* 才是一个地址
	//cout << hex << pvf << endl; // 验证强转之后的数值与整型数值是否相同 相同则说明拿到了虚表地址
	// 至此，获取到虚表地址了
	//*pvf = nullptr; // 运行时，代码崩溃 虚表中内容放在代码段，是只读的，不允许修改

	cout << str << endl;
	// pvf指向虚表的起始位置，pvf解引用之后拿到的就是虚函数表第一个虚函数的地址，后面加上()
	// 相当于调用虚表中第一个虚函数
	//(*pvf)();

	// 调用虚表中所有虚函数
	while (*pvf)
	{
		(*pvf)();
		pvf++;
	}
}

int main()
{
	/*
	同一个类的不同对象共享同一个虚表
	*/
	Base b, b1;
	Derived d, d1;

	// 虚函数的类型
	cout << typeid(&Derived::Fun4).name() << endl;

	GetVFT(b, "Base VFT:");
	GetVFT(d, "Derived VFT:");

	system("pause");
	return 0;
}
#endif

/*
虚函数调用原理:
1. 获取对象地址，然后从对象前四个字节拿到虚表地址
2. 传递参数&this指针
3. 从虚表中获取对应虚函数地址
4. 调用该虚函数
*/
#if 0
class Base
{
public:
	void Test()
	{
		cout << "Test()" << endl;
	}

	virtual void Fun1()
	{
		cout << "Base::Fun1()" << endl;
	}

	virtual void Fun2()
	{
		cout << "Base::Fun2()" << endl;
	}

	virtual void Fun3()
	{
		cout << "Base::Fun3()" << endl;
	}

	int _b;
};

class Derived :public Base
{
public:
	virtual void Fun1() // 重写基类虚函数Fun1
	{
		cout << "Derived::Fun1()" << endl;
	}

	virtual void Fun2() // 重写基类虚函数Fun2
	{
		cout << "Derived::Fun2()" << endl;
	}

	virtual void Fun3() // 重写基类虚函数Fun3
	{
		cout << "Derived::Fun3()" << endl;
	}

	virtual void Fun4() // 派生类自己的虚函数
	{
		cout << "Derived::Fun4()" << endl;
	}

	virtual void Fun5() // 派生类自己的虚函数
	{
		cout << "Derived::Fun5()" << endl;
	}

	int _d;
};

/*
如果是基类指针，指针能访问的空间大小只有基类那么大
所以，即使基类指针指向子类对象，也调不到派生类独有的
*/
void TestVirtual(Base* b)
{
	b->Test();
	b->Fun1();
	b->Fun2();
	b->Fun3();
}

int main()
{
	Base b, b1;
	Derived d, d1;

	d._b = 1;
	d._d = 2;

	TestVirtual(&b);
	cout << "---------------------------" << endl;
	TestVirtual(&d);

	b = (Base)d; // 可能会生成临时对象
	// (Base*)&d 告诉编译器，将该派生类对象d按照基类对象的布局方式进行解析
	// 不会生成临时对象
	Base* pb = (Base*)&d; 
	pb->Fun1(); // 调用派生类虚函数


	system("pause");
	return 0;
}
#endif

// 基类含有虚函数的多继承下的对象模型
// 派生类继承几个基类，就有几个虚表，派生类新增的虚函数会添加在第一个继承的类的虚表中
// 调用不同的基类中的虚函数，要用不同的基类指针或引用去调用
/*
B1的对象模型:
                  B1的虚表
B1的虚表指针----->B1::fun1()
_b1               B1::fun2()
*/
#if 0
class B1
{
public:
	virtual void fun1()
	{
		cout << "B1::fun1()" << endl;
	}

	virtual void fun2()
	{
		cout << "B1::fun2()" << endl;
	}

	int _b1;
};

/*
B2的对象模型:
                  B2的虚表
B2的虚表指针----->B2::fun3()
                  B2::fun4()
	_b2
*/
class B2
{
public:
	virtual void fun3()
	{
		cout << "B2::fun3()" << endl;
	}

	virtual void fun4()
	{
		cout << "B2::fun4()" << endl;
	}

	int _b2;
};

/*
D的对象模型:
                             D的虚表
从B1继承下来的虚表指针----->B1::fun1()
                            D::fun2()
							D::fun5()
		_b1
从B2继承下来的虚表指针----->B2::fun3()
                            D::fun4()
        _b2
		_d
*/
class D :public B1, public B2
{
public:
	virtual void fun2()
	{
		cout << "D::fun3()" << endl;
	}

	virtual void fun4()
	{
		cout << "D::fun4()" << endl;
	}

	virtual void fun5()
	{
		cout << "D::fun5()" << endl;
	}

	int _d;
};

typedef void(*PVFT)();
// 基类B1中的虚函数要用基类B1类型的指针调用
void TestVirtual1(B1& b, const string& str)
{
	cout << str << endl;

	PVFT* pvf = (PVFT*)(*(int*)&b);
	while (*pvf)
	{
		(*pvf)();
		pvf++;
	}
}

// 基类B2中的虚函数要用基类B2类型的指针调用
void TestVirtual2(B2& b, const string& str)
{
	cout << str << endl;
	
	PVFT* pvf = (PVFT*)(*(int*)&b);
	while (*pvf)
	{
		(*pvf)();
		pvf++;
	}
}

int main()
{
	D d;
	d._b1 = 1;
	d._b2 = 2;
	d._d = 3;

	TestVirtual1(d, "B1的VFT：");
	cout << "----------------------" << endl;
	TestVirtual2(d, "B2的VFT：");


	system("pause");
	return 0;
}
#endif

// 题
#if 0
class A{
public:
	A(char *s) 
	{ 
		cout << s << endl; 
	}
	~A(){}
};
class B :virtual public A 
{
public:
	B(char *s1, char*s2) 
		:A(s1) 
	{ 
		cout << s2 << endl; 
	}
};
class C :virtual public A 
{
public:
	C(char *s1, char*s2) 
		:A(s1) 
	{ 
		cout << s2 << endl;
	}
};
class D :public B, public C {
public:
	D(char *s1, char *s2, char *s3, char *s4)
		:B(s1, s2)
		, C(s1, s3)
		, A(s1)
	{
		cout << s4 << endl;
	}
};

int main() {
	/*
	最终打印结果为class A class B class C class D
	构造函数调用次序：
	要先调用基类构造函数完成对基类中成员的初始化
	D先继承B，而B继承自A，所以先调用A的构造函数，再调用B的构造函数
	然后D继承C，再调用C的构造函数
	最后调用D自己的构造函数
	*/
	D *p = new D("class A", "class B", "class C", "class D");
	delete p;

	system("pause");
	return 0;
}
#endif

// 题2
#if 0
class Base1 
{ 
public: 
	int _b1; 
};
class Base2 
{ 
public: 
	int _b2;
};
class Derive : public Base1, public Base2 
{ 
public: 
	int _d; 
};
/*
派生类对象d的对象模型
Base1
Base2
_d
*/
int main(){
	Derive d;
	Base1* p1 = &d; // p1指向对象d模型中基类Base1的位置，只能访问Base1类型大小的空间，即只能访问Base1类中成员
	Base2* p2 = &d; // p2指向对象d模型中基类Base2的位置，只能访问Base2类型大小的空间，即只能访问Base2类中成员
	Derive* p3 = &d; // 指向对象d的起始位置
	// 所以p1 = p3 != p2

	return 0;
}
#endif

// 题3
#if 0
class A {
public:
	virtual void func(int val = 1)
	{ 
		std::cout << "A->" << val << std::endl;
	}

	virtual void test()
	{ 
		/*
		虚函数fun的调用过程
		1. 从对象前四个字节中取虚表地址
		2. 传参：
		       val传递1 是在编译期间用了A类中的默认值，但是最终调用是根据调用对象来决定调用哪个类的虚函数
			   传递this
		3. 从虚表中取虚函数地址
		4. 进行调用
		*/
		func(); 
	}
};
class B : public A {
public:
	void func(int val = 0)
	{ 
		std::cout << "B->" << val << std::endl; 
	}
};

int main(int argc, char* argv[])
{
	B*p = new B;
	p->test(); // 打印结果为B->1

	system("pause");
	return 0;
}
#endif

/*
静态多态：在编译时就决定函数行为，即调用哪个函数
两种典型的静态多态：
1. 函数重载
2. 模板
*/


