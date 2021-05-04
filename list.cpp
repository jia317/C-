#include<iostream>
#include<Windows.h>
#include<vector>
using namespace std;

#include<list>
// list底层结构：带头双向循环链表

// list接口的使用

// 1. 构造和析构
/*
list(); // 无参构造
list(size_t n,const value_type& val=value()); // n个值为val的构造
template<class InputIterator> 
list(InputIterator first, InputIterator last); // 区间构造
list(const list& l); // 拷贝构造
*/

// 2.迭代器
/*
iterator begin();
const iterator begin()const;
iterator end();
const iterator end()const;

reverse_iterator rbegin();
const_reverse_iterator rbegin() const;
reverse_iterator rend();
const_reverse_iterator rend() const;
*/
void Test1()
{
	list<int> l1;
	list<int> l2(5, 7);

	vector<int> v{ 1, 2, 3, 4, 5 };
	list<int> l3(v.begin(), v.end());

	list<int> l4(l3);

	list<int> l5{ 5, 4, 3, 2, 1 };
	
	// list的两种遍历方式：范围for和迭代器
	for (auto e : l2)
		cout << e << " ";
	cout << endl;

	list<int>::iterator it = l3.begin(); // auto it = l3.begin();
	while (it != l3.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	// 反向迭代器实现需要注意！！！
	auto rit = l4.rbegin();
	while (rit != l4.rend())
	{
		cout << *rit << " ";
		--rit;
	}
	cout << endl;
}

// 3. 容量操作
/*
bool empty()const;
size_t size()const;
void resize(size_t n, value_type val = value_type());
*/

// 4. 元素访问
/*
reference front();
const_reference front() const;

reference back();
const_reference back() const;
*/

// 5. 修改
/*
void push_front(const value_type& val);
void pop_front();

void push_back(const value_type& val);
void pop_back();

iterator insert(iterator position, const value_type& val);
void insert(iterator positon, size_t n, const value_type& val);
template<class InputIterator>
void insert(iterator position, InputIterator first, InputIterator last);

iterator erase(iterator position);
iterator erase(iterator first, iterator last);

void swap(list& x);

void clear();
*/

// 6. 特殊操作
/*
void remove(const value_type& val);

template<class Predicate>
void remove_if(Predicate pred);

// 删除重复元素中除第一个元素的其余所有元素 去重
// 注意：unique去重之前要对list排序
void unique(); 
template <class BinaryPredicate>
void unique (BinaryPredicate binary_pred);

void merge(list& x);
template<class Compare>
void merge(list& x, Compare comp);

void sort();
template<class Compare>
void sort(Compare comp);

void reverse();
*/

void Test2()
{
	list<int> L;
	L.push_back(1);
	L.push_back(2);
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.push_front(0);
	cout << "头插0之后" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.pop_back();
	L.pop_front();
	cout << "头删一次，尾删一次之后" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.insert(L.begin(), 3, 0);
	cout << "在L.begin()这个位置插入3个0" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	list<int> L1{ 4, 2, 1 };
	cout << "在L.end()这个位置插入L1区间中所有元素" << endl;
	L.insert(L.end(), L1.begin(), L1.end());
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	// 如果没找到值为val的位置 在list末尾进行插入
	L.insert(std::find(L.begin(), L.end(), 7), 1, 9);
	cout << "在元素值为7的位置插入1个9" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.insert(std::find(L.begin(), L.end(), 3), 1, 9);
	cout << "在元素值为3的位置插入1个9" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	// 删除值为3的元素
	L.erase(std::find(L.begin(), L.end(), 3));
	cout << "删除值为3的元素之后" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.erase(L.begin(), L.end()); // 相当于L.clear();

	if (L.empty())
		cout << "已清空";

	list<int> L2{ 2, 2, 2, 2, 2};
	cout << "交换前L1和L2：" << endl;
	for (auto e : L1)
		cout << e << " ";
	cout << endl;
	for (auto e : L2)
		cout << e << " ";
	cout << endl;

	L1.swap(L2); // 调用std::list::swap
	cout << "交换后L1和L2：" << endl;
	for (auto e : L1)
		cout << e << " ";
	cout << endl;
	for (auto e : L2)
		cout << e << " ";
	cout << endl;

	std::swap(L1, L2); // 调用全局std::swap
	

}

void Test3()
{
	list<int> L{ 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
	// 不排序直接unique
	L.unique();
	cout << "unique前list未排序" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.sort();
	cout << "排序后" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;
	L.unique();
	cout << "排序后进行去重" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.reverse();
	cout << "逆置后" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;
}

bool isOdd(int data)
{
	return data & 0x01;
}
// list特殊操作：remove和remove_if
void Test4()
{
	list<int> L{ 1, 4, 5, 6, 7, 9, 2 };
	L.remove(4); // 删除值为4的元素
	L.remove_if(isOdd); // 删除list中奇数
}

// merge的两个list必须有序
void Test5()
{
	list<int> L1{ 1, 4, 5, 6, 7, 9, 2 };
	list<int> L2{ 5, 6, 4, 3, 7 };
	L1.sort();
	L2.sort();
	L1.merge(L2);
	for (auto e : L1)
		cout << e << " ";
	cout << endl;
}

// list迭代器失效：只有erase一种场景
void Test6()
{
	list<int> L{ 1, 4, 5, 6, 7, 9, 2 };
	list<int>::iterator it = L.begin();
	while (it != L.end())
	{
		// erase返回被删元素的下一个位置的迭代器
		it = L.erase(it);
		//++it; // 迭代器失效，程序崩溃
	}
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();

	system("pause");
	return 0;
}