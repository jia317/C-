#pragma once 

#include<string>

// �����б�T��������double��short������
template<class T>
class DToIntDef
{
public:
	size_t operator()(const T& data) // �º���
	{
		return data;
	}
};

// ר�Ž��ַ���ת��Ϊ���ͽ��
class StrToInt
{
public:
	size_t operator()(const std::string& s) // �º���
	{
		return BKDRHash(s.c_str());
	}

	size_t BKDRHash(const char* str)
	{
		size_t seed = 131;
		size_t hash = 0;

		while (*str)
		{
			hash = hash*seed + (*str++);
		}

		return (hash & 0x7FFFFFFF);
	}
};

// ���������� ����������С�ӽ����������
const int PRIMECOUNT = 28;
const size_t primeList[PRIMECOUNT] = {
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

size_t GetNextPrime(size_t prime) {
	size_t i = 0;
	for (; i < PRIMECOUNT; ++i)
	{
		if (prime < primeList[i])
			return primeList[i];
	}

	return primeList[i];
}