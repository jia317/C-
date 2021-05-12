#include<iostream>
#include<Windows.h>
using namespace std;

/*
��̬��ʵ������
ǰ�᣺�ڼ̳з�ʽ��
�����б������麯������������Ҫ��д�����麯��
�����û���ָ������ã�ָ��ͬ��Ķ��󣬵����麯��
*/
#if 0
class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "ȫ��Ʊ" << endl;
	}
protected:
	string _name;
	string _gender;
	int _age;
};

class Student :public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "���Ʊ" << endl;
	}
protected:
	int _stuID;
};

class Solider :public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "���" << endl;
	}
protected:
	string _ID;
};

// ע�⣺�ڳ�������ʱ������p�����ö���Ĳ�ͬ�����յ��õ��麯����ͬ
// �ڳ������ʱ���޷�ȷ������Ҫ�����ĸ��麯��---��Ϊ����׶Σ���������֪��p�����ĸ�����
void Test(Person& p)
{
	p.BuyTicket();
}

int main()
{
	Person p;
	Student stu;
	Solider sol;

	Test(p);
	Test(stu);
	Test(sol);

	system("pause");
	return 0;
}
#endif

/*
��д
ǰ�᣺һ�����ڼ̳���ϵ�У�������Ի����е��麯��������д
1. ����ĺ����������麯��
2. ����Ҫ��д�����麯�����������麯����ԭ�ͱ���Ҫ�ͻ����麯��ԭ��һ��
   ԭ��һ�£�����ֵ���� ��������(�����б�) ������ȫ��ͬ
   ���⣺
       1��Э�䣺�����麯�����ػ���ָ�������
	            �����ຯ������������ָ�������
	   2��
3. �����麯�����Բ���virtual�ؼ��֣����ǽ������
4. ����ͻ����麯���ķ���Ȩ�޿��Բ�ͬ
*/
#if 0
class B
{
public:
	void Test1()
	{
		cout << "B::Test1()" << endl;
	}

	virtual void Test2()
	{
		cout << "B::Test2()" << endl;
	}

	void Test3()
	{
		cout << "B::Test3()" << endl;
	}

	virtual void Test4()
	{
		cout << "B::Test4()" << endl;
	}

	virtual void Test5()
	{
		cout << "B::Test5()" << endl;
	}

	virtual void Test6(int)
	{
		cout << "B::Test5()" << endl;
	}

	virtual void Test7()
	{
		cout << "B::Test7()" << endl;
	}

	virtual void Test8()
	{
		cout << "B::Test8()" << endl;
	}

	void Test9()
	{
		cout << "B::Test9()" << endl;
	}

	virtual void Test10(int a = 10)
	{
		cout << "B::Test10()" << endl;
	}
protected:
	int _b;
};

class D :public B
{
public:
	// �������Test1Ϊͬ������
	void Test1()
	{
		cout << "D::Test1()" << endl;
	}

	// ��д�˻����е�Test2
	// �����麯�����Բ���virtual�ؼ��֣����ǽ������
	void Test2()
	{
		cout << "D::Test2()" << endl;
	}

	// �������Test3Ϊͬ������
	virtual void Test3()
	{
		cout << "D::Test3()" << endl;
	}

	// �������Test4������д
	// ��д�ı�׼д������
	virtual void Test4()
	{
		cout << "D::Test4()" << endl;
	}

	// ������Test5û�в������������Test5�в���---����ԭ�Ͳ�һ��---������д
	// �������Test5Ϊͬ������
	virtual void Test5(int d)
	{
		cout << "D::Test5()" << endl;
	}

	// ��������ͬ
	virtual void Tset6(int)
	{
		cout << "D::Test6()" << endl;
	}

	// Test8ɶҲ����
	// ����ֵ���Ͳ�ͬ --- �������ʧ��
	/*virtual int Test8()
	{
		cout << "D::Test8()" << endl;
		return 0;
	}*/

	// ͬ������ ��������ͬ
	virtual int Test9()
	{
		cout << "D::Test9()" << endl;
		return 0;
	}

	// ͬ������
	virtual void Test10()
	{
		cout << "B::Test10()" << endl;
	}
private:
	// ����Test7��Ȩ����˽�еģ�������������Ե���
	// �������Test7������д
	virtual void Test7()
	{
		cout << "D::Test7()" << endl;
	}
protected:
	int _d;
};

void TestVirtual(B* pb)
{
	/*
	Test1��ͬ������
	pbָ�������������������󣬶����û����Test1
	����ָ����ã����û����Ա����
	*/
	pb->Test1();

	/*
	�������������Test2������д
	pbָ�������󣬵��û���Test2
	pbָ����������󣬵���������Test2
	*/
	pb->Test2();

	/*
	����Test3�����麯����������������Test3Ϊ�麯��
	Ҳ��ͬ������
	pbָ�������������������󣬶����û����Test3
	����ָ����ã����û����Ա����
	*/
	pb->Test3();

	pb->Test4();

	pb->Test5();

	pb->Test6(1);

	pb->Test7();

	pb->Test9();

	pb->Test10();
}

int main()
{
	B b;
	TestVirtual(&b);

	cout << "---------------------" << endl;

	D d;
	TestVirtual(&d);

	system("pause");
	return 0;
}
#endif

// ��д����---Э��
/*
�����麯�����ػ���ָ�������
�����ຯ������������ָ�������

ֻҪ�����麯�� �Ļ��� �� �������麯�� �������� �Ǽ̳й�ϵ 
���صĻ���ָ������� �Ļ��� �� ���صĻ���ָ������� �������� �Ǽ̳й�ϵ����
*/
#if 0
class A{};
class B:public A{};

class Base
{
public:
	virtual Base& Test1()
	{
		cout << "Base::Test1()" << endl;
		return *this;
	}

	virtual A* Test2()
	{
		cout << "A::Test2()" << endl;
		return nullptr;
	}
};

class Derived :public Base
{
public:
	virtual Derived& Test1()
	{
		cout << "Derived::Test()" << endl;
		return *this;
	}

	virtual B* Test2()
	{
		cout << "B::Test2()" << endl;
		return nullptr;
	}

};

void TestVir(Base& b)
{
	b.Test1();
	b.Test2();
}

int main()
{
	Base b;
	TestVir(b);

	cout << "---------------------" << endl;

	Derived d;
	TestVir(d);

	system("pause");
	return 0;
}
#endif

// ��д����2---������������д
// ���������������麯����ֻҪ���ඨ���������������͹�����д
// �����ڼ̳���ϵ�н������������������麯��
class A
{
public:
	virtual ~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
};

class B:public A
{
public:
	/*
	���������漰����Դ����������������һ��Ҫ���麯��
	�����������������ʱ��ֻ���û�����������
	*/
	B()
	{
		pb = new int[10];
	}

	virtual ~B()
	{
		if (pb)
			delete[] pb;

		cout << "~B()" << endl;
	}
private:
	int* pb;
};

int main()
{
	A* pa = new B;

	/*
	delete����������
	1. ������������
	��Ϊpa�ǻ���A���͵�ָ�룬���Ա���������û���A����������
	�������A���������������麯��
	���������A������������
	����operator deleteֻ�ͷ���paָ��Ŀռ䣬��pb�Ŀռ�
	��������B�������10��int���͵Ŀռ䲢û���ͷţ����Ի�����ڴ�й©
	2. ����operator delete
	*/
	delete pa;

	system("pause");
	return 0;
}