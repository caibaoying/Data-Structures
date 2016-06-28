#pragma once

#include <assert.h>
//��������������ڵ���������
template <class T>
struct BinaryTreeNode
{
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	int MaxLeft;    //�������е������
	int MaxRight;   //�������е������

	T _value;       //�ڵ��ֵ
	BinaryTreeNode(const T& value)
		:_value(value)
	{}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* arr, size_t size)
	{
		assert(arr);
		//����
		size_t index = 0;
		_root = _Create(arr, size, index);
	}
	//�����distance
	int FindMaxLen()
	{
		int maxlen = 0;
		//return _FindMaxLen(_root, maxlen);
		return _FindMaxLen2(_root, maxlen);
	}
	
	~BinaryTree()
	{
		if (_root != NULL)
		{
			_Destory(_root);
		}
		_root = NULL;
	}
protected:
	Node* _Create(const T* a, size_t size, size_t& index)
	{
		assert(a);
		Node* root = NULL;
		if (index < size && a[index] != '#')
		{
			root = (Node*)new Node(a[index]);
			root->_left = _Create(a, size, ++index);
			root->_right = _Create(a, size, ++index);
		}
		return root;
	}
	void _Destory(Node* root)
	{
		/*if (root = NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		if (root)
		{
			delete root;
		}*/
	}
	int _FindMaxLen2(BinaryTreeNode<char>* root, int& len)
	{
		if (root == NULL)
			return 0;
		int left = _FindMaxLen2(root->_left, len);
		int right = _FindMaxLen2(root->_right, len);

		if (left + right > len)
			len = left + right;

		return left > right ? left + 1 : right + 1;
	}
	int _FindMaxLen(Node* root, int& MaxLen)  //MaxLen��ΪDistance���ֵ����
	{
		if (root == NULL)
			return 0;

		if (root->_left == NULL)
			root->MaxLeft = 0;
		if (root->_right == NULL)
			root->MaxRight = 0;

		if (root->_left)
			_FindMaxLen(root->_left, MaxLen);
		if (root->_right)
			_FindMaxLen(root->_right, MaxLen);

		//qiu��������ڵ����
		if (root->_left)
		{
			int tmpMax = 0;
			if (root->_left->MaxLeft > root->_left->MaxRight)
				tmpMax = root->_left->MaxLeft;
			else
				tmpMax = root->_left->MaxRight;

			root->MaxLeft = tmpMax + 1;
		}

		//��������ڵ����
		if (root->_right)
		{
			int tmpMax = 0;
			if (root->_right->MaxLeft > root->_right->MaxRight)
				tmpMax = root->_right->MaxLeft;
			else
				tmpMax = root->_right->MaxRight;

			root->MaxRight = tmpMax + 1;
		}

		//���½ڵ��������
		if (root->MaxLeft + root->MaxRight > MaxLen)
			MaxLen = root->MaxLeft + root->MaxRight;

		return MaxLen;
	}
private:
	Node* _root;
};

void TestBinaryTreeNodeMaxDis()
{
	char arr[] = { '1', '2', '#', '#', '3', '4', '#', '#', '5', '6' };
	BinaryTree<char> BT(arr, 10);
	cout << BT.FindMaxLen() << endl;
}
