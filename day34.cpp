#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;

// �ռ����б�
/*
NowCoderÿ��Ҫ�����ͻ�д�����ʼ�����������֪�����һ���ʼ��а�������ռ��ˣ��ռ�������֮�����һ�����źͿո������
����ռ�������Ҳ�����ո�򶺺ţ���������Ҫ��˫���Ű�����
���ڸ���һ���ռ����������������������Ӧ���ռ����б�

����������
��������������ݡ�

ÿ�����ݵĵ�һ����һ������n (1��n��128)����ʾ������n��������

������n�У�ÿһ�а���һ���ռ��˵��������������Ȳ�����16���ַ���

���������
��Ӧÿһ�����룬���һ���ռ����б�

ʾ��
����
3
Joe
Quan, William
Letendre,Bruce
2
Leon
Kewell
���
Joe, "Quan, William", "Letendre,Bruce"
Leon, Kewell
*/
#if 0
int main()
{
	int n;
	while (cin >> n)
	{
		getchar(); // ע�⣡ˢ�»�����
		while (n--)
		{
			string str;
			getline(cin, str);
			if (str.find(',') != -1 || str.find(' ') != -1)
			{
				str.insert(str.begin(), '"');
				str.insert(str.end(), '"');
			}
			if (n == 0)
				cout << str << endl;
			else
				cout << str << ", ";
		}
	}
	return 0;
}
#endif

// ������
/*
һֻ���������ÿ���ܲ���һ̥���ӡ�ÿֻС���ӵĳ�������һ�졣 
ĳ��������һֻС���ӣ����ʵ�N���Ժ�������õ�����ֻ���ӡ�

����������
�������ݰ������飬ÿ��һ�У�Ϊ����n(1��n��90)��

���������
��Ӧ�����n���м�ֻ����(����û��������������)��
*/
#include<vector>
int main()
{
	vector<long> v(91, 1);
	for (int i = 2; i<91; i++)
	{
		v[i] = v[i - 2] + v[i - 1];
	}
	int n;
	while (cin >> n)
		cout << v[n] << endl;

	system("pause");
	return 0;
}