#include<iostream>
#include<Windows.h>
using namespace std;

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

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	~Date(){ }

	/*
	ע��+���غ�+=������
	+���أ����ı�ԭ����
	+=���أ��ı�ԭ����
	*/
	Date operator+(/*Date* const this,*/int days) // ��Ϊtemp����ʱ���󣬺�����������ʱ�����ͻ����٣���ֵ���ػ��temp��������һ����ʱ����
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}

	Date& operator+=(int days)
	{
		_day += days;
		return *this;
	}

	/* 
	��ֵ�����������ȷ���ƣ�
	1. �������ô����÷�ʽ�����Ч��
	2. ����ֵ��������
	3. ������Լ����Լ���ֵ�������в���ֱ�ӷ���thisָ��
	4. ����ʱ����Ϊ���÷��أ�����ֵ�������ڱ�����ں��������Է���thisָ��
	*/
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		
		return *this;
	}

	// ������ֵ
	/*Date& operator=(const Date d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	 }*/

	// ��ֵ����
	/*Date operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	 }*/

	// ǰ��++
	Date& operator++()
	{
		_day++;
		return *this;
	}

	// ����++
	/* 
	��ʹ�ã���++
	���ԣ����ص���++ǰ�ľ�ֵ��ֻ������ʱ���������ֵ���ٽ��ö����е�ֵ++
	���ص�����ʱ����������������ʱ����Ҫ���٣����Բ��ô�ֵ���أ�������ֵ����һ����ʱ����
	���ص�����ʱ����

	�����е�int��Ϊ�˹��ɺ������أ��ɱ�����������
	*/
	Date operator++(int)
	{
		Date temp(*this);
		_day++;
		return temp;
	}

	// ǰ��--
	// ��--����ʹ��
	Date& operator--()
	{
		_day--;
		return *this;
	}

	// ����--
	Date operator--(int)
	{
		Date temp(*this);
		_day--;
		return temp;
	}

	// &����
	Date* operator&()
	{
		cout << this << endl;
		return this;
	}

	// 
	const Date* operator&()const
	{
		return this;
	}
private:
	int _year;
	int _month;
	int _day;
};

// ���������ʵ����������أ�û��thisָ��
// ���ⲻ�ܷ������˽�г�Ա
//Date operator-(const Date& d, int days)
//{
//	Date temp(d);
//	temp._day += days;
//	return temp;
//}
//Date& operator-=(Date& d, int days)
//{
//	d._day -= days;
//	return d;
//}

int main()
{
	Date d1(2021, 4, 21);
	Date d2(2021, 3, 17);

	/*d1.operator+(7);
	d2.operator+=(7);*/

	Date d3(2021, 4, 23);
	//d1 = d3;
	
	/*
	������ֵ������d3��d2��ֵ������d2��d1��ֵ
	Ҳ����˵������ֵӦ�÷��ص��ø�ֵ������Ķ���
	*/
	//d1 = d2 = d3;
	
	//d2 = d1++; // d2����21 d1����22
	//d2 = ++d1; // d2����23 d1����23

	&d2;

	const Date d4(2021, 4, 21);
	&d4;

	system("pause");
	return 0;
}

// d1=d2=d3 ---�� return *this
// const Date& d��Date& const d
#endif

#if 0
// const���͵ĳ�Ա���� const���ε���ʵ��thisָ��
// thisָ�����ͣ�������* const this
// ��const���εĳ�Ա�����У�const ������* const this
// ����thisָ���ָ���ָ��Ŀռ��е����ݶ������޸�
// const���εĳ�Ա�������ǲ����޸ĳ�Ա������ֵ��
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	~Date(){ }

	// ���øú����Ķ���thisָ��Ķ���ʹ��εĶ��󶼲��ı� ��const
	bool operator==(const Date& d)const
	{
		return _year == d._year &&
			_month == d._month &&
			_day == d._day;
	}

	void Print()const
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	const Date* operator&()const
	{
		return this;
	}

	
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2021, 4, 21);
	Date d2(2021, 4, 21);
	Date d3(2021, 4, 22);

	if (d1 == d2)
	{
		cout << "��ͬ" << endl;
	}
	else
	{
		cout << "��ͬ" << endl;
	}

	if (d1 == d3)
	{
		cout << "��ͬ" << endl;
	}
	else
	{
		cout << "��ͬ" << endl;
	}

	system("pause");
	return 0;
}
#endif

#if 0
// const��Ա
// 1. const�����ܵ��÷�const��Ա����
// 2. ��const������Ե���const��Ա����
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	~Date(){ }

	// ���øú����Ķ���thisָ��Ķ���ʹ��εĶ��󶼲��ı� ��const
	bool operator==(const Date& d)const
	{
		return _year == d._year &&
			_month == d._month &&
			_day == d._day;
	}

	void Print()const
	{

		cout << _year << "-" << _month << "-" << _day << endl;
	}

	const Date* operator&()const
	{
		return this;
	}

	Date* operator&()
	{
		cout << this << endl;
		return this;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	const Date d1(2021, 4, 21);
	Date d2(2021, 4, 22);

	&d1; // ����const Date* operator&()const
	&d2; // ����Date* operator&()
	
	d2.Print(); // ��const������Ե���const��Ա����

	system("pause");
	return 0;
}
#endif

class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
		:_year(year)
		, _month(month)
		, _day(day)
	{ 
		cout << "Date(int, int, int)" << this << endl;
	}

	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date& d)" << this << endl;
	}

	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_day = d._day;
			_month = d._month;
			_day = d._month;
		}

		cout << "operator" << this << endl;
		return *this;
	}

	~Date()
	{ 
		cout << "~Date()" << this << endl;
	}

	
private:
	int _year;
	int _month;
	int _day;
};

Date TestDate1(Date d)
{
	Date temp(d);
	temp = d;
	return temp;
}


Date& TestDate2(Date& d)
{
	Date temp(d);
	temp = d;
	return d;
}

Date TestDate3(Date d)
{
	return d;
}

void TestDate()
{
	Date d1(2021, 4, 21); // ���ù���
	Date d2(d1); // ��������

	// ���Ե���TestDate1�͵���TestDate2�Ĵ�ӡ���

	//d2 = TestDate1(d1);
	
	/*
	���þ�����
	�������� -�� d
	�������� -�� temp
	��ֵ��������� -�� temp = d
	�������� -�� ֵ���أ�����ֵ����һ����ʱ����ret��ֻ�ڸ�ֵ����Ч
	�������� -�� temp
	�������� -�� d
	��ֵ��������� -�� d2 = TestDate1(d1)
	�������� -�� ret
	*/

	//d2 = TestDate2(d1);

	/*
	���þ�����
	�������� -�� temp 
	��ֵ��������� -�� temp = d
	�������� -�� temp
	��ֵ��������� -�� d2 = TestDate2(d1)
	*/

	/*
	TestDate��������
	�������� -�� d2
	�������� -�� d1
	*/

	TestDate3(TestDate3(d1));

	/*
	�������� -�� d1����ʱ����
	�������� -�� ret1����ʱ����
	���� -�� d1����ʱ����

	�������� -�� ret1����ʱ��������ʱ����
	���������� -�� ret2����ʱ������û���������������Ż�
	���� -�� ret1����ʱ����
	���� -�� ret2����ʱ����
	*/
}

void Test()
{
	TestDate1(Date d(2021, 4, 21));
}
int main()
{
	//TestDate();

	Test();

	system("pause");
	return 0;
}