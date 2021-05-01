#include<iostream>
#include<Windows.h>
using namespace std;
#pragma warning(disable:4996)


// �����ʵ��һ����ͳ�棩
/*
�±ߴ����ȱ�ݣ������ظ��ȸ�
*/
#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (str == nullptr)
			str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);

#if 0
		if (str != nullptr)
		{
			_str = new char[strlen(str) + 1];
			strcpy(_str, str); // ��������\0
		}
		else // �������Ϊnullptr ���䵱�ɿ��ַ�������
		{
			// ����д��������string����ʱ�õ���new�����������ͷ�ʱҪ��delete
			// ʵ������������
			_str = new char;
			*_str = '\0';
		}
#endif		
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
			
	}

	/*
	������Ĭ�����ɵĿ������캯����ǳ����
	ǳ��������������ָ��ͬһ��ռ�
	ǳ�������ͷ���Դʱ���Ὣͬһ��ռ��ͷ����ε��³������
	���ԣ��漰����Դ����Ҫ��ʽ���忽�����캯��
	����������������ӵ��һ��ռ�
	*/
	String(const String& s)
		:_str(new char[strlen(s._str)+1])
	{ 
		strcpy(_str, s._str);
	}

	/*
	������Ĭ�����ɵĸ�ֵ��������ش����������⣺
	һ��ǳ���������Ǳ���ֵ����ԭ���Ŀռ䱻���ǣ�����û���ͷţ������ڴ�й©
	��ֵ���������ͬ��������һ�����漰����Դ����һ��Ҫ��ʽ����
	ע�⣺�������ֵ�ռ� < ��ֵ����ռ� ��ôstrcpy�����
	      ���ԣ��ȿ���һ�κ͸�ֵ����ռ�һ�������ʱ�ռ䣬Ȼ�󽫸�ֵ�����е����ݿ�������ʱ�ռ�
		  Ȼ���ͷŸ�ֵ����ľɿռ䣬����ָ��ָ����ʱ�ռ�
	*/
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* temp = new char[strlen(s._str) + 1];
			strcpy(temp, s._str);
			delete[] _str;
			_str = temp;
		}
		return *this;
	}


private:
	char* _str;
};

void Test1()
{
	String s1;
	String s2("jiajia");
	String s3(s2);

	String s4 = s2; // ���ÿ�������

	// ��һ���Ѵ��ڵĶ������һ���Ѵ��ڵĶ���ֵ�ŵ��ø�ֵ���������
	String s5("haha");
	s1 = s5;
}
#endif

// �����ʵ�ֶ�(�ִ���)
// ��ϻ�ͼ�����Test2() Test3() Test4()
#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (str == nullptr)
			str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);		
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}

	}

	/* 
	�ÿ������������д��ʼ���б�������
	Test2��Test3��Test2û���⣬����Test3�ͷ���Դ�������
	*/
	String(const String& s)
		:_str(nullptr)
	{
		// �ù��캯������һ����ʱ����
		String sTemp(s._str);
		// ����thisָ��ָ������_str����ʱ�����_str�ĵ�ַ
		std::swap(_str,sTemp._str);
	}


	// ��Ϊ��ֵʱ���Լ����Լ���ֵ��������٣����Բ�����������
	/*
	����д�������ƣ������ʹ���˴�ֵ�������ʱ����
	����ʱ�����󴫲�Ҫ���ÿ������캯���ȴ���һ����ʱ����
	����ʱ������_str��thisָ��ָ������_str�ĵ�ַ����
	��ʱ�����ں���ִ����Ҫ���٣���������������������ֵ����ԭ���Ŀռ��ͷŵ�
	*/
	String& operator=(String s)
	{
		std::swap(_str, s._str);
		return *this;
	}
	
	// ���������Ȼ�ظ��ȸ�
	/*String& operator=(const String& s)
	{
		if (this != &s)
		{
			String sTemp(s._str);
			swap(_str, sTemp._str);
		}
		return *this;
	}*/


private:
	char* _str;
};

/*
Test2�е���û�г�ʼ���б�Ŀ������캯�������յ�����������û������
*/
void Test2()
{
	String s1("hello");
	String s2(s1);
}

// Test3�е���û�г�ʼ���б�Ŀ������캯�������յ�����������������ж�
String Test3()
{
	String s1("sad");
	return s1;
}

void Test4()
{
	String s1("sad");
	String s2("happy");
	s1 = s2;
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();

	system("pause");
	return 0;
}
#endif

