#include<iostream>
using namespace std;

#include<cstring>
#pragma warning(disable:4996)

/*
C�����е��ַ�������: #include<cstring>

����C�ַ�������(��Ч�ַ�����������\0)
size_t strlen(const char* str);

��source�е��ַ���(����\0)������destination�У�����destination
char* strcpy(char* destnation, const char* source);

��source�ַ�����һ�ݿ���׷�ӵ�destinationָ��Ŀռ���
ָ��destination�����ָ�룬������Ӧ�ð���һ��C�ַ�����Ҫ���㹻��Ŀռ�
destination�е�\0�ᱻsource�ַ����ĵ�һ���ַ�����
source�ַ����Ŀ�������\0
char * strcat ( char * destination, const char * source );

һ��һ���Ƚ�str1��str2�е��ַ���С��ֱ�������ַ����г����˲�һ�����ַ�����һ���ַ���������
����ֵ��
< 0����һ����ƥ����ַ���str1�е�ֵС��str2�е�ֵ
> 0����һ����ƥ����ַ���str1�е�ֵ����str2�е�ֵ
= 0: �����ַ����������
int strcmp ( const char * str1, const char * str2 );

��source����ǰnum���ַ�������destination��
����ڸ���num���ַ�ǰsource�Ѿ�����ĩβ����������0
���source����num����ôdestination������\0������
char * strncpy ( char * destination, const char * source, size_t num );

��sourceǰnum���ַ�׷�ӵ�destination���ټ���\0
���source��C�ַ����ĳ���С��num��������Ƶ�source����
char * strncat ( char * destination, const char * source, size_t num );

ƥ�䵽��һ����ͬ�ַ� ���߱Ƚϵ�num �Ƚϵ���\0
����ֵ��strcmp��ȫ��ͬ
int strncmp ( const char * str1, const char * str2, size_t num );

����str2��str1�г��ֵ�λ��
���str1����str2������str2��str1��λ�ã����򷵻ؿ�ָ��
const char * strstr ( const char * str1, const char * str2 );
char * strstr ( char * str1, const char * str2 );

��delimiters�ض�str
char * strtok ( char * str, const char * delimiters );
*/

#if 0
int main()
{
	// ��strlen��ʹ�á�
	char* str = "happy birthday"; // str�д�ŵ����ַ�����һ���ַ��ĵ�ַ
	cout << strlen(str) << endl; // 14

	char str1[] = "happy birthday"; // ����������ַ����������ַ�(����\0)��ÿ���ַ��������е�һ��Ԫ��
	char str2[40];
	char str3[40];
	strcpy(str2, str1);
	cout << str2;
	strcpy(str3, "jia");
	cout << str3 << endl;

	// ��strcat���ӡ�
	char str1[10] = { 'j', 'i', 'a' }; // �ַ�����
	char* str2[] = { "happy", "sad" }; // �ַ�ָ�����飬������ÿ��Ԫ�ض���һ��ָ���ַ��������ݵ�ָ�룬ָ���б�����ǵ�һ���ַ��ĵ�ַ
	char* str3 = "fighting"; // ����һ��ָ���ַ�����ָ�����str3
	
	cout << str2 + 1 << endl; // s�ĵ�ַ
	cout << *(str2 + 1) << endl; // sad
	cout << *str2 + 1 << endl; // appy
	
	cout << str3 + 1 << endl; // ighting
	cout << *(str3 + 1) << endl; // i
	cout << *str3 << endl; // f-��ASCII��Ϊ102 
	cout << *str3 + 1 << endl; // 103

	cout << strcat(str1, str3) << endl; // ���뱣֤destination���㹻��Ŀռ�

	// ��strcmp���ӡ�
	char* str1 = "happy";
	char* str2 = "happya";
	cout << strcmp(str1, str2) << endl; // -1 

	char* str3 = "abcd";
	char* str4 = "abbb"; 
	// ��һ����ƥ���ַ�Ϊc -> c > b -> ����0
	cout << strcmp(str3, str4) << endl; // 1

	// ��strncpy���ӡ�
	char str1[20];
	char* str2 = "fighting";
	char str3[20];
	cout << strncpy(str1, str2, 15) << endl; // sourceֻ��9����ʣ�µ�6����0���
	
	strncpy(str3, str2, 5); // ֻ����source��5���ַ�
	str1[5] = '\0'; // �ֶ���\0
	cout << str3 << endl;

	// ��strncat���ӡ�
	char str1[20] = "jia";
	char* str2 = "happy";
	char str3[30] = "fighting";
	strncat(str1, str2, 10); // num > sourceֻ���Ƶ�source����
	cout << str1 << endl;
	strncat(str3, str2, 3); // num < source
	str3[3] = '\0'; // �ֶ���\0
	cout << str3 << endl;

	// ��strncmp���ӡ�
	char* str1 = "abcde";
	char* str2 = "abbbb";
	cout << strncmp(str1, str2, 2) << endl; // 0
	cout << strncmp(str1, str2, 3) << endl; // c > b -> 1

	//��strstr���ӡ�
	char* str1 = "abcdefg";
	char* str2 = "def";
	cout << strstr(str1, str2) << endl; // ����d�ĵ�ַ
	cout << strstr(str1, "jia") << endl; // ���ؿ�ָ��

	// ��strtok���ӡ�
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
C�����е��ڴ��������:#include<cstring>

��source��num���ֽڵ�ֵ���Ƶ�destination
�����source���Ƿ��п��ַ�
void * memcpy ( void * destination, const void * source, size_t num );

source��destination�����ص�
void * memmove ( void * destination, const void * source, size_t num );

��ǰnum���ֽ�����Ϊָ��ֵ
void * memset ( void * ptr, int value, size_t num );

int memcmp(const void * ptr1, const void * ptr2, size_t num);
*/

// ��memcpy���ӡ�
#if 0
struct
{
	char name[40];
	int age;
}person, person_copy;

int main()
{
	char name[] = "jia";

	// �����ַ���
	memcpy(person.name, name, strlen(name) + 1);
	person.age = 22;

	// �����ṹ�����
	memcpy(&person_copy, &person, sizeof(person));
	cout << person_copy.name << person_copy.age << endl;

	system("pause");
	return 0;
}
#endif

// ��memmove���ӡ�
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

// ��memset���ӡ�
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

// ��memcmp���ӡ�

int main()
{
	int ret = memcmp("abcde", "abcdg", 5);
	cout << ret << endl;

	system("pause");
	return 0;
}
