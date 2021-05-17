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
		// 1.���ն����������ķ�ʽ����
		// 1.1 ����ֱ�ӽ��в���
		if (nullptr == root)
		{
			root = new Node(x);
			root->parent = head;
			head->left = root;
			head->right = root;
			return true;
		}

		// 1.2 �ǿ�
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

		// 2.�����ڵ���ɫ
		while (parent!=head && RED==parent->color)
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

			return true;

		}
	}

	void InOrder()
	{
		InOrder(GetRoot());
		cout << endl;
	}
private:
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

	// ��֤�������ȷ��
	// 1.�Ƿ�Ϊ����������
	t.InOrder();
	// 2.��֤���������
}