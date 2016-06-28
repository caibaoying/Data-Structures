#pragma once
#include <assert.h>

struct Node
{
	Node* _left;
	Node* _right;
	int _data;
	Node(const int& data)
		: _left(NULL)
		, _right(NULL)
		, _data(data)
	{}
};

//找到根节点在中序遍历中的下标【】闭区间
int FindIndex(Node* a, Node& x, int left, int right)
{
	for (int i = left; i <= right; ++i)
	{
		if (a[i]._data == x._data)
			return i;
	}
	//return -1;
}

void _CreateTree(Node*& root, Node* PrevOrder, Node* InOrder,
	             int left, int right, int& index)
{
	assert(PrevOrder && InOrder);
	
	if (left <= right)
		root = new Node(PrevOrder[index]);
	int RootIndex = FindIndex(InOrder, PrevOrder[index], left, right);
	if (RootIndex == -1)
	{
		return;
	}
	//也就是binary，边界

	if (left <= RootIndex - 1)
	{
		_CreateTree(root->_left, PrevOrder, InOrder, left, RootIndex - 1, ++index);
	}
	else
	{
		root->_left = NULL;
		return;
	}

	if (RootIndex + 1 <= right)
	{
		_CreateTree(root->_right, PrevOrder, InOrder, RootIndex + 1, right, ++index);
	}
	else
	{
		root->_right = NULL;
		return;
	}
}
//根据前序，中序重构二叉树
Node* Reconstruct(Node* PrevOrder, Node* InOrder, int PrevSize, int InSize)
{
	assert(PrevSize == InSize);
	int left = 0;
	int right = InSize - 1;
	if (PrevOrder == NULL || InOrder == NULL)
		return NULL;
	int index = 0;
	Node* root = new Node(PrevOrder[index]);
	int RootIndex = FindIndex(InOrder, PrevOrder[index], left, right);
	if (RootIndex == -1)
		return NULL;

	_CreateTree(root->_left, PrevOrder, InOrder, left, RootIndex - 1, ++index);
	_CreateTree(root->_right, PrevOrder, InOrder, RootIndex + 1, right, ++index);

	return root;
}

//前序遍历一波
void _PrevOrder(Node* root)
{
	if (root == NULL)
		return;
	cout << root->_data << " ";
	_PrevOrder(root->_left);
	_PrevOrder(root->_right);
}
void TestRebuildBinaryTree()
{
	Node PrevOrder[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //前序
	Node InOrder[] = { 2, 3, 1, 6, 7, 8, 5, 9, 4 }; //中序

	Node* root = Reconstruct(PrevOrder,InOrder, 9, 9);
	_PrevOrder(root);
}