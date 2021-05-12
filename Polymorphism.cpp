#include<iostream>
#include<Windows.h>
#include<string>
using namespace std;

// �������麯�������Ϊ������
// �����಻��ʵ�������� ���ǿ��Զ�����������͵�ָ��
// ������һ��Ҫ���̳У��������������������Ҫ�Դ��麯��������д
#if 0
class Car
{
public:
	// ���麯�����ں���ǰ����virtual�ؼ��֣���߼���=0
	virtual void Drive() = 0;
};

class Benz :public Car
{
public:
	virtual void Drive()
	{
		cout << "Benz-����" << endl;
	}
};

class BMW :public Car
{
public:
	virtual void Drive()
	{
		cout << "BMW-����" << endl;
	}
};

void TestCar()
{
	//Car c; // �����಻��ʵ��������
	Car *pc; // ���Զ�����������͵�ָ��

	Car *pBenz = new Benz;
	pBenz->Drive();
	delete pBenz;

	Car *pBMW = new BMW;
	pBMW->Drive();
	delete pBMW;
}
int main()
{
	TestCar();

	system("pause");
	return 0;
}
#endif

/*
�����麯�����࣬���û����ʽ���幹�캯����������������Ĭ�ϵĹ��캯��
*/
// ��̬��ԭ��
#if 0
class Base
{
public:
	void Test()
	{
		cout << "Test()" << endl;
	}

	virtual void Fun1()
	{
		cout << "Base::Fun1()" << endl;
	}

	virtual void Fun2()
	{
		cout << "Base::Fun2()" << endl;
	}

	int _b;
};

/*
��������������ӵ��һ�����
�������̳л���������ֻ�ǽ���������е����ݿ���һ��
*/
class Derived:public Base
{
public:
	int _d;
};

int main()
{
	/*
	�����麯������Ĵ�С���4���ֽ�(��32λvsƽ̨��)
	�����ж����麯������ֻ��4���ֽڣ�˵�����ĸ��ֽڵ�ָ��_vfptr��ָ��һ��ռ�
	���ռ�������Ŀռ�
	����д�ŵ����麯���ĵ�ַ
	�麯���Ĵ�ų������麯�����������Ⱥ�������
	*/
	cout << sizeof(Base) << endl;

	/*
	���ڴ洰��&b���ڴ���������ǰ�ĸ��ֽڱ����
	˵�����ָ��_vfptr���ڹ��캯���б����ģ���Ϊ��������ʱ��ֻ�����˹��캯��
	*/
	Base b;

	Derived d;

	system("pause");
	return 0;
}
#endif

// �������в���д�����麯��������д�ŵ��ǻ����麯��
// ��������д�˻����麯��������д�ŵ�����������д���麯��
#if 0
class Base
{
public:
	void Test()
	{
		cout << "Test()" << endl;
	}

	virtual void Fun1()
	{
		cout << "Base::Fun1()" << endl;
	}

	virtual void Fun2()
	{
		cout << "Base::Fun2()" << endl;
	}

	virtual void Fun3()
	{
		cout << "Base::Fun3()" << endl;
	}

	int _b;
};

/*
��ʱ�������麯�����д�ŵ���
Derived::Fun1()
Base::Fun2()
Derived::Fun3()
*/
class Derived :public Base
{
public:
	virtual void Fun1() // ��д�����麯��Fun1
	{
		cout << "Derived::Fun1()" << endl;
	}

	virtual void Fun3() // ��д�����麯��Fun3
	{
		cout << "Derived::Fun1()" << endl;
	}
	int _d;
};

int main()
{
	Base b;
	Derived d;

	system("pause");
	return 0;
}
#endif

// ���������Լ����麯�������ģ�
/*
�Ӽ��Ӵ��ڿ������������������麯��
���ڴ洰�ڿ��Կ���
*/
#if 0
class Base
{
public:
	void Test()
	{
		cout << "Test()" << endl;
	}

	virtual void Fun1()
	{
		cout << "Base::Fun1()" << endl;
	}

	virtual void Fun2()
	{
		cout << "Base::Fun2()" << endl;
	}

	virtual void Fun3()
	{
		cout << "Base::Fun3()" << endl;
	}

	int _b;
};

class Derived :public Base
{
public:
	virtual void Fun1() // ��д�����麯��Fun1
	{
		cout << "Derived::Fun1()" << endl;
	}

	/*
	����������е��麯����������������д�����麯����˳���޹�
	�������������麯���������������򣬼���������
	*/
	virtual void Fun3() // ��д�����麯��Fun3
	{
		cout << "Derived::Fun3()" << endl;
	}

	virtual void Fun2() // ��д�����麯��Fun2
	{
		cout << "Derived::Fun2()" << endl;
	}

	

	virtual void Fun4() // �������Լ����麯��
	{
		cout << "Derived::Fun4()" << endl;
	}

	virtual void Fun5() // �������Լ����麯��
	{
		cout << "Derived::Fun5()" << endl;
	}

	int _d;
};

// ��λ�ȡ����ַ�� ��λ�ȡ����е�ÿһ�
/*
1. �����ַ������ַ����ֵ������ͬ�ģ�����ͨ��&�������õ������ַ
2. &�����������������* Ҫ�õ�ǰ�ĸ��ֽ���ҪǿתΪint* 
   �� *(int*)(&������) ��������ַ����������
3. Ҫ����������ת��Ϊָ������ 
   �麯��������Ϊ void (*)(void)
   typedef void (*PVFT)(void) ���麯������ȡһ��������ΪPVFT
   �ٽ���������ת��ΪPVFT���ͼ��ɻ�ȡ���麯����ַ
*/
typedef void(*PVFT)();
/*
���ִ�����typedefʱ��PVFT
typedef void(*PVFT)(); ��ʾ��void(*)()�������ָ����������һ������ ��PVFT
void(*PVFT)(); ��ʾ������һ��void(*)()�������ָ�����͵ı��� ��������PVFT
*/
void GetVFT(Base& b, const string& str)
{
	//cout << hex << *(int*)(&b) << endl; // ����һ���������֣�������ַ����ֵ��ͬ���ѣ�����������ַ

	PVFT* pvf = (PVFT*)(*(int*)(&b)); // ����ǿתΪPVFT* ����һ����ַ
	//cout << hex << pvf << endl; // ��֤ǿת֮�����ֵ��������ֵ�Ƿ���ͬ ��ͬ��˵���õ�������ַ
	// ���ˣ���ȡ������ַ��
	//*pvf = nullptr; // ����ʱ��������� ��������ݷ��ڴ���Σ���ֻ���ģ��������޸�

	cout << str << endl;
	// pvfָ��������ʼλ�ã�pvf������֮���õ��ľ����麯�����һ���麯���ĵ�ַ���������()
	// �൱�ڵ�������е�һ���麯��
	//(*pvf)();

	// ��������������麯��
	while (*pvf)
	{
		(*pvf)();
		pvf++;
	}
}

int main()
{
	/*
	ͬһ����Ĳ�ͬ������ͬһ�����
	*/
	Base b, b1;
	Derived d, d1;

	// �麯��������
	cout << typeid(&Derived::Fun4).name() << endl;

	GetVFT(b, "Base VFT:");
	GetVFT(d, "Derived VFT:");

	system("pause");
	return 0;
}
#endif

/*
�麯������ԭ��:
1. ��ȡ�����ַ��Ȼ��Ӷ���ǰ�ĸ��ֽ��õ�����ַ
2. ���ݲ���&thisָ��
3. ������л�ȡ��Ӧ�麯����ַ
4. ���ø��麯��
*/
#if 0
class Base
{
public:
	void Test()
	{
		cout << "Test()" << endl;
	}

	virtual void Fun1()
	{
		cout << "Base::Fun1()" << endl;
	}

	virtual void Fun2()
	{
		cout << "Base::Fun2()" << endl;
	}

	virtual void Fun3()
	{
		cout << "Base::Fun3()" << endl;
	}

	int _b;
};

class Derived :public Base
{
public:
	virtual void Fun1() // ��д�����麯��Fun1
	{
		cout << "Derived::Fun1()" << endl;
	}

	virtual void Fun2() // ��д�����麯��Fun2
	{
		cout << "Derived::Fun2()" << endl;
	}

	virtual void Fun3() // ��д�����麯��Fun3
	{
		cout << "Derived::Fun3()" << endl;
	}

	virtual void Fun4() // �������Լ����麯��
	{
		cout << "Derived::Fun4()" << endl;
	}

	virtual void Fun5() // �������Լ����麯��
	{
		cout << "Derived::Fun5()" << endl;
	}

	int _d;
};

/*
����ǻ���ָ�룬ָ���ܷ��ʵĿռ��Сֻ�л�����ô��
���ԣ���ʹ����ָ��ָ���������Ҳ��������������е�
*/
void TestVirtual(Base* b)
{
	b->Test();
	b->Fun1();
	b->Fun2();
	b->Fun3();
}

int main()
{
	Base b, b1;
	Derived d, d1;

	d._b = 1;
	d._d = 2;

	TestVirtual(&b);
	cout << "---------------------------" << endl;
	TestVirtual(&d);

	b = (Base)d; // ���ܻ�������ʱ����
	// (Base*)&d ���߱��������������������d���ջ������Ĳ��ַ�ʽ���н���
	// ����������ʱ����
	Base* pb = (Base*)&d; 
	pb->Fun1(); // �����������麯��


	system("pause");
	return 0;
}
#endif

// ���ຬ���麯���Ķ�̳��µĶ���ģ��
// ������̳м������࣬���м�������������������麯��������ڵ�һ���̳е���������
// ���ò�ͬ�Ļ����е��麯����Ҫ�ò�ͬ�Ļ���ָ�������ȥ����
/*
B1�Ķ���ģ��:
                  B1�����
B1�����ָ��----->B1::fun1()
_b1               B1::fun2()
*/
#if 0
class B1
{
public:
	virtual void fun1()
	{
		cout << "B1::fun1()" << endl;
	}

	virtual void fun2()
	{
		cout << "B1::fun2()" << endl;
	}

	int _b1;
};

/*
B2�Ķ���ģ��:
                  B2�����
B2�����ָ��----->B2::fun3()
                  B2::fun4()
	_b2
*/
class B2
{
public:
	virtual void fun3()
	{
		cout << "B2::fun3()" << endl;
	}

	virtual void fun4()
	{
		cout << "B2::fun4()" << endl;
	}

	int _b2;
};

/*
D�Ķ���ģ��:
                             D�����
��B1�̳����������ָ��----->B1::fun1()
                            D::fun2()
							D::fun5()
		_b1
��B2�̳����������ָ��----->B2::fun3()
                            D::fun4()
        _b2
		_d
*/
class D :public B1, public B2
{
public:
	virtual void fun2()
	{
		cout << "D::fun3()" << endl;
	}

	virtual void fun4()
	{
		cout << "D::fun4()" << endl;
	}

	virtual void fun5()
	{
		cout << "D::fun5()" << endl;
	}

	int _d;
};

typedef void(*PVFT)();
// ����B1�е��麯��Ҫ�û���B1���͵�ָ�����
void TestVirtual1(B1& b, const string& str)
{
	cout << str << endl;

	PVFT* pvf = (PVFT*)(*(int*)&b);
	while (*pvf)
	{
		(*pvf)();
		pvf++;
	}
}

// ����B2�е��麯��Ҫ�û���B2���͵�ָ�����
void TestVirtual2(B2& b, const string& str)
{
	cout << str << endl;
	
	PVFT* pvf = (PVFT*)(*(int*)&b);
	while (*pvf)
	{
		(*pvf)();
		pvf++;
	}
}

int main()
{
	D d;
	d._b1 = 1;
	d._b2 = 2;
	d._d = 3;

	TestVirtual1(d, "B1��VFT��");
	cout << "----------------------" << endl;
	TestVirtual2(d, "B2��VFT��");


	system("pause");
	return 0;
}
#endif

// ��
#if 0
class A{
public:
	A(char *s) 
	{ 
		cout << s << endl; 
	}
	~A(){}
};
class B :virtual public A 
{
public:
	B(char *s1, char*s2) 
		:A(s1) 
	{ 
		cout << s2 << endl; 
	}
};
class C :virtual public A 
{
public:
	C(char *s1, char*s2) 
		:A(s1) 
	{ 
		cout << s2 << endl;
	}
};
class D :public B, public C {
public:
	D(char *s1, char *s2, char *s3, char *s4)
		:B(s1, s2)
		, C(s1, s3)
		, A(s1)
	{
		cout << s4 << endl;
	}
};

int main() {
	/*
	���մ�ӡ���Ϊclass A class B class C class D
	���캯�����ô���
	Ҫ�ȵ��û��๹�캯����ɶԻ����г�Ա�ĳ�ʼ��
	D�ȼ̳�B����B�̳���A�������ȵ���A�Ĺ��캯�����ٵ���B�Ĺ��캯��
	Ȼ��D�̳�C���ٵ���C�Ĺ��캯��
	������D�Լ��Ĺ��캯��
	*/
	D *p = new D("class A", "class B", "class C", "class D");
	delete p;

	system("pause");
	return 0;
}
#endif

// ��2
#if 0
class Base1 
{ 
public: 
	int _b1; 
};
class Base2 
{ 
public: 
	int _b2;
};
class Derive : public Base1, public Base2 
{ 
public: 
	int _d; 
};
/*
���������d�Ķ���ģ��
Base1
Base2
_d
*/
int main(){
	Derive d;
	Base1* p1 = &d; // p1ָ�����dģ���л���Base1��λ�ã�ֻ�ܷ���Base1���ʹ�С�Ŀռ䣬��ֻ�ܷ���Base1���г�Ա
	Base2* p2 = &d; // p2ָ�����dģ���л���Base2��λ�ã�ֻ�ܷ���Base2���ʹ�С�Ŀռ䣬��ֻ�ܷ���Base2���г�Ա
	Derive* p3 = &d; // ָ�����d����ʼλ��
	// ����p1 = p3 != p2

	return 0;
}
#endif

// ��3
#if 0
class A {
public:
	virtual void func(int val = 1)
	{ 
		std::cout << "A->" << val << std::endl;
	}

	virtual void test()
	{ 
		/*
		�麯��fun�ĵ��ù���
		1. �Ӷ���ǰ�ĸ��ֽ���ȡ����ַ
		2. ���Σ�
		       val����1 ���ڱ����ڼ�����A���е�Ĭ��ֵ���������յ����Ǹ��ݵ��ö��������������ĸ�����麯��
			   ����this
		3. �������ȡ�麯����ַ
		4. ���е���
		*/
		func(); 
	}
};
class B : public A {
public:
	void func(int val = 0)
	{ 
		std::cout << "B->" << val << std::endl; 
	}
};

int main(int argc, char* argv[])
{
	B*p = new B;
	p->test(); // ��ӡ���ΪB->1

	system("pause");
	return 0;
}
#endif

/*
��̬��̬���ڱ���ʱ�;���������Ϊ���������ĸ�����
���ֵ��͵ľ�̬��̬��
1. ��������
2. ģ��
*/


