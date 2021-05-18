#pragma once

#include"AVLTree_SM.h"

namespace jia
{
	template<class K,class V>
	class map
	{
		typedef pair<K, V> ValueType;
		/*
		map��data����Ϊ pair<K,V>
		set��data����Ϊ K
		����map��set����ʱ��Ҫ�Ƚϣ�
		map�ıȽϷ�ʽ���ü�ֵ���е�key
		set�ıȽϷ�ʽ����key
		��������޷�����
		����Ҫ�ڲ���dataʱ����map��Ҫ��K��ȡ���������ܺ�set��ʹ��RBTree���ṩ��ͬһ�ֲ��뷽ʽ���в���
		*/
		// ��ȡdata�е�key
		struct KOFD
		{
			// ��������
			const K& operator()(const ValueType& data)
			{
				return data.first;
			}
		};
		typedef RBTree<ValueType,KOFD> RBT;
	public:
		/*
		ע�⣺RBT::iterator
		iterator�����Ǻ�����е����ͣ�Ҳ�����Ǻ�����еľ�̬��Ա����
		����������κ�˵�����������Ͳ�֪��iterator�Ǻ�����е����ͻ��Ǿ�̬��Ա����
		��Ҫ�û���ʾ���߱�������iterator�Ǻ�����е�һ������
		*/
		typedef typename RBT::iterator iterator;
	public:
		map()
			:_t()
		{ }

        //////////////////////////////////////////////
		// ������
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

	m.insert(make_pair("orange", "����"));
	m.insert(make_pair("apple", "ƻ��"));
	m.insert(make_pair("banana", "�㽶"));

	cout << m.size() << endl;

	cout << m["apple"] << endl;

	// map�е�[]���Խ��в���
	m["peach"] = "����";

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
		cout << "�����" << endl;
	}
	else
	{
		cout << "���ʧ��" << endl;
	}
}