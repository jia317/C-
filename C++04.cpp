#include<iostream>
using namespace std;

// ���캯�����ڵĺ�����ʵ�����Ǹ�ֵ�����ǳ�ʼ��
/*
��ʼ���͸�ֵ������
��ʼ���ڶ�����������ֻ����һ��
��ֵ���Զ��
*/

/*
�����ڳ�ʼ���б���г�ʼ���ĳ�Ա
1. ���ó�Ա����
2. const��Ա����
3. �Զ������ͳ�Ա(����û��Ĭ�Ϲ��캯��)
*/
#if 0
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 22, int ref = 7, int x = 8 )
		// �ó�ʼ���б�Žг�ʼ��
		:_year(year)
		, _month(month)
		, _day(day)
		, ra(ref)
		, a(x)
	{
		// �±ߵ���䶼�Ǹ�ֵ ���ǳ�ʼ��
		_year = year;
		_month = month;
		_day = day;
		//_day = day; // û�б���˵���Ǹ�ֵ
	}

	Date(const Date& d)
		// ������ǳ�ʼ��
		:_year(d._year)
		, _month(d._month)
		,_day(d._day)
		, ra(d.ra)
		, a(d.a)
	{
		// ���Ǹ�ֵ
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

private:
	int _year;
	int _month;
	int _day;

	int& ra; // ���ó�Ա���������ڳ�ʼ���б���г�ʼ��

	const int a; // const��Ա���������ڳ�ʼ���б���г�ʼ��
};
#endif

// ���е��Զ����Ա����(����û��Ĭ�Ϲ��캯��)�����ڳ�ʼ���б���г�ʼ��
// ȫȱʡ���캯�����޲ι��캯����δ��ʽ����������Զ����ɵĹ��캯������Ĭ�Ϲ��캯��
#if 0
class Time
{
public:
	// Time����û��Ĭ�Ϲ��캯��(��Ϊ������ʽ�����˴������������Ĺ��캯��)
	// Date���е�t��ʼ��ʱҪ��Date��ĳ�ʼ���б���г�ʼ��
	Time(int hour, int min, int sec)
		:_hour(hour)
		, _min(min)
		, _sec(sec)
	{ }

private:
	int _hour;
	int _min;
	int _sec;
};

class Date
{
public:
	// ���캯�����г�ʼ���б�
	// �û�û��д���������Ჹ�ϣ��Ծɻ�ִ�г�ʼ���б���
	Date()
		// �ó�ʼ���б�Žг�ʼ��
		:_year(2000)
		, _month(4)
		, _day(21)
		, t(11, 0, 0)
	{ }

	Date(int year, int month, int day)
		: _year(year)
		, _month(month)
		, _day(day)
		, t(11, 0, 0)
	{ }

	Date(const Date& d)
		// ������ǳ�ʼ��
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
		, t(d.t)
	{ }

private:
	int _year;
	int _month;
	int _day;

	Time t;
};

int main()
{
	Date d1;
	Date d2(2021, 4, 22);

	system("pause");
	return 0;
}
#endif

// ��ʼ����Ա�����Ĵ���������������г�ʼ�������ʼ���б�˳���޹�
#if 0
class Time
{
public:
	// Time����û��Ĭ�Ϲ��캯��(��Ϊ������ʽ�����˴������������Ĺ��캯��)
	// Date���е�t��ʼ��ʱҪ��Date��ĳ�ʼ���б���г�ʼ��
	Time(int hour, int min, int sec)
		:_min(min)
		,_hour(hour) 
		, _sec(sec)
	{ }

private:
	int _hour;
	int _min;
	int _sec;
};

int main()
{
	/*
	����ǰ��ճ�ʼ���б�˳����г�ʼ������ô
	min = 11   hour = 47   sec = 33
	���ǣ�ͨ�����Ӵ��ڿ����ģ��Ծ���
	hour = 11    min = 47    sec = 33

	���ۣ���ʼ����Ա������˳���ǳ�Ա��������������
	*/
	Time t(11, 47, 33);

	system("pause");
	return 0;
}
#endif

// ���ڵ��������Ĺ��캯��������������ת��������
// explicit�ؼ��ֵ����ã���ֹ���ι��캯������ʽת��
#if 0
class Date
{
public:
	// ���εĹ��캯��
	/*Date(int year)
		:_year(year)
		, _month(4)
		, _day(21)
	{
		cout << "Date(int)" << this << endl;
	}*/

	// ����explicit�ؼ��֣����ι��캯���Ͳ����������ת����
	explicit Date(int year)
		:_year(year)
		, _month(4)
		, _day(21)
	{
		cout << "Date(int)" << this << endl;
	}

	Date& operator=(const Date& d)
	{
		cout << this << "=" << &d << endl;

		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}

	~Date()
	{
		cout << "~Date() : " << this << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

// ��֤���ι��캯��������ת��
void Test()
{
	Date d1(2021);

	/*
	�Ƚ�2022��Ϊʵ�δ��ݸ����ι��캯��������һ����ʱ����
	���������ʱ�����d1��ֵ
	*/
	d1 = 2022;
}
int main()
{
	Test();

	system("pause");
	return 0;
}
#endif

// static��Ա
/*
C�����е�static
1. static���κ���������ֻ�����������ļ���ʹ��
2. static���α���
   2.1 static���ξֲ��������ӳ��������ڣ����ȫ�ֱ�������������׷�����
                           ���¼��һ�ε�ֵ������һ���޸ĵĻ������޸�
   2.2 static����ȫ�ֱ������ñ���ֻ���ڵ�ǰ�ļ���ʹ��
*/

#if 0
// ��֤static���ξֲ������ļ��书��
void TestStatic2()
{
	/*
	�����static���ξֲ���������ô��������TestStatic2()����ӡ���Ϊ1 2 3 
	��Ϊstatic���ξֲ������������������ھ�׷�����ֻ�г������������
	�������ᱣ����һ���޸ĵ�ֵ���������м��书��һ��

	����Ǿֲ���������������TestStatic2()����ӡ���Ϊ1 1 1
	��Ϊ�ֲ������ں���ִ����ͻᱻ���٣�ÿ�ε��ö���һ���µľֲ�����
	*/
	static int a = 0;
	int a = 0; 
	a++;
	cout << a << endl;
}
int main()
{
	TestStatic2();
	TestStatic2();
	TestStatic2();

	system("pause");
	return 0;
}
#endif

// C++�е�static
// ���캯�����������캯������ֵ��������ء��������������ܱ�static���Σ������ûthisָ��
/*
1. static���γ�Ա����
   
2. static���γ�Ա����
*/

// һ�ֳ�����ͳ�ƴ����Ķ������
/*
˼·�����������������һ��ȫ�ֱ���
ȱ�ݣ�ȫ�ֱ���������λ�ÿ����޸�

����static�ؼ���
��static���εĳ�Ա�������������������������ԣ��������κ�һ��ʵ��
������static int _count��Ϊͳ�ƶ����������ȫ
*/

//int _count = 0;
#if 0
class Date
{
public:
	Date(int year,int month,int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int,int,int)" << endl;
		_count++;
	}

	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date& d)" << endl;
		_count++;
	}

	~Date()
	{
		cout << "~Date() : " << this << endl;
		_count--;
	}

	// ��̬��Ա����
	// ��̬��Ա�������ܱ�const���Σ���Ϊconst���γ�Ա����ʵ����������thisָ�룬���ھ�̬��Ա������û��thisָ��
	static int GetCount()
	{
		// ��̬��Ա����û��thisָ��
		//cout << this << endl; // ���뱨�� 

		/* 
		��̬��Ա�������ܵ��÷Ǿ�̬��Ա����

		Print����ĳ�Ա��������ӡʱ��ͨ��thisָ�������ʳ�Ա����
		��GetCount�Ǿ�̬��Ա������û��thisָ�룬������Print�����в��ܷ��ʳ�Ա����
		*/
		//Print(); // ���뱨��

		// ��̬��Ա�����в��ܷ��ʷǾ�̬��Ա����
		//cout << _day << endl;

		return _count;
	}

	void Print()
	{
		// �Ǿ�̬��Ա�������Ե��þ�̬��Ա����
		GetCount();
		cout << _year << _month << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;

	static int _count;
};
// ��̬��Ա����������������г�ʼ��
int Date::_count = 0;
 
void TestDate()
{
	Date d1(2021, 2, 22);
	Date d2(2022, 2, 24);
}

// ��̬��ԱΪ���������������������ĳ������ʵ��
void Test1()
{
	Date d1(2021, 2, 22);

	cout << sizeof(d1) << endl; // 12 ����int���͵ĳ�Ա�����Ĵ�С
}

// �ྲ̬��Ա�ķ��ʷ�ʽ
void Test2()
{
	Date d1(2021, 2, 22);
	/*
	1. ��̬��Ա�����ĵ��÷�ʽ��
	����.��̬��Ա����
	����::��̬��Ա����
	*/
	d1.GetCount();
	Date::GetCount();
	
	// �þ�̬��Ա_countΪprivate�������ⲻ�ܷ���
	//cout << d1._count <<endl;
	//cout << Date::_count <<endl;

}
int main()
{
	//TestDate();

	Test1();

	system("pause");
	return 0;
}
#endif

// <<������
#if 0
class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	Date(int year, int month, int day)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int,int,int)" << endl;
	}

	// ���������н���<<����
	/*
	<<������Ҫ��������������ķǾ�̬��Ա�����е�һ�����������ص�thisָ�룬����ֻҪ��һ��ostream(cout����)�Ĳ�������
	*/
	// ���ǣ�����д������Ƿ���
	// Ϊ����_cout��ɵ�һ��������ֻ�ܽ�������������
	// ���ۣ�<<ֻ�����������أ�����
	/*void operator<<(ostream& _cout)
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}*/
private:
	int _year;
	int _month;
	int _day;
};
#endif

// ������������������<<
#if 0
int main() 
{
	Date d1(2021, 4, 22);

	// ˵����Ҫ����������
	// ����������֮������Ĵ����Բ���ִ��
	//cout << d1;

	// ��������д����
	//d1 << cout;
	// ˵���������������ص�<<�ﵽ��Ч�����෴��
	/*
	�����෴�������ԭ��
	��Ϊd1�����������cout���Ҳ��������൱���±�d1.operator<<(cout)��д��
	*/

	// ���еĳ�Ա��������ͨ������������
	//d1.operator<<(cout);

	system("pause");
	return 0;
}
#endif

// <<���صķ���ֵ������ostream
// ���ô��Ρ����÷��ض���Ϊ����ߺ�������Ч��
#if 0
ostream& operator<<(ostream& _cout, const Date& d)
{
	/* ��Ϊ����������������˽�г�Ա�����������
	1. ������дһЩpublic������ȡ˽�г�Ա����������ó�Ա����������
	2. �����ⶨ��ĺ�������Ϊ��Ԫ�����Ϳ����ڸú����з������˽�г�Ա��
	// 
	*/
	_cout << d._year << "-" << d._month << "-" << d._day ;
	return _cout;
}

// ������������������<<
int main()
{
	Date d1(2021, 4, 22);

	cout << d1;
	operator<<(cout, d1);

	// ̽��<<���غ����ķ���ֵ
	/*
	����<<
	�Ƚ�"d1�������ǣ�"�����cout���ٽ�d1�����cout���ٽ�endl�����cout
	����<<����һ�����з���ֵ��
	��Ϊ��Ҫ�����cout�����Է���ֵ����Ҳ��ostream
	*/
	cout << "d1�������ǣ�" << d1 << endl;

	cout << d1 << 10;
	operator << (cout, d1) << 10;

	system("pause");
	return 0;
}
#endif

// ��Ԫ��Ϊ�˽�����ⲻ�ܷ������˽�г�Ա
/*
1. ��Ԫ����������ֱ�ӷ������˽�г�Ա�����������⣬�������κ��࣬����Ҫ����������������ʱ��friend
1����Ԫ��������ֱ�ӷ�����ı�����Ա��˽�г�Ա����������ĳ�Ա����
2����Ԫ�������ܱ�const����
3����Ԫ��������������κ�λ������������������޶�������
4��һ�����������Ƕ�������Ԫ����
5����Ԫ�����ĵ�������ͨ����ԭ����ͬ
*/

// ��Ԫ��
/*
1. ��Ԫ��Ĺ�ϵ�ǵ���� 
���ͣ�������B����A����Ԫ�࣬��ô��B���Է�����A�е�˽�г�Ա��������A���ܷ�����B��˽�г�Ա
2. ��Ԫ��ϵ���ܴ���
���ͣ�B��A����Ԫ�࣬C��B����Ԫ�࣬������C�в��ܷ�����A��˽�г�Ա
*/
#if 0
class Time
{
	friend class Date;
public:
	Time(int hour = 0, int min = 0, int sec = 0)
		:_hour(hour)
		, _min(min)
		, _sec(sec)
	{ }

private:
	int _hour;
	int _min;
	int _sec;
};

class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int,int,int)" << endl;
	}

	void Print()
	{
		cout << _year << "-" << _month << "-" << _day;
		cout << _t._hour << "-" << _t._min << "-" << _t._sec;
	}
private:
	int _year;
	int _month;
	int _day;

	Time _t;
};
#endif

// �ڲ���
/*
1. �ڲ�����һ���������࣬���������ⲿ�࣬�������ⲿ�����ȥ�����ڲ���
2. �ڲ������ⲿ�����Ԫ�࣬�ڲ������ͨ���ⲿ������������ⲿ���е����г�Ա
3. �ڲ�����Զ������ⲿ���public��protected��public
4. �ڲ������ֱ�ӷ����ⲿ���static��ö�ٳ�Ա������Ҫ�ⲿ��Ķ���/����
5. sizeof(�ⲿ��)���ڲ����޹�
*/
class DList
{
	struct DListNode // �ڲ���
	{
	public:
		DListNode(int x)
			:prev(nullptr)
			, next(nullptr)
			, data(x)
		{ }

		// �ڲ���������ⲿ���������ⲿ������г�Ա
		void fun()
		{
			DList L;
			L._head; // �����ⲿ���˽�г�Ա����
			a = 10; // �����ⲿ���static��Ա����������Ҫ���ⲿ������޶��������ⲿ��������
			L.Fun(); // �����ⲿ��ĳ�Ա����
		}
	private:
		DListNode* prev;
		DListNode* next;
		int data;
	};

public:
	DList()
		:_head(nullptr)
	{ }

	void Fun()
	{

	}
private:
	DListNode* _head;
	static int a;
};

int DList:: a = 7; // ����static��Ա���������������ʼ��

void Test()
{
	DList L;
	//L.data; // �������ⲿ���������ڲ���

	cout << sizeof(DList) << endl; // 4 ֻ��һ��ָ��DListNode���Ͷ����ָ��_head

}

int main()
{
	Test();

	system("pause");
	return 0;
}