#include<iostream>
#include<stack>
using namespace std;

// 计算糖果
int main()
{
	int arr[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		cin >> arr[i];
	}

	int a = (arr[0] + arr[2]) >> 1;
	int b = (arr[1] + arr[3]) >> 1;
	int c = b - arr[1];

	if ((a - b == arr[0]) && (b - c == arr[1]) && (a + b == arr[2]) && (b + c) == arr[3])
		cout << a << " " << b << " " << c << endl;
	else
		cout << "No" << endl;

	return 0;
}

// 进制转换
int main()
{
	int M, N;
	cin >> M >> N;
	stack<int> st;
	while (M != 0)
	{
		st.push(M%N);
		M = M / N;	
	}
	if (!st.empty())
	{
		cout << st.top();
		st.pop();
	}

	return 0;
}