#include<iostream>
#include<Windows.h>
using namespace std;


// ��������
/*
NowCoder����һ����͵꣬��ҵ�Ŀ��˶��и���ֵ��ã�����ֻҪ����ҵ�Թ�һ����ͣ��ͻ�ÿ�춼������
���ң�����������ҵ����������ͺ󣬽�����ÿ�춼���һλ������һ����Ʒ����
���ǣ���ҵ�Ŀ��˴����һ���˷�չ�ɺƺƵ����ɰ���ǧ�ˣ�1��1��2��3��5����
���ڣ�NowCoder�������æͳ��һ�£�ĳһ��ʱ�䷶Χ�����ܹ��������ٷ���ͣ�����ÿλ����ֻ��һ����ͣ���

����������
�������ݰ������顣
ÿ�����ݰ�����������from��to(1��from��to��80)���ֱ������ĵ�from��͵�to�졣

���������
��Ӧÿһ�����룬�����from��to��Щ�������from��to���죩����Ҫ�����ٷ���͡�
*/

// ���⣺ÿ��Ŀ�������Ϊ쳲��������У����from��to���쳲��������ĺ�
#include<vector>

int main()
{
	int from, to;
	while (cin >> from >> to)
	{
		vector<long long> Fib(80); // ע�⣺����Ҫ��long long
		Fib[0] = 0;
		Fib[1] = 1;
		for (int i = 2; i <= to; i++)
		{
			Fib[i] = Fib[i - 2] + Fib[i - 1];
		}

		long long count = 0; // ע�⣺����Ҫ��long long
		for (int i = from; i <= to; i++)
		{
			count += Fib[i];
		}

		cout << count << endl;
	}
	

	system("pause");
	return 0;
}



// ��������
/*
����������
��������������ݡ�
ÿ�����ݰ��������ַ���s,t���ֱ��ǳɶԳ��ֵĻ�������С�������䲼�������ÿɼ�ASCII�ַ���ʾ�ģ�
�ɼ���ASCII�ַ��ж��ٸ��������Ļ���Ҳ�ж����ֻ�������������С�������ᳬ��1000���ַ���

���������
��Ӧÿ�����룬����ܴӻ��Ʋ��м��������С�������������һ�鶼û�У��Ǿ����0��ÿ�����ռһ�С�

ʾ����
����
abcde a3
aaaaaa aa
���
0
3
*/

// ���⣺size_t find (const string& str, size_t pos = 0) const;
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