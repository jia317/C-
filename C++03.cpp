#include <assert.h>
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
#pragma warning(disable:4996)

// ��������
// 1. �����ڶ��������˿ռ�
typedef int DataType;
class SeqList
{
public:
	SeqList(int capacity = 10)
	{
		_pData = (DataType*)malloc(capacity*sizeof(DataType));
		assert(_pData);

		_size = 0;
		_capacity = capacity;
	}

	~SeqList()
	{
		if (_pData)
		{
			free(_pData);
			*_pData = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
private:
	DataType* _pData;
	DataType _size;
	DataType _capacity;
};

// ���а����Զ������ͳ�Ա
class String
{
public:
	String(const char* str = "jia")
	{
		_str = (char*)malloc(strlen(str) + 1);
		strcpy(_str, str);
	}

	~String()
	{
		cout << "~String()" << endl;
		free(_str);
	}
private:
	char* _str;
};

class Person
{
private:
	string _name;
	int _age;
};

//int main()
//{
//	//SeqList s;
//
//	Person s;
//
//	system("pause");
//	return 0;
//}

#if 0
fstream fout("destructor.txt", ios::app); // Ҫ��Ȼ���������������е�������

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		fout << "~A()" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}
	~B()
	{
		fout << "~B()" << endl;
	}
};

int main()
{
	A a;
	B b;

	system("pause");
	return 0;
}
#endif

// ������������ʱ��
// ���2��delete ָ������ָ��ʱ��
//   ����delete ָ�����Ļ������͵�ָ�룬�����������������麯��
#if 0
fstream fout("destructor_case3.txt", ios::app);

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}

	virtual ~A()
	{
		fout << "~A()" << endl;
	}

private:
	int _a;
};

class B :public A
{
public:
	B()
	{
		cout << "B()" << endl;
	}

	~B()
	{
		fout << "~B()" << endl;
	}
};

//void Test()
//{
//	A *a = new A(10); // ��̬����һ����A���ʹ�С�Ŀռ䲢��ʼ��Ϊ10
//	delete a;
//}
#endif

// ���3������A����B�ĳ�Ա��B��������������ʱ����ȥ����A����������
#if 0
fstream fout("destructor_case4.txt", ios::app);

class A
{
public:
	A()
	{
		fout << "A()" << endl;
	}
	~A()
	{
		fout << "~A()" << endl;
	}
};

class B : public A
{
public:
	B()
	{
		fout << "B()" << endl;
	}
	~B()
	{
		fout << "~B()" << endl;
	}

private:
	A a;
};

int main()
{
	//A a; // ����һ���������a
	//B b; // ����һ�����������b

	//A* pa1 = &a; // ָ��������Ļ���ָ��pa1
	//A* pa2 = &b; // ָ�����������Ļ���ָ��pa2

	//A* pa = new B(); // ����ָ��paָ��new���������������
	//delete pa;
	//B* pb = new B(); // 

	B b;

	system("pause");
	return 0;
}
#endif

#if 0
// �������캯��
// û����ʽ���忽�����캯����������������Ĭ�Ͽ������캯��
class Date
{
public:
	Date(int year = 2021, int month = 4, int day = 18)
	{
		_year = year;
		_month = month;
		_day = day;
	}

private:
	int _year;
	int _month;
	int _day;
};

void Test1()
{
	Date d1;

	Date d2 = d1; // ���ǳ�ʼ���������Ǹ�ֵ
	Date d3(d2); // ����д�����ϱ�һ��
}

// ���ÿ������캯�����������
class Point
{
public:
	Point(int x = 0, int y = 0)
		:_x(x)
		, _y(y)
	{ }

	~Point(){ };

	Point(const Point &p);

	int getX()const
	{
		return _x;
	}

	int getY()const
	{
		return _y;
	}
private:
	int _x;
	int _y;
};

Point::Point(const Point &p)
{
	_x = p._x;
	_y = p._y;
	cout << "Calling the copy constructor" << endl;
}

// 2. ��������Ϊ�����ʱ
void func1(const Point& p) // �����Ͷ����β�ʵ����ʱҪ���ÿ������캯��������һ��ʵ��
{
	cout << p.getX() << endl;
}

// 3. ��������ֵΪ�����ʱ
Point func2()
{
	Point a(1, 2);
	return a;
}

int main()
{
	//Test1();
	Point p1(7, 2);
	// 1. ��һ�������ʼ��ͬ�����һ������
	Point p2(p1); // ���ÿ������캯��
	cout << "x = " << p2.getX() << "," << "y = " << p2.getY() << endl;

	func1(p2); // p1������Ϊʵ�δ���

	p2 = func2();
	cout << "x = " << p2.getX() << "," << "y = " << p2.getY() << endl;

	system("pause");
	return 0;
}
#endif

//����һ��Point��
class Point{
public:
	Point(int xx = 0, int yy = 0) :x(xx), y(yy){}     //���캯��
	~Point(){ };                              //��������
	Point(const Point &p);                //���ƹ��캯��
	int getX()const{ return x; }
	int getY()const { return y; }
private:
	int x, y;//˽�г�Ա

};

Point::Point(const Point &p)
{
	x = p.x;
	y = p.y;
	cout << "Calling the copy constructor" << endl;

}
//�β���ΪPoint�����ĺ���
void fun1(Point p)
{
	cout << p.getX() << endl;

}

//������Ķ���
Point fun2()
{
	Point a(1, 2);
	return a;
}

int main()
{
	Point a(4);    //��һ������A,�ù������������أ������yĬ��Ϊ0

	Point b(a);      //��ʱ����copy���캯�������1����a��ʼ��b����һ�ε���copy���캯��
	cout << b.getX() << endl;

	fun1(b);  //��ʱ����copy���캯������Ķ����ں�����Ϊʵ�Σ��ڶ��ε���copy���캯��

	b = fun2();//��ʱ����copy���캯������������ֵΪ��Ķ��󣬵����ε���copy���캯��
	cout << b.getX() << endl;

	system("pause");
	return 0;
}