#include<iostream>
#include<string>
#include<map>
#include<Windows.h>
using namespace std;

// �����Լ��
#if 0
int gcd(int a, int b)
{
	while (b!=0)
	{
		int temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}
// С�׵�����֮·
int main()
{
	int n, a; // nΪ�������� aΪС�׳�ʼ����ֵ
	while (cin >> n >> a)
	{
		while (n--)
		{
			int temp;
			cin >> temp;
			if (temp <= a)
				a += temp;
			else
				a += gcd(a, temp);
		}
		cout << a << endl;
	}
	system("pause");
	return 0;
}
#endif

// �ҳ��ַ����е�һ��ֻ����һ�ε��ַ�
// ��һ��
#if 0
int main()
{
	string s;
	while (getline(cin,s))
	{
		int count[256] = { 0 };
		for (int i = 0; i < s.size(); i++)
		{
			count[s[i]]++;
		}
	
		int i = 0;
		for (; i < s.size(); i++)
		{
			if (count[s[i]] == 1)
			{
				cout << s[i] << endl;
				break;
			}
		}

		if (i > s.size())
			cout << -1 << endl;
	}

	system("pause");
	return 0;
}
#endif

// ��������ϣ��
const int tableSize = 256;
int hashTable[tableSize];
int main()
{
	string s;
	while (getline(cin, s))
	{
		for (int i = 0; i < tableSize; i++)
		{
			hashTable[i] = 0;
		}

		for (int i = 0; i < s.size(); i++)
		{
			hashTable[s[i]]++;
		}

		bool flag = false;
		for (int i = 0; i < s.size(); i++)
		{
			if (hashTable[s[i]] == 1)
			{
				cout << s[i] << endl;
				flag = true;
				break;
			}
		}

		if (!flag)
			cout << -1 << endl;
	}

	system("pause");
	return 0;
}
