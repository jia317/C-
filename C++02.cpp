#include <iostream>
#include <Windows.h>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;

#if 0
// ��Ĵ�С
class A
{
public:
	void func1(){ }

private:
	int a;
	char b;
};

class B
{
public:
	void func2(){ }
};

class C{ };

int main()
{
	/*cout << "��A�Ĵ�СΪ��" << sizeof(A) << endl;
	cout << "��B�Ĵ�СΪ��" << sizeof(B) << endl;
	cout << "��C�Ĵ�СΪ��" << sizeof(C) << endl;*/

	//p = &x; // �������Ὣ������������������ȫ��ͬ���������ͣ���������

	system("pause");
	return 0;
}
#endif

#if 0
// �ṹ������
// 1.��tag�Ľṹ����������
struct student
{
	int id;
	char name[20];
	int age;
	char sex[5];
};

// 2. �����ṹ����������
struct
{
	int a;
	char b;
	float c;
}x;

struct
{
	int a;
	char b;
	float c;
}a[20], *p;

// �ṹ���������
struct Node
{
	int data;
	struct Node* n;
};

// typedef�������������Ͷ����
typedef struct Node
{
	int data;
	Node* n; // �൱��struct Node* n;
}Node; // �����Node���൱��struct Node 

// �ṹ������Ķ���ͳ�ʼ��
// 1.�������͵�ͬʱ���������
struct Point
{
	int x;
	int y;
}p1;

// 2.ֱ�Ӷ���
struct Point p2;

// ��ʼ��
// 1. ���������ͬʱ��ʼ��
struct Point p3 = { 1, 2 };

typedef struct stu // ��������
{
	char name[25];
	int age;
}stu;
stu s = { "jia", 21 }; // ��ʼ��

// 2. �ṹ��Ƕ�׳�ʼ��
// ������ͬʱ���岢��ʼ��
struct Node
{
	int data;
	struct Point p;
	struct Node* next;
}n1 = { 10, {4, 5}, NULL };

// ����ʱ���г�ʼ��
struct Node n2 = { 1, { 2, 3 }, NULL };
#endif

#if 0
// �ṹ���ڴ����
// �޸�Ĭ�϶�����
//#pragma pack(1) // �޸�Ĭ�϶�����Ϊ1�ֽ�
// vsĬ�϶�����Ϊ8
typedef struct S1 // sizeof(S1) = 12 �������� = 4
{
	char a; // 1 ������1
	int b; // 8 ������4
	long c; // 12 ������4
}S1;
typedef struct S2 // sizeof(S2) = 24 �������� = 8
{
	short a; // 2 ������2
	double b; // 16 ������8
	S1* s1; // 24 �ṹ�������С���뵽����������������
}S2;
//#pragma pack() // ȡ�����õ�Ĭ�϶���������ԭΪĬ��(4)

// ����ĳ����������׵�ַ��ƫ��

// �ṹ�崫�Σ����ṹ���ַ
struct S
{
	int data[100];
	int num;
}s = { {1,2,3}, 7 };

// ���ṹ��
void Print1(struct S s)
{
	cout << s.data << endl;;
	cout << s.num << endl;
}

// ���ṹ���ַ
void Print2(struct S* s)
{
	cout << s->data << endl;;
	cout << s->num << endl;
}

int main()
{

	//cout << "�޸�Ĭ�϶�����Ϊ1��struct S2�Ĵ�СΪ��" << sizeof(struct S2) << endl;
	//cout << "ȡ�����õ�Ĭ�϶�������struct A�Ĵ�СΪ��" << sizeof(struct A) << endl;
	
	//Print1(s); // ���ṹ��
	//Print2(&s); // ���ṹ���ַ

	cout << "sizeof(S1) = " << sizeof(S1) << endl;
	cout << "sizeof(S2) = " << sizeof(S2) << endl;

	cout << sizeof(float) << endl;
	system("pause");
	return 0;
}
#endif

// thisָ��
#if 0
class A
{
public:
	void PrintA()
	{
		cout << _a << endl;
	}

	void Show()
	{
		cout << "Show()" << endl;
	}
private:
	int _a;
};

int main()
{
	A* const p = NULL;
	p->PrintA();
	p->Show();

	system("pause");
	return 0;
}
#endif

// ��֤������ڴ沼��
#if 0
class Student
{
public:
	char _name[20];
	char _sex[3];
	int _age;

public:
	void InitStu(char name[], char sex[], int age)
	{
		strcpy(_name, name);
		strcpy(_sex, sex);
		_age = age;
	}

	void PrintStu()
	{
		cout << _name << "-" << _sex << "-" << _age << endl;
	}

};

int main()
{
	Student s1, s2, s3;
	s1.InitStu("jia", "Ů", 21);
	s2.InitStu("ha", "��", 22);
	s3.InitStu("der", "��", 18);

	s1.PrintStu();
	s2.PrintStu();
	s3.PrintStu();

	cout << sizeof(s1) << endl;

	system("pause");
	return 0;
}
#endif

// thisָ�����⣺���±ߴ��뷭���c���Դ���
#if 0
class Car
{
public:
	void SetPrice(int price)
	{
		_price = price;
	}
	void GetPrice()
	{
		cout << _price << endl;
	}
private:
	int _price;
};

int main()
{
	Car c;
	c.SetPrice(100);
	c.GetPrice();

	system("pause");
	return 0;
}

// ��ΪC���ԣ���Ա�����ýṹ�屣�棬��Ա�������ȫ�ֺ�������
struct Car
{
	int _price;
};

void SetPrice(struct Car* This, int price)
{
	This->_price = price;
}

void GetPrice(struct Car* This)
{
	cout << This->_price << endl;
}

int main()
{
	struct Car c;
	SetPrice(&c, 100);
	GetPrice(&c);

	system("pause");
	return 0;
}
#endif

// ����thisָ�����Ĵ洢
#if 0
class Person
{
public:
	void SetAge(int age)
	{
		_age = age;
		cout << _age << endl;
	}
private:
	char _name[20];
	int _age;
};

int main()
{
	//Person p;
	//p.SetAge(21);

	system("pause");
	return 0;
}
#endif

// �������Ĭ�ϳ�Ա����
// 1. ���캯����ֻ�����ʼ������
// ��������������ͬ���޷���ֵ������ʵ����ʱ�������Զ����ö�Ӧ�Ĺ��캯��
// ����û�����ʽ���幹�캯������������Ĭ������һ�����캯��
// ���캯����������

#if 0
class Date
{
public:
	// �޲ι���
	//Date(){ }

	// ���ι���
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	/*void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}*/

	// ---------------------------------------------------------

	Date()
	{
		_year = 2021;
		_month = 4;
		_day = 17;
	}

	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

void TestDate()
{
	Date d1; // �����޲ι���
	Date d2(2021,4,17); // ���ô��ι���

	//Date d3(); // ����һ�������������ú����޲Σ�����һ��Date���͵Ķ���
}

void TestDate2()
{
	Date d;
}

int main()
{
	/*Date d1, d2;
	d1.SetDate(2021, 4, 17);
	d1.Display();

	d2.SetDate(2021, 4, 18);
	d2.Display();*/

	//TestDate2();

	Date d;

	system("pause");
	return 0;
}
#endif

#if 0
// ����ʽ���幹�캯��
// ���������ܻ�����Ĭ�Ϲ��캯��
class Date
{
public:

private:
	int _year;
	int _month;
	int _day;
};
#endif

// ������Ĭ�����ɹ��캯����4�����
// 1. ���а�����һ�����Ա���������Ա��������ж�����Ĭ�Ϲ��캯��
// Time����ʽ���幹�캯����Date�಻��ʽ���幹�캯��
// Date���а���һ��Time�����
class Time
{
public:
	/*Time()
	{
	cout << "Time()" << endl;
	_hour = 0;
	_min = 0;
	_sec = 0;
	}*/
private:
	int _hour;
	int _min;
	int _sec;
};

class Date
{
private:
	// ��������(��������)
	int _year;
	int _month;
	int _day;

	Time _t; // �Զ�������
};

// 2.���ඨ����Ĭ�Ϲ��캯���������࣬�������������ʱ
class Base
{
public:
	Base()
	{
		cout << "Base()" << endl;
	}
};

class Derived :public Base
{
public:
	int _d;
};


int main()
{
	//Date d;

	Derived d;
	system("pause");
	return 0;
}