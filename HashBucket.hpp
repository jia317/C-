#pragma once

#include<vector>
#include<string>
#include<iostream>
using namespace std;

#include"Common.h"

// ��ϣͰ�й������һ��һ��������
template<class T>
struct HashBucketNode
{
public:
	HashBucketNode(const T& x = T())
		:next(nullptr)
		, data(x)
	{ }

	HashBucketNode<T>* next;
	T data;
};

// ǰ������
template<class T, class DToI = DToIntDef<T>>
class HashBucket;

template<class T, class DToI = DToInt>
class HashBucketIterator
{
	typedef HashBucketNode<T> Node;
	typedef HashBucketIterator<T, DToI> Self;
public:
	HashBucketIterator(Node* node = nullptr, HashBucket<T,DToI>* ht=nullptr)
		:_node(node)
		, _ht(ht)
	{ }

	// ������Ҫ��ָ�����ƵĲ���
	T& operator*()
	{
		return _node->data;
	}

	T& operator->()
	{
		return &(operator*());
		//return &_node->data;
	}

	// ������Ҫ�ܹ��ƶ�
	// ��ϣͰ�ǵ�����������ֻ��++
	Self& operator++() // ǰ��++
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
		if (_node->next) // ����Ͱ�����һ����㣬���Ҹ�Ͱ����һ���ڵ�
		{
			_node = _node->next;
		}
		else // Ͱ�����һ����㣬�Ҹ�Ͱ����һ���ǿ�Ͱ�ĵ�һ���ڵ�
		{
			// ��ΪҪ֪����Ͱ�ǵڼ���Ͱ������Ҫ���ù�ϣ������
			// ���ӹ�ϣͰ���͵�ָ�������ù�ϣ����
			size_t bucketNo = _ht->HashFunc(_ht->BucketCount(), _node->data)+1;
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
	HashBucket<T, DToI>* _ht;
};

template<class T, class DToI>
class HashBucket
{
	friend HashBucketIterator<T, DToI>;
	typedef HashBucketNode<T> Node;
public:
	typedef HashBucketIterator<T, DToI> iterator;

public:

	HashBucket(size_t capacity = 10)
		: _table(GetNextPrime(capacity))
		, _size(0)
	{ }

	~HashBucket()
	{
		Clear();
	}

	iterator begin()
	{
		// �ڵ�һ���ǿ�Ͱ�׽ڵ�λ��
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

	// ����Ԫ��ҪΨһ
	bool InsertUnique(const T& data)
	{
		CheckCapacity();

		// 1. ͨ����ϣ��ַ����Ԫ������Ͱ��
		size_t bucketNo = HashFunc(_table.capacity(),  data);

		// 2. ���data�Ƿ���Ͱ�д���
		Node* cur = _table[bucketNo];
		while (cur)
		{
			if (data == cur->data)
				return false;
				
			cur = cur->next;
		}

		// 3. �����½�� --- β����Ҫ���������һ��Ԫ�أ�Ч�ʵͣ������������ͷ��
		cur = new Node(data);
		cur->next = _table[bucketNo]; // ���½���nextָ��ָ��Ͱ�е�һ��Ԫ��
		_table[bucketNo] = cur; // ��cur����ΪͰ�ĵ�һ�����
		_size++;

		return true;
	}
	
	// ����Ԫ�ؿ����ظ�
	bool Insert(const T& data)
	{
		CheckCapacity();

		// 1. ͨ����ϣ��ַ����Ԫ������Ͱ��
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. �����½�� --- β����Ҫ���������һ��Ԫ�أ�Ч�ʵͣ������������ͷ��
		Node* cur = new Node(data);
		cur->next = _table[bucketNo]; // ���½���nextָ��ָ��Ͱ�е�һ��Ԫ��
		_table[bucketNo] = cur; // ��cur����ΪͰ�ĵ�һ�����
		_size++;

		return true;
	}

	Node* Find(const T& data)
	{
		// 1. ����data�Ĺ�ϣ��ַ
		size_t bucketNo = HashFunc(data);

		// 2. �ڸ�Ͱ�����������ֵΪdata��Ԫ��
		Node* cur = _table[bucketNo];
		while (cur)
		{
			if (data == cur->data)
				return cur;
			
			cur = cur->next;
		}
		return nullptr;
	}

	// ɾ����ϣ����Ψһֵ
	size_t EraseUnique(const T& data)
	{
		// 1. ͨ����ϣ������data����Ͱ��
		size_t bucketNo = HashFunc(_table.capacity(),  data);

		// 2. �ڸ�Ͱ����ֵΪdata��Ԫ��
		Node* cur = _table[bucketNo];
		Node* pre = nullptr;
		while (cur)
		{
			if (data == cur->data)
			{
				if (pre == nullptr) 
				{
					// ��ɾԪ��ΪͰ�е�һ��Ԫ��
					// ���µ�һ�����
					_table[bucketNo] = cur->next;
				}
				else 
				{
					// �������׽�㣬���´�ɾԪ����һ��Ԫ�ص�ָ����
					pre->next = cur->next;
				}
				delete cur;
				_size--;
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

	// ɾ����ϣ��������ֵΪdata��Ԫ��
	//size_t Erase(const T& data);

	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	void Clear()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			Node* cur = _table[bucketNo];
			while (cur)
			{
				// ����ͷɾ��ɾ�������н��
				_table[bucketNo] = cur->next;
				delete cur;
				cur = _table[bucketNo];
			}
		}
	}

	void Swap(HashBucket<T, DToI>& newHt)
	{
		_table.swap(newHt._table);
		std::swap(_size, newHt._size);
	}

	size_t BucketCount()const
	{
		return _table.capacity();
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
	void CheckCapacity()
	{
#if 0
		// �������ݷ�ʽ��Ԫ�������ݣ��ɹ�ϣ������һ�ݣ��¹�ϣ������һ��
		// �˷ѿռ�
		if (_size == _table.capacity())
		{
			// ���¹�ϣ�����ݵ�����
			HashBucket<T, DToI> newHt(_table.capacity() * 2);

			// ���ɹ�ϣ����Ԫ�ز��뵽�¹�ϣ��
			for (size_t i = 0; i < _table.capacity(); i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					newHt.Insert(cur->data);
					cur = cur->next;
				}
			}

			this->Swap(newHt);
		}
#endif

		// �õ����ݷ�ʽ����Ϊ����ھ�Ͱ���Ѿ����ڣ�ֻ�轫��Ͱ�н����Ƶ���Ͱ��
		if (_size == _table.capacity())
		{
			vector<Node*> newTable(GetNextPrime(_table.capacity() * 2));
			for (size_t i = 0; i < _table.capacity(); i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					// ����Ͱ�еĽ�������
					_table[i] = cur->next;

					// ���ý����뵽��Ͱ��
					// ��������Ͱ�е�Ͱ��
					size_t bucketNo = HashFunc(newTable.capacity(), cur->data);

					// ���ý����뵽��Ͱ��
					cur->next = newTable[bucketNo];
					newTable[bucketNo] = cur;

					// ȡ�ɹ�ϣͰ��һ���ڵ�
					cur = _table[i];
				}
			}

			_table.swap(newTable);
		}
	}

	size_t HashFunc(size_t capacity, const T& data)
	{
		DToI dToInt;
		//dToI.operator()(data);
		return dToInt(data) % capacity;
	}
private:
	vector<Node*> _table;
	size_t _size;
};

// ���Թ�ϣ����Ԫ��Ψһ
void TestBucket1()
{
	int arr[] = { 19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79 };
	HashBucket<int> ht(7);

	for (auto e : arr)
		ht.InsertUnique(e);

	ht.Print();

	cout << ht.EraseUnique(19) << endl;
}

// ���Թ�ϣ����Ԫ�ز�Ψһ
void TestBucket2()
{
	int arr[] = { 20, 68, 1, 68, 20, 84, 27, 55, 11, 10, 79, 20 };
	HashBucket<int> ht(7);

	for (auto e : arr)
		ht.Insert(e);

	ht.Print();

	//cout << ht.Erase(20) << endl;
}

void TestBucket3()
{
	// ������ַ����������ϣ����ʱҪ��StrToInt���������Ĭ��DToIntDef����
	HashBucket<string,StrToInt> ht;
	ht.Insert("apple");
	ht.Insert("orange");
	ht.Insert("banana");
}

// ��������
void TestBucket4()
{
	int arr[] = { 19, 14, 23, 1, 68, 20, 84, 27, 55, 11};
	HashBucket<int> ht;

	for (auto e : arr)
		ht.InsertUnique(e);

	ht.Print();

	ht.Insert(10);
	ht.Insert(79);
	ht.Print();

	auto it = ht.begin();
	while (it != ht.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : ht)
		cout << e << " ";
	cout << endl;
}