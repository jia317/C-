#pragma once

#include"AVLTree_SM.h"

namespace jia
{
	template<class K>
	class set
	{
		typedef K ValueType;
		struct KOFD
		{
			const K& operator()(const ValueType& data)
			{
				return data;
			}
		};

		typedef RBTree<ValueType, KOFD> RBT;
	public:
		/*
		注意：RBT::iterator
		iterator可能是红黑树中的类型，也可能是红黑树中的静态成员变量
		如果不进行任何说明，编译器就不知道iterator是红黑树中的类型还是静态成员变量
		需要用户显示告诉编译器：iterator是红黑树中的一个类型
		*/
		typedef typename RBT::iterator iterator;
	public:
		set()
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
		
		////////////////////////////////////////////////
		// modify
		pair<iterator, bool> insert(const ValueType& data)
		{
			return _t.Insert(data);
		}

		void swap(set<K>& s)
		{
			_t.Swap(s._t);
		}

		void clear()
		{
			_t.Clear();
		}
		/////////////////////////////////////////////////
		iterator find(const K& key)
		{
			return _t.Find(key);
		}
	private:
		RBT _t;
	};
}

#include<string>
#include<iostream>
using namespace std;

void TestSet()
{
	jia::set<string> s;

	s.insert("orange");
	s.insert("apple");
	s.insert("mango");
	
	cout << s.size() << endl;

	for (auto e : s)
		cout << e << " ";
	cout << endl;

	auto ret = s.insert("apple");
	if (ret.second)
	{
		cout << "apple is not in set" << endl;
	}
	else
	{
		cout << "apple already in set" << endl;
	}

	s.clear();
	cout << s.size() << endl;
}