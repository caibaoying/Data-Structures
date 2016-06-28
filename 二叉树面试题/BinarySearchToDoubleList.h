#pragma once 
#include "SearchTree.h"
#include <assert.h>

BinarySearchNode<int, int>* FindHead(BinarySearchNode<int, int>* root)
{
	assert(root);
	BinarySearchNode<int, int>* cur = root;
	BinarySearchNode<int, int>* prev = NULL;
	while (cur)
	{
		prev = cur;
		cur = cur->_left;
	}
	return prev;
}
void BSToDL(BinarySearchNode<int, int>* cur, BinarySearchNode<int, int>*& prev)
{
	if (cur == NULL)
		return;
    
	BSToDL(cur->_left, prev);

	if (cur->_left == NULL)
	{
		cur->_left = prev;
		if (prev)
		{
			prev->_right = cur;
		}
	}
	if (prev && prev->_right == NULL)
	{
		prev->_right = cur;
		if (cur)
		{
			cur->_left = prev;
		}
	}
	prev = cur;

	BSToDL(cur->_right, prev);
}

void TestBSToDL()
{
	int a[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BinarySearchTree<int, int> BS;
	BS.Create(a, 10);
	BinarySearchNode<int, int>* newroot = FindHead(BS.Root());

	BinarySearchNode<int, int>* prev = NULL;
	BSToDL(BS.Root(), prev);

	while (newroot)
	{
		cout << newroot->_key << " ";
		newroot = newroot->_right;
	}
}