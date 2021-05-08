#include<iostream>
#include<Windows.h>
using namespace std;

#pragma warning(disable:4996)

/*
ģ��������
1. û��ʵ������������ֻ��ģ����м򵥵��﷨��飬���������������Ĵ���
2. ʵ����֮�󣺸����û���ģ��ʵ���������������ɴ����Լ������ɵĴ�����б���
*/

/*
1. ��������������Լ��ַ����ǲ�������Ϊ������ģ�������
2. �����͵�ģ����������ڱ����ھ���ȷ�Ͻ��
*/
#if 0
namespace jia
{
	// N���Ƿ�����ģ�����
	// ������ģ���������ģ������һ������
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

// ģ����ػ�
// ����ģ����ػ���һ������£�����Ҫ�Ժ���ģ������ػ�
#if 0
template<class T>
const T& Max(const T& left, const T& right)
{
	return left > right ? left : right;
}

// ����ģ�崦���˵ĳ���
// 1. ֱ�����¶���һ������
const char* Max(const char* left, const char* right)
{
	if (strcmp(left, right) > 0)
		return left;

	return right;
}
// ��ģ����ػ�
int main()
{
	cout << Max(1, 2) << endl;

	// �ַ����ıȽϷ�ʽ��ģ���ṩ�Ĳ�һ������ģ��ʵ���������Ĵ���ȥ�Ƚ��Ǵ����
	const char* s1 = "hello";
	const char* s2 = "World";
	cout << Max(s1, s2) << endl;

	system("pause");
	return 0;
}
#endif

// ����������ģ������ػ�
/*
����ģ���ػ��Ĳ��裺
1. ����Ҫ����һ�������ĺ���ģ��
2. �ؼ���template���һ�Կյļ�����
3. ���������һ�Լ����ţ���������ָ����Ҫ�ػ�������
4. �����βα�����Ҫ�ͺ���ģ��Ļ�������������ȫ��ͬ�������ͬ�����������ܻᱨ��
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

// ��ģ���ػ�
// 1. ȫ�ػ� ---> ��ģ������б����������Ͳ������廯
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
	Data<int, int> d1; // ����ģ��
	Data<int, char> d2; // ����ȫ�ػ�ģ��
}
#endif

// ƫ�ػ�
/*
1. ����ƫ�ػ�
2. ������һ������
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
// ����ƫ�ػ�
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
	Data<int, int> d1; // ���ò����ػ�
	Data<int, double> d2; // ���û���ģ��
	Data<double, double> d3; // ���û���ģ��
	Data<double, int> d4; // ���ò����ػ�
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
// ���ģ���������һ����������������Ƴ�����һ���ػ��汾
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
	Data<double, int> d1; // ���û���ģ��
	Data<int, double> d2; // ���û���ģ��
	Data<int*, int*> d3; // �����ػ���ָ��ģ��
	Data<int&, int&> d4(1,2); // �����ػ�������ģ��
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

// sizeof�Ľ�����޷��ŵ� i���з�������
// i��sizeof(i)���бȽ�ʱ��i������Ϊ�޷��ţ�����һ���ܴ����
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

// ʵ��һ��ͨ�õĿ�������

// �������ַ�ʽȱ�㣺������������memcpyЧ����Ϊǰ���if�жϻ�Ҫ����isPODType����������Ч�ʱ��
#if 0
// �ж��ǲ�����������
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

// �Ľ�����������ģ����ػ�
struct TrueType // ��������
{
	static bool Get()
	{
		return true;
	}
};

struct FalseType // �Զ�������
{
	static bool Get()
	{
		return false;
	}
};

template<class T> // ������ģ�� �Զ������͵��û�����ģ��
struct TypeTraits
{
	typedef FalseType PODTYPE;
};
// ��ģ���ػ� �������͵����ػ��汾
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

// ... ��ÿ�����������ػ�

#if 0
template<class T>
void Copy(T* dst, T* src, size_t size)
{
	// typeid().name()��ȡ������ ����ֵΪ�洢�����������ַ���
	//if (isPODType(typeid(T).name()) // �������͵Ŀ�����memcpy
	//{
	//	/*
	//	memcpy���ŵ㣺Ч�ʸߣ����ֽڿ���
	//	memcpy��ȱ�㣺ǳ���������ܻ�������ڴ�й©
	//	*/
	//	memcpy(dst, src, size*sizeof(T));
	//}
	if (TypeTraits<T>::PODTYPE::Get())
	{
		memcpy(dst, src, size*sizeof(T));
	}
	else // �����Դ������Զ������͵Ŀ���
	{
		// ���ֿ�����ʽ
		// �ŵ㣺һ���������
		// ȱ�㣺Ч�ʵ� ��ΪҪ���ø�ֵ��������ص�
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

	// ��ֵ��������ر������س���ĳ�Ա����
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
