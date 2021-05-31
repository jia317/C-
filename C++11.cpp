#include<iostream>
#include<windows.h>
using namespace std;

// �б��ʼ��

#include<vector>
#include<map>
// �������͵��б��ʼ��
#if 0
int main()
{
	// �������ͱ���
	int a1 = 10;
	int a2(10);
	int a3{ 10 };

	// ����
	int arr1[5]{1, 2, 3, 4, 5};
	int arr2[]{1, 2, 3};

	// ��̬���飬��C++98�в�֧��
	int* arr3 = new int[5]{1, 2, 3, 4, 5};

	// ��׼����
	vector<int> v{ 1, 2, 3, 4, 5 };
	map<string, string> m{ { "orange", "����" }, { "mango", "â��" } };


	system("pause");
	return 0;
}
#endif

// �Զ������͵��б��ʼ��
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
	// ��׼��֧�ֵ���������б��ʼ��
	//Point p{ 1, 2 };

	// ���������Ҫ֧���б��ʼ������Ҫ������(ģ����)���һ������initializer_list���Ͳ����Ĺ��캯������
	jia::vector<int> v1{ 1, 2, 3 };

	/*
	���û���ṩ�б��ʽ�ĸ�ֵ
	1. ����{4��5��6}�����б��ʼ����ʽ�Ĺ��캯������һ����ʱ����
	2. ����ʱ�����v1��ֵ
	3. ��ֵ��ɺ���ʱ�����������
	*/
	v1 = { 4, 5, 6 };

	system("pause");
	return 0;
}
#endif

/*
autoʹ�õ�ǰ���ǣ�����Ҫ��auto���������ͽ��г�ʼ��������������޷��Ƶ���auto��ʵ�ʱ���
auto������Ϊ�����������ߺ�������ֵ
C++98��֧�ֵ�RTTI(����ʱ����ʶ��)��
1��typeid��ֻ�ܲ鿴���ͣ�������������������
2��dynamic_cast��ֻ��Ӧ���ں����麯���ļ̳���ϵ��
RTTIȱ�㣺���ͳ�������Ч��

decltype�����ݱ��ʽ��ʵ���������ݶ������ʱ���õ�����
*/
#if 0
void* GetMemory(size_t size)
{
	cout << "����GetMemory()" << endl;
	return malloc(size);
}

// C�����еĶ��巽ʽ
// ������Getmemory����������ͬ�ĺ���ָ������ --- ����ָ������
typedef void* (*CF)(size_t size); // pF��һ������
// ������Getmemory����������ͬ�ĺ���ָ������ --- ����ָ�����
void* (*pFun)(size_t size); // pFun��������ָ������һ������ֵΪvoid*�������б�Ϊ(size_t size)�ĺ���

typedef decltype(&GetMemory) CPPF; // PF��һ������
CPPF pf; // pf�Ǻ���ָ�����͵ı���
/*
int arr[10]
arr����������Ҳ��������Ԫ�ص�ַ
�������ͣ�ȥ�������������������� ---> int[10]

void* GetMemory(size_t size)
GetMemory���Ǻ�������Ҳ�Ǻ�����ڵ�ַ
�������ͣ�ȥ�����������Ǻ�������void* _cdecl(size_t) 
����ָ�����ͣ�void* (*_cdecl)(size_t) 
����ָ�������void* (*p_cdecl)(size_t)

decltype(GetMemory)�����ݳ������Ǻ�������
decltype(&GetMemory)�����ݳ������Ǻ���ָ������

���庯��ָ�����
decltype(&GetMemory) pf;
typedef decltype(&GetMemory) PF; PF pf;
*/

int main()
{
	int a = 10;
	double b = 3.14;
	auto c = a + b;

	// ���ݱ��ʽ������Ϊ�����Ķ�������
	decltype(a + b) d;
	cout << typeid(d).name() << endl;

	// ���ݺ�������ֵ����
	// ���ֱ����decltype֮����������֣��Ƶ��������Ǻ�������
	cout << typeid(decltype(GetMemory)).name() << endl;
	 // �����decltype֮������Ǻ������ã��Ƶ��������Ǻ�������ֵ���� ע�⣺���Ƶ��ڼ䲻����øú���
	cout << typeid(decltype(GetMemory(100))).name() << endl; // ��������ֵ����

	pFun = GetMemory; // pFun�Ǻ���ָ�������ָ��GetMemory����
	pFun(10); // �൱��GetMemory(10)

	// ��֤��
	cout << typeid(CF).name() << endl;
	cout << typeid(CPPF).name() << endl;

	// ��C�����У�������ֻ����sizeof��&֮�󣬲Ŵ������鱾��
	// ��������decltype��������Ҳ��ʾ���鱾��
	int arr[10];
	cout << typeid(decltype(arr)).name() << endl;

	system("pause");
	return 0;
}
#endif
#if 0
template<class T1, class T2>
auto Add(const T1& left, const T2& right)->decltype(left+right) // auto��һ��ռλ��
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

// ��ֵ����
#if 0
int main()
{
	// C++98�е�����
	int a = 10;
	int& ra = a;

	// C++11�е���ֵ����
	int&& rra = 100;

	// ע�⣺��ֵ���ò���ֱ��������ֵ
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
	//int&& rrc = c; // c����ȡ��ַ����������ֵ

	// ������ʽ�����н����һ����ʱ�����������Ϊ����ֵ
	int&& rr = a + b; // a+b�Ľ����һ����ʱ����
	A&& rr1 = Get(); // Get()����һ����ʱ����

	//int&& rrb = GetI(); // a��һ��ȫ�ֱ���������ֵ

	// ������ʽ���н���򵥸�������һ�����ã�����Ϊ����ֵ
	int& ra = a;
	//int&& rra = ra; 

	system("pause");
	return 0;
}
#endif

// C++98�����ã�����������ֵ��Ҳ����������ֵ
// C++11����ֵ���ã�һ��ֻ��������ֵ
#if 0
void TestRef98()
{
	// C++98 ����
	// ��ͨ���͵�����
	int a = 10;
	int& ra = a; // ���õ�����ֵ
	//int& rb = 10; // ��ͨ���͵����ò���������ֵ

	// const���͵�����
	// ��C++98�У�const���͵�����ʵ������������
	const int b = 100;
	const int& rb = b; // const�������ÿ���������ֵ
	const int& rc = 100; // const�������ÿ���������ֵ

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

	// ��ֵ�ķ�ʽ���ؽ��
	int&& rc = Get();

	//int&& rrd = a;
	int&& rre = move(a); // ������ֵ�ķ�ʽ

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
		return ret; // ����ֵ��ret��һ����ʱ��������retCopy��ret����ֵ�������ƶ�����
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
	��C++98�У�s3 = s1 + s2������������
	1. ����operator+������s1��s2�ַ���ƴ����������operator+�����У����ڲ��ܸı�s1��s2������ʹ��const���Σ�����Ҫ����һ����ʱ����temp������s1��s2��ƴ�ӽ��
	   ����ʱҪ����һ��string��������Ҫ��temp�Ŀռ䴴��һ������ret������ret�Ǻ���ջ�ϵĶ��󣬳�����������Ҫ���٣����Է���ֵҪ��������һ��ret����ʱ����retCopy
	   retCopy������ɺ�ret�ͻ����٣�ret�е�_str����ԴҪ�ͷ�
	2. ���ø�ֵ��������غ�������retCopy��ֵ��s3��retCopy��ֵ������ҲҪ���٣�retCopy�е�_str����ԴҲҪ�ͷ�
	3. ���ԣ������ַ�ʽ�£������ο��ٿռ�Ĺ��̣���ret,retCopy,s3������ÿ���������Դ��ֻ�к̵ܶ��������ڣ����ֶ����ǽ���ֵ��Ҳ������ֵ������ͨ����ֵ��������߳�������Ч��
	4. ���ԣ���Ҫͨ����Դת�Ƶķ�ʽ���ٿ�����Դ������

	C++11�е��ƶ�����Ϳ��Խ����������
	�ƶ�������ƶ���ֵ���������
	*/
	s3 = s1 + s2; // s1+s2�Ľ��retCopy����ֵ�������ƶ���ֵ
}

// move������
void TestString2()
{
	String s1 = "hello";
	String s2(move(s1));
	String s3(s2);

	/*
	s1��һ����ֵ����s1��moveת��Ϊ��ֵ������s2��������ƶ����죬��s1�е���Դת�Ƹ�s2����s1._str==nullptr
	֮����ʹ��s1������Դ�ͻ����
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
	p���õ�����ֵ������p�е�_name��_sex��������ֵ�������String���п�������
	����p��һ������ֵ�����Կ��԰�p�е���Դת�Ƹ�thisָ��Ķ���
	����Ҫ��_name��_sexת��Ϊ��ֵ���������String���е��˶�����
	*/
	Person(Person&& p)
		:_name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{ }
#endif

	// move����ȷʹ�ã�
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
	Person person("jia", "Ů", 21);
	return person; // person��һ������ֵ��ֵ����Ҫ������ʱ���󣬵���Person�е��ƶ�����
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

// ����ת��---std::forward<T>��ʹ��
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
PerfectForwardΪת���ĺ���ģ�壬FunΪʵ��Ŀ�꺯��
����ת����Ŀ�꺯����ϣ�����������մ��ݸ�ת��������ʵ������ת��Ŀ�꺯��
��������ģ������Ŀ�꺯������ʱ��
������ݸ�����ģ���ʵ������ֵ�����ݸ�Ŀ�꺯����Ҳ����ֵ
������ݸ�����ģ���ʵ������ֵ�����ݸ�Ŀ�꺯����Ҳ����ֵ
*/
void PerfectForward(T &&t)
{
	Fun(t); //
	//Fun(std::forward<T>(t));
}

int main()
{
	PerfectForward(10); // ��ͨ��ֵ����

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

// ��ֵ���ø��м���ʱ����ȡ����
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
		return ret; // ����ֵ��ret��һ����ʱ��������retCopy��ret����ֵ�������ƶ�����
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
	s1 = s2 + s3; // s2+s3�ķ���ֵretCopy�ڸ�ֵ�����������

	// s3��s4������ֵ���ø��м���ʱ����ȡ������д��
	String s4 = s2 + s3; // s2+s3�ķ���ֵretCopy�ڸ�ֵ�����󲻻����٣�s4����retCopy���ӳ���retCopy����������
	String&& s5 = s2 + s3;

	system("pause");
	return 0;
}
#endif

/*
lambda���ʽ
Ӧ�ó�����
1. �ڱȽ��У��Զ������͵�Ԫ�رȽϣ���Ҫ�û�����Ƚ����������ַ�ʽ������ָ����߷�װ���࣬����������()
   ���ÿ�αȽ��߼���ͬ����Ҫȥʵ�ֶ���࣬�ر�����ͬ����������鷳�������ظ�
2. C++98�У���һ�������в��ܶ�����һ���������Һ�����Ҫ�õ����ڲ�����ĺ������ִ����϶࣬����ֻ�ڸú�����ʹ��
lambda���ʽ�ṹ
[�����б�](�����б�)multable->����ֵ����{������}
*/

#include<algorithm>
#include<functional>
// ��C++98�У������Ҫ��һ�����ݼ����е�Ԫ�ؽ������򣬿���ʹ��std::sort����
#if 0
int main()
{
	int arr[] = { 6, 4, 2, 1, 7, 5, 3 };

	std::sort(arr, arr + sizeof(arr) / sizeof(arr[0])); // ����������������Ĭ������������
	// �����Ҫ������Ҫ�ı�Ԫ�صıȽϹ���
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

// ���������Ԫ��Ϊ�Զ������ͣ���Ҫ�û���������ʱ�ıȽϹ���
// ���ַ�ʽ������ָ����װ������()
struct Compare
{
	bool operator()(const Goods& gl, const Goods& gr)
	{
		return gl._price <= gr._price;
	}
};

int main()
{
	Goods gds[] = { { "ƻ��", 2.1 }, { "�㽶", 3 }, { "â��", 5 } };
	//sort(gds, gds + sizeof(gds) / sizeof(gds[0]), Compare());

	// ����lambda���ʽ
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

	// lambda���ʽʵ�����
	auto ADD = [a,b](int left, int right)->int{ return left + right; };
	auto add = [a](int left, int right)mutable->int{ a += 2; return left + right; }; 

	cout << ADD(a, b) << endl;
	cout << add(a, b) << endl;
	cout << a << endl;

	// ��ֵ�ķ�ʽ�����������еı�����&a����ͬ��lambda���ʽ�е�a��a����ʱ����
	auto Add = [a](int left, int right)->int{ cout << &a << endl; return left + right; };
	Add(a, b);
	cout << &a << endl;

	// �����õķ�ʽ�����������еı�����&a��ͬ
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

		// ��ֵ�ķ�ʽ���������������б���������thisָ��
		auto l1 = [=]
		{
			cout << a << endl;
			cout << b << endl;
			cout << c << endl;

			cout << this << endl;
			this->_year = 2021;
			this->_month = 5;
			this->_day = 30;

			// ���ܲ����������ж�����lambda���ʽ��ı���
			//cout << d << endl;
		};
		int d;

		// �����ظ�����
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
		

		// �����õķ�ʽ���������������б���������thisָ��
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

			//this = nullptr; // �����޸�this
			pa = &b;
		};
		l3();
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
		cout << this->_year << endl;
		cout << this->_month << endl;
		cout << this->_day << endl;

		// �����ظ����ò���
		/*auto l4 = [&, &a]
		{
			a = 15;

			cout << this << endl;
			this->_year = 2021;
			this->_month = 5;
			this->_day = 30;
		};
		*/

		// ��ʾ����a��ֵ�ķ�ʽ���������������������б����������÷�ʽ����
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

// �ڿ������������lambda���ʽ�Ĳ����б����Ϊ��
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
		// l1�ĸ����������if�Ļ�����
		auto l1 = [a]{
			cout << a << endl;
		};
	}
	
	// ֻ�ܲ���lambda���ʽ���������еı���
	// ���ܲ���������������ı���
	//auto l2 = [b]{ };
	// ���ܲ����ȫ��������ı���
	//[c]{};
}
#endif

// lambda���ʽ�ڵײ�ʵ����Ҳ�Ƿº����ķ�ʽ
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
	// ��������
	double rate = 0.49;
	Rate r1(rate);
	r1(10000, 2);
	// lamber
	auto r2 = [=](double monty, int year)->double{return monty*rate*year; };
	r2(10000, 2);
	return 0;
}
#endif

// C�����е�����ת��
#if 0
int main()
{
	// C�����е���ʽ����ת�����ܻ����м����
	double a = 12.34;
	//int& ra = a;
	/*
	���ñ���������������һ�£�Ϊ����ra����a��ֻ����a���������ִ���һ����ʱ��������raȥ������ʱ����
	������ʱ��������ȡ��ַҲ�����޸ģ�������ʱ�������г��ԣ���������ʱҪ��const
	*/
	const int& ra = a; 

	/*
	��֤��ra���õ�����ʱ������������a
	�޸�a��ֵ������raû�б䣬����a��ra�ĵ�ַҲ��ͬ
	*/
	a = 23.45;
	cout << a << endl;    
	cout << ra << endl;
	cout << &a << endl;
	cout << &ra << endl;

	// ��a�ĵ�ַ����int*���͵ĵ�ַ���� ���ᴴ����ʱ����
	// ��a�Ŀռ���8�ֽڣ�paֻ�ܷ���4�ֽ�����
	int* pa = (int*)&a;
	cout << &a << endl;
	cout << pa << endl;

	// ��C++�У�const���ε����ݱ�������Ϊ��һ�����������Ҿ��к��滻��Ч��
	const int b = 7;
	int* pb = (int*)&b; // &b��������const int*������ǿתΪint*���൱��ȥ��const
	*pb = 10;
	//b = 12; // ���������޸�
	cout << b << endl; // �ڱ���ʱ�Ѿ��滻Ϊ7�ˣ����Լ�ʹ�޸���b����ӡ���������7
	cout << *pb << endl;


	system("pause");
	return 0;
}
#endif

// static_cast��reinterpret_cast��const_cast���÷�
#if 0
int main()
{
	double d = 12.34;
	int a = static_cast<int>(d);

	int* pd = reinterpret_cast<int*>(&d);

	// reinterpret_cast���Խ�һ��ָ��ת��Ϊ�������ٽ�����ת��Ϊָ�룬ת��֮���ָ�����ɿ����õ�ԭָ���ֵ
	int c = 10;
	int* pc = &c;
	cout << *pc << endl;
	int rc = reinterpret_cast<int>(pc);
	int* rpc = reinterpret_cast<int*>(rc);
	cout << *rpc << endl;

	// const_cast����ɾ��������const����
	const int e = 7;
	int& re = const_cast<int&>(e);
	int* pe = const_cast<int*>(&e);



	system("pause");
	return 0;
}
#endif

// dynamic_cast���÷�
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
	// static_cast�رջ���������������ͼ�飬���ܻ����
	D* pd1 = static_cast<D*>(pb);
	// dynamic_cast���ȼ���Ƿ��ܹ�ת���ɹ����ܳɹ���ת�����򷵻�0
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
	func(&b); // ����ָ��ָ��������
	func(&d);

	system("pause");
	return 0;
}
#endif

// explicit�ؼ���
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
	������ι��캯������explicit
	1. ���õ��ι���һ����������
	2. �����������a1��ֵ

	����explicit�ؼ��־Ͳ���������ֵ��
	*/
	//a1 = 1; 

	//A a2 = 1;

	system("pause");
	return 0;
}
#endif

// �߳̿�
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
	thread t1; // ����һ�����󣬵���ʵ����û�д����߳�

	// ������ָ��
	thread t2(TFunc,7); // ��һ��Ϊ�߳�Ҫ�����£���ߵ��Ǻ����Ĳ���

	// �º������ȴ�������Ȼ�󴫵ݶ���
	TF f;
	thread t3(f);

	// lambda���ʽ
	thread t4([](int a){
		cout << "Lambda" << endl;
		cout << a << endl;
	}, 12);


	system("pause");
	return 0;
}
#endif

// �̺߳����Ĳ�������ֵ�����ķ�ʽ�������߳�ջ�ռ��

#if 0
void ThreadFunc1(int& ra) // raʵ�������õ���ʵ��a�ں�������ջ�еĿ��������Բ���ͨ��ra�޸��ⲿʵ��a��ֵ
{
	cout << &ra << endl;
	ra += 10;
}

void ThreadFunc2(int* pa) // paʵ�������õ���&a�ں�������ջ�еĿ��������ǿ����д�ŵľ���a�ĵ�ַ������ͨ��pa�����޸��ⲿʵ��a��ֵ
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

	// ���һ��Ҫ�����÷�ʽ������ʹ��std::ref
	thread t3(ThreadFunc1, std::ref(a));
	t3.join();
	cout << a << endl;

	system("pause");
	return 0;
}
#endif