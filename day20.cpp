#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;

// �ַ�����ת
void ReverseStr(string s)
{
	auto it = s.rbegin();
	while (it != s.rend())
	{
		cout << *it;
		++it;
	}
	cout << endl;
}

int main()
{
	string str;
	while (cin >> str)
	{
		ReverseStr(str);
	}

	system("pause");
	return 0;
}

// �����ִ�����
int getCommonStrLength(string s1, string s2)
{
	// 1.�Ƚ������ַ�����ת��ȫ��Сд�ĵ��ַ���
	for (int i = 0; i < s1.size(); i++)
	{
		if (s1[i] >= 'A' && s1[i] <= 'Z')
			s1[i] += 'a' - 'A';
	}

	for (int i = 0; i < s2.size(); i++)
	{
		if (s2[i] >= 'A' && s2[i] <= 'Z')
			s2[i] += 'a' - 'A';
	}

	// 2.�ý϶̵Ĵ��ڽϳ�����ƥ�䣬�ӽ϶̴������ʼ���Ҳ�����--
	if (s1.size() > s2.size())
		swap(s1, s2);

	string strm;
	for (int i = 0; i < s1.size(); i++)
	{
		for (int j = i; j < s1.size(); j++)
		{
			string tmp = s1.substr(i, j - i + 1);
			if (int(s2.find(tmp)) < 0)
				break;
			if (tmp.size() > strm.size())
				strm = tmp;
		}
	}
	return strm.size();
}
int main()
{
	string s1, s2;
	while (cin >> s1 >> s2)
	{
		cout << getCommonStrLength(s1, s2) << endl;
	}
	return 0;
}