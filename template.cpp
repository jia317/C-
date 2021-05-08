#include<iostream>
#include<Windows.h>
using namespace std;

#pragma warning(disable:4996)

/*
模板编译过程
1. 没有实例化：编译器只对模板进行简单的语法检查，并不会生成真正的代码
2. 实例化之后：根据用户对模板实例化的类型来生成代码以及对生成的代码进行编译
*/

/*
1. 浮点数、类对象以及字符串是不允许作为非类型模板参数的
2. 非类型的模板参数必须在编译期就能确认结果
*/
#if 0
namespace jia
{
	// N就是非类型模板参数
	// 非类型模板参数在类模板中是一个常量
	template<class T,size_t N>
	class array
	{
	public:
		array()
			: _size(0)
		{

		} 
	private:
		T _array[N];
		size_t _size;
	};
}

int main()
{
	jia::array<int, 10> a;

	system("pause");
	return 0;
}
#endif

// 模板的特化
// 函数模板的特化：一般情况下，不需要对函数模板进行特化
#if 0
template<class T>
const T& Max(const T& left, const T& right)
{
	return left > right ? left : right;
}

// 对于模板处理不了的场景
// 1. 直接重新定义一个函数
const char* Max(const char* left, const char* right)
{
	if (strcmp(left, right) > 0)
		return left;

	return right;
}
// 类模板的特化
int main()
{
	cout << Max(1, 2) << endl;

	// 字符串的比较方式和模板提供的不一样，用模板实例化出来的代码去比较是错误的
	const char* s1 = "hello";
	const char* s2 = "World";
	cout << Max(s1, s2) << endl;

	system("pause");
	return 0;
}
#endif

// 对上述函数模板进行特化
/*
函数模板特化的步骤：
1. 必须要先有一个基础的函数模板
2. 关键字template后接一对空的尖括号
3. 函数名后跟一对尖括号，尖括号中指定需要特化的类型
4. 函数形参表：必须要和函数模板的基础参数类型完全相同，如果不同，编译器可能会报错
*/
#if 0
template<class T>
T& Max(T& left, T& right)
{
	return left > right ? left : right;
}

template<>
char*& Max<char*>(char*& left, char*& right)
{
	if (strcmp(left, right) > 0)
		return left;

	return right;
}

int main()
{
	char* s1 = "hello";
	char* s2 = "World";
	cout << Max(s1, s2) << endl;

	system("pause");
	return 0;
}
#endif

// 类模板特化
// 1. 全特化 ---> 将模板参数列表中所有类型参数具体化
#if 0
template<class T1,class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1,T2>()" << endl;
	}
private:
	T1 _d1;
	T2 _d2;
};

template<>
class Data<int,char>
{
public:
	Data()
	{
		cout << "Data<int,char>" << endl;
	}
private:
	int _d1;
	char _d2;
};

void Test1()
{
	Data<int, int> d1; // 调用模板
	Data<int, char> d2; // 调用全特化模板
}
#endif

// 偏特化
/*
1. 部分偏特化
2. 参数进一步限制
*/

#if 0
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1,T2>()" << endl;
	}
private:
	T1 _d1;
	T2 _d2;
};
// 部分偏特化
template<class T1>
class Data<T1,int>
{
public:
	Data()
	{
		cout << "Data<T1,int>" << endl;
	}
private:
	T1 _d1;
	int _d2;
};

void Test2()
{
	Data<int, int> d1; // 调用部分特化
	Data<int, double> d2; // 调用基础模板
	Data<double, double> d3; // 调用基础模板
	Data<double, int> d4; // 调用部分特化
}
#endif

#if 0
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1,T2>()" << endl;
	}
private:
	T1 _d1;
	T2 _d2;
};
// 针对模板参数更进一步的条件限制所设计出来的一个特化版本
template<class T1, class T2>
class Data<T1*,T2*>
{
public:
	Data()
	{
		cout << "Data<T1*,T2*>()" << endl;
	}
private:
	T1* _d1;
	T2* _d2;
};
template<class T1, class T2>
class Data<T1&, T2&>
{
public:
	Data(const T1& d1,const T2& d2)
		:_d1(d1)
		, _d2(d2)
	{
		cout << "Data<T1&,T2&>()" << endl;
	}
private:
	const T1& _d1;
	const T2& _d2;
};

void Test3()
{
	Data<double, int> d1; // 调用基础模板
	Data<int, double> d2; // 调用基础模板
	Data<int*, int*> d3; // 调用特化的指针模板
	Data<int&, int&> d4(1,2); // 调用特化的引用模板
}
int main()
{
	//Test1();
	//Test2();
	Test3();

	system("pause");
	return 0;
}
#endif

// sizeof的结果是无符号的 i是有符号整型
// i和sizeof(i)进行比较时，i会提升为无符号，会变成一个很大的数
#if 0
int i;
int main()
{
	i--;
	if (i > sizeof(i))
		cout << ">" << endl;
	else
		cout << "<" << endl;

	system("pause");
	return 0;
}
#endif

// 实现一个通用的拷贝函数

// 下面这种方式缺点：对于内置类型memcpy效率因为前面的if判断还要调用isPODType函数而导致效率变低
#if 0
// 判断是不是内置类型
bool isPODType(const string& strType)
{
	string types[] = { "char", "short", "int", "long", "double" };
	for (auto e : types)
	{
		if (e == strType)
			return true;
	}
	return false;
}
#endif

// 改进方法：用类模板的特化
struct TrueType // 内置类型
{
	static bool Get()
	{
		return true;
	}
};

struct FalseType // 自定义类型
{
	static bool Get()
	{
		return false;
	}
};

template<class T> // 基础类模板 自定义类型调用基础类模板
struct TypeTraits
{
	typedef FalseType PODTYPE;
};
// 类模板特化 内置类型调用特化版本
template<>
struct TypeTraits<int>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<double>
{
	typedef TrueType PODTYPE;
};

template<>
struct TypeTraits<char>
{
	typedef TrueType PODTYPE;
};

// ... 将每个内置类型特化

#if 0
template<class T>
void Copy(T* dst, T* src, size_t size)
{
	// typeid().name()获取类型名 返回值为存储了类型名的字符串
	//if (isPODType(typeid(T).name()) // 内置类型的拷贝用memcpy
	//{
	//	/*
	//	memcpy的优点：效率高，按字节拷贝
	//	memcpy的缺点：浅拷贝，可能还会造成内存泄漏
	//	*/
	//	memcpy(dst, src, size*sizeof(T));
	//}
	if (TypeTraits<T>::PODTYPE::Get())
	{
		memcpy(dst, src, size*sizeof(T));
	}
	else // 设计资源管理的自定义类型的拷贝
	{
		// 这种拷贝方式
		// 优点：一定不会出错
		// 缺点：效率低 因为要调用赋值运算符重载等
		for (int i = 0; i < size; i++)
			dst[i] = src[i];

	}
	
}
#endif

class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(new char[strlen(s._str)+1])
	{
		strcpy(_str, s._str);
	}

	// 赋值运算符重载必须重载成类的成员函数
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

template<class T>
void Copy(T* dst, T* src, size_t size, TrueType)
{
	memcpy(dst, src, size*sizeof(T));
}

template<class T>
void Copy(T* dst, T* src, size_t size, FalseType)
{
	for (size_t i = 0; i < size; i++)
	{
		dst[i] = src[i];
	}
}

template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	Copy(dst, src, size, TypeTraits<T>::PODTYPE());
}
int main()
{
	/*int array1[] = { 1, 2, 3, 4, 5 };
	int array2[sizeof(array1) / sizeof(array1[0])];

	Copy(array2, array1, 5);
	for (auto e : array2)
		cout << e << " ";
	cout << endl;*/
	
	String s1[] = { "11111", "22222", "33333" };
	String s2[3];
	Copy(s2, s1, 3);

	system("pause");
	return 0;
}
