#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

// 1.��ͨ�����ռ�
namespace N1
{
	int a=1;
	int Add(int left, int right)
	{
		return left + right;
	}
}

// 2. �����ռ����Ƕ��
namespace N2
{
	int a=2, b=2;
	int Add(int left, int right)
	{
		return left + right;
	}

	namespace N3
	{
		int c=3, d=3;
		int Sub(int left, int right)
		{
			return left - right;
		}
	}
}

// 3. ͬһ��������������ͬ���Ƶ������ռ䣬����������ϳ�ͬһ�������ռ�
namespace N1
{
	int Mul(int left, int right)
	{
		return left*right;
	}
}

// 4. �����ռ��ʹ��
namespace N
{
	int a = 10;
	int b = 20;
	int Add(int left, int right)
	{
		return left + right;
	}

	int Sub(int left, int right)
	{
		return left - right;
	}
}

#if 0
int main()
{
	// �����ռ��г�Ա��ʹ��
	// 1.�������ռ����Ƽ��������޶���
	printf("%d\n", N1::a);

	system("pause");
	return 0;
}
#endif

#if 0
// 2.ʹ��using�������ռ��г�Ա����
using N2::a;
int main()
{
	printf("%d\n", a);
	printf("%d\n", N2::N3::c);

	system("pause");
	return 0;
}
#endif

#if 0
// 3.ʹ�� using namespace �����ռ����� ����
using namespace N;
int main()
{
	printf("%d\n", a);
	printf("%d\n", b);

	cout << "��N�е�Add:" << Add(7, 8) << endl;
	cout << "��N1�е�Add:" << N1::Add(a,b) << endl;

	system("pause");
	return 0;
}
#endif

#if 0
// ȱʡ����
void TestFunc(int a = 0)
{
	cout << a << endl;
}

// ȫȱʡ����
void TestFunc1(int a = 1, int b = 2, int c = 3)
{
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
}

// ��ȱʡ����
// ��ȱʡ�����������������������ܼ���Ÿ�
void TestFunc2(int a, int b = 2, int c = 3)
{
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
}
int main()
{
	//TestFunc();
	//TestFunc(10);

	//TestFunc1();
	//TestFunc1(7); // a=7,b��c����Ĭ��ֵ
	//TestFunc1(7, 8); // a=7, b=8, c����Ĭ��ֵ
	//TestFunc1(4, 5, 6);

	TestFunc2(1); // a=1, b=2, c=3
	TestFunc2(7, 8); // a=7, b=8, c=3
	TestFunc2(7, 8, 9); // a=7, b=8, c=9

	system("pause");
	return 0;
}
#endif

#if 0
// ��������
// ͬһ������ ͬ�� �����б�(�������� �� �������� �� ����˳��)���벻ͬ
int Add(int left, int right)
{
	return left + right;
}

int Add(int a, int b, int c)
{
	return a + b + c;
}

double Add(double a, double b)
{
	return a + b;
}

double Add(int a, double b)
{
	return a + b;
}

int main()
{
	cout << Add(1, 2) << endl;
	cout << Add(1, 2, 3) << endl;
	double ret = Add(1.0, 2.0);
	printf("%f\n", ret);
	cout << Add(1, 2.0) << endl;

	system("pause");
	return 0;
}
#endif

#if 0
#include "test.h"
int main()
{
	Add(1, 2);
	return 0;
}
#endif

// ����
void TestRef()
{
	int a = 10;
	int b = 1;
	// һ�����������ж������
	int& ra = a;  // �����ڶ���ʱ�����ʼ��
	int& rra = a;

	// �±�������ַһ����˵��������ͬһ������
	printf("%p:%d\n", &a, a);
	printf("%p:%d\n", &ra, ra);
	printf("%p:%d\n", &rra, rra);
}

// ����һ����ʼ���Ͳ�������������ʵ��
// ��˼�ǣ���������������ʵ�壬���ĵ�ַҲ��û�иı䣬ʼ��ָ���ʼ��ʱ���õ�ʵ��
void TestRef1()
{
	string s1 = "a";
	string s3 = "c";

	string& s2 = s1;
	s2 = s3;

	printf("%p\n", &s1);
	printf("%p\n", &s2);
	printf("%p\n", &s3);
}

void TestConstRef()
{
	const int a = 10;
	//int& ra = a; // ����д���Ǵ���ģ���ΪaΪ����
	const int& ra = a; // ��ȷд��

	//int& b = 7; //����д��Ҳ�Ǵ���ģ���Ϊ7�ǳ���
	const int& b = 7; // ��ȷд��

	double c = 12.34;
	const int& rc = c; // ��Ȼ����ͨ�����룬�����������һ��
	cout << "�޸�ǰrc=" << rc << endl;
	c = 56.78; // ����ı���c��ֵ�����rc��c�����ã���ôrc��ֵҲӦ�ñ��56
	cout << "�޸ĺ�rc=" << rc << endl; // ���Ǵ�ӡ�������12��˵��rc��������c������

}

// ����������

// ֵ���Σ��ᷢ����ʱ����������������ʱ����
// ����Swap1����������޸ı�
void Swap1(int left, int right)
{
	int temp = left;
	left = right;
	right = temp;
}

// ���ô��Σ�������Ǳ���ʵ��
// ����Swap�����������
void Swap(int& left, int& right)
{
	int temp = left;
	left = right;
	right = temp;
}

// ����������ֵ
// 
//int& Add(int left, int right) // ��û����
//{
//	return left + right; 
//}

int& Add(int a, int b)
{
	int c = a + b;
	return c;
}

#if 0
int main()
{
	//TestRef();
	//TestRef1();
	//TestConstRef();

	//int a = 1, b = 7;
	//cout << "��swap1����ǰa��b��" << a << "," << b << endl;
	//Swap1(a, b);
	//cout << "��swap1������a��b��" << a << "," << b << endl;
	//
	//a = 1, b = 7;
	//cout << "��swap����ǰa��b��" << a << "," << b << endl;
	//Swap(a, b);
	//cout << "��swap������a��b��" << a << "," << b << endl;

	/*int& ret = Add(1, 2);
	Add(3, 4);
	printf("%d\n", ret);*/

	//cout << "Add(1,2):" << ret << endl; // 7

	system("pause");
	return 0;
}
#endif


// ���ú�ָ��
void Swap_p(int* left, int* right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}

void Swap_r(int& left, int& right)
{
	int temp = left;
	left = right;
	right = temp;
}

#if 0
int main()
{
	//int a = 10;

	//int& ra = a; // ra����a
	//ra = 20; // ��ra���൱�ڸ�a

	//int* pa = &a; // pa��ָ��a�ı�����pa�б������a�ĵ�ַ
	//*pa = 20; // pa������

	int a = 10;
	int b = 20;

	Swap_p(&a, &b);   // ����int*
	Swap_r(a, b);     // ����int&

	int* pa = &a;
	*pa = 100;

	int& ra = a;
	ra = 100;
	
	system("pause");
	return 0;
}
#endif

#if 0
int main()
{
	int a = 10;
	int& ra = a;

	int* p = &a;
	// ����ʵ��ķ�ʽ
	cout << ra << endl; // ���÷���ʵ���ɱ���������
	cout << *p << endl; // ָ�����ʵ����Ҫ��ʽ������

	int b = 20;
	p = &b; // ָ��������κ�ʱ��ָ���κ�һ��ͬ����ʵ��

	char c = 'a';
	char& rc = c;
	char* pc = &c;

	rc++; // �����Լ� = ����ʵ���ֵ+1
	pc++; // ָ���Լ� = ָ�����ƫ��һ�����͵Ĵ�С
	cout << rc << endl;
	cout << pc << endl;
	cout << sizeof(rc) << endl; // sizeof(����) = �������͵Ĵ�С
	cout << sizeof(pc) << endl; // sizeof(ָ��) = ָ���д洢�ı����ĵ�ַ��ռ�ֽڸ���(32λƽ̨��ռ4�ֽ�)

	// �ж༶ָ��
	int*p1;
	int** p2;
	int*** p3;

	int d = 10;
	int& rd = d;
	// û�ж༶����
	//int&& rrd = d;
	//int&&& rrrd = d;

	// C++11���������ֵ����
	const int&& rrd = 10;
	
	system("pause");
	return 0;
}
#endif

// auto��ʹ��
int Func()
{
	return 10;
}
int TestAuto()
{
	int a = 10;
	auto b = a;
	auto c = 'a';
	auto d = Func();

	cout << typeid(b).name() << endl; // int
	cout << typeid(c).name() << endl; // char 
	cout << typeid(d).name() << endl; // int

	return 0;
}

// auto������Ϊ�����Ĳ���
//void TestAuto1(auto a) // ����ʾ��
//{ }

// auto����ֱ��������������
//void TestAuto2() // ����ʾ��
//{ 
//	int a[] = { 1, 2, 3 };
//	auto b[] = { 4, 5, 6 };
//}

#if 0
int main()
{
	//TestAuto();

	// auto��ָ������ý������ʹ��
	int x = 10;
	// ��auto����ָ������ʱ����auto��auto*û���κ�����
	auto a = &x;
	auto* b = &x;

	// ��auto������������ʱ�����&
	int& rx = x;
	auto& c = rx;

	cout << typeid(a).name() << endl; // int*
	cout << typeid(b).name() << endl; // int*
	cout << typeid(c).name() << endl; // int

	*a = 20;
	cout << x << endl; // 20
	*b = 30;
	cout << x << endl; // 30
	c = 40;
	cout << x << endl; // 40

	// ��ͬһ�������������ʱ����Щ������������ͬ���ͣ�����������ᱨ��
	// ��Ϊ������ֻ�Ե�һ�����ͽ����Ƶ���Ȼ�����Ƶ����������Ͷ�����������
	auto a = 1, b = 2; // ��ȷд��
	//auto c = 3, d = 4.0; // ����
	
	system("pause");
	return 0;
}
#endif

#if 0
// auto�ͷ�Χfor(C++11)
// ��Χfor��������":"��Χ�����֣���һ�����Ƿ�Χ�����ڵ����ı������ڶ����ֱ�ʾ�������ķ�Χ
void TestFor()
{
	int array[] = { 1, 2, 3, 4, 5 };
	// ��array��ÿ��Ԫ�س�2
	for (auto& e : array) // ע�⣺auto = int��e�൱����array�е���Ԫ�صı���
	{
		e *= 2;
		cout << typeid(e).name() << endl; // int
	}
	
	for (auto e : array) // auto a = auto* a
	{
		cout << e << " ";
		cout << typeid(e).name() << endl; // int
	}
}

int main()
{
	TestFor();

	system("pause");
	return 0;
}
#endif

// ��
#if 0
#define MAX 10

int main()
{
	const int a = 10;
	int b = 20;

	int* pa = (int*)&a;
	*pa = 100;

	printf("%d\n", MAX);
	printf("%d\n", a);
	printf("%d\n", b);

	cout << a << endl;
	cout << *pa << endl;

	return 0;
}
#endif

// �꺯���Ķ��弰ʹ��
#if 0
#define SQUARE(x) x*x

int main()
{
	int a = 5;

	cout << SQUARE(a) << endl;
	cout << SQUARE(a+1) << endl; // 11

	system("pause");
	return 0;
}

#define MAX(a,b) (a>b ? a:b)

int main()
{
	int a = 10;
	int b = 20;

	// MAX(++b, a)
	// -> ++b>a ? ++b : a
	// -> 21>10 ? 22 : 10
	cout << MAX(++b, a) << endl; //22

	system("pause");
	return 0;
}
#endif

// ��������
inline int fun(int left, int right)
{
	return left + right;
}

int main()
{
	int ret = Add(1, 2);
	return 0;
}