#include<iostream>
#include<Windows.h>
using namespace std;


// 客似云来
/*
NowCoder开了一家早餐店，这家店的客人都有个奇怪的癖好：他们只要来这家店吃过一次早餐，就会每天都过来；
并且，所有人在这家店吃了两天早餐后，接下来每天都会带一位新朋友一起来品尝。
于是，这家店的客人从最初一个人发展成浩浩荡荡成百上千人：1、1、2、3、5……
现在，NowCoder想请你帮忙统计一下，某一段时间范围那他总共卖出多少份早餐（假设每位客人只吃一份早餐）。

输入描述：
测试数据包括多组。
每组数据包含两个整数from和to(1≤from≤to≤80)，分别代表开店的第from天和第to天。

输出描述：
对应每一组输入，输出从from到to这些天里（包含from和to两天），需要做多少份早餐。
*/

// 解题：每天的客人数量为斐波那契数列，求从from到to天的斐波那契数的和
#include<vector>

int main()
{
	int from, to;
	while (cin >> from >> to)
	{
		vector<long long> Fib(80); // 注意：这里要用long long
		Fib[0] = 0;
		Fib[1] = 1;
		for (int i = 2; i <= to; i++)
		{
			Fib[i] = Fib[i - 2] + Fib[i - 1];
		}

		long long count = 0; // 注意：这里要用long long
		for (int i = from; i <= to; i++)
		{
			count += Fib[i];
		}

		cout << count << endl;
	}
	

	system("pause");
	return 0;
}



// 剪花布条
/*
输入描述：
输入包含多组数据。
每组数据包含两个字符串s,t，分别是成对出现的花布条和小饰条，其布条都是用可见ASCII字符表示的，
可见的ASCII字符有多少个，布条的花纹也有多少种花样。花纹条和小饰条不会超过1000个字符长

输出描述：
对应每组输入，输出能从花纹布中剪出的最多小饰条个数，如果一块都没有，那就输出0，每个结果占一行。

示例：
输入
abcde a3
aaaaaa aa
输出
0
3
*/

// 解题：size_t find (const string& str, size_t pos = 0) const;
#include<string>

//int main()
//{
//	string str, s;
//	while (cin >> str >> s)
//	{
//		int count = 0;
//		size_t pos = 0;
//		while ((pos = str.find(s, pos)) != string::npos)
//		{
//			count++;
//			pos += s.size();
//		}
//		cout << count << endl;
//	}
//
//	system("pause");
//	return 0;
//}