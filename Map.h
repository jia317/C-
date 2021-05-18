#pragma once

#include"AVLTree_SM.h"

namespace jia
{
	template<class K,class V>
	class map
	{
		typedef pair<K, V> ValueType;
		/*
		map的data类型为 pair<K,V>
		set的data类型为 K
		由于map和set插入时需要比较，
		map的比较方式是用键值对中的key
		set的比较方式是用key
		红黑树中无法处理
		所以要在插入data时，在map中要将K提取出来，才能和set中使用RBTree中提供的同一种插入方式进行插入
		*/
		// 提取data中的key
		struct KOFD
		{
			// 函数对象
			const K& operator()(const ValueType& data)
			{
				return data.first;
			}
		};
		typedef RBTree<ValueType,KOFD> RBT;
	public:
		/*
		注意：RBT::iterator
		iterator可能是红黑树中的类型，也可能是红黑树中的静态成员变量
		如果不进行任何说明，编译器就不知道iterator是红黑树中的类型还是静态成员变量
		需要用户显示告诉编译器：iterator是红黑树中的一个类型
		*/
		typedef typename RBT::iterator iterator;
	public:
		map()
			:_t()
		{ }

        //////////////////////////////////////////////
		// 迭代器
		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		//////////////////////////////////////////////
		// capacity
		size_t size()const
		{
			return _t.size();
		}

		bool empty()const
		{
			return _t.empty();
		}
		//////////////////////////////////////////////////
		// access
		V& operator[](const K& key)
		{
			return (*(_t.Insert(make_pair(key, V()))).first).second;
		}
		////////////////////////////////////////////////
		// modify
		pair<iterator, bool> insert(const ValueType& data)
		{
			return _t.Insert(data);
		}

		void swap(map<K, V>& m)
		{
			_t.Swap(m._t);
		}

		void clear()
		{
			_t.Clear();
		}
		/////////////////////////////////////////////////
		iterator find(const K& key)
		{
			return _t.Find(make_pair(key, V()));
		}
	private:
		RBT _t;
	};
}

#include<string>
#include<iostream>
using namespace std;

void TestMap()
{
	jia::map<string, string> m;

	m.insert(make_pair("orange", "橙子"));
	m.insert(make_pair("apple", "苹果"));
	m.insert(make_pair("banana", "香蕉"));

	cout << m.size() << endl;

	cout << m["apple"] << endl;

	// map中的[]可以进行插入
	m["peach"] = "桃子";

	auto it = m.begin();
	while (it != m.end())
	{
		cout << "[" << it->first << "," << (*it).second << "]" << endl;
		++it;
	}
	cout << endl;

	it = m.find("mango");
	if (it != m.end())
	{
		cout << "mango is in m" << endl;
	}
	else
	{
		cout << "mango is not in m" << endl;
	}

	m.clear();
	cout << m.size() << endl;
	if (m.empty())
	{
		cout << "已清空" << endl;
	}
	else
	{
		cout << "清空失败" << endl;
	}
}