#pragma once

#include<iostream>
#include<vector>
using namespace std;

#include"Common.h"

template<class T>
struct HashBucketNode
{
	HashBucketNode(const T& x = T())
	: next(nullptr)
	, data(x)
	{ }

	HashBucketNode<T>* next;
	T data;
};

template<class T, class KOFD, class DToI = StrToInt>
class HashBucket;

template<class T, class KOFD, class DToI = StrToInt>
struct HashBucketIterator
{
	typedef HashBucketIterator<T, KOFD, DToI> Self;
	typedef HashBucketNode<T> Node;
public:
	HashBucketIterator(Node* node = nullptr, HashBucket<T, KOFD, DToI>* ht = nullptr)
		: _node(node)
		, _ht(ht)
	{ }

	// ����ָ�����ƵĲ���
	T& operator*()
	{
		return _node->data;
	}

	T* operator->()
	{
		return &(opeartor*());
	}

	// ������Ҫ�ܹ��ƶ�
	// ������ֻ�������� ����ֻ��++����
	Self& operator++()
	{
		Next();
		return *this;
	}

	Self operator++(int) // ����++
	{
		Self temp(*this);
		Next();
		return temp;
	}

	// ������Ҫ�ܹ��Ƚ�
	bool operator==(const Self& s)const
	{
		return _node == s._node;
	}

	bool operator!=(const Self& s)const
	{
		return _node != s._node;
	}
private:
	void Next()
	{
		if (_node->next)
		{
			_node = _node->next;
		}
		else
		{
			// _node���������һ�����
			size_t bucketNo = _ht->HashFunc(_ht->BucketCount(), _node->data) + 1;
			// ����һ���ǿ�Ͱ���׽ڵ�
			for (; bucketNo < _ht->BucketCount(); ++bucketNo)
			{
				_node = _ht->_table[bucketNo];
				if (_node)
				{
					return;
				}
			}

			_node = nullptr;
		}
	}
private:
	Node* _node;
	HashBucket<T, KOFD, DToI>* _ht;
};

// ��ϣ����ֻ�ܴ����������ݣ�������ַ�������Ҫת��������
template<class T, class KOFD, class DToI>
class HashBucket
{
	friend HashBucketIterator<T, KOFD, DToI>;
	typedef HashBucketNode<T> Node; 
public:
	typedef typename HashBucketIterator<T, KOFD, DToI> iterator;
public:
	HashBucket(size_t capacity=10)
		: _table(GetNextPrime(capacity))
		, _size(0)
	{ }

	~HashBucket()
	{
		Clear();
	}

	iterator begin()
	{
		// �ҵ�һ���ǿ�Ͱ���׽ڵ�λ��
		for (size_t bucketNo = 0; bucketNo < BucketCount(); ++bucketNo)
		{
			if (_table[bucketNo])
			{
				return iterator(_table[bucketNo], this);
			}
		}

		return end();
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}
	///////////////////////////////////////////////////////////////
	// capacity
	// ��ϣ���нڵ����
	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}


	// ��ϣ��Ԫ��Ψһ�Ĳ���
	pair<iterator,bool> InsertUnique(const T& data)
	{
		CheckCapacity();

		// 1. ͨ����ϣ��������Ͱ��
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. ��������Ԫ���Ƿ���Ͱ��
		Node* cur = _table[bucketNo];
		KOFD kofd;
		while (cur)
		{
			if (kofd(data) == kofd(cur->data))
			{
				return make_pair(iterator(cur, this), false);
			}
			cur = cur->next;
		}
		
		// 3. �����½ڵ� --- ����ͷ��Ч�ʸ���
		cur = new Node(data);
		cur->next = _table[bucketNo];
		_table[bucketNo] = cur;
		_size++;

		return make_pair(iterator(cur, this), true);
	}

	// ����Ԫ�ؿ����ظ�
	bool Insert(const T& data)
	{
		CheckCapacity();

		// 1. ͨ����ϣ��������Ͱ��
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. �����½ڵ� --- ����ͷ��Ч�ʸ���
		Node* cur = new Node(data);
		cur->next = _table[bucketNo];
		_table[bucketNo] = cur;
		_size++;

		return true;
	}

	size_t EraseUnique(const T& data)
	{
		// 1. ͨ����ϣ��������Ͱ��
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. �ڸ�Ͱ�в��Ҵ�ɾ�ڵ��Ƿ����
		Node* cur = _table[bucketNo];
		Node* pre = nullptr;
		while (cur)
		{
			if (KOFD()(data) == KOFD()(cur->data))
			{
				if (nullptr == pre)
					_table[bucketNo] = cur->next;
				else
					pre->next = cur->next;

				delete cur;
				--_size;
				return 1;
			}
			else
			{
				pre = cur;
				cur = cur->next;
			}
		}
		return 0;
	}

	iterator Find(const T& data)
	{
		// 1. ͨ����ϣ��������Ͱ��
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. ��������Ԫ���Ƿ���Ͱ��
		Node* cur = _table[bucketNo];
		while (cur)
		{
			if (KOFD()(data) == KOFD()(cur->data))
			{
				return iterator(cur, this);
			}
			cur = cur->next;
		}

		return end();
	}

	void Swap(HashBucket<T, KOFD, DToI>& ht)
	{
		_table.swap(ht._table);
		std::swap(_size, ht._size);
	}

	size_t BucketCount()const
	{
		return _table.capacity();
	}

	void Clear()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			Node* cur = _table[bucketNo];
			while (cur)
			{
				// ����ͷɾ
				_table[bucketNo] = cur->next;
				delete cur;
				cur = _table[bucketNo];
			}
		}

		_size = 0;
	}

	size_t BucketSize(size_t bucketNo)const
	{
		size_t count = 0;
		Node* cur = _table[bucketNo];
		while (cur)
		{
			count++;
			cur = cur->next;
		}

		return count;
	}


	size_t Bucket(const T& data)const
	{
		return HashFunc(BucketCount(), KOFD(data));
	}


	void Print()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			cout << "[" << bucketNo << "]";
			Node* cur = _table[bucketNo];
			while (cur)
			{
				cout << cur->data << "--->";
				cur = cur->next;
			}
			cout << "NULL" << endl;
		}
		cout << endl;
	}

private:
	// ����
	void CheckCapacity()
	{
#if 0
		// ���ַ�ʽ��ϣ���нڵ������ݣ��˷ѿռ�
		if (_size == _table.capacity())
		{
			// ����һ���¹�ϣ������������2��
			HashBucket<T, DToI> newHt(_table.capacity()*2);

			// ���ɹ�ϣ����Ԫ�ز��뵽�¹�ϣ��
			for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
			{
				Node* cur = _table[bucketNo];
				while (cur)
				{
					newHt.Insert(cur->data);
					cur = cur->next;
				}
			}

			this->Swap(newHt);
		}
#endif

		if (_size == _table.capacity())
		{
			// �õĵ����ݷ�������Ϊ�ڵ��ھ�Ͱ���Ѿ������ˣ�ֻ�轫��Ͱ�еĽڵ��ƶ�����Ͱ��
			vector<Node*> newTable(GetNextPrime(_table.capacity() * 2));
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				// ����i��Ͱ�еĽڵ���Ƶ���Ͱ��
				Node* cur = _table[i];
				while (cur)
				{
					// ����Ͱ�е��׽ڵ������
					_table[i] = cur->next;

					// ���ýڵ���뵽��Ͱ��
					// ����ýڵ�����Ͱ�е�Ͱ��
					size_t bucketNo = HashFunc(newTable.capacity(), cur->data);

					// ���ýڵ���뵽��Ͱ��
					cur->next = newTable[bucketNo];
					newTable[bucketNo] = cur;

					// ȡ�ɹ�ϣͰ�е���һ���ڵ�
					cur = _table[i];
				}
			}

			_table.swap(newTable);
		}
		
	}

	size_t HashFunc(size_t capacity, const T& data)
	{
		DToI dToInt;
		//dToInt.operator()(data);
		return dToInt(KOFD()(data)) % capacity;
	}

private:
	std::vector<Node*> _table;
	size_t _size; // ��ϣ����Ԫ�ظ���
};

#include<string>

#if 0
void TestBucket3()
{
	// ������ַ����������ϣ����ʱҪ��StrToInt���������Ĭ��DToIntDef����
	HashBucket<string, StrToInt> ht;
	ht.Insert("apple");
	ht.Insert("orange");
	ht.Insert("banana");
}
#endif

#if 0
void TestCheckCap()
{
	int arr[] = { 19, 14, 23, 1, 68, 20, 84, 27, 55, 11 };
	HashBucket<int> ht;
	for (auto e : arr)
		ht.Insert(e);
	ht.Print();

	ht.Insert(77);
	ht.Insert(2);
	ht.Print();

}
#endif