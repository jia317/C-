#include<iostream>
#include<Windows.h>
#include<set>
#include<map>
#include<string>
using namespace std;

void TestSet()
{
	int array[] = { 1, 2, 3, 5, 4, 8, 7, 6, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	set<int> s;
	for (auto e : array)
		s.insert(e);

	set<int> s2(array, array + sizeof(array) / sizeof(array[0])); // 区间构造

	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	cout << s.size() << endl;

	s.erase(s.find(7)); // 删除7第一次出现的位置的元素
	cout << s.erase(3) << endl; // 删除key值为3的所有元素，返回值为3元素个数

	cout << s.count(3) << endl;
	cout << s.count(5) << endl;

	s.clear();
	if (s.empty())
		cout << "已清空" << endl;
	else
		cout << "不空" << endl;
}


void TestMultiset()
{
	int array[] = { 1, 2, 3, 5, 4, 8, 7, 6, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	multiset<int> ms;
	for (auto e : array)
		ms.insert(e);

	set<int> s2(array, array + sizeof(array) / sizeof(array[0])); // 区间构造

	auto it = ms.begin();
	while (it != ms.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	cout << ms.size() << endl;

	ms.erase(ms.find(7)); // 删除7第一次出现的位置的元素
	cout << ms.erase(3) << endl; // 删除key值为3的所有元素，返回值为3元素个数

	for (auto i : ms)
		cout << i << " ";
	cout << endl;

	cout << "ms.count(3)" << ms.count(3) << endl;
	cout << "ms.count(5)" << ms.count(5) << endl;

	ms.clear();
	if (ms.empty())
		cout << "已清空" << endl;
	else
		cout << "不空" << endl;
}

void TestMultiMap()
{
	// 一名同学身兼数职
	multimap<string, string> mm;

	mm.insert(make_pair("小徐", "党员"));
	mm.insert(make_pair("小徐", "学习委员"));
	mm.insert(make_pair("小王", "团员"));
	mm.insert(make_pair("小王", "班长"));

	cout << mm.count("小徐") << endl;

	for (auto& e : mm)
		cout << "[" << e.first << "，" << e.second << "]" << endl;
	cout << endl;
}
int main()
{
	//TestSet();
	//TestMultiset();
	TestMultiMap();

	system("pause");
	return 0;
}