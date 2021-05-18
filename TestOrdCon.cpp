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

	set<int> s2(array, array + sizeof(array) / sizeof(array[0])); // ���乹��

	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	cout << s.size() << endl;

	s.erase(s.find(7)); // ɾ��7��һ�γ��ֵ�λ�õ�Ԫ��
	cout << s.erase(3) << endl; // ɾ��keyֵΪ3������Ԫ�أ�����ֵΪ3Ԫ�ظ���

	cout << s.count(3) << endl;
	cout << s.count(5) << endl;

	s.clear();
	if (s.empty())
		cout << "�����" << endl;
	else
		cout << "����" << endl;
}


void TestMultiset()
{
	int array[] = { 1, 2, 3, 5, 4, 8, 7, 6, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	multiset<int> ms;
	for (auto e : array)
		ms.insert(e);

	set<int> s2(array, array + sizeof(array) / sizeof(array[0])); // ���乹��

	auto it = ms.begin();
	while (it != ms.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	cout << ms.size() << endl;

	ms.erase(ms.find(7)); // ɾ��7��һ�γ��ֵ�λ�õ�Ԫ��
	cout << ms.erase(3) << endl; // ɾ��keyֵΪ3������Ԫ�أ�����ֵΪ3Ԫ�ظ���

	for (auto i : ms)
		cout << i << " ";
	cout << endl;

	cout << "ms.count(3)" << ms.count(3) << endl;
	cout << "ms.count(5)" << ms.count(5) << endl;

	ms.clear();
	if (ms.empty())
		cout << "�����" << endl;
	else
		cout << "����" << endl;
}

void TestMultiMap()
{
	// һ��ͬѧ�����ְ
	multimap<string, string> mm;

	mm.insert(make_pair("С��", "��Ա"));
	mm.insert(make_pair("С��", "ѧϰίԱ"));
	mm.insert(make_pair("С��", "��Ա"));
	mm.insert(make_pair("С��", "�೤"));

	cout << mm.count("С��") << endl;

	for (auto& e : mm)
		cout << "[" << e.first << "��" << e.second << "]" << endl;
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