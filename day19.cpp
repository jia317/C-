#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;

// ���������ַ���a,b�е�������Ӵ�
void LongestComStr(string a, string b)
{
	// �Զ̵��ַ����ĳ���Ϊ���ҵĳ���
	if (a.size() > b.size())
		std::swap(a, b);

	string strm; // ����ÿ�ε�����Ӵ�
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = i; j < a.size(); j++)
		{
			// �ַ����±��0��ʼ�����Խ�ȡ�Ӵ�ʱ����Ҫ+1
			string tmp = a.substr(i, j - i + 1);
			if (int(b.find(tmp)) < 0) 
				// ���û�ҵ� ˵����i��ʼ���Ӵ���b���в�����
				// ��i����һ��λ�ÿ�ʼ��ȡ�µ��Ӵ�
				break;

			if (tmp.size()>strm.size())
				strm = tmp;

		}
	}
	cout << strm << endl;
}
#if 0
int main()
{
	string a, b;
	while (cin >> a >> b)
	{
		LongestComStr(a, b);
	}
	system("pause");
	return 0;
}
#endif

// ��ˮƿ
/*
��ƿ��     ����ֱ�ӻ�����ˮ��     soda(ʣ�಻������ˮ�Ŀ�ƿ��+�»�����ˮ�Ŀ�ƿ)     �����ܻ���ˮ��
  n            n / 3                      soda(n % 3 + n / 3)                    n / 3 + soda(n % 3 + n / 3)
  1              0                          1+0 --->���ܻ���
  2              0                          2+��һƿ = 3
  3              1                          0+1 --->���ܻ���
  4              1                          1+1+��һƿ = 3
  5              1                          2+1 = 3                             
*/
int soda(int n)
{
	if (n == 1)
		return 0;
	if (n == 2)
		return 1;
	return n / 3 + soda(n / 3 + n % 3);
}
int main()
{
	int n;
	while (cin >> n)
	{
		if (n == 0)
			break;
		cout << soda(n) << endl;
	}

	system("pause");
	return 0;
}