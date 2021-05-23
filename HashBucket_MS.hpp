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

	// 具有指针类似的操作
	T& operator*()
	{
		return _node->data;
	}

	T* operator->()
	{
		return &(opeartor*());
	}

	// 迭代器要能够移动
	// 单链表只能往后走 所以只有++操作
	Self& operator++()
	{
		Next();
		return *this;
	}

	Self operator++(int) // 后置++
	{
		Self temp(*this);
		Next();
		return temp;
	}

	// 迭代器要能够比较
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
			// _node是链表最后一个结点
			size_t bucketNo = _ht->HashFunc(_ht->BucketCount(), _node->data) + 1;
			// 找下一个非空桶的首节点
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

// 哈希函数只能处理整形数据，如果是字符串类型要转化成整型
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
		// 找第一个非空桶的首节点位置
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
	// 哈希表中节点个数
	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}


	// 哈希表元素唯一的插入
	pair<iterator,bool> InsertUnique(const T& data)
	{
		CheckCapacity();

		// 1. 通过哈希函数计算桶号
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. 检测待插入元素是否在桶中
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
		
		// 3. 插入新节点 --- 采用头插效率更高
		cur = new Node(data);
		cur->next = _table[bucketNo];
		_table[bucketNo] = cur;
		_size++;

		return make_pair(iterator(cur, this), true);
	}

	// 插入元素可以重复
	bool Insert(const T& data)
	{
		CheckCapacity();

		// 1. 通过哈希函数计算桶号
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. 插入新节点 --- 采用头插效率更高
		Node* cur = new Node(data);
		cur->next = _table[bucketNo];
		_table[bucketNo] = cur;
		_size++;

		return true;
	}

	size_t EraseUnique(const T& data)
	{
		// 1. 通过哈希函数计算桶号
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. 在该桶中查找待删节点是否存在
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
		// 1. 通过哈希函数计算桶号
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. 检测待插入元素是否在桶中
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
				// 采用头删
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
	// 扩容
	void CheckCapacity()
	{
#if 0
		// 该种方式哈希表中节点有两份，浪费空间
		if (_size == _table.capacity())
		{
			// 创建一个新哈希表，容量扩增至2倍
			HashBucket<T, DToI> newHt(_table.capacity()*2);

			// 将旧哈希表中元素插入到新哈希表
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
			// 好的的扩容方法：因为节点在旧桶中已经存在了，只需将旧桶中的节点移动到新桶中
			vector<Node*> newTable(GetNextPrime(_table.capacity() * 2));
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				// 将第i个桶中的节点搬移到新桶中
				Node* cur = _table[i];
				while (cur)
				{
					// 将旧桶中的首节点拆下来
					_table[i] = cur->next;

					// 将该节点插入到新桶中
					// 计算该节点在新桶中的桶号
					size_t bucketNo = HashFunc(newTable.capacity(), cur->data);

					// 将该节点插入到新桶中
					cur->next = newTable[bucketNo];
					newTable[bucketNo] = cur;

					// 取旧哈希桶中的下一个节点
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
	size_t _size; // 哈希表中元素个数
};

#include<string>

#if 0
void TestBucket3()
{
	// 如果是字符串，构造哈希对象时要传StrToInt，否则采用默认DToIntDef构造
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