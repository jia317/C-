#pragma once

#include<vector>
#include<string>
#include<iostream>
using namespace std;

#include"Common.h"

// 哈希桶中管理的是一个一个的链表
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

// 前置声明
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

	// 迭代器要有指针类似的操作
	T& operator*()
	{
		return _node->data;
	}

	T& operator->()
	{
		return &(operator*());
		//return &_node->data;
	}

	// 迭代器要能够移动
	// 哈希桶是单向链表，所以只有++
	Self& operator++() // 前置++
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
		if (_node->next) // 不是桶中最后一个结点，就找该桶中下一个节点
		{
			_node = _node->next;
		}
		else // 桶中最后一个结点，找该桶的下一个非空桶的第一个节点
		{
			// 因为要知道该桶是第几个桶，所以要调用哈希函数，
			// 增加哈希桶类型的指针来调用哈希函数
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
		// 在第一个非空桶首节点位置
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

	// 插入元素要唯一
	bool InsertUnique(const T& data)
	{
		CheckCapacity();

		// 1. 通过哈希地址计算元素所在桶号
		size_t bucketNo = HashFunc(_table.capacity(),  data);

		// 2. 检测data是否在桶中存在
		Node* cur = _table[bucketNo];
		while (cur)
		{
			if (data == cur->data)
				return false;
				
			cur = cur->next;
		}

		// 3. 插入新结点 --- 尾插需要找链表最后一个元素，效率低，所以这里采用头插
		cur = new Node(data);
		cur->next = _table[bucketNo]; // 将新结点的next指针指向桶中第一个元素
		_table[bucketNo] = cur; // 将cur更新为桶的第一个结点
		_size++;

		return true;
	}
	
	// 插入元素可以重复
	bool Insert(const T& data)
	{
		CheckCapacity();

		// 1. 通过哈希地址计算元素所在桶号
		size_t bucketNo = HashFunc(_table.capacity(), data);

		// 2. 插入新结点 --- 尾插需要找链表最后一个元素，效率低，所以这里采用头插
		Node* cur = new Node(data);
		cur->next = _table[bucketNo]; // 将新结点的next指针指向桶中第一个元素
		_table[bucketNo] = cur; // 将cur更新为桶的第一个结点
		_size++;

		return true;
	}

	Node* Find(const T& data)
	{
		// 1. 计算data的哈希地址
		size_t bucketNo = HashFunc(data);

		// 2. 在该桶所在链表查找值为data的元素
		Node* cur = _table[bucketNo];
		while (cur)
		{
			if (data == cur->data)
				return cur;
			
			cur = cur->next;
		}
		return nullptr;
	}

	// 删除哈希表中唯一值
	size_t EraseUnique(const T& data)
	{
		// 1. 通过哈希函数找data所在桶号
		size_t bucketNo = HashFunc(_table.capacity(),  data);

		// 2. 在该桶中找值为data的元素
		Node* cur = _table[bucketNo];
		Node* pre = nullptr;
		while (cur)
		{
			if (data == cur->data)
			{
				if (pre == nullptr) 
				{
					// 待删元素为桶中第一个元素
					// 更新第一个结点
					_table[bucketNo] = cur->next;
				}
				else 
				{
					// 非链表首结点，更新待删元素上一个元素的指针域
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

	// 删除哈希表中所有值为data的元素
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
				// 采用头删法删除链表中结点
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
		// 该种扩容方式，元素有两份，旧哈希表中有一份，新哈希表中有一份
		// 浪费空间
		if (_size == _table.capacity())
		{
			// 将新哈希表扩容到两倍
			HashBucket<T, DToI> newHt(_table.capacity() * 2);

			// 将旧哈希表中元素插入到新哈希表
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

		// 好的扩容方式：因为结点在旧桶中已经存在，只需将旧桶中结点搬移到新桶中
		if (_size == _table.capacity())
		{
			vector<Node*> newTable(GetNextPrime(_table.capacity() * 2));
			for (size_t i = 0; i < _table.capacity(); i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					// 将旧桶中的结点拆下来
					_table[i] = cur->next;

					// 将该结点插入到新桶中
					// 计算在新桶中的桶号
					size_t bucketNo = HashFunc(newTable.capacity(), cur->data);

					// 将该结点插入到新桶中
					cur->next = newTable[bucketNo];
					newTable[bucketNo] = cur;

					// 取旧哈希桶下一个节点
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

// 测试哈希表中元素唯一
void TestBucket1()
{
	int arr[] = { 19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79 };
	HashBucket<int> ht(7);

	for (auto e : arr)
		ht.InsertUnique(e);

	ht.Print();

	cout << ht.EraseUnique(19) << endl;
}

// 测试哈希表中元素不唯一
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
	// 如果是字符串，构造哈希对象时要传StrToInt，否则采用默认DToIntDef构造
	HashBucket<string,StrToInt> ht;
	ht.Insert("apple");
	ht.Insert("orange");
	ht.Insert("banana");
}

// 测试扩容
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