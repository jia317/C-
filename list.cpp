#include<iostream>
#include<Windows.h>
#include<vector>
using namespace std;

#include<list>
// list�ײ�ṹ����ͷ˫��ѭ������

// list�ӿڵ�ʹ��

// 1. ���������
/*
list(); // �޲ι���
list(size_t n,const value_type& val=value()); // n��ֵΪval�Ĺ���
template<class InputIterator> 
list(InputIterator first, InputIterator last); // ���乹��
list(const list& l); // ��������
*/

// 2.������
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
	
	// list�����ֱ�����ʽ����Χfor�͵�����
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

	// ���������ʵ����Ҫע�⣡����
	auto rit = l4.rbegin();
	while (rit != l4.rend())
	{
		cout << *rit << " ";
		--rit;
	}
	cout << endl;
}

// 3. ��������
/*
bool empty()const;
size_t size()const;
void resize(size_t n, value_type val = value_type());
*/

// 4. Ԫ�ط���
/*
reference front();
const_reference front() const;

reference back();
const_reference back() const;
*/

// 5. �޸�
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

// 6. �������
/*
void remove(const value_type& val);

template<class Predicate>
void remove_if(Predicate pred);

// ɾ���ظ�Ԫ���г���һ��Ԫ�ص���������Ԫ�� ȥ��
// ע�⣺uniqueȥ��֮ǰҪ��list����
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
	cout << "ͷ��0֮��" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.pop_back();
	L.pop_front();
	cout << "ͷɾһ�Σ�βɾһ��֮��" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.insert(L.begin(), 3, 0);
	cout << "��L.begin()���λ�ò���3��0" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	list<int> L1{ 4, 2, 1 };
	cout << "��L.end()���λ�ò���L1����������Ԫ��" << endl;
	L.insert(L.end(), L1.begin(), L1.end());
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	// ���û�ҵ�ֵΪval��λ�� ��listĩβ���в���
	L.insert(std::find(L.begin(), L.end(), 7), 1, 9);
	cout << "��Ԫ��ֵΪ7��λ�ò���1��9" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.insert(std::find(L.begin(), L.end(), 3), 1, 9);
	cout << "��Ԫ��ֵΪ3��λ�ò���1��9" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	// ɾ��ֵΪ3��Ԫ��
	L.erase(std::find(L.begin(), L.end(), 3));
	cout << "ɾ��ֵΪ3��Ԫ��֮��" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.erase(L.begin(), L.end()); // �൱��L.clear();

	if (L.empty())
		cout << "�����";

	list<int> L2{ 2, 2, 2, 2, 2};
	cout << "����ǰL1��L2��" << endl;
	for (auto e : L1)
		cout << e << " ";
	cout << endl;
	for (auto e : L2)
		cout << e << " ";
	cout << endl;

	L1.swap(L2); // ����std::list::swap
	cout << "������L1��L2��" << endl;
	for (auto e : L1)
		cout << e << " ";
	cout << endl;
	for (auto e : L2)
		cout << e << " ";
	cout << endl;

	std::swap(L1, L2); // ����ȫ��std::swap
	

}

void Test3()
{
	list<int> L{ 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
	// ������ֱ��unique
	L.unique();
	cout << "uniqueǰlistδ����" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.sort();
	cout << "�����" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;
	L.unique();
	cout << "��������ȥ��" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;

	L.reverse();
	cout << "���ú�" << endl;
	for (auto e : L)
		cout << e << " ";
	cout << endl;
}

bool isOdd(int data)
{
	return data & 0x01;
}
// list���������remove��remove_if
void Test4()
{
	list<int> L{ 1, 4, 5, 6, 7, 9, 2 };
	L.remove(4); // ɾ��ֵΪ4��Ԫ��
	L.remove_if(isOdd); // ɾ��list������
}

// merge������list��������
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

// list������ʧЧ��ֻ��eraseһ�ֳ���
void Test6()
{
	list<int> L{ 1, 4, 5, 6, 7, 9, 2 };
	list<int>::iterator it = L.begin();
	while (it != L.end())
	{
		// erase���ر�ɾԪ�ص���һ��λ�õĵ�����
		it = L.erase(it);
		//++it; // ������ʧЧ���������
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