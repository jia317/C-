#pragma once

#include"HashBucket_MS.hpp"

namespace jia
{
	template<class K>
	class unordered_set
	{
		typedef K ValueType;

		struct KOFD
		{
			const K& operator()(const ValueType& data)
			{
				return data;
			}
		};

	public:
		typedef typename HashBucket<ValueType, KOFD>::iterator iterator;
	public:
		unordered_set()
			:_ht()
		{ }

		//////////////////////////////////////////////////////////
		// capacity
		size_t size()const
		{
			return _ht.Size();
		}

		bool empty()const
		{
			return _ht.Empty();
		}

		//////////////////////////////////////////////////////////
		// iterator
		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		//////////////////////////////////////////////////////////
		// modify
		pair<iterator, bool> insert(const ValueType& val)
		{
			return _ht.InsertUnique(val);
		}

		size_t erase(const K& key)
		{
			return _ht.EraseUnique(key);
		}

		iterator find(const K& key)
		{
			return _ht.Find(key);
		}

		void clear()
		{
			return _ht.Clear();
		}

		void swap(unordered_set<K>& s)
		{
			_ht.Swap(s._ht);
		}

		// 返回当前桶中的节点个数
		size_t bucket_size(size_t bucketNo)const
		{
			return _ht.BucketSize(bucketNo);
		}

		// 返回桶个数
		size_t bucket_count()const
		{
			return _ht.BucketCount();
		}

		// 返回key所在桶的桶号
		size_t bucket(const K& key)const
		{
			return _ht.Bucket(key);
		}

	private:
		HashBucket<ValueType, KOFD> _ht;
	};
}

#include<string>

void TestUnorderedSet()
{
	jia::unordered_set<string> s;
	s.insert("apple");
	s.insert("orange");
	s.insert("grape");
	s.insert("banana");

	for (auto& e : s)
	{
		cout << e <<  endl;
	}

	cout << s.size() << endl;
	cout << s.bucket_count() << endl;
	cout << s.bucket_size(0) << endl;

	s.erase("apple");
	for (auto& e : s)
	{
		cout << e << endl;
	}

	s.clear();
	if (s.empty())
	{
		cout << "empty()" << endl;
	}
	else
	{
		cout << "false" << endl;
	}
}