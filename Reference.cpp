#include<iostream>
#include<Windows.h>
using namespace std;

#if 0
void TestRef()
{
	const int a = 10;
	//int& ra = a; // ����д���Ǵ���ģ���ΪaΪ����
	const int& ra = a; // ��ȷд��

	//int& b = 7; //����д��Ҳ�Ǵ���ģ���Ϊ7�ǳ���������ͨ������
	const int& b = 7; // ��ȷд��

	double c = 12.34;
	const int& rc = c; // ��Ȼ����ͨ�����룬�����������һ��
	cout << "�޸�ǰrc=" << rc << endl;
	c = 56.78; // ����ı���c��ֵ�����rc��c�����ã���ôrc��ֵҲӦ�ñ��56
	cout << "�޸ĺ�rc=" << rc << endl;
}

int main()
{
	/*int a = 10;
	const int& ra = a;
	a = 17;
	cout << "ra = " << ra << endl;

	double b = 12.34;
	const int& rb = b;
	b = 56.78;
	cout << "rb = " << rb << endl;*/

	TestRef();

	system("pause");
	return 0;
}
#endif

// ���õ�ʹ�ó���
// 1. �򻯴���
// ��1��
#if 0
struct A
{
	int x;
	int y;

	struct B
	{
		int i;
		int j;
	};

	B b;
};

// ��2������int*���͵�ָ�뺯��
// C����
void Swap(int** l,int** r)
{
	int temp = *l;
	*l = *r;
	*r = temp;
}

void Swap(int& pa, int& pb)
{
	int temp = pa;
	pa = pb;
	pb = temp;
}
int main()
{
	//A a;
	//a.b.i = 12;

	//// ����֮��ᾭ���õ�a.b.i�����������ôÿһ��ʹ�ö�Ҫд�ܳ��ı�����
	//// �����������
	//a.b.i = 10;

	//// ������
	//int &ri = a.b.i;
	//ri = 22;
	//cout << "ri = " << ri << endl;

	const int a = 10;
	int b;
	int* pa = (int*)&a;
	int* pb = &b;
	Swap(&pa, &pb);
	Swap(pa, pb);

	system("pause");
	return 0;
}
#endif

#if 0
// 2. ����������Ϊ�����β�
// C����Swap
void Swap(int* l, int* r)
{
	int temp = *l;
	*l = *r;
	*r = temp;
}

// C++���ô���
void Swap(int& l, int& r)
{
	int temp = l;
	l = r;
	r = temp;
}

// �������ͨ���β����ı��ⲿʵ�Σ�������const����������Ϊ�β�����
void Print(const int& x)
{
	cout << x << endl;
}

int main()
{
	int a = 3;
	int b = 8;

	Swap(&a, &b);
	Swap(a, b);

	system("pause");
	return 0;
}
#endif

int main()
{
	const int a = 10;
	int* pa = (int*)&a;

	*pa = 100;

	/*
	��C++�У���const���εı���һ���Ϊ�������ó������к��滻��Ч��
	����ĺ��滻���ڱ���׶Σ�������ʹ��const�����ĵط��ó�����ֵ�滻�ó���
	ע�⣺��&������
	*/
	cout << a << endl; // �ڱ���׶ν������滻���൱��cout<<10<<endl;
	cout << *pa << endl;
	cout << *&a << endl; // 10

	system("pause");
	return 0;
}

// ���main��������C���Բ��ԣ����ļ���׺��Ϊ.c
// ������C�����У�const���εı����Ծ��Ǳ�����ֻ���������޸�
// ������C++�У���const���εı���һ���Ϊ�������ó������к��滻��Ч��
#if 0
int main()
{
	const int a = 10;
	int array[a]; // ��C�����лᱨ����Ϊ���鿪��int���͵ı����ĸ��������ǳ���(���Ƿ������е�ֵ)

	system("pause");
	return 0;
}
#endif
