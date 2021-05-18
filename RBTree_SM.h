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
	// 构造
	RBTreeIterator(Node* n = nullptr)
		:node(n)
	{}

	// 迭代器要有指针类似的方法
	T& operator*()
	{
		return node->data;
	}

	T* operator->()
	{
		return &(operator*());
	}

	// 迭代器要能够移动
	Self& operator++() // 前置++
	{
		Increment();
		return *this;
	}

	Self operator++(int) // 后置++
	{
		Self temp(*this);
		Increment();
		return temp;
	}

	Self& operator--() // 前置--
	{
		Decrement();
		return *this;
	}

	Self operator--(int) // 后置--
	{
		Self temp(*this);
		Decrement();
		return temp;
	}

	void Increment()
	{
		// 一定要先在其右子树中找，右子树不存在说明node是该条路径中最大的，
		// 再去找该路径根节点，根节点即为node的节点
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

		// 特殊情况：node为红黑树的根节点
		/*
		经过上面的else
		node == head，parent == root
		但是node的下一个节点应该是end()所在位置，即head的位置
		所以要对node的特殊情况进行判断，再赋值node=parent
		*/

	}

	void Decrement()
	{
		// 特殊情况：node在end()的位置
		// node == node->parent->parent这一个条件不能保证node在end()的位置，还有可能是红黑树的根节点
		// head->color是红色，当node->color是红色时，node才一定在end()的位置
		if (RED == node->color && node == node->parent->parent)
		{
			node = node->right;
		}
		// 找左子树中最大的
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
			// 左子树不存在，要在node的双亲中找比node小的结点
			Node* parent = node->parent;
			while (node == parent->left)
			{
				// node是parent的左孩子说明，node还是比parent小
				// 需要继续向上找，直到node大于parent
				node = parent;
				parent = node->parent;
			}
			node = parent;
		}

		// node是红黑树的根节点时，node就是红黑树中最小的结点
		// --操作是非法的，所以直接让node在parent的位置(红黑树根节点)即可
	}

	// 迭代器要能够比较
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
// T：表示红黑树中数据的类型
// KOFD：从T中提取key的类型
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

	// 容量相关操作
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
		// 1.按照二叉搜索树的方式插入
		// 1.1 空树直接进行插入
		if (nullptr == root)
		{
			root = new Node(data);
			root->parent = head;
			head->left = root;
			head->right = root;
			_size = 1;
			return make_pair(iterator(root), true);
		}

		// 1.2 非空
		Node* cur = root;
		Node* parent = head;
		KOFD key; //函数对象
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

		// 2.调整节点颜色
		while (parent != head && RED == parent->color)
		{
			Node* grandFather = parent->parent;
			if (parent == grandFather->left)
			{
				// 三种情况
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
					// 先将情况三转化为情况二，再用情况二的解决方式解决
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
				// 上面三种情况的镜像
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

			// 3.最终将根节点改成黑色 
			// 如果插入节点为最大或者小要更新head的指针域
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
			KOFD()(data) 解释：KOFD()相当于创建一个匿名对象
			和下边这种写法效果一样
			KOFD key; // 创建一个对象
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
		// 空树是红黑树
		Node* root = GetRoot();
		if (nullptr == root)
			return true;

		// 树非空：检测红黑树性质
		// 1. 检测性质2：根节点是黑色
		if (root->color != BLACK)
			return false;

		// 2. 检测性质3：不能有连在一起的红色节点
		// 3. 检测性质4：每条路径的黑色节点个数相同
		// 统计每条路径黑色节点个数时要遍历所有节点，可以顺便检测性质3
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
	// 注意：pathBlackCount传参时不能传size_t& ，否则pathBlackCount会被带出递归调用，最终pathBlackCount就是红黑树中所有黑色节点个数
	// 传递size_t，每次调用_IsValidRBTree函数都会有一个pathBlackCount的临时变量
	// 递归调用返回时，pathBlackCount就是当前节点调用函数时的pathBlackCount的值 
	bool _IsValidRBTree(Node* root, size_t pathBlackCount, const size_t blackCount)
	{
		if (nullptr == root)
			return true;

		if (BLACK == root->color)
			pathBlackCount++;

		Node* parent = root->parent;
		if (parent != head && RED == parent->color && RED == root->color)
		{
			cout << "违反性质3：存在连在一起的红色节点" << endl;
			return false;
		}

		if (nullptr == root->left && nullptr == root->right)
		{
			if (pathBlackCount != blackCount)
			{
				cout << "违反性质4：路径中黑色节点的个数不同" << endl;
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
		// 注意右单枝的情况，右单枝没有subRL，代码subRL->parent会崩溃
		if (subRL)
			subRL->parent = parent;

		subR->left = parent;

		// 更新subR和parent的双亲
		// parent可能是根节点，也可能是子树
		Node* pparent = parent->parent;
		parent->parent = subR;
		subR->parent = pparent;

		// 处理旋转后parent双亲的指针域
		if (pparent == head) // 旋转前parent是根节点
		{
			head->parent = subR;
		}
		else // 旋转前parent是子树
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


	// 验证红黑树正确性
	// 1.是否为二叉搜索树
	t.InOrder();

	// 验证封装的迭代器
	cout << "=========================" << endl;
	cout << "采用迭代器来遍历红黑树：" << endl;
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

	// 2.验证红黑树性质
	if (t.IsVaildRBTree())
		cout << "是红黑树" << endl;
	else
		cout << "不是红黑树" << endl;

}