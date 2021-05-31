#include<stdio.h>

#include<iostream>
#include<Windows.h>
#include<malloc.h>
#include<memory>
#pragma warning(disable:4996)
using namespace std;

#if 0
template<class T>
class SmartPtr
{
public:
	// RAII:资源获取即初始化
	// 
	SmartPtr(T* ptr = nullptr)
	:_ptr(ptr)
	{ }

	~SmartPtr()
	{
		if (_ptr)
		{
			delete _ptr;
			_ptr = nullptr;
		}
	}

	//////////////////////////////////
	// 指针的操作
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

struct S
{
	int a;
	int b;
	int c;
};

void TestSmartPtr1()
{
	int* p1 = new int;
	*p1 = 10;
	SmartPtr<int> sm1(p1);
	*sm1 = 100;

	S* ps = new S;
	ps->a = 10;
	ps->b = 20;
	ps->c = 30;

	SmartPtr<S> sm2(ps);
	sm2->a = 100;
	sm2->b = 200;
	sm2->c = 300;
}

/*
验证上面实现的SmartPtr中存在的问题
没有显示定义拷贝构造函数和赋值运算符重载，编译器会生成一份默认的
浅拷贝，copy析构时会将管理资源释放，sm析构已经释放的资源会崩溃
*/
void TestSmartPtr2()
{
	SmartPtr<int> sm(new int);
	*sm = 10;

	SmartPtr<int> copy(sm);
	*copy = 100;
}

int main()
{
	//TestSmartPtr1();
	TestSmartPtr2();

	system("pause");
	return 0;
}
#endif

// C++98：auto_ptr
/*
解决浅拷贝的方式：资源转移方式
将资源交给最新对象，认为旧对象不会再使用了
*/
// 版本一
#if 0
namespace jia
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII:资源获取即初始化
		// 
		auto_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{ }

		~auto_ptr()
		{
			if (_ptr)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		auto_ptr(auto_ptr<T>& ap)
			:_ptr(ap._ptr)
		{
			ap._ptr = nullptr; 
		}

		auto_ptr<T>& operator=(auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr)
					delete _ptr;

				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}
			return *this;
		}

		//////////////////////////////////
		// 指针的操作
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T* get()
		{
			return _ptr;
		}

	private:
		T* _ptr;
	};

}
void TestAutoPtr1()
{
	jia::auto_ptr<int> sm(new int);
	*sm = 10;

	jia::auto_ptr<int> copy(sm);
	*copy = 100;
	//*sm = 200; // 因为sm已经将资源转移给copy了，所以sm不能访问该资源了

	jia::auto_ptr<int> ap1(new int);
	*ap1 = 10;
	jia::auto_ptr<int> ap2(new int);
	*ap2 = 20;

	ap1 = ap2;
	*ap1 = 200;
	//*ap2 = 300; // ap2将资源转移给ap1了，即ap2与资源已断开联系
}

void TestAutoPtr2()
{
	// 版本一可以防止野指针
	jia::auto_ptr<int> ap1(new int);
	*ap1 = 10;

	if (true)
	{
		jia::auto_ptr<int> ap2(ap1);
		*ap2 = 20;
	}// 出该作用域 ap2对象会销毁，调用析构函数释放资源

	// 因为ap1拷贝构造ap2后，ap1就与资源断开联系了
	// ap1._ptr==nullptr
	if (nullptr != ap1.get())
		*ap1 = 100;
}

int main()
{
	//TestAutoPtr1();
	TestAutoPtr2();

	system("pause");
	return 0;
}
#endif

/*
C++98:auto_ptr 版本二
解决浅拷贝的方式：资源管理权限转让 --- 释放资源的权限
缺陷:可能会造成野指针
*/
#if 0
namespace jia
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII:资源获取即初始化
		// 
		auto_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _owner(false)
		{ 
			if (_ptr)
				_owner = true;
		}

		~auto_ptr()
		{
			if (_ptr && _owner)
			{
				delete _ptr;
				_ptr = nullptr;
				_owner = false;
			}
		}

		auto_ptr(auto_ptr<T>& ap)
			:_ptr(ap._ptr)
			, _owner(ap._owner)
		{
			ap._owner = false;
		}

		auto_ptr<T>& operator=(const auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr && _owner)
					delete _ptr;

				_ptr = ap._ptr;
				_owner = ap._owner;
				ap._owner = false;
			}
			return *this;
		}

		//////////////////////////////////
		// 指针的操作
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T* get()
		{
			return _ptr;
		}

	private:
		T* _ptr;
		mutable bool _owner; // 释放资源权限的对象为true
		/*
		在C++中，mutable 是为了突破 const 的限制而设置的。
		可以用来修饰一个类的成员变量。
		被 mutable 修饰的变量，将永远处于可变的状态，即使是 const 函数中也可以改变这个变量的值。
		*/
	};

}

void TestAutoPtr1()
{
	jia::auto_ptr<int> sm(new int);
	*sm = 10;

	jia::auto_ptr<int> copy(sm);
	*copy = 100;
	*sm = 200;

	jia::auto_ptr<int> ap1(new int);
	*ap1 = 10;
	jia::auto_ptr<int> ap2(new int);
	*ap2 = 20;

	ap1 = ap2;
	*ap1 = 200;
	*ap2 = 300;
}

void TestAutoPtr2()
{
	// 版本二可能会造成野指针
	jia::auto_ptr<int> ap1(new int);
	*ap1 = 10;

	if (true)
	{
		jia::auto_ptr<int> ap2(ap1);
		*ap2 = 20;
	}

	// 在版本二中不能用该判断来防止ap1访问ap2释放的资源
	// 因为版本二中资源共享，即使ap2已经释放了，ap1指向的空间还在，只不过已经不是自己的了
	// 如果该内存已经是别的占用了，可能会修改占用该块内存的内容
	//if (nullptr == ap1.get())
		//*ap1 = 100;
}


int main()
{
	TestAutoPtr2();

	system("pause");
	return 0;
}
#endif

#include<memory>

// 验证C++98中auto_ptr采用的是版本一的资源转移方式
#if 0
int main()
{
	auto_ptr<int> ap1(new int);
	auto_ptr<int> ap2(ap1);

	if (nullptr == ap1.get())
		cout << "资源转移" << endl;
	else
		cout << "资源管理权限转移" << endl;

	system("pause");
	return 0;
}
#endif

/*
unique_ptr
解决浅拷贝方式：资源独占
缺陷：不能资源共享
*/
#if 0
// 释放new出来的资源
template<class T>
class Delete
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

// 释放malloc出来的资源
template<class T>
class Free
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			free(p);
			p = nullptr;
		}
	}
};

// 文件类型的指针
class FClose
{
public:
	void operator()(FILE*& p)
	{
		if (p)
		{
			fclose(p);
			p = nullptr;
		}
	}
};

namespace jia
{
	template<class T, class DF = Delete<T>>
	class unique_ptr
	{
	public:
		// RAII
		unique_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{ }

		~unique_ptr()
		{
			if (_ptr)
			{
				// 不同资源释放方式不同，需要分别处理
				/*delete _ptr;
				_ptr = nullptr;*/
				DF df;
				df(_ptr);
			}
		}

		////////////////////////////////////
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		//////////////////////////////////////
#if 0
	private:
		// 解决浅拷贝：防拷贝
		// 禁止使用拷贝构造函数和赋值运算符重载
		// 方式一：只声明不定义且权限设置为private
		unique_ptr(const unique_ptr<t>& up);

		unique_ptr<t> operator=(const unique_ptr<t>& up);
#endif
		// C++11 可以控制编译器生成默认成员函数
		unique_ptr(const unique_ptr<T>& up)=delete;

		unique_ptr<T> operator=(const unique_ptr<T>& up)=delete;

	private:
		T* _ptr;
	};

	// 如果不设置为private，用户可以在类外进行定义，依然可以调用拷贝构造
	/*template<class T>
	unique_ptr<T>::unique_ptr(const unique_ptr<T>& up)
		:_ptr(up._ptr)
	{ }*/

	
}


void TestUniquePtr1()
{
	jia::unique_ptr<int> up1(new int);
	//jia::unique_ptr<int> up2(up1);
}

// 测试DF，不同资源释放方式
void TestUniquePtr2()
{
	jia::unique_ptr<int> up1(new int);
	jia::unique_ptr<int, Free<int>> up2((int*)malloc(sizeof(int)));
	jia::unique_ptr<FILE, FClose> up3(fopen("1.txt", "w"));
}

int main()
{
	//TestUniquePtr1();
	TestUniquePtr2();

	system("pause");
	return 0;
}
#endif

// C++11中的default和delete修饰成员函数
#if 0
class A
{
public:
	A(int a)
		:_a(a)
	{ }

	// 上面我们已经显示定义了构造函数，在C++98中编译器不会再生成默认构造函数(无参构造)
	// 在C++11中，用=default修饰后：告诉编译器，让编译器生成无参构造
	A() = default;

	// 告诉编译器，将用=delete修饰的成员函数删除
	A(const A& a) = delete;
	A& operator=(const A& a) = delete;

private:
	int _a;
};

void TestA()
{
	A a1(7);
	A a2;

	a2 = a1;
	A a3(a1);
}

void Test1()
{
	/*
	验证标准库中unique_ptr
	编译会报错：尝试调用已经删除的拷贝构造函数和赋值运算符重载函数
	说明标准库中的unique_ptr是采用=delete修饰成员函数的方式来防拷贝的
	*/
	unique_ptr<int> up1(new int);
	unique_ptr<int> up2(up1);

	unique_ptr<int> up3;
	up3 = up1;
}

void FClose(FILE*& p)
{
	if (p)
	{
		fclose(p);
		p = nullptr;
	}
}

typedef void(*FP)(FILE*& p); // 给函数指针取别名

void Test2()
{
	unique_ptr<int, Free<int>> up1((int*)malloc(sizeof(int))); // 仿函数
	unique_ptr<FILE, FP> up2(fopen("1.txt", "r"), FClose); // 函数指针
}

int main()
{
	//TestA();

	//Test();

	Test2();

	system("pause");
	return 0;
}
#endif

/*
共享智能指针shared_ptr
解决浅拷贝方式：共享资源时，让最后一个使用资源的对象进行释放---引用计数
*/
#if 0
int main()
{
	// 标准库中shared_ptr的使用
	shared_ptr<int> sp1(new int);
	cout << sp1.use_count() << endl;
	shared_ptr<int> sp2(sp1);
	cout << sp2.use_count() << endl;
	shared_ptr<int> sp3;
	sp3 = sp1;

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
	cout << sp3.use_count() << endl;

	system("pause");
	return 0;
}
#endif

// 引用计数不能是普通成员变量，也不能是static成员变量
#if 0
namespace jia
{
#if 0
	// 引用计数为普通成员变量（不行！）
	template<class T>
	class shared_ptr
	{
	public:
		/////////////////////////////////////////
		// RAII
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _count(0)
		{ 
			if (_ptr)
				_count = 1;
		}

		~shared_ptr()
		{
			if (_ptr && --_count == 0)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		shared_ptr(shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _count(++sp._count)
		{ }

		shared_ptr<T> operator=(shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				if (_ptr)
				{
					_ptr = nullptr;
					--_count;
				}
				_ptr = sp._ptr;
				_count = sp._count;
			}
			return *this;
		}
		/////////////////////////////////////////
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	
		int Count()
		{
			return this->_count;
		}
	private:
		T* _ptr;
		/*
		引用计数不能是普通成员变量
		普通成员变量每个对象都拥有一份，对象销毁时，只能改变销毁对象中的引用计数
		不能改变其他对象中的引用计数，导致引用计数出错
		*/
		//int _count; 
	};
#endif
	// 引用计数为static成员变量(不行)
	template<class T>
	class shared_ptr
	{
	public:
		/////////////////////////////////////////
		// RAII
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{
			if (_ptr)
				_count = 1;
		}

		~shared_ptr()
		{
			if (_ptr && --_count == 0)
			{
				delete _ptr;
				_ptr = nullptr;
			}
		}

		shared_ptr(shared_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			_count++;
		}

		shared_ptr<T> operator=(shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				if (_ptr)
				{
					_ptr = nullptr;
					--_count;
				}
				_ptr = sp._ptr;
				_count = sp._count;
			}
			return *this;
		}
		/////////////////////////////////////////
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		int Count()
		{
			return this->_count;
		}
	private:
		T* _ptr;
		static int _count;
	};

	template<class T>
	int shared_ptr<T>::_count = 0;
}

void TestSharedPtr()
{
	jia::shared_ptr<int> sp1(new int);
	cout << sp1.Count() << endl;

	jia::shared_ptr<int> sp2(sp1);
	cout << sp2.Count() << endl;
	cout << sp1.Count() << endl;
}

int main()
{
	TestSharedPtr();

	system("pause");
	return 0;
}
#endif

// shared_ptr实现
// 存在问题：单线程没问题，多线程会出错
#if 0
namespace jia
{
	template<class T>
	struct Delete
	{
		void operator()(T*& p)
		{
			if (p)
			{
				delete p;
				p = nullptr;
			}
		}
	};

	template<class T, class DF = Delete<T>>
	class shared_ptr
	{
	public:
		/////////////////////////////////////////////
		// RAII
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _pCount(nullptr)
		{
			if (_ptr)
				_pCount = new int(1);
		}

		~shared_ptr()
		{
			Release();
		}

		////////////////////////////////////////////
		// 指针类似操作
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
		/////////////////////////////////////////////
		// 解决浅拷贝：每个资源都有一个引用计数
		shared_ptr(const shared_ptr<T>& sp) // 拷贝构造，两个对象使用的是同一份资源，只要有资源，计数+1即可
			:_ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_ptr)
				++(*_pCount);
		}

		shared_ptr<T> operator=(const shared_ptr<T>& sp) // 赋值运算符重载要考虑两个对象是否为同一份资源
		{
			if (_ptr != sp._ptr)
			{
				// 将原来资源计数-1
				Release();

				// 新资源计数+1
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				++(*_pCount);
			}
			return *this;
		}
	private:
		void Release()
		{
			if (_ptr && 0 == --(*_pCount))
			{
				DF()(_ptr); // 释放资源

				delete _pCount; // 释放计数
				_pCount = nullptr;
			}
		}
	private:
		T* _ptr;
		int* _pCount; // 引用计数
	};
}
#endif

#if 0
void TestShared_ptr()
{
	jia::shared_ptr<int> sp1(new int);
	jia::shared_ptr<int> sp2(sp1);

	jia::shared_ptr<int> sp3(new int);
	jia::shared_ptr<int> sp4(sp3);

	sp3 = sp2;
	sp4 = sp2;
}

int main()
{
	TestShared_ptr();

	system("pause");
	return 0;
}
#endif

// 加锁的shared_ptr
#include<mutex>
#if 0
namespace jia
{
	template<class T>
	struct Delete
	{
		void operator()(T*& p)
		{
			if (p)
			{
				delete p;
				p = nullptr;
			}
		}
	};

	template<class T, class DF = Delete<T>>
	class shared_ptr
	{
	public:
		/////////////////////////////////////////////
		// RAII
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _pCount(nullptr)
			, _pMutex(nullptr)
		{
			if (_ptr)
			{
				_pCount = new int(1);
				_pMutex = new mutex;
			}
				
		}

		~shared_ptr()
		{
			Release();
		}

		////////////////////////////////////////////
		// 指针类似操作
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
		/////////////////////////////////////////////
		// 解决浅拷贝：每个资源都有一个引用计数
		shared_ptr(const shared_ptr<T>& sp) // 拷贝构造，两个对象使用的是同一份资源，只要有资源，计数+1即可
			:_ptr(sp._ptr)
			, _pCount(sp._pCount)
			, _pMutex(sp._pMutex)
		{
			if (_ptr)
				AddRef();
		}

		shared_ptr<T> operator=(const shared_ptr<T>& sp) // 赋值运算符重载要考虑两个对象是否为同一份资源
		{
			if (_ptr != sp._ptr)
			{
				// 将原来资源计数-1
				Release();

				// 新资源计数+1
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				AddRef();
			}
			return *this;
		}

		void AddRef()
		{
			_pMutex->lock();
			++(*_pCount);
			_pMutex->unlock();
		}

		int SubRef()
		{
			_pMutex->lock();
			--(*_pCount);
			_pMutex->unlock();
			return *_pCount;
		}
	private:
		void Release()
		{
			if (_ptr && 0 == SubRef())
			{
				DF()(_ptr); // 释放资源

				delete _pCount; // 释放计数
				_pCount = nullptr;

				delete _pMutex; // 释放锁
				_pMutex = nullptr;
			}
		}
	private:
		T* _ptr;
		int* _pCount; // 引用计数
		mutex* _pMutex;
	};
}

struct A
{
	A()
	{
		a = b = c = 0;
	}
	int a;
	int b;
	int c;
};

#include<thread>
void ThreadFunc(jia::shared_ptr<A>& sp, int n)
{
	for (int i = 0; i < n; ++i)
	{
		sp->a++;
		sp->b++;
		sp->c++;
	}
}

void TestShared_ptr()
{
	jia::shared_ptr<A> sp(new A);

	thread t1(ThreadFunc, sp, 10000);
	thread t2(ThreadFunc, sp, 10000);

	t1.join();
	t2.join();

	cout << sp->a << endl;
	cout << sp->b << endl;
	cout << sp->c << endl;
	
}

int main()
{
	TestShared_ptr();

	system("pause");
	return 0;
}
#endif

// 循环引用的解决方式：用weak_ptr
struct ListNode
{
	ListNode(int x = 10)
		: data(x)
	{ 
		cout << "ListNode()" << this << endl;
	}

	~ListNode()
	{
		cout << "~ListNode()" << this << endl;
	}

	// shared_ptr的循环引用问题
	//shared_ptr<ListNode> next;
	//shared_ptr<ListNode> prev;

	weak_ptr<ListNode> next; 
	weak_ptr<ListNode> prev;
	int data;
};

void TestWeak_ptr()
{
	// 验证标准库中shared_ptr的问题：循环引用
	shared_ptr<ListNode> sp1(new ListNode(10));
	shared_ptr<ListNode> sp2(new ListNode(20));

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	sp1->next = sp2;
	sp2->prev = sp1;

	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
}
int main()
{
	TestWeak_ptr();

	system("pause");
	return 0;
}