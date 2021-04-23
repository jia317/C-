#include<iostream>
#include<Windows.h>
using namespace std;

// ��ͬ�������ڴ��еĴ��λ��
#if 0
int globalVar = 1; 
static int staticGlobalVal = 1;
void Test()
{
	static int staticVar = 1; 
	int localVar = 1; 

	int num[] = { 1, 2, 3, 4 }; 
	char str[] = "abcd"; 
	char* p = "abcd"; 
	int* ptr1 = (int*)malloc(sizeof(int)* 4); 
	int* ptr2 = (int*)calloc(4, sizeof(int));
	int* ptr3 = (int*)realloc(ptr2, sizeof(int)* 4);
	free(ptr1);
	free(ptr3);
}
#endif

// ̽��C++ΪʲôҪ�����Լ��Ķ�̬�ڴ����ʽ
/*
����������������Զ����ù��캯�������ٶ���ʱ���������Զ�������������
�ڶ��ϴ������󣬲�����malloc
��Ϊmalloc������ù��캯���������ù��캯��˵�����󴴽�ʧ�ܣ�
����malloc�Ӷ�������Ŀռ�͸������Ƕ���Ŀռ䣬��ֻ��һ�κͶ������ʹ�С��ȵĶѿռ����
������free�ͷŶѶ���Ŀռ�
��Ϊfree��������������������������������Ͳ��ܽ������е���Դ����ɾ� 
*/
#if 0
class A
{
public:
	A(int a)
		:_a(a)
	{ 
		cout << "A()" << endl;
	}

	~A()
	{ 
		cout << "~A()" << endl;
	}
private:
	int _a;
};

int main()
{
	// ��ջ�ϴ�������
	A a1(10);

	// �ڶ��ϴ�������
	A* pa = (A*)malloc(sizeof(A));

	free(pa);

	system("pause");
	return 0;
}
#endif

// new��delete���÷�
#if 0
int main()
{
	// �������Ϳռ������
	int* p1 = new int;
	int* p2 = new int(10); // ����1��int���ʹ�С�Ŀռ䣬����ʼ����10

	// �������Ϳռ������
	int* p3 = new int[5]; // ����5��int���ʹ�С�������ռ�
	int* p4 = new int[5]{ 1, 2, 3, 4, 5 }; // ����5��int���ʹ�С�������ռ䣬����ʼ��Ϊ1��2��3��4��5

	// �������Ϳռ���ͷ�
	delete p1;
	delete p2;

	// �����ռ���ͷ�
	delete[] p3;
	delete[] p4;

	system("pause");
	return 0;
}
#endif

// ��֤new����ù��캯�� delete�������������
#if 0
class Test
{
public:
	Test(int t = 7)
		:_t(t)
	{
		cout << "Test(int)" << this << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	int _t;
};

int main()
{
	Test* p1 = new Test(100);

	delete p1;

	system("pause");
	return 0;
}
#endif


// windows�ṩ��api�������������м򵥵��ڴ�й©�ļ��
// ֻ�����Ҫ���Ĵ������󼴿�
//_CrtDumpMemoryLeaks();

// �����Զ�������
#if 0
class Test
{
public:
	Test(int t = 7)
		:_t(t)
	{
		cout << "Test(int)" << this << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	int _t;
};

int main()
{
	Test* p1 = new Test; // �ڶ��ϴ���һ��Test���͵Ķ���
	delete p1;

	Test* p2 = new Test(100); // ���ڶ��ϴ���һ��Test���͵Ķ��󲢽����еĳ�Ա������ʼ��Ϊ100
	delete p2;

	Test* p3 = new Test[5]; // �ڶ��ϴ���5��Test���͵Ķ���
	delete[] p3;	

	system("pause");
	return 0;
}
#endif

// ��λnew���ʽ�����ѷ����ԭʼ�ڴ�ռ��е��ù��캯����ʼ��һ������
#if 0
class Test
{
public:
	Test(int t = 7)
		:_t(t)
	{
		cout << "Test(int)" << this << endl;
	}

	~Test()
	{
		cout << "~Test()" << endl;
	}
private:
	int _t;
};

int main()
{
	Test* pt = (Test*)malloc(sizeof(Test)); // malloc����Ķѿռ䲻�Ƕ���Ŀռ�
	
	new(pt)Test; // ��λnew����ù��캯��
	/* 
	�ϱ����д���������൱��new
	new��ʵ��ԭ��
	1. ����ѿռ�
	2. ���ù��캯��
	*/

	// ��ʱ��ptָ��Ķѿռ���Ƕ���Ŀռ���
	// ���Բ�����free���ͷſռ䣬��Ϊfree���������������
	// ���������ֶ�������������

	/*
	�±����д���������൱��delete
	delete��ʵ��ԭ��
	1. ��������������������е���Դ
	2. �ͷſռ�
	*/
	pt->~Test();
	free(pt);


	system("pause");
	return 0;
}
#endif

