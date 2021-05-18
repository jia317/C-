#pragma once

#include<iostream>
using namespace std;

enum Color{ BLACK, RED };

template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& x = T(), Color c = RED)
	:left(nullptr)
	, right(nullptr)
	, parent(nullptr)
	, data(x)
	, color(c)
	{ }

	RBTreeNode<T>* left;
	RBTreeNode<T>* right;
	RBTreeNode<T>* parent;
	T data;
	Color color;
};

template<class T>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;
public:
	// ����
	RBTreeIterator(Node* n = nullptr)
		:node(n)
	{}

	// ������Ҫ��ָ�����Ƶķ���
	T& operator*()
	{
		return node->data;
	}

	T* operator->()
	{
		return &(operator*());
	}

	// ������Ҫ�ܹ��ƶ�
	Self& operator++() // ǰ��++
	{
		Increment();
		return *this;
	}

	Self operator++(int) // ����++
	{
		Self temp(*this);
		Increment();
		return temp;
	}

	Self& operator--() // ǰ��--
	{
		Decrement();
		return *this;
	}

	Self operator--(int) // ����--
	{
		Self temp(*this);
		Decrement();
		return temp;
	}

	void Increment()
	{
		// һ��Ҫ���������������ң�������������˵��node�Ǹ���·�������ģ�
		// ��ȥ�Ҹ�·�����ڵ㣬���ڵ㼴Ϊnode�Ľڵ�
		if (node->right)
		{
			node = node->right;
			while (node->left)
			{
				node = node->left;
			}
		}
		else
		{
			Node* parent = node->parent;
			while (node == parent->right)
			{
				node = parent;
				parent = node->parent;
			}

			if (node->right != parent)
				node = parent;
		}

		// ���������nodeΪ������ĸ��ڵ�
		/*
		���������else
		node == head��parent == root
		����node����һ���ڵ�Ӧ����end()����λ�ã���head��λ��
		����Ҫ��node��������������жϣ��ٸ�ֵnode=parent
		*/

	}

	void Decrement()
	{
		// ���������node��end()��λ��
		// node == node->parent->parent��һ���������ܱ�֤node��end()��λ�ã����п����Ǻ�����ĸ��ڵ�
		// head->color�Ǻ�ɫ����node->color�Ǻ�ɫʱ��node��һ����end()��λ��
		if (RED == node->color && node == node->parent->parent)
		{
			node = node->right;
		}
		// ��������������
		else if (node->left)
		{
			node = node->left;
			while (node->right)
			{
				node = node->right;
			}
		}
		else
		{
			// �����������ڣ�Ҫ��node��˫�����ұ�nodeС�Ľ��
			Node* parent = node->parent;
			while (node == parent->left)
			{
				// node��parent������˵����node���Ǳ�parentС
				// ��Ҫ���������ң�ֱ��node����parent
				node = parent;
				parent = node->parent;
			}
			node = parent;
		}

		// node�Ǻ�����ĸ��ڵ�ʱ��node���Ǻ��������С�Ľ��
		// --�����ǷǷ��ģ�����ֱ����node��parent��λ��(��������ڵ�)����
	}

	// ������Ҫ�ܹ��Ƚ�
	bool operator!=(const Self& s)const
	{
		return node != s.node;
	}

	bool operator==(const Self& s)const
	{
		return node == s.node;
	}

private:
	Node* node;
};

template<class T,class KOFD>
// T����ʾ����������ݵ�����
// KOFD����T����ȡkey������
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T> iterator;
public:
	RBTree()
		:_size(0)
	{
		head = new Node();
		head->left = head;
		head->right = head;
		head->parent = nullptr;
	}

	~RBTree()
	{
		Destroy(GetRoot());
		delete head;
		head = nullptr;
		_size = 0;
	}

	iterator begin()
	{
		return iterator(head->left);
	}

	iterator end()
	{
		return iterator(head);
	}

	// ������ز���
	size_t size()const
	{
		return _size;
	}

	bool empty()const
	{
		return head->parent == nullptr;
	}

	pair<iterator,bool> Insert(const T& data)
	{
		Node*& root = GetRoot();
		// 1.���ն����������ķ�ʽ����
		// 1.1 ����ֱ�ӽ��в���
		if (nullptr == root)
		{
			root = new Node(data);
			root->parent = head;
			head->left = root;
			head->right = root;
			_size = 1;
			return make_pair(iterator(root), true);
		}

		// 1.2 �ǿ�
		Node* cur = root;
		Node* parent = head;
		KOFD key; //��������
		//key.operator()(data);
		//key(data);
		while (cur)
		{
			parent = cur;
			if (key(data) < key(cur->data))
				cur = cur->left;
			else if (key(data) > key(cur->data))
				cur = cur->right;
			else
				return make_pair(iterator(cur), false);
		}

		Node* newNode = new Node(data);
		cur = newNode;
		if (key(cur->data) < key(parent->data))
			parent->left = cur;
		else
			parent->right = cur;

		newNode->parent = parent;

		// 2.�����ڵ���ɫ
		while (parent != head && RED == parent->color)
		{
			Node* grandFather = parent->parent;
			if (parent == grandFather->left)
			{
				// �������
				Node* uncle = grandFather->right;
				if (uncle && uncle->color == RED)
				{
					parent->color = BLACK;
					uncle->color = BLACK;
					grandFather->color = RED;
					cur = grandFather;
					parent = cur->parent;
				}
				else
				{
					// �Ƚ������ת��Ϊ�����������������Ľ����ʽ���
					if (cur == parent->right)
					{
						RotateLeft(parent);
						std::swap(parent, cur);
					}

					parent->color = BLACK;
					grandFather->color = RED;
					RotateRight(grandFather);
				}
			}
			else
			{
				// ������������ľ���
				Node* uncle = parent->left;
				if (uncle && uncle->color == RED)
				{
					parent->color = BLACK;
					uncle->color = BLACK;
					grandFather->color = RED;
					cur = grandFather;
					parent = cur->parent;
				}
				else
				{
					if (cur == parent->left)
					{
						RotateRight(parent);
						std::swap(cur, parent);
					}

					parent->color = BLACK;
					grandFather->color = RED;
					RotateLeft(grandFather);
				}
			}

			// 3.���ս����ڵ�ĳɺ�ɫ 
			// �������ڵ�Ϊ������СҪ����head��ָ����
			root->color = BLACK;
			head->left = LeftMost();
			head->right = RightMost();
			_size++;

			return make_pair(iterator(newNode), true);

		}
	}

	void Swap(RBTree<T,KOFD>& t)
	{
		std::swap(head, t.head);
		std::swap(_size, t._size);
	}

	void Clear()
	{
		Destroy(GetRoot());
		_size = 0;
	}

	iterator Find(const T& data)
	{
		Node* cur = GetRoot();
		KOFD key;
		while (cur)
		{
			/*
			KOFD()(data) ���ͣ�KOFD()�൱�ڴ���һ����������
			���±�����д��Ч��һ��
			KOFD key; // ����һ������
			key(data)
			*/
			if (key(data) == key(cur->data))
				return iterator(cur);
			else if (key(data) < key(cur->data))
				cur = cur->left;
			else
				cur = cur->right;
		}

		return end();
	}

	void InOrder()
	{
		InOrder(GetRoot());
		cout << endl;
	}

	bool IsVaildRBTree()
	{
		// �����Ǻ����
		Node* root = GetRoot();
		if (nullptr == root)
			return true;

		// ���ǿգ������������
		// 1. �������2�����ڵ��Ǻ�ɫ
		if (root->color != BLACK)
			return false;

		// 2. �������3������������һ��ĺ�ɫ�ڵ�
		// 3. �������4��ÿ��·���ĺ�ɫ�ڵ������ͬ
		// ͳ��ÿ��·����ɫ�ڵ����ʱҪ�������нڵ㣬����˳��������3
		Node* cur = root;
		size_t blackCount = 0;
		while (cur)
		{
			if (BLACK == cur->color)
				blackCount++;

			cur = cur->left;
		}

		size_t pathBlackCount = 0;
		return _IsValidRBTree(root, pathBlackCount, blackCount);
	}

private:
	// ע�⣺pathBlackCount����ʱ���ܴ�size_t& ������pathBlackCount�ᱻ�����ݹ���ã�����pathBlackCount���Ǻ���������к�ɫ�ڵ����
	// ����size_t��ÿ�ε���_IsValidRBTree����������һ��pathBlackCount����ʱ����
	// �ݹ���÷���ʱ��pathBlackCount���ǵ�ǰ�ڵ���ú���ʱ��pathBlackCount��ֵ 
	bool _IsValidRBTree(Node* root, size_t pathBlackCount, const size_t blackCount)
	{
		if (nullptr == root)
			return true;

		if (BLACK == root->color)
			pathBlackCount++;

		Node* parent = root->parent;
		if (parent != head && RED == parent->color && RED == root->color)
		{
			cout << "Υ������3����������һ��ĺ�ɫ�ڵ�" << endl;
			return false;
		}

		if (nullptr == root->left && nullptr == root->right)
		{
			if (pathBlackCount != blackCount)
			{
				cout << "Υ������4��·���к�ɫ�ڵ�ĸ�����ͬ" << endl;
				return false;
			}
		}

		return _IsValidRBTree(root->left, pathBlackCount, blackCount) &&
			_IsValidRBTree(root->right, pathBlackCount, blackCount);
	}

	void RotateLeft(Node* parent)
	{
		Node* subR = parent->right;
		Node* subRL = subR->left;

		parent->right = subRL;
		// ע���ҵ�֦��������ҵ�֦û��subRL������subRL->parent�����
		if (subRL)
			subRL->parent = parent;

		subR->left = parent;

		// ����subR��parent��˫��
		// parent�����Ǹ��ڵ㣬Ҳ����������
		Node* pparent = parent->parent;
		parent->parent = subR;
		subR->parent = pparent;

		// ������ת��parent˫�׵�ָ����
		if (pparent == head) // ��תǰparent�Ǹ��ڵ�
		{
			head->parent = subR;
		}
		else // ��תǰparent������
		{
			if (parent == pparent->left)
			{
				pparent->left = subR;
			}
			else
			{
				pparent->right = subR;
			}
		}
	}

	void RotateRight(Node* parent)
	{
		Node* subL = parent->left;
		Node* subLR = subL->right;

		parent->left = subLR;
		if (subLR)
			subLR->parent = parent;

		subL->right = parent;

		Node* pparent = parent->parent;
		parent->parent = subL;
		subL->parent = pparent;

		if (pparent == head)
		{
			head->parent = subL;
		}
		else
		{
			if (parent == pparent->left)
				pparent->left = subL;
			else
				pparent->right = subL;
		}
	}

	Node*& GetRoot()
	{
		return head->parent;
	}

	Node* LeftMost()
	{
		Node* root = GetRoot();
		if (root == nullptr)
			return head;

		Node* cur = root;
		while (cur->left)
			cur = cur->left;

		return cur;
	}

	Node* RightMost()
	{
		Node* root = GetRoot();
		if (root == nullptr)
			return head;

		Node* cur = root;
		while (cur->right)
			cur = cur->right;

		return cur;
	}

	void InOrder(Node* root)
	{
		if (root)
		{
			InOrder(root->left);
			cout << root->data << " ";
			InOrder(root->right);
		}
	}

	void Destroy(Node*& root)
	{
		if (root)
		{
			Destroy(root->right);
			Destroy(root->left);
			delete root;
			root = nullptr;
		}
	}
private:
	Node* head;
	size_t _size;
};

struct KOFD
{
	int operator()(int data)
	{
		return data;
	}
};
void TestRBTree()
{
	int array[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	RBTree<int,KOFD> t;
	for (auto e : array)
		t.Insert(e);


	// ��֤�������ȷ��
	// 1.�Ƿ�Ϊ����������
	t.InOrder();

	// ��֤��װ�ĵ�����
	cout << "=========================" << endl;
	cout << "���õ������������������" << endl;
	auto it = t.begin();
	while (it != t.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : t)
		cout << e << " ";
	cout << endl;

	// 2.��֤���������
	if (t.IsVaildRBTree())
		cout << "�Ǻ����" << endl;
	else
		cout << "���Ǻ����" << endl;

}