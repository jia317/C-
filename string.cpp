#include<iostream>
#include<windows.h>
using namespace std;
#include<string>

#include<string.h>

#pragma warning(disable:4996)

/*
�ַ������췽ʽ
string(); // ����һ���մ�
string(const string& str); // ��������
string(const string& str,size_t pos, size_t len=npos); // ��str��posλ�ÿ�ʼ��len���ַ�����
string(const char* s); // ��C�ַ�������
string(const char* s,sizt_t n); // ��C����ǰn���ַ�����
string(size_t n,char c); // ��n���ַ�c����
*/
#if 0
int main()
{
	string s1; // ����һ�����ַ��� ������һ��\0
	string s2("hello"); // string(const char* s)
	string s3(10, 'a'); // string(size_t n,char c)
	string s4(s2); // ��������
	string s5(s2, 0, 3); // string(const string& str,size_t pos, size_t len=npos)
	string s6("world", 4); // string(const char* s,sizt_t n)

	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << s4 << endl;
	cout << s5 << endl;
	cout << s6 << endl;

	system("pause");
	return 0;
}
#endif

#if 0
int main()
{
	string s("hello world");
	cout << s[0] << endl;
	s[0] = 'H';
	cout << s << endl;

	// length��size�������ַ�������ЧԪ�ظ����� ������\0
	cout << s.length() << endl;
	cout << s.size() << endl;

	// ��operator[]��ʹ��assert����Ƿ�Խ��
	cout << s[13] << endl;

	// at�ڲ������쳣���Ƽ���Ƿ�Խ�� out_of_range
	cout << s.at[13] << endl;

	system("pause");
	return 0;
}
#endif 

// �����ַ����ķ�ʽ
#if 0
int main()
{
	// ��һ
	string s("hello world");
	for (int i = 0; i < s.size(); ++i)
		cout << s[i] << endl;
	cout << endl;

	// ������
	for (auto e : s)
		cout << e;
	cout << endl;

	// ������
	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << endl;
		++it;
	}
	cout << endl;

	system("pause");
	return 0;
}
#endif

void TestString1()
{
	string s("jiajia fighting");
	cout << s.size() << endl;
	cout << s.length() << endl;

	// �ײ�ռ��ܴ�С
	cout << s.capacity() << endl;

	// ����ַ����Ƿ�Ϊ��(�ַ���)
	// ���ַ����к���һ��\0
	if (s.empty())
		cout << "��" << endl;
	else
		cout << "����" << endl;

	// ��s����Ч�ַ����
	s.clear();
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	if (s.empty())
		cout << "��" << endl;
	else
		cout << "����" << endl;


}

/*
����ЧԪ�ظ���������newsize�� 
void resize(size_t newsize, char c); 
void resize(size_t newsize);
1. newsize < oldsize
   resize(newsize);
   ��ЧԪ�ظ�����С��newsize�������ı�ԭ����capacity
2. newsize > oldsize
   �Ƽ�ʹ��resize(newsize, char c)
   ��ЧԪ�����䵽newsize�����������������ԭcapacityΪoldcapacity
    1��newsize <= oldcapacity
	   ֱ�ӽ� (newsize - oldsize) ���ַ�c׷�ӵ�ԭ�����ַ����ռ����
	2��newsize > oldcapacity
	   �� �����¿ռ�
	   �� ���ɿռ�Ԫ�ؿ������¿ռ䣬�ٽ�(newsize - oldsize) ���ַ�c׷���ں���
	   �� �ͷžɿռ�
	   �� ����ָ��ָ������ָ���¿ռ�

���ײ�ռ������޸ĵ�newcapacity
void reserve(size_t newcapacity)
1. newcapacity <= oldcapacity
   newcapacity > 15 ---> reserveֱ�Ӻ���
   newcapacity <= 15 ---> capacity = 15
2. newcapacity > oldcapacity
   reserve���Լ������ݻ���
*/
void TestString2()
{
	string s("hello world");
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	// ���� newsize < oldsize
	s.resize(5);
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	// ���� newsize > oldsize
	s.resize(20, '!');
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	
}

// ����reserve����
void TestString3()
{
	string s("hello");
	cout << s.size() << endl;
	cout << s.capacity() << endl; // 15

	s.reserve(10);
	cout << s.size() << endl;
	cout << s.capacity() << endl; // 15

	s.reserve(20);
	cout << s.size() << endl;
	cout << s.capacity() << endl; // 31

	s.reserve(50);
	cout << s.size() << endl;
	cout << s.capacity() << endl; // 63

	// ˵��reserve�ڲ����Լ������ݻ���

	s.reserve(30);
	cout << s.size() << endl;
	cout << s.capacity() << endl; // 63

	s.reserve(20);
	cout << s.size() << endl;
	cout << s.capacity() << endl; // 63

	s.reserve(31);
	cout << s.size() << endl;
	cout << s.capacity() << endl; // 63

	s.reserve(10);
	cout << s.size() << endl;
	cout << s.capacity() << endl; // 15
}

// ����string���͵Ĵ�С
#if 0
void TestString()
{
	cout << sizeof(string) << endl; // 28
	/*
	ע�⣺ֻ����vs��
	string���͵Ĵ�СΪ28
	string�ĳ�Ա����������
	һ��char* ���͵�ָ�� (4)
	��¼�ײ�ռ��С��size_t capacity (4)
	��¼string����ЧԪ�ظ���size_t size (4)
	ռ16���ֽڵľ�̬���飺��ΪҪ��һ���ֽڴ��\0�������������Դ洢��ЧԪ�صĴ�СΪ15������capacity=15

	���û�����string����ʱ�������Ч�ַ�����<=15ʱ��ֱ��ʹ���Լ��ڲ��ľ�̬���飻���>15���Ŷ�̬���ٿռ�
	*/

	string s("I,am,fine!fighting"); // ����һ��string���͵Ķ��� 
	/*
	const char* c_str()const;
	����ֵ������һ��ָ�������ָ�룬�����а���һ����\0��β���ַ���
	������������Եõ�string�����е��ַ����ĵ�ַ
	*/
	char* p = (char*)s.c_str();
	strtok(p, ",!");
	while (p != NULL)
	{
		//cout << *p << endl; // ���ִ�ӡ��ʽ��ֻ��ӡÿ�����ʵ�����ĸ
		printf("%s\n", p); // �������ܵõ�ͨ���ַ��ָ�֮���ÿ������
		p = strtok(NULL, ",!");
	}
}
#endif

/*
׷���ַ���
�� operator+= ��
string& operator+=(const string& str);
string& operator+=(const char* s);
string& operator+=(char c);

�� append ��
string& append(const string& s);
string& append(const string& s, size_t subpos, size_t sublen);

string& append(const char* s);
string& append(const char* s, size_t n);

string& append(size_t n, char c);

template <class InputIterator>
string& append (InputIterator first, InputIterator last);
*/
void TestString4()
{
	string s1("The");
	string s2(" weather");
	s1 += s2;
	s1 += " is pretty good";
	s1 += '!';
	cout << s1 << endl;

	string s3("I");
	string s4(" am");
	string s5(" hhh");
	s3.append(s4);
	s3.append(s5, 0, 1);
	s3.append(" so");
	s3.append(" lonely", 6);
	s3.append(1, 'y');
	cout << s3 << endl;

	string s6("say");
	string s7("hello");
	s6.append(s7.begin()+2, s7.end()-1);
	cout << s6 << endl;
}

/*
push_backһ��ֻ�ܼ�һ���ַ�
void push_back(char c);
*/
void TestString5()
{
	string s("Yes");
	s.push_back('I');
	s.push_back('d');
	s.push_back('o');
	cout << s << endl;
}

/*
�����ַ����滻���ַ���
string& assign(const string& str);
string& assign(const string& str, size_t subpos, size_t sublen);

string& assign(const char* str);
string& assign(const char* str, size_t n);

string& assign(size_t n, char c);

template <class InputIterator>
string& assign (InputIterator first, InputIterator last);
*/
void TestString6()
{
	string s1("hello");
	string s2("bye");
	s1.assign(s2);
	cout << s1 << endl;
	s2.assign(s2, 2, 2);
	cout << s2 << endl;
	s2.assign("just soso");
	cout << s2 << endl;
	s2.assign("okdokey", 2);
	cout << s2 << endl;
	s2.assign(10, 'a');
	cout << s2 << endl;
	string s("abcdefg");
	s1.assign(s.begin() + 2, s.end() - 1);
	cout << s1 << endl;
}

void TestString7()
{
	string s1("want");
	string s2("you");
	s1.insert(4, s2);
	cout << s1 << endl;

	size_t pos = s2.find('o');
	if (pos != string::npos)
	{
		s2.insert(pos, "home");
	}
	cout << s2 << endl; // yhomeou

	s1.erase(0, 3); // ��0��λ�ÿ�ʼ��ɾ3���ַ�
	cout << s1 << endl;
	s1.erase(s1.begin()); // ɾ����λ�õ��ַ�
	cout << s1 << endl;
}

void TestString8()
{
	string s1("jiajia");
	string s2("happy");

	//����������
	/*
	C++�ṩ��ȫ��swap��
	*/
	swap(s1, s2);

	/* 
	string���ṩ��swap��
	Ч�ʸߣ�
	*/
	s1.swap(s2);
}

// ���ַ�������ת��Ϊ��������
void TestString9()
{
	string s("1234");
	int value = atoi(s.c_str());
	cout << value << endl;
}

/*
size_t find(const string& str, size_t pos = 0)const;
size_t find(const char* s, size_t pos = 0)const;
size_t find(const char* s, size_t pos, size_t n)const;
size_t find(char c, size_t pos = 0)const;

����ֵ�����ز��ҵ��ַ����ַ�����һ�γ��ֵ�λ��
*/
void TestString10()
{
	string s1("abcdefgh");
	string s2("def");
	cout << s1.find(s2) << endl; // 3
	cout << s2.find('e') << endl; // 1
	cout << s1.find("bcd") << endl; // 1
}

/*
���һ���Ӵ�
string substr (size_t pos = 0, size_t len = npos) const;
*/
// ��ȡ����
void TestString11()
{
	string s("http://www.baidu.com");
	int pos = s.find("www");
	if (pos != string::npos)
	{
		cout << s.substr(pos) << endl;
	}
}

// �ж�����ʣ�����֮���ÿո�����������һ�����ʵĳ���
void getLastLength()
{
	string s;
	getline(cin, s);
	int pos = s.rfind(' ');
	if (pos != string::npos)
	{
		string temp = s.substr(pos+1);
		cout << temp << endl;
		cout << temp.size() << endl;
	}
}

// ����ķ�ʽ
void func()
{
	// C�����������ַ���
	// char* gets(char* str);
	//char* str;
	//gets(str);

	// cin�������ո��س��Ͳ�����������

	/*
	istream& getline(istream& is, string& str, char delim); // delim��������ֹ��
	istream& getline(istream& is, string& str);
	*/
	string s;
	getline(cin, s, 'a');
	cout << s << endl;

	// ��������
	while (getline(cin, s))
	{
		//...
	}

}

void TestString12()
{
	string s1("abcde");
	string s2("abcdf");
	if (s1 > s2)
		cout << s1 << endl;
	else
		cout << s2 << endl;

	// C�����бȽ��ַ�����С
	char* s3 = "abcde";
	char* s4 = "abdfe";
	if (strcmp(s3, s4) > 0)
		cout << s3 << endl;
	else
		cout << s4 << endl;
}

// �±ߵĴ�����Կ�����vs�µ����ݻ��ƣ�1.5��
void TestPushBack()
{
	string s;
	s.reserve(100); // ���֪����Ҫ���ٿռ����ֱ��Ԥ���ռ䣬����һ�߲���һ���������Ч��
	size_t sz = s.capacity();
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed:" << sz << endl;
		}
	}
}
int main()
{
	//TestString1();
	//TestString2();
	//TestString3();

	//TestString();

	//TestString4();
	//TestString5();
	//TestString6();
	//TestString7();
	TestString8();
	//TestString9();
	//TestString10();
	//TestString11();
	
	//getLastLength();

	//func();

	//TestString12();

	//TestPushBack();

	system("pause");
	return 0;
}