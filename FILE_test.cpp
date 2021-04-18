#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)
#pragma warning(disable:4806)
using namespace std;


#if 0
int main()
{
	int a = 10000;
	FILE* pf = fopen("test.txt", "wb");
	fwrite(&a, 4, 1, pf);
	fclose(pf);
	pf = NULL;
	return 0;
}
#endif

#if 0
int main()
{
	FILE* pf = fopen("Example.txt", "w");
	if (pf != NULL)
	{
		fputs("fopen example", pf);
		fclose(pf);
	}
	return 0;
}
#endif

#if 0
int main()
{
	FILE* pf = fopen("example.txt", "wb");
	fputs("Hello C++", pf);
	fseek(pf, 7, SEEK_SET);
	fputs("Fine", pf);
	fclose(pf);
	return 0;
}
#endif

#if 0
int main()
{
	FILE* pf;
	long size;

	pf = fopen("myfile.txt", "w");
	fputs("hhhhhhhhhh", pf);
	if (pf == NULL) perror("open file failed");
	else
	{
		fseek(pf, 0, SEEK_END);
		size = ftell(pf);
		fclose(pf);
		printf("Size of myfile.txt:%ld bytes.\n", size);
	}
	system("pause");
	return 0;
}
#endif

#if 0
int main()
{
	int n;
	FILE* pf;
	char buf[27];
	long size;

	pf = fopen("myfile.txt", "w+");
	for (n = 'A'; n <= 'Z'; n++)
	{
		fputc(n, pf);
	}
	rewind(pf); // 让文件指针回到文件起始位置
	fread(buf, 1, 26, pf);
	buf[26] = '\0'; // 
	puts(buf);
	
	rewind(pf);
	fseek(pf, 0, SEEK_END);
	size = ftell(pf);
	fclose(pf);
	printf("%ld\n", size);
	
	system("pause");
	return 0;
}
#endif

#if 0
// 判断文本文件是否读取结束
int main(void)
{
	FILE* fp = fopen("myfile.txt", "r");
	if (!fp)
	{
		perror("open failed\n");
		return EXIT_FAILURE;
	}
	
	while (c != EOF)
	{
		putchar(c);
	}

	if (ferror(fp))
		puts("I/O error when reading\n");
	else if (feof(fp))
		puts("End of file reached successfully\n");

	fclose(fp);
	system("pause");
	return 0;
}
#endif

#if 0
// 判断二进制文件是否读取结束

int main(void)
{
	double a[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	double b = 0.0;
	size_t ret_code = 0;
	FILE *fp = fopen("test.bin", "wb"); // 必须用二进制模式
	fwrite(a, sizeof(*a), 5, fp); // 写 double 的数组
	fclose(fp);

	fp = fopen("test.bin", "rb");
	// 读 double 的数组
	while ((ret_code = fread(&b, sizeof(double), 1, fp)) >= 1)
	{
		printf("%lf\n", b);
	}
	if (feof(fp))
		printf("Error reading test.bin: unexpected end of file\n");
	else if (ferror(fp)) {
		perror("Error reading test.bin");
	}
	fclose(fp);
	fp = NULL;

	system("pause");
}
#endif

#if 0
int main()
{
	FILE *fp;
	char c;

	fp = fopen("fgetcTest.txt", "w");
	if (fp!=NULL)
	{
		/*for (c = 'A'; c <= 'Z'; c++)
		{
			fputc(c, fp);
		}*/
		fputs("abcde", fp);
		fclose(fp);
	}
	system("pause");
	return 0;
}
#endif

#if 0
// 将整型变量转化成字符串格式
// _itoa()
// sprintf()
int main()
{
	int n = 123456789;
	char s1[32];
	_itoa(n, s1, 10);
	cout << s1 << endl;

	char s2[32];
	sprintf(s2, "%d", n);
	cout << s2 << endl;

	char s3[32];
	sprintf(s3, "%f", n);
	cout << s3 << endl;

	system("pause");
	return 0;
}
#endif

// stringstream的使用
#include <sstream>
#if 0
// 1.将数值类型数据转化成字符串
int main()
{
	int a = 12345678;
	string sa;

	// 将一个整型变量转化为字符串，存储到string类对象中
	stringstream s;
	s << a;
	s >> sa;

	// 将stringstream底层管理string对象设置成""
	// 否则多次转换时，会将结果全部累积在底层string对象中
	s.clear(); 	// 相当于s.str("");
	double d = 12.34;
	s << d;
	s >> sa;

	string sValue;
	sValue = s.str(); // str()方法：返回stringstream中管理的string类型
	cout << sValue << endl;

	system("pause");
	return 0;
}
#endif

// 2. 字符串拼接
int main()
{
	stringstream sstream;
	sstream << "jiajia" << " " << "fighting!";
	sstream << "chong!";
	cout << sstream.str() << endl;

	sstream.str("");
	sstream << "third";
	cout << "After clear:" << sstream.str() << endl;

	system("pause");
	return 0;
}
