#include <iostream>
using namespace std;

// thisָ���ܷ�Ϊ�գ�
class A
{
public:
	/*
	�ڱ��������±ߵĳ�Ա������������
	void func(A* const this)
	{
	this->_t = 10;
	cout << this << endl;
	}
	*/
	void func()
	{
		_t = 10; // ��Ա�����з��ʳ�Ա�������ߵ��ó�Ա���������thisָ��Ϊ�գ��϶�����
		cout << this << endl;
	}

	int _t;
};
int main()
{
	A a1, a2, a3;

	// ���ó�Ա���������ַ�ʽ
	// 1. ����.��Ա����
	a1.func(); // call A::func(&a1)

	// 2. ָ������ָ��->��Ա����
	A* pa1 = &a2;
	pa1->func(); // call A::func(pa1)

	A* pa2 = &a3;
	pa2 = nullptr;
	pa2->func(); // call A::func(nullptr)

	system("pause");
	return 0;
}