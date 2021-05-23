#pragma once


#include"HashBucket_MS.hpp"

namespace jia
{
	template<class K,class V>
	class unordered_map
	{
		typedef pair<K, V> ValueType;

		struct KOFD
		{
			const K& operator()(const ValueType& data)
			{
				return data.first;
			}
		};

	public:
		typedef typename HashBucket<ValueType, KOFD>::iterator iterator;
	public:
		unordered_map()
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
		/////////////////////////////////////////////////////////
		// access
		V& operator[](const K& key)
		{
			return (*((_ht.InsertUnique(make_pair(key, V()))).first)).second;
		}
		//////////////////////////////////////////////////////////
		// modify
		pair<iterator, bool> insert(const ValueType& val)
		{
			return _ht.InsertUnique(val);
		}

		size_t erase(const K& key)
		{
			return _ht.EraseUnique(make_pair(key,V()));
		}

		iterator find(const K& key)
		{
			return _ht.Find(key);
		}

		void clear()
		{
			return _ht.Clear();
		}

		void swap(unordered_map<K, V>& m)
		{
			_ht.Swap(m._ht);
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
			return _ht.Bucket(make_pair(key,V()));
		}
	private:
		HashBucket<ValueType, KOFD> _ht;
	};
}

#include<string>

void TestUnorderedMap()
{
	jia::unordered_map<string, string> m;
	m.insert(make_pair("apple", "苹果"));
	m.insert(make_pair("orange", "橙子"));
	m.insert(make_pair("grape", "葡萄"));
	m.insert(make_pair("banana", "香蕉"));

	cout << m["apple"] << endl;
	cout << m["mango"] << endl;

	for (auto& e : m)
	{
		cout << e.first << "---" << e.second << endl;
	}

	cout << m.size() << endl;
	cout << m.bucket_count() << endl;
	cout << m.bucket_size(0) << endl;

	m.erase("apple");
	for (auto& e : m)
	{
		cout << e.first << "---" << e.second << endl;
	}

	m.clear();
	if (m.empty())
	{
		cout << "empty()" << endl;
	}
	else
	{
		cout << "false" << endl;
	}
}