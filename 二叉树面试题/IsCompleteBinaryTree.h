#pragma once

#include "BinaryTree.h"
#include <queue>
#include <math.h>

//�ж�һ�����ǲ�����ȫ������
//��α���
bool Deal(BinaryTreeNode<char>* child, queue<BinaryTreeNode<char>*>& QUEUE, bool& flag)
{
	if (child)
	{
		if (!flag)
		{
			QUEUE.push(child);
		}
		else
		{
			return false;
		}
	}
	else
	{
		flag = true;
	}

	return true;
}

bool IsCompleteBT1(BinaryTreeNode<char>* root)
{
	//����Ҳ����ȫ������
	if (root == NULL)
		return true;
	queue<BinaryTreeNode<char>*> QUEUE;
	QUEUE.push(root);

	bool flag = false;

	while (!QUEUE.empty())
	{
		BinaryTreeNode<char>* cur = QUEUE.front();
		
		//������ڵ�
		if (!Deal(cur->_left, QUEUE, flag))
		{
			return false;
		}

		//c�����ҽڵ�
		if (!Deal(cur->_right, QUEUE, flag))
		{
			return false;
		}
		QUEUE.pop();
	}
	
	return true;
}

//�߶Ȳ�
int IsCompleteBT2(BinaryTreeNode<char>* root, bool& flag)
{
	if (root == NULL)
		return -1;

	int Left = IsCompleteBT2(root->_left, flag) + 1;
	int Right = IsCompleteBT2(root->_right, flag) + 1;

	if (abs(Left-Right) <= 1)
	{
		flag = true;
	}
	else
	{
		flag = false;
		return -1;
	}
	return Left > Right ? Left : Right;
}
void TestIsCompleteBinaryTree()
{
	char arr[] = { '1', '2', '#', '#', '3'};	
	BinaryTree<char> BT(arr, 5);
	bool tmp = IsCompleteBT1(BT.Root());
	cout << tmp << endl;

	bool tmp2 = false;
	tmp = IsCompleteBT2(BT.Root(), tmp2);
	cout << tmp2 << endl;
}