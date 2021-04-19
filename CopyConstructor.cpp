#include <iostream>
#include <Windows.h> 
#pragma warning(disable:4996)
using namespace std;

// �������캯�����ó���
// �������캯���Ĳ���ΪʲôҪ��const
// �������캯���Ĳ���ΪʲôҪ������
/*
������Ĭ�����ɵĿ������캯���Ŀ�����ʽ��ǳ����(���ֽڿ���)
ʲôʱ����붨�忽�����캯�����Զ�������ʱ���Լ�д�ͱ������Զ����ɵ�һ�� 
�漰����Դ����ʱ�ͻ������ ��������ͬһ���ռ��ͷ�����
*/

#if 0
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	// �������캯��
	/*Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}*/
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2021, 4, 19);
	Date d2(d1);

	system("pause");
	return 0;
}
#endif

#if 0
class String
{
public:
	// ���캯��
	String(const char* str = "jia")
	{
		/*
		strlen�����������ַ������ȣ�������\0
		sizeof�������������ʹ�С
		*/
		// �Ӷ��Ͽ����ܱ����ַ�����С��һ�οռ䣬������οռ���׵�ַ����_str
		_str = (char*)malloc(strlen(str) + 1);
		// ��str�ַ����е��ַ�һ��һ��������_strָ��Ŀռ���
		strcpy(_str, str);
	}

	// �������캯��
	String(const String& s)
	{
		_str = (char*)malloc(strlen(s._str)+1);
		strcpy(_str, s._str);
	}

	// ��������
	~String()
	{
		cout << "~String()" << endl;
		free(_str);
		_str = nullptr;
	}
private:
	char* _str;
};

// ��TestString����ִ���꣬s1��s2��Ҫ�����٣��������Կ�������ʱ�������������Ľ��
// ���ֱ��д��main�����У�Ҫreturn֮�󣬶���Żᱻ���٣��������������������Ľ������Ҫ����������ļ���
void TestString()
{
	String s1("hello");
	String s2(s1);
}
int main()
{
	TestString();

	system("pause");
	return 0;
}
#endif

// ��ֵ���������
#if 0
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		cout << "Constructor" << endl;
		_year = year;
		_month = month;
		_day = day;
	}

	// д�����������ֻ��Ϊ����֤d2��d4�����˿������캯������ӡ����
	/*Date(const Date& d)
	{
		cout << "Copy_Constructor" << endl;
	}*/

	/*Date& operator+(int days)
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}*/
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2021, 4, 19); // ���ù��캯��
	Date d3; // ���ù��캯��

	/*
	1. ���ֵ��ÿ������캯���͸�ֵ���������
	�������캯���������Ѿ����ڵĶ����ʼ���´����Ķ���
	��ֵ��������أ������Ѿ����ڵĶ������һ���Ѿ����ڵĶ���ֵ
	*/
	Date d2 = d1; // ���ÿ������캯��
	Date d4(d3); // ���ÿ������캯��

	d3 = d1; // ���ø�ֵ���������

	system("pause");
	return 0;
}
#endif

/*
2. δ��ʽ���帳ֵ��������أ����������Զ�����
���ǣ���������һ���������һ������ֵ�󣬱���ֵ�Ķ���ԭ���Ŀռ�ͱ�������
����漰����Դ�����ڵ�����������ʱ���޷��ͷ���οռ䣬�����ڴ�й©
*/
#if 0
class String
{
public:
	// ���캯��
	String(const char* str = "jia")
	{
		/*
		strlen�����������ַ������ȣ�������\0
		sizeof�������������ʹ�С
		*/
		// �Ӷ��Ͽ����ܱ����ַ�����С��һ�οռ䣬������οռ���׵�ַ����_str
		_str = (char*)malloc(strlen(str) + 1);
		// ��str�ַ����е��ַ�һ��һ��������_strָ��Ŀռ���
		strcpy(_str, str);
	}

	// �������캯��
	String(const String& s)
	{
		_str = (char*)malloc(strlen(s._str) + 1);
		strcpy(_str, s._str);
	}

	// ��������
	~String()
	{
		cout << "~String()" << endl;
		free(_str);
		_str = nullptr;
	}
private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	String s2(s1);
	
	String s3;
	s3 = s1;
}
int main()
{
	TestString();

	system("pause");
	return 0;
}
#endif

// ����������
// 1. ��������صĲ���������һ�������ͻ��Զ������͵Ĳ���
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	/*Date& operator+(int days)
	{
	Date temp(*this);
	temp._day += days;
	return temp;
	}*/

	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	/*
	ΪʲôҪ������������أ�
	�����Զ������ͣ���������֪����ν������������
	�Ը���������أ����Ǹ��߱�������Ը����͵Ķ�����ν��и��ֲ������Ĳ���
	*/
	// < �����������
	bool operator<(const Date& d)
	{
		if ((_year<d._year)||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day))
		{
				return true;
		}
		return false;
	}

	bool operator==(const Date& d)
	{
		if (_year == d._year &&
			_month == d._month &&
			_day == d._day)
		{
			return true;
		}
		return false;
	}

	/* 
	�����������������У��Ǹ���������غ�������ĳ�Ա����
	��Ա�������������Ĳ���thisָ��
	*/
	// !=�����غܺõ�˵����������������غ����Ĳ�������������thisָ��
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	/*
	�±ߵ�+��������ش��ڵ����⣺
	1. ���������ͻ��Զ������
	2. ����ֻ���������͵Ĳ��������������޵ݹ���������������غ���
	*/
	/*int operator+(int a, int b)
	{
		return a + b;
	}*/

	// û�����ף���
	/*enum Data
	{THREE}; 
	int operator+(Data a, int b)
	{
		return a + b;
	}*/
	 
	/*

	*/
	// �����÷��أ����ض����������ڱ���Ⱥ����������ڳ�
	Date& operator+(int days)
	{
		_day += days;
		return *this;
	}

	Date operator+=(int days)
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1;
	Date d2(2000, 8, 2);

	if (d1 < d2)
	{
		cout << "d1 < d2" << endl;
	}
	else
	{
		cout << "d1 >= d2" << endl;
	}

	d2 = d1 + 2; // ����+���������
	d1 += 2; // ����+=���������

	system("pause");
	return 0;
}
