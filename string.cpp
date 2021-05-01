#include<iostream>
#include<windows.h>
using namespace std;
#include<string>

#include<string.h>

#pragma warning(disable:4996)

/*
字符串构造方式
string(); // 构造一个空串
string(const string& str); // 拷贝构造
string(const string& str,size_t pos, size_t len=npos); // 用str从pos位置开始的len个字符构造
string(const char* s); // 用C字符串构造
string(const char* s,sizt_t n); // 用C串的前n个字符构造
string(size_t n,char c); // 用n个字符c构造
*/
#if 0
int main()
{
	string s1; // 构造一个空字符串 里面有一个\0
	string s2("hello"); // string(const char* s)
	string s3(10, 'a'); // string(size_t n,char c)
	string s4(s2); // 拷贝构造
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

	// length和size都是求字符串中有效元素个数的 不包含\0
	cout << s.length() << endl;
	cout << s.size() << endl;

	// 在operator[]中使用assert检测是否越界
	cout << s[13] << endl;

	// at内部采用异常机制检测是否越界 out_of_range
	cout << s.at[13] << endl;

	system("pause");
	return 0;
}
#endif 

// 遍历字符串的方式
#if 0
int main()
{
	// 法一
	string s("hello world");
	for (int i = 0; i < s.size(); ++i)
		cout << s[i] << endl;
	cout << endl;

	// 法二：
	for (auto e : s)
		cout << e;
	cout << endl;

	// 法三：
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

	// 底层空间总大小
	cout << s.capacity() << endl;

	// 检测字符串是否为空(字符串)
	// 空字符串中含有一个\0
	if (s.empty())
		cout << "空" << endl;
	else
		cout << "不空" << endl;

	// 将s中有效字符清空
	s.clear();
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	if (s.empty())
		cout << "空" << endl;
	else
		cout << "不空" << endl;


}

/*
将有效元素个数调整到newsize个 
void resize(size_t newsize, char c); 
void resize(size_t newsize);
1. newsize < oldsize
   resize(newsize);
   有效元素个数缩小到newsize个，不改变原来的capacity
2. newsize > oldsize
   推荐使用resize(newsize, char c)
   有效元素扩充到newsize个分两种情况：假设原capacity为oldcapacity
    1）newsize <= oldcapacity
	   直接将 (newsize - oldsize) 个字符c追加到原来的字符串空间后面
	2）newsize > oldcapacity
	   ① 开辟新空间
	   ② 将旧空间元素拷贝至新空间，再将(newsize - oldsize) 个字符c追加在后面
	   ③ 释放旧空间
	   ④ 更新指针指向，让其指向新空间

将底层空间容量修改到newcapacity
void reserve(size_t newcapacity)
1. newcapacity <= oldcapacity
   newcapacity > 15 ---> reserve直接忽略
   newcapacity <= 15 ---> capacity = 15
2. newcapacity > oldcapacity
   reserve有自己的扩容机制
*/
void TestString2()
{
	string s("hello world");
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	// 测试 newsize < oldsize
	s.resize(5);
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	// 测试 newsize > oldsize
	s.resize(20, '!');
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	
}

// 测试reserve扩容
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

	// 说明reserve内部有自己的扩容机制

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

// 测试string类型的大小
#if 0
void TestString()
{
	cout << sizeof(string) << endl; // 28
	/*
	注意：只是在vs中
	string类型的大小为28
	string的成员变量包括：
	一个char* 类型的指针 (4)
	记录底层空间大小的size_t capacity (4)
	记录string中有效元素个数size_t size (4)
	占16个字节的静态数组：因为要留一个字节存放\0，所以真正可以存储有效元素的大小为15，所以capacity=15

	当用户构造string对象时，如果有效字符个数<=15时，直接使用自己内部的静态数组；如果>15，才动态开辟空间
	*/

	string s("I,am,fine!fighting"); // 这是一个string类型的对象 
	/*
	const char* c_str()const;
	返回值：返回一个指向数组的指针，数组中包含一个以\0结尾的字符串
	用这个函数可以得到string对象中的字符串的地址
	*/
	char* p = (char*)s.c_str();
	strtok(p, ",!");
	while (p != NULL)
	{
		//cout << *p << endl; // 这种打印方式，只打印每个单词的首字母
		printf("%s\n", p); // 这样才能得到通过字符分割之后的每个单词
		p = strtok(NULL, ",!");
	}
}
#endif

/*
追加字符串
【 operator+= 】
string& operator+=(const string& str);
string& operator+=(const char* s);
string& operator+=(char c);

【 append 】
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
push_back一次只能加一个字符
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
用新字符串替换旧字符串
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

	s1.erase(0, 3); // 从0号位置开始，删3个字符
	cout << s1 << endl;
	s1.erase(s1.begin()); // 删除该位置的字符
	cout << s1 << endl;
}

void TestString8()
{
	string s1("jiajia");
	string s2("happy");

	//【？？？】
	/*
	C++提供的全局swap：
	*/
	swap(s1, s2);

	/* 
	string类提供的swap：
	效率高！
	*/
	s1.swap(s2);
}

// 将字符串对象转化为整型数字
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

返回值：返回查找的字符或字符串第一次出现的位置
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
获得一个子串
string substr (size_t pos = 0, size_t len = npos) const;
*/
// 截取域名
void TestString11()
{
	string s("http://www.baidu.com");
	int pos = s.find("www");
	if (pos != string::npos)
	{
		cout << s.substr(pos) << endl;
	}
}

// 有多个单词，单词之间用空格隔开，求最后一个单词的长度
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

// 输入的方式
void func()
{
	// C语言中输入字符串
	// char* gets(char* str);
	//char* str;
	//gets(str);

	// cin：遇到空格或回车就不能再输入了

	/*
	istream& getline(istream& is, string& str, char delim); // delim：输入终止符
	istream& getline(istream& is, string& str);
	*/
	string s;
	getline(cin, s, 'a');
	cout << s << endl;

	// 多行输入
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

	// C语言中比较字符串大小
	char* s3 = "abcde";
	char* s4 = "abdfe";
	if (strcmp(s3, s4) > 0)
		cout << s3 << endl;
	else
		cout << s4 << endl;
}

// 下边的代码可以看出在vs下的扩容机制：1.5倍
void TestPushBack()
{
	string s;
	s.reserve(100); // 如果知道需要多少空间可以直接预留空间，避免一边插入一边扩容提高效率
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