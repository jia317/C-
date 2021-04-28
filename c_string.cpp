#include<iostream>
using namespace std;

#include<cstring>
#pragma warning(disable:4996)

/*
C语言中的字符串函数: #include<cstring>

返回C字符串长度(有效字符个数不包含\0)
size_t strlen(const char* str);

将source中的字符串(包括\0)拷贝到destination中，返回destination
char* strcpy(char* destnation, const char* source);

将source字符串的一份拷贝追加到destination指向的空间中
指向destination数组的指针，该数组应该包含一个C字符串，要有足够大的空间
destination中的\0会被source字符串的第一个字符覆盖
source字符串的拷贝包括\0
char * strcat ( char * destination, const char * source );

一个一个比较str1和str2中的字符大小，直到两个字符串中出现了不一样的字符或者一个字符串结束了
返回值：
< 0：第一个不匹配的字符在str1中的值小于str2中的值
> 0：第一个不匹配的字符在str1中的值大于str2中的值
= 0: 两个字符串内容相等
int strcmp ( const char * str1, const char * str2 );

将source串中前num个字符拷贝到destination中
如果在复制num个字符前source已经到了末尾，不足的填充0
如果source大于num，那么destination不是以\0结束的
char * strncpy ( char * destination, const char * source, size_t num );

将source前num个字符追加到destination，再加上\0
如果source中C字符串的长度小于num，则仅复制到source结束
char * strncat ( char * destination, const char * source, size_t num );

匹配到第一个不同字符 或者比较到num 比较到达\0
返回值与strcmp完全相同
int strncmp ( const char * str1, const char * str2, size_t num );

返回str2在str1中出现的位置
如果str1中有str2，返回str2在str1中位置；否则返回空指针
const char * strstr ( const char * str1, const char * str2 );
char * strstr ( char * str1, const char * str2 );

用delimiters截断str
char * strtok ( char * str, const char * delimiters );
*/

#if 0
int main()
{
	// 【strlen的使用】
	char* str = "happy birthday"; // str中存放的是字符串第一个字符的地址
	cout << strlen(str) << endl; // 14

	char str1[] = "happy birthday"; // 保存了组成字符串的所有字符(包括\0)，每个字符是数组中的一个元素
	char str2[40];
	char str3[40];
	strcpy(str2, str1);
	cout << str2;
	strcpy(str3, "jia");
	cout << str3 << endl;

	// 【strcat例子】
	char str1[10] = { 'j', 'i', 'a' }; // 字符数组
	char* str2[] = { "happy", "sad" }; // 字符指针数组，数组中每个元素都是一个指向字符类型数据的指针，指针中保存的是第一个字符的地址
	char* str3 = "fighting"; // 创建一个指向字符串的指针变量str3
	
	cout << str2 + 1 << endl; // s的地址
	cout << *(str2 + 1) << endl; // sad
	cout << *str2 + 1 << endl; // appy
	
	cout << str3 + 1 << endl; // ighting
	cout << *(str3 + 1) << endl; // i
	cout << *str3 << endl; // f-》ASCII码为102 
	cout << *str3 + 1 << endl; // 103

	cout << strcat(str1, str3) << endl; // 必须保证destination有足够大的空间

	// 【strcmp例子】
	char* str1 = "happy";
	char* str2 = "happya";
	cout << strcmp(str1, str2) << endl; // -1 

	char* str3 = "abcd";
	char* str4 = "abbb"; 
	// 第一个不匹配字符为c -> c > b -> 大于0
	cout << strcmp(str3, str4) << endl; // 1

	// 【strncpy例子】
	char str1[20];
	char* str2 = "fighting";
	char str3[20];
	cout << strncpy(str1, str2, 15) << endl; // source只有9个，剩下的6个用0填充
	
	strncpy(str3, str2, 5); // 只拷贝source中5个字符
	str1[5] = '\0'; // 手动加\0
	cout << str3 << endl;

	// 【strncat例子】
	char str1[20] = "jia";
	char* str2 = "happy";
	char str3[30] = "fighting";
	strncat(str1, str2, 10); // num > source只复制到source结束
	cout << str1 << endl;
	strncat(str3, str2, 3); // num < source
	str3[3] = '\0'; // 手动加\0
	cout << str3 << endl;

	// 【strncmp例子】
	char* str1 = "abcde";
	char* str2 = "abbbb";
	cout << strncmp(str1, str2, 2) << endl; // 0
	cout << strncmp(str1, str2, 3) << endl; // c > b -> 1

	//【strstr例子】
	char* str1 = "abcdefg";
	char* str2 = "def";
	cout << strstr(str1, str2) << endl; // 返回d的地址
	cout << strstr(str1, "jia") << endl; // 返回空指针

	// 【strtok例子】
	char str[] = "- This, a sample string.";
	char * pch;
	printf("Splitting string \"%s\" into tokens:\n", str);
	pch = strtok(str, " ,.-");
	while (pch != NULL)
	{
		printf("%s\n", pch);
		pch = strtok(NULL, " ,.-");
	}

	system("pause");
	return 0;
}
#endif

/*
C语言中的内存操作函数:#include<cstring>

将source中num个字节的值复制到destination
不检测source中是否有空字符
void * memcpy ( void * destination, const void * source, size_t num );

source和destination可以重叠
void * memmove ( void * destination, const void * source, size_t num );

将前num个字节设置为指定值
void * memset ( void * ptr, int value, size_t num );

int memcmp(const void * ptr1, const void * ptr2, size_t num);
*/

// 【memcpy例子】
#if 0
struct
{
	char name[40];
	int age;
}person, person_copy;

int main()
{
	char name[] = "jia";

	// 拷贝字符串
	memcpy(person.name, name, strlen(name) + 1);
	person.age = 22;

	// 拷贝结构体对象
	memcpy(&person_copy, &person, sizeof(person));
	cout << person_copy.name << person_copy.age << endl;

	system("pause");
	return 0;
}
#endif

// 【memmove例子】
#if 0
int main()
{
	char str[] = "abcdefghijk";
	memmove(str + 3, str + 5, 4);
	puts(str); // abcfghijk

	system("pause");
	return 0;
}
#endif

// 【memset例子】
#if 0
int main()
{
	char str[] = "hhhhhhhhjiajia";
	memset(str, 'a', 5);
	puts(str);

	system("pause");
	return 0;
}
#endif

// 【memcmp例子】

int main()
{
	int ret = memcmp("abcde", "abcdg", 5);
	cout << ret << endl;

	system("pause");
	return 0;
}
