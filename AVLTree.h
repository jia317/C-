#pragma once

template<class T>
struct AVLTreeNode
{
	AVLTreeNode(const T& x = T())
	: left(nullptr)
	, right(nullptr)
	, parent(nullptr)
	, data(x)
	, _bf(0)
	{}

	AVLTreeNode* left;
	AVLTreeNode* right;
	AVLTreeNode* parent;
	T data;
	int _bf;
};

template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;

public:
	AVLTree()
		:_root(nullptr)
	{}

	~AVLTree()
	{
		Destroy(_root);
	}

	bool Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			return true;
		}

		// 1. �����������������
		// ��λ��
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (data < cur->data)
				cur = cur->left;
			else if (data > cur->data)
				cur = cur->right;
			else
				return false;

		}

		// �����½ڵ�
		cur = new Node(data);
		if (data < parent->data)
			parent->left = cur;
		else
			parent->right = cur;

		cur->parent = parent;

		// 2. ����ƽ������
		while (parent)
		{
			if (cur == parent->left) // �������߶ȼ�1
				parent->_bf--;
			else
				parent->_bf++;

			if (0 == parent->_bf)
				break;
			else if (-1 == parent->_bf || 1 == parent->_bf)
			{
				// ����curǰ��parent��Ҷ�ӽڵ� ƽ������Ϊ0
				// ����cur��ƽ�����ӱ�Ϊ1��-1����˵����parentΪ���������߶�������
				// ����Ҫ���ϸ��������ڵ��ƽ������
				cur = parent;
				parent = cur->parent;
			}
			else // ƽ������Ϊ-2��2 Ҫ����parentΪ���Ķ�����������ת
			{
				if (2 == parent->_bf) // �������� ����Ҫ����
				{
					if (1 == cur->_bf) // ͬ�ŵ���
					{
						RotateLeft(parent);
					}
					else // -1==cur->_bf ���˫��
					{
						RotateRL(parent);
					}
				}
				else // -2 == parent->_bf �������� ����Ҫ����
				{
					if (-1 == cur->_bf) // ͬ�ŵ���
					{
						RotateRight(parent);
					}
					else // 1==cur->_bf ���˫��
					{
						RotateLR(parent);
					}
				}
				break;
			}
		}
		return true;
	}

	void InOrder()
	{
		InOrder(_root);
		cout << endl;
	}

	bool IsBalanceTree()
	{
		return _IsBalanceTree(_root);
	}

private:
	void InOrder(Node* root)
	{
		if (root)
		{
			InOrder(root->left);
			cout << root->data << " ";
			InOrder(root->right);
		}
	}

	// ���ٶ�����Ҫ�����������
	// ���ڵ㱾����һ��ָ�룬Ҫ��ͨ���βθı�ʵ�α��봫����
	void Destroy(Node*& root)
	{
		if (root)
		{
			Destroy(root->left);
			Destroy(root->right);
			delete root;
			root = nullptr;
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

		if (pparent == nullptr)
			_root = subL;
		else
		{
			if (parent == pparent->left)
				pparent->left = subL;
			else
				pparent->right = subL;
		}

		parent->_bf = subL->_bf = 0;
		
	}

	void RotateLeft(Node* parent)
	{
		Node* subR = parent->right;
		Node* subRL = subR->left;

		parent->right = subRL;
		if (subRL)
			subRL->parent = parent;
		subR->left = parent;

		Node* pparent = parent->parent;
		parent->parent = subR;
		subR->parent = pparent;

		if (nullptr == pparent)
			_root = subR;
		else
		{
			if (parent == pparent->left)
				pparent->left = subR;
			else
				pparent->right = subR;
		}

		parent->_bf = subR->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->left;
		Node* subLR = subL->right;
		int bf = subLR->_bf;

		RotateLeft(subL);
		RotateRight(parent);

		if (-1 == bf)
			parent->_bf = 1;
		else if (1 == bf)
			subL->_bf = -1;

	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->right;
		Node* subRL = subR->left;
		int bf = subRL->_bf;

		RotateRight(subR);
		RotateLeft(parent);

		if (-1 == bf)
			subR->_bf = 1;
		else if (1 == bf)
			parent->_bf = -1;
	}

	int _Height(Node* root)
	{
		if (nullptr == root)
			return 0;

		int LHeight = _Height(root->left);
		int RHeight = _Height(root->right);
		
		return LHeight > RHeight ? LHeight + 1 : RHeight + 1;
	}

	bool _IsBalanceTree(Node* root)
	{
		if (nullptr == root)
			return true;

		int leftHeight = _Height(root->left);
		int rightHeight = _Height(root->right);
		int bf = rightHeight - leftHeight;
		if (abs(bf) > 1 || bf != root->_bf)
		{
			cout << root->data << "�ڵ��ƽ������������" << endl;
			return false;
		}

		return _IsBalanceTree(root->left) && _IsBalanceTree(root->right);
	}
private:
	AVLTreeNode<T>* _root;
};

void TestAVLTree()
{
	//int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	AVLTree<int> t;
	for (auto e : array)
		t.Insert(e);

	t.InOrder();

	if (t.IsBalanceTree())
	{
		cout << "t is a AVL tree!!!" << endl;
	}
	else
	{
		cout << "t is not a AVL tree!!!" << endl;
	}
}