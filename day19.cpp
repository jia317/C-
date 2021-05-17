#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;

// 查找两个字符串a,b中的最长公共子串
void LongestComStr(string a, string b)
{
	// 以短的字符串的长度为查找的长度
	if (a.size() > b.size())
		std::swap(a, b);

	string strm; // 保存每次的最大子串
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = i; j < a.size(); j++)
		{
			// 字符串下标从0开始，所以截取子串时个数要+1
			string tmp = a.substr(i, j - i + 1);
			if (int(b.find(tmp)) < 0) 
				// 如果没找到 说明以i开始的子串在b串中不存在
				// 从i的下一个位置开始截取新的子串
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

// 汽水瓶
/*
空瓶数     可以直接换的汽水数     soda(剩余不够换汽水的空瓶数+新换的汽水的空瓶)     最终能换汽水数
  n            n / 3                      soda(n % 3 + n / 3)                    n / 3 + soda(n % 3 + n / 3)
  1              0                          1+0 --->不能换了
  2              0                          2+借一瓶 = 3
  3              1                          0+1 --->不能换了
  4              1                          1+1+借一瓶 = 3
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