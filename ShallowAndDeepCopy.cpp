#include<iostream>
#include<Windows.h>
using namespace std;
#pragma warning(disable:4996)


// 深拷贝的实现一（传统版）
/*
下边代码的缺陷：代码重复度高
*/
#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (str == nullptr)
			str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);

#if 0
		if (str != nullptr)
		{
			_str = new char[strlen(str) + 1];
			strcpy(_str, str); // 拷贝包括\0
		}
		else // 如果传参为nullptr 将其当成空字符串处理
		{
			// 这种写法，构造string对象时用的是new，析构函数释放时要用delete
			// 实现起来不方便
			_str = new char;
			*_str = '\0';
		}
#endif		
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
			
	}

	/*
	编译器默认生成的拷贝构造函数是浅拷贝
	浅拷贝：两个对象指向同一块空间
	浅拷贝在释放资源时，会将同一块空间释放两次导致程序崩溃
	所以，涉及到资源管理要显式定义拷贝构造函数
	深拷贝：两个对象各自拥有一块空间
	*/
	String(const String& s)
		:_str(new char[strlen(s._str)+1])
	{ 
		strcpy(_str, s._str);
	}

	/*
	编译器默认生成的赋值运算符重载存在两个问题：
	一是浅拷贝，二是被赋值对象原来的空间被覆盖，导致没有释放，存在内存泄漏
	赋值运算符重载同拷贝构造一样，涉及到资源管理，一定要显式定义
	注意：如果被赋值空间 < 赋值对象空间 那么strcpy会出错
	      所以，先开辟一段和赋值对象空间一样大的临时空间，然后将赋值对象中的内容拷贝到临时空间
		  然后释放赋值对象的旧空间，让其指针指向临时空间
	*/
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


private:
	char* _str;
};

void Test1()
{
	String s1;
	String s2("jiajia");
	String s3(s2);

	String s4 = s2; // 调用拷贝构造

	// 用一个已存在的对象给另一个已存在的对象赋值才调用赋值运算符重载
	String s5("haha");
	s1 = s5;
}
#endif

// 深拷贝的实现二(现代版)
// 结合画图板体会Test2() Test3() Test4()
#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (str == nullptr)
			str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);		
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}

	}

	/* 
	该拷贝构造如果不写初始化列表会出问题
	Test2和Test3中Test2没问题，但是Test3释放资源会出问题
	*/
	String(const String& s)
		:_str(nullptr)
	{
		// 用构造函数构造一个临时变量
		String sTemp(s._str);
		// 交换this指针指向对象的_str和临时对象的_str的地址
		std::swap(_str,sTemp._str);
	}


	// 因为赋值时，自己给自己赋值的情况很少，所以采用以下做法
	/*
	这种写法的优势，巧妙的使用了传值构造的临时对象
	传参时，对象传参要调用拷贝构造函数先创建一份临时变量
	将临时变量的_str和this指针指向对象的_str的地址交换
	临时对象在函数执行完要销毁，调用析构函数，将被赋值对象原来的空间释放掉
	*/
	String& operator=(String s)
	{
		std::swap(_str, s._str);
		return *this;
	}
	
	// 下面代码依然重复度高
	/*String& operator=(const String& s)
	{
		if (this != &s)
		{
			String sTemp(s._str);
			swap(_str, sTemp._str);
		}
		return *this;
	}*/


private:
	char* _str;
};

/*
Test2中调用没有初始化列表的拷贝构造函数，最终调用析构函数没有问题
*/
void Test2()
{
	String s1("hello");
	String s2(s1);
}

// Test3中调用没有初始化列表的拷贝构造函数，最终调用析构函数会程序中断
String Test3()
{
	String s1("sad");
	return s1;
}

void Test4()
{
	String s1("sad");
	String s2("happy");
	s1 = s2;
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();

	system("pause");
	return 0;
}
#endif

