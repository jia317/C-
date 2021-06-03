#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;

// 收件人列表
/*
NowCoder每天要给许多客户写电子邮件。正如你所知，如果一封邮件中包含多个收件人，收件人姓名之间会用一个逗号和空格隔开；
如果收件人姓名也包含空格或逗号，则姓名需要用双引号包含。
现在给你一组收件人姓名，请你帮他生成相应的收件人列表。

输入描述：
输入包含多组数据。

每组数据的第一行是一个整数n (1≤n≤128)，表示后面有n个姓名。

紧接着n行，每一行包含一个收件人的姓名。姓名长度不超过16个字符。

输出描述：
对应每一组输入，输出一行收件人列表。

示例
输入
3
Joe
Quan, William
Letendre,Bruce
2
Leon
Kewell
输出
Joe, "Quan, William", "Letendre,Bruce"
Leon, Kewell
*/
#if 0
int main()
{
	int n;
	while (cin >> n)
	{
		getchar(); // 注意！刷新缓冲区
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

// 养兔子
/*
一只成熟的兔子每天能产下一胎兔子。每只小兔子的成熟期是一天。 
某人领养了一只小兔子，请问第N天以后，他将会得到多少只兔子。

输入描述：
测试数据包括多组，每组一行，为整数n(1≤n≤90)。

输出描述：
对应输出第n天有几只兔子(假设没有兔子死亡现象)。
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