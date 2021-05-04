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
// vector的构造及遍历
/*
explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
value_type()
1. 当value_type为内置类型时，默认为0
2. 1） 当value_type为自定义类型时，初始值默认为0
	    例如：value_type为int  const int& value = int()
	          int() 为0
   2） ① 如果该自定义类型有无参构造或全缺省构造，
          例如：value_type为Date  const Date& value = Date()
                Date()相当于调用该类的无参构造函数创建一个匿名对象作为初始值
	   ② 如果该自定义类型没有无参构造或全缺省构造，编译器报错
*/
void Test1()
{
	vector<int> v1;
	vector<int> v2(5, 7);
	vector<int> v3(10); // 数据类型为内置类型，默认值为0
	vector<Date> v4(3); // 数据类型为自定义类型，如果自定义类型中有无参构造函数或全缺省构造函数，构造一个匿名对象作为初始值，如果没有无参构造或全缺省构造，编译失败

	int array[] = { 1, 2, 3, 4, 5 };
	vector<int> v5(array,array+sizeof(array)/sizeof(array[0])); // 区间构造

	vector<int> v6(v2); // 拷贝构造

	vector<int> v7{ 1, 2, 3, 4, 5 }; // C++11新增加的构造方式

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
将有效元素个数修改到n个，如果n>oldsize，多出来的n-size个元素用data填充
data如果不传参采用T()的默认值填充

resize时如果n > capacity 要进行扩容
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
	1. newcapacity <= oldcapacity : capacity = oldcapacity 不改变
	2. newcapacity > oldcapacity : capacity = newcapacity 真正扩容
	*/
	v.reserve(10);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(30);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

// 元素访问操作
/*
reference front();
const_reference front() const;
返回vector第一个元素的引用

reference back();
const_reference back() const;
返回vector最后一个元素的引用

reference at (size_type n);
const_reference at (size_type n) const;
返回下标为n的元素的引用

operator[]：越界assert
at()：越界抛异常out_of_range
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
// 验证扩容机制
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

	// push_back的不是d对象本身，而是d的一个副本
	v.push_back(d); // 调用了一次拷贝构造函数
}

// insert
/*
iterator insert (iterator position, const value_type& val);
void insert (iterator position, size_type n, const value_type& val);
插入区间是左闭右开！！！
template <class InputIterator>
void insert (iterator position, InputIterator first, InputIterator last);

iterator erase (iterator position);
删除区间是左闭右开！！！
iterator erase (iterator first, iterator last);
*/
void Test6()
{
	vector<int> v{ 1, 2, 3 };
	v.insert(v.begin(), 0); // 0 1 2 3

	// 在值为3的迭代器位置插入4个6
	v.insert(find(v.begin(), v.end(), 3), 4, 6); // 0 1 2 6 6 6 6 3

	vector<int> v2{ 7, 6, 5, 4, 3 };
	// 在v的最后一个有效元素后的位置插入从 v2.begin() 开始到 v2.end()-2前一个位置 区间的元素
	v.insert(v.end(), v2.begin(), v2.end() - 2); // 0 1 2 6 6 6 6 3 7 6 5 

	v.erase(v.begin()); // 1 2 6 6 6 6 3 7 6 5 
	// 删除从 v.begin() + 1 开始到 v.end() - 4前一个位置 区间的元素
	v.erase(v.begin() + 1, v.end() - 4); // 1 3 7 6 5
}

// swap
/*
vector中提供的swap实际上是交换start、finish、end_if_storage三个指针的指向
*/
void Test7()
{
	vector<int> v1{ 1, 2, 3 };
	vector<int> v2{ 1, 2, 3, 4, 5 };
	v1.swap(v2);
}

// 验证迭代器失效
// 1. 扩容改变底层空间
void Test8()
{
	vector<int> v{ 1, 2, 3 };

	vector<int>::iterator it = v.begin();
	v.assign(10,2); // 由于这里底层空间改变导致迭代器失效
	it = v.begin(); // 一定要重新给迭代器赋值 否则程序会崩溃

	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
// 2. erase(pos)：删除之后pos位置的迭代器失效
void Test9()
{
	vector<int> v{ 1, 2, 3 };
	vector<int>::iterator it = v.begin();
	v.erase(v.begin());
	it = v.begin();
	cout << *it << endl;
}
// 3. swap()/clear()导致迭代器失效
void Test10()
{
	vector<int> v1{ 1, 2, 3 };
	vector<int> v2{ 4, 5, 6, 7, 8 };

	vector<int>::iterator it1 = v1.begin();
	vector<int>::iterator it2 = v2.begin();

	v1.swap(v2);

	// 更新迭代器
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

// 使用迭代器删除vector中所有元素
void iteratorErase()
{
	vector<int> v{ 1, 2, 3, 4, 5 };
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		// erase的返回值为指向被删元素的下一个位置的迭代器
		it = v.erase(it);
		//it = v.begin();
	}

	if (v.empty())
		cout << "已清空" << endl;
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

// 二维数组的创建
// 1.矩阵方式
// 创建一个5行4列的vector
// 理解resize()和reserve()!!!
void Testvv1()
{
	vector<vector<int>> vv1;
	// 用resize创建出来的二维vector每一个元素都被初始化为0
	vv1.resize(5); 
	for (int i = 0; i < vv1.size(); ++i)
	{
		vv1[i].resize(4);
	}

	// 打印二维vector
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
	用reserve创建出来的二维vector，只有空间，空间中没有元素
	vv.start 和 vv.finish 指向空间起始位置 vv.end_of_storage指向空间末尾
	*/
	vv2.reserve(5); // 堆上申请5行空间
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

// 每行中有效元素不同
// 创建5行杨辉三角
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