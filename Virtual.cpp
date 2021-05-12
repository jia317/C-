#include<iostream>
#include<Windows.h>
using namespace std;

/*
多态的实现条件
前提：在继承方式下
基类中必须有虚函数，且派生类要重写基类虚函数
必须用基类指针或引用，指向不同类的对象，调用虚函数
*/
#if 0
class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "全价票" << endl;
	}
protected:
	string _name;
	string _gender;
	int _age;
};

class Student :public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "半价票" << endl;
	}
protected:
	int _stuID;
};

class Solider :public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "免费" << endl;
	}
protected:
	string _ID;
};

// 注意：在程序运行时，根据p所引用对象的不同，最终调用的虚函数不同
// 在程序编译时，无法确定具体要调用哪个虚函数---因为编译阶段，编译器不知道p引用哪个对象
void Test(Person& p)
{
	p.BuyTicket();
}

int main()
{
	Person p;
	Student stu;
	Solider sol;

	Test(p);
	Test(stu);
	Test(sol);

	system("pause");
	return 0;
}
#endif

/*
重写
前提：一定是在继承体系中，派生类对基类中的虚函数进行重写
1. 基类的函数必须是虚函数
2. 子类要重写基类虚函数：派生类虚函数的原型必须要和基类虚函数原型一致
   原型一致：返回值类型 函数名字(参数列表) 必须完全相同
   例外：
       1）协变：基类虚函数返回基类指针或引用
	            派生类函数返回派生类指针或引用
	   2）
3. 子类虚函数可以不加virtual关键字，但是建议加上
4. 子类和基类虚函数的访问权限可以不同
*/
#if 0
class B
{
public:
	void Test1()
	{
		cout << "B::Test1()" << endl;
	}

	virtual void Test2()
	{
		cout << "B::Test2()" << endl;
	}

	void Test3()
	{
		cout << "B::Test3()" << endl;
	}

	virtual void Test4()
	{
		cout << "B::Test4()" << endl;
	}

	virtual void Test5()
	{
		cout << "B::Test5()" << endl;
	}

	virtual void Test6(int)
	{
		cout << "B::Test5()" << endl;
	}

	virtual void Test7()
	{
		cout << "B::Test7()" << endl;
	}

	virtual void Test8()
	{
		cout << "B::Test8()" << endl;
	}

	void Test9()
	{
		cout << "B::Test9()" << endl;
	}

	virtual void Test10(int a = 10)
	{
		cout << "B::Test10()" << endl;
	}
protected:
	int _b;
};

class D :public B
{
public:
	// 与基类中Test1为同名隐藏
	void Test1()
	{
		cout << "D::Test1()" << endl;
	}

	// 重写了基类中的Test2
	// 子类虚函数可以不加virtual关键字，但是建议加上
	void Test2()
	{
		cout << "D::Test2()" << endl;
	}

	// 与基类中Test3为同名隐藏
	virtual void Test3()
	{
		cout << "D::Test3()" << endl;
	}

	// 与基类中Test4构成重写
	// 重写的标准写法！！
	virtual void Test4()
	{
		cout << "D::Test4()" << endl;
	}

	// 基类中Test5没有参数，派生类的Test5有参数---函数原型不一致---不是重写
	// 与基类中Test5为同名隐藏
	virtual void Test5(int d)
	{
		cout << "D::Test5()" << endl;
	}

	// 函数名不同
	virtual void Tset6(int)
	{
		cout << "D::Test6()" << endl;
	}

	// Test8啥也不是
	// 返回值类型不同 --- 代码编译失败
	/*virtual int Test8()
	{
		cout << "D::Test8()" << endl;
		return 0;
	}*/

	// 同名隐藏 函数名相同
	virtual int Test9()
	{
		cout << "D::Test9()" << endl;
		return 0;
	}

	// 同名隐藏
	virtual void Test10()
	{
		cout << "B::Test10()" << endl;
	}
private:
	// 子类Test7的权限是私有的，但是在类外可以调用
	// 与基类中Test7构成重写
	virtual void Test7()
	{
		cout << "D::Test7()" << endl;
	}
protected:
	int _d;
};

void TestVirtual(B* pb)
{
	/*
	Test1是同名隐藏
	pb指向基类对象或者派生类对象，都调用基类的Test1
	基类指针调用，调用基类成员函数
	*/
	pb->Test1();

	/*
	基类和派生类中Test2构成重写
	pb指向基类对象，调用基类Test2
	pb指向派生类对象，调用派生类Test2
	*/
	pb->Test2();

	/*
	基类Test3不是虚函数，但是派生类中Test3为虚函数
	也是同名隐藏
	pb指向基类对象或者派生类对象，都调用基类的Test3
	基类指针调用，调用基类成员函数
	*/
	pb->Test3();

	pb->Test4();

	pb->Test5();

	pb->Test6(1);

	pb->Test7();

	pb->Test9();

	pb->Test10();
}

int main()
{
	B b;
	TestVirtual(&b);

	cout << "---------------------" << endl;

	D d;
	TestVirtual(&d);

	system("pause");
	return 0;
}
#endif

// 重写例外---协变
/*
基类虚函数返回基类指针或引用
派生类函数返回派生类指针或引用

只要基类虚函数 的基类 和 派生类虚函数 的派生类 是继承关系 
返回的基类指针或引用 的基类 和 返回的基类指针或引用 的派生类 是继承关系即可
*/
#if 0
class A{};
class B:public A{};

class Base
{
public:
	virtual Base& Test1()
	{
		cout << "Base::Test1()" << endl;
		return *this;
	}

	virtual A* Test2()
	{
		cout << "A::Test2()" << endl;
		return nullptr;
	}
};

class Derived :public Base
{
public:
	virtual Derived& Test1()
	{
		cout << "Derived::Test()" << endl;
		return *this;
	}

	virtual B* Test2()
	{
		cout << "B::Test2()" << endl;
		return nullptr;
	}

};

void TestVir(Base& b)
{
	b.Test1();
	b.Test2();
}

int main()
{
	Base b;
	TestVir(b);

	cout << "---------------------" << endl;

	Derived d;
	TestVir(d);

	system("pause");
	return 0;
}
#endif

// 重写例外2---析构函数的重写
// 基类析构函数是虚函数，只要子类定义了析构函数，就构成重写
// 建议在继承体系中将基类析构函数给成虚函数
class A
{
public:
	virtual ~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
};

class B:public A
{
public:
	/*
	派生类中涉及到资源管理，基类析构函数一定要是虚函数
	否则，销毁派生类对象时，只调用基类析构函数
	*/
	B()
	{
		pb = new int[10];
	}

	virtual ~B()
	{
		if (pb)
			delete[] pb;

		cout << "~B()" << endl;
	}
private:
	int* pb;
};

int main()
{
	A* pa = new B;

	/*
	delete会做两件事
	1. 调用析构函数
	因为pa是基类A类型的指针，所以编译器会调用基类A的析构函数
	如果基类A的析构函数不是虚函数
	调用完基类A的析构函数后，
	调用operator delete只释放了pa指向的空间，即pb的空间
	而派生类B中申请的10个int类型的空间并没有释放，所以会造成内存泄漏
	2. 调用operator delete
	*/
	delete pa;

	system("pause");
	return 0;
}