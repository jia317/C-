#pragma once

#include<iostream>
using namespace std;

enum Color{BLACK, RED};

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
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	RBTree()
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
	}

	bool Insert(const T& x)
	{
		Node*& root = GetRoot();
		// 1.按照二叉搜索树的方式插入
		// 1.1 空树直接进行插入
		if (nullptr == root)
		{
			root = new Node(x);
			root->parent = head;
			head->left = root;
			head->right = root;
			return true;
		}

		// 1.2 非空
		Node* cur = root;
		Node* parent = head;
		while (cur)
		{
			parent = cur;
			if (x < cur->data)
				cur = cur->left;
			else if (x > cur->data)
				cur = cur->right;
			else
				return false;
		}

		Node* newNode = new Node(x);
		cur = newNode;
		if (cur->data < parent->data)
			parent->left = cur;
		else
			parent->right = cur;

		newNode->parent = parent;

		// 2.调整节点颜色
		while (parent!=head && RED==parent->color)
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

			return true;

		}
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
		while (cur)
			cur = cur->left;

		return cur;
	}

	Node* RightMost()
	{
		Node* root = GetRoot();
		if (root == nullptr)
			return head;

		Node* cur = root;
		while (cur)
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
};

void TestRBTree()
{
	int array[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	RBTree<int> t;
	for (auto e : array)
		t.Insert(e);

	// 验证红黑树正确性
	// 1.是否为二叉搜索树
	t.InOrder();
	// 2.验证红黑树性质
	if (t.IsVaildRBTree())
		cout << "是红黑树" << endl;
	else
		cout << "不是红黑树" << endl;
}