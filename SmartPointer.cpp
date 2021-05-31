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
	// RAII:��Դ��ȡ����ʼ��
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
	// ָ��Ĳ���
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
��֤����ʵ�ֵ�SmartPtr�д��ڵ�����
û����ʾ���忽�����캯���͸�ֵ��������أ�������������һ��Ĭ�ϵ�
ǳ������copy����ʱ�Ὣ������Դ�ͷţ�sm�����Ѿ��ͷŵ���Դ�����
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

// C++98��auto_ptr
/*
���ǳ�����ķ�ʽ����Դת�Ʒ�ʽ
����Դ�������¶�����Ϊ�ɶ��󲻻���ʹ����
*/
// �汾һ
#if 0
namespace jia
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII:��Դ��ȡ����ʼ��
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
		// ָ��Ĳ���
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
	//*sm = 200; // ��Ϊsm�Ѿ�����Դת�Ƹ�copy�ˣ�����sm���ܷ��ʸ���Դ��

	jia::auto_ptr<int> ap1(new int);
	*ap1 = 10;
	jia::auto_ptr<int> ap2(new int);
	*ap2 = 20;

	ap1 = ap2;
	*ap1 = 200;
	//*ap2 = 300; // ap2����Դת�Ƹ�ap1�ˣ���ap2����Դ�ѶϿ���ϵ
}

void TestAutoPtr2()
{
	// �汾һ���Է�ֹҰָ��
	jia::auto_ptr<int> ap1(new int);
	*ap1 = 10;

	if (true)
	{
		jia::auto_ptr<int> ap2(ap1);
		*ap2 = 20;
	}// ���������� ap2��������٣��������������ͷ���Դ

	// ��Ϊap1��������ap2��ap1������Դ�Ͽ���ϵ��
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
C++98:auto_ptr �汾��
���ǳ�����ķ�ʽ����Դ����Ȩ��ת�� --- �ͷ���Դ��Ȩ��
ȱ��:���ܻ����Ұָ��
*/
#if 0
namespace jia
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII:��Դ��ȡ����ʼ��
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
		// ָ��Ĳ���
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
		mutable bool _owner; // �ͷ���ԴȨ�޵Ķ���Ϊtrue
		/*
		��C++�У�mutable ��Ϊ��ͻ�� const �����ƶ����õġ�
		������������һ����ĳ�Ա������
		�� mutable ���εı���������Զ���ڿɱ��״̬����ʹ�� const ������Ҳ���Ըı����������ֵ��
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
	// �汾�����ܻ����Ұָ��
	jia::auto_ptr<int> ap1(new int);
	*ap1 = 10;

	if (true)
	{
		jia::auto_ptr<int> ap2(ap1);
		*ap2 = 20;
	}

	// �ڰ汾���в����ø��ж�����ֹap1����ap2�ͷŵ���Դ
	// ��Ϊ�汾������Դ������ʹap2�Ѿ��ͷ��ˣ�ap1ָ��Ŀռ仹�ڣ�ֻ�����Ѿ������Լ�����
	// ������ڴ��Ѿ��Ǳ��ռ���ˣ����ܻ��޸�ռ�øÿ��ڴ������
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

// ��֤C++98��auto_ptr���õ��ǰ汾һ����Դת�Ʒ�ʽ
#if 0
int main()
{
	auto_ptr<int> ap1(new int);
	auto_ptr<int> ap2(ap1);

	if (nullptr == ap1.get())
		cout << "��Դת��" << endl;
	else
		cout << "��Դ����Ȩ��ת��" << endl;

	system("pause");
	return 0;
}
#endif

/*
unique_ptr
���ǳ������ʽ����Դ��ռ
ȱ�ݣ�������Դ����
*/
#if 0
// �ͷ�new��������Դ
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

// �ͷ�malloc��������Դ
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

// �ļ����͵�ָ��
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
				// ��ͬ��Դ�ͷŷ�ʽ��ͬ����Ҫ�ֱ���
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
		// ���ǳ������������
		// ��ֹʹ�ÿ������캯���͸�ֵ���������
		// ��ʽһ��ֻ������������Ȩ������Ϊprivate
		unique_ptr(const unique_ptr<t>& up);

		unique_ptr<t> operator=(const unique_ptr<t>& up);
#endif
		// C++11 ���Կ��Ʊ���������Ĭ�ϳ�Ա����
		unique_ptr(const unique_ptr<T>& up)=delete;

		unique_ptr<T> operator=(const unique_ptr<T>& up)=delete;

	private:
		T* _ptr;
	};

	// ���������Ϊprivate���û�������������ж��壬��Ȼ���Ե��ÿ�������
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

// ����DF����ͬ��Դ�ͷŷ�ʽ
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

// C++11�е�default��delete���γ�Ա����
#if 0
class A
{
public:
	A(int a)
		:_a(a)
	{ }

	// ���������Ѿ���ʾ�����˹��캯������C++98�б���������������Ĭ�Ϲ��캯��(�޲ι���)
	// ��C++11�У���=default���κ󣺸��߱��������ñ����������޲ι���
	A() = default;

	// ���߱�����������=delete���εĳ�Ա����ɾ��
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
	��֤��׼����unique_ptr
	����ᱨ�����Ե����Ѿ�ɾ���Ŀ������캯���͸�ֵ��������غ���
	˵����׼���е�unique_ptr�ǲ���=delete���γ�Ա�����ķ�ʽ����������
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

typedef void(*FP)(FILE*& p); // ������ָ��ȡ����

void Test2()
{
	unique_ptr<int, Free<int>> up1((int*)malloc(sizeof(int))); // �º���
	unique_ptr<FILE, FP> up2(fopen("1.txt", "r"), FClose); // ����ָ��
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
��������ָ��shared_ptr
���ǳ������ʽ��������Դʱ�������һ��ʹ����Դ�Ķ�������ͷ�---���ü���
*/
#if 0
int main()
{
	// ��׼����shared_ptr��ʹ��
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

// ���ü�����������ͨ��Ա������Ҳ������static��Ա����
#if 0
namespace jia
{
#if 0
	// ���ü���Ϊ��ͨ��Ա���������У���
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
		���ü�����������ͨ��Ա����
		��ͨ��Ա����ÿ������ӵ��һ�ݣ���������ʱ��ֻ�ܸı����ٶ����е����ü���
		���ܸı����������е����ü������������ü�������
		*/
		//int _count; 
	};
#endif
	// ���ü���Ϊstatic��Ա����(����)
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

// shared_ptrʵ��
// �������⣺���߳�û���⣬���̻߳����
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
		// ָ�����Ʋ���
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
		/////////////////////////////////////////////
		// ���ǳ������ÿ����Դ����һ�����ü���
		shared_ptr(const shared_ptr<T>& sp) // �������죬��������ʹ�õ���ͬһ����Դ��ֻҪ����Դ������+1����
			:_ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_ptr)
				++(*_pCount);
		}

		shared_ptr<T> operator=(const shared_ptr<T>& sp) // ��ֵ���������Ҫ�������������Ƿ�Ϊͬһ����Դ
		{
			if (_ptr != sp._ptr)
			{
				// ��ԭ����Դ����-1
				Release();

				// ����Դ����+1
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
				DF()(_ptr); // �ͷ���Դ

				delete _pCount; // �ͷż���
				_pCount = nullptr;
			}
		}
	private:
		T* _ptr;
		int* _pCount; // ���ü���
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

// ������shared_ptr
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
		// ָ�����Ʋ���
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
		/////////////////////////////////////////////
		// ���ǳ������ÿ����Դ����һ�����ü���
		shared_ptr(const shared_ptr<T>& sp) // �������죬��������ʹ�õ���ͬһ����Դ��ֻҪ����Դ������+1����
			:_ptr(sp._ptr)
			, _pCount(sp._pCount)
			, _pMutex(sp._pMutex)
		{
			if (_ptr)
				AddRef();
		}

		shared_ptr<T> operator=(const shared_ptr<T>& sp) // ��ֵ���������Ҫ�������������Ƿ�Ϊͬһ����Դ
		{
			if (_ptr != sp._ptr)
			{
				// ��ԭ����Դ����-1
				Release();

				// ����Դ����+1
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
				DF()(_ptr); // �ͷ���Դ

				delete _pCount; // �ͷż���
				_pCount = nullptr;

				delete _pMutex; // �ͷ���
				_pMutex = nullptr;
			}
		}
	private:
		T* _ptr;
		int* _pCount; // ���ü���
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

// ѭ�����õĽ����ʽ����weak_ptr
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

	// shared_ptr��ѭ����������
	//shared_ptr<ListNode> next;
	//shared_ptr<ListNode> prev;

	weak_ptr<ListNode> next; 
	weak_ptr<ListNode> prev;
	int data;
};

void TestWeak_ptr()
{
	// ��֤��׼����shared_ptr�����⣺ѭ������
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