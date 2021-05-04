#include<iostream>
#include<Windows.h>
using namespace std;

#include<vector>

#if 0
class Date
{
public:
	Date(int year=2000, int month=4, int day=21)
	{ }
private:
	int _year;
	int _month;
	int _day;
};
// vector�Ĺ��켰����
/*
explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
value_type()
1. ��value_typeΪ��������ʱ��Ĭ��Ϊ0
2. 1�� ��value_typeΪ�Զ�������ʱ����ʼֵĬ��Ϊ0
	    ���磺value_typeΪint  const int& value = int()
	          int() Ϊ0
   2�� �� ������Զ����������޲ι����ȫȱʡ���죬
          ���磺value_typeΪDate  const Date& value = Date()
                Date()�൱�ڵ��ø�����޲ι��캯������һ������������Ϊ��ʼֵ
	   �� ������Զ�������û���޲ι����ȫȱʡ���죬����������
*/
void Test1()
{
	vector<int> v1;
	vector<int> v2(5, 7);
	vector<int> v3(10); // ��������Ϊ�������ͣ�Ĭ��ֵΪ0
	vector<Date> v4(3); // ��������Ϊ�Զ������ͣ�����Զ������������޲ι��캯����ȫȱʡ���캯��������һ������������Ϊ��ʼֵ�����û���޲ι����ȫȱʡ���죬����ʧ��

	int array[] = { 1, 2, 3, 4, 5 };
	vector<int> v5(array,array+sizeof(array)/sizeof(array[0])); // ���乹��

	vector<int> v6(v2); // ��������

	vector<int> v7{ 1, 2, 3, 4, 5 }; // C++11�����ӵĹ��췽ʽ

	for (int i = 0; i < v2.size(); ++i)
		cout << v2[i] << " ";
	cout << endl;

	// C++11
	for (auto e : v3)
		cout << e << " ";
	cout << endl;

	vector<int>::iterator it = v7.begin();
	while (it != v7.end())
	{
		cout << *it << " ";
		++it;
	}	
	cout << endl;
}
#endif

/*
void resize(size_t n, const T& data = T());
����ЧԪ�ظ����޸ĵ�n�������n>oldsize���������n-size��Ԫ����data���
data��������β���T()��Ĭ��ֵ���

resizeʱ���n > capacity Ҫ��������
*/
void Test2()
{
	vector<int> v{ 1, 2, 3, 4, 5 };
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	// newsize > oldsize
	v.resize(10); 
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(20);
	cout << v.size() << endl;
	cout << v.capacity() << endl;;

	// newsize < oldsize
	v.resize(15);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(7);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	cout << "-------------------" << endl;

	/*
	reserve
	1. newcapacity <= oldcapacity : capacity = oldcapacity ���ı�
	2. newcapacity > oldcapacity : capacity = newcapacity ��������
	*/
	v.reserve(10);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(30);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

// Ԫ�ط��ʲ���
/*
reference front();
const_reference front() const;
����vector��һ��Ԫ�ص�����

reference back();
const_reference back() const;
����vector���һ��Ԫ�ص�����

reference at (size_type n);
const_reference at (size_type n) const;
�����±�Ϊn��Ԫ�ص�����

operator[]��Խ��assert
at()��Խ�����쳣out_of_range
*/
void Test3()
{
	vector<int> v{ 1, 2, 3, 4, 5 };
	cout << v[0] << endl;
	cout << v.front() << endl;
	cout << v.back() << endl;

	v[2] = 777;
	v.front() = 100;
	v.back() = 200;
	v.at(3) = 666;
	
	for (auto e : v)
		cout << e << " ";
	cout << endl;
}

// push_back()
// ��֤���ݻ���
void Test4()
{
	vector<int> v;
	size_t capacity = v.capacity();
	v.reserve(100);
	for (int i = 0; i < 100; ++i)
	{
		v.push_back(i);
		if (capacity != v.capacity())
		{
			cout << v.capacity() << endl;
			capacity = v.capacity();
		}	
	}
}

// push_back
class Date
{
public:
	Date(int year = 2000, int month = 4, int day = 21)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int, int, int)" << endl;
	}

	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date&)" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
void Test5()
{
	Date d(2021, 5, 1);
	vector<Date> v;

	// push_back�Ĳ���d����������d��һ������
	v.push_back(d); // ������һ�ο������캯��
}

// insert
/*
iterator insert (iterator position, const value_type& val);
void insert (iterator position, size_type n, const value_type& val);
��������������ҿ�������
template <class InputIterator>
void insert (iterator position, InputIterator first, InputIterator last);

iterator erase (iterator position);
ɾ������������ҿ�������
iterator erase (iterator first, iterator last);
*/
void Test6()
{
	vector<int> v{ 1, 2, 3 };
	v.insert(v.begin(), 0); // 0 1 2 3

	// ��ֵΪ3�ĵ�����λ�ò���4��6
	v.insert(find(v.begin(), v.end(), 3), 4, 6); // 0 1 2 6 6 6 6 3

	vector<int> v2{ 7, 6, 5, 4, 3 };
	// ��v�����һ����ЧԪ�غ��λ�ò���� v2.begin() ��ʼ�� v2.end()-2ǰһ��λ�� �����Ԫ��
	v.insert(v.end(), v2.begin(), v2.end() - 2); // 0 1 2 6 6 6 6 3 7 6 5 

	v.erase(v.begin()); // 1 2 6 6 6 6 3 7 6 5 
	// ɾ���� v.begin() + 1 ��ʼ�� v.end() - 4ǰһ��λ�� �����Ԫ��
	v.erase(v.begin() + 1, v.end() - 4); // 1 3 7 6 5
}

// swap
/*
vector���ṩ��swapʵ�����ǽ���start��finish��end_if_storage����ָ���ָ��
*/
void Test7()
{
	vector<int> v1{ 1, 2, 3 };
	vector<int> v2{ 1, 2, 3, 4, 5 };
	v1.swap(v2);
}

// ��֤������ʧЧ
// 1. ���ݸı�ײ�ռ�
void Test8()
{
	vector<int> v{ 1, 2, 3 };

	vector<int>::iterator it = v.begin();
	v.assign(10,2); // ��������ײ�ռ�ı䵼�µ�����ʧЧ
	it = v.begin(); // һ��Ҫ���¸���������ֵ �����������

	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
// 2. erase(pos)��ɾ��֮��posλ�õĵ�����ʧЧ
void Test9()
{
	vector<int> v{ 1, 2, 3 };
	vector<int>::iterator it = v.begin();
	v.erase(v.begin());
	it = v.begin();
	cout << *it << endl;
}
// 3. swap()/clear()���µ�����ʧЧ
void Test10()
{
	vector<int> v1{ 1, 2, 3 };
	vector<int> v2{ 4, 5, 6, 7, 8 };

	vector<int>::iterator it1 = v1.begin();
	vector<int>::iterator it2 = v2.begin();

	v1.swap(v2);

	// ���µ�����
	it1 = v1.begin();
	it2 = v2.begin();

	while (it1 != v1.end())
	{
		cout << *it1 << endl;
		++it1;
	}
	while (it2 != v2.end())
	{
		cout << *it2 << endl;
		++it2;
	}

	v1.clear();
	it1 = v1.begin();
	cout << *it1 << endl;
}

// ʹ�õ�����ɾ��vector������Ԫ��
void iteratorErase()
{
	vector<int> v{ 1, 2, 3, 4, 5 };
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		// erase�ķ���ֵΪָ��ɾԪ�ص���һ��λ�õĵ�����
		it = v.erase(it);
		//it = v.begin();
	}

	if (v.empty())
		cout << "�����" << endl;
	else
		cout << "ERR" << endl;
}
#if 0
int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	iteratorErase();

	system("pause");
	return 0;
}
#endif

// ��ά����Ĵ���
// 1.����ʽ
// ����һ��5��4�е�vector
// ���resize()��reserve()!!!
void Testvv1()
{
	vector<vector<int>> vv1;
	// ��resize���������Ķ�άvectorÿһ��Ԫ�ض�����ʼ��Ϊ0
	vv1.resize(5); 
	for (int i = 0; i < vv1.size(); ++i)
	{
		vv1[i].resize(4);
	}

	// ��ӡ��άvector
	for (int i = 0; i < vv1.size(); i++)
	{
		for (int j = 0; j < vv1[i].size(); ++j)
		{
			cout << vv1[i][j] << " ";
		}
	}
	cout << endl;

}

void Testvv2()
{
	vector<vector<int>> vv2;
	/*
	��reserve���������Ķ�άvector��ֻ�пռ䣬�ռ���û��Ԫ��
	vv.start �� vv.finish ָ��ռ���ʼλ�� vv.end_of_storageָ��ռ�ĩβ
	*/
	vv2.reserve(5); // ��������5�пռ�
	for (int i = 0; i < 5; i++)
	{
		vv2.push_back(vector<int>(4,0));
	}
	
	for (int i = 0; i < vv2.size(); i++)
	{
		for (int j = 0; j < vv2[i].size(); ++j)
		{
			cout << vv2[i][j] << " ";
		}
	}
	cout << endl;
}

void Testvv3()
{
	vector<vector<int>> vv(5, vector<int>{1, 2, 3, 4, 5});
	vector<vector<int>> vv2(5, vector<int>(4,1));
}

// ÿ������ЧԪ�ز�ͬ
// ����5���������
/*
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
*/
void YangHui()
{
	vector<vector<int>> vv;
	vv.resize(5);
	for (size_t i = 0; i < vv.size(); i++)
	{
		vv[i].resize(i + 1, 1);
	}
	for (size_t i = 2; i < vv.size(); i++)
	{
		for (size_t j = 1; j < vv[i].size() - 1; j++)
		{
			vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
		}
	}

	for (int i = 0; i < vv.size(); i++)
	{
		for (int j = 0; j < vv[i].size(); j++)
		{
			cout << vv[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}
int main()
{
	//Testvv1();
	//Testvv2();
	
	YangHui();

	system("pause");
	return 0;
}