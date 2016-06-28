#pragma once

#include "BinaryTree.h"
#include <stack>

//��������������Ĺ�������
//����Ľⷨ�����֣�1����parent,2����parent��
//BinaryTreeNode<char>* FNCA(BinaryTreeNode<char>* left, BinaryTreeNode<char>* right)                       //��������Ĺ�������
//{
//	assert(left && right);
//	//������ֵ�Ƚϣ�����Ϊ�����ڵ�Ƚ�
//	if (left == right)
//		return left;
//	while (left != NULL)
//	{
//		left = left->_parent;
//		BinaryTreeNode<char>* temp = right;
//		while (temp)
//		{
//			if (temp == left || temp->_parent == left)
//			{
//				return left;
//			}
//			temp = temp->_parent;
//		}
//	}
//}

//�ڶ��ֽⷨ
//�㷨˼�룺���һ���ڵ���������left,��������right����ô����ڵ����CA(common ancestor)
//����ջ��⣬�Ż�,               �����������ǵݹ������⡢������������
//bool Path1(BinaryTreeNode<char>* root, BinaryTreeNode<char>* x, stack<BinaryTreeNode<char>*>& s)
//{
//	assert(root);
//	s.push(root);
//	bool Lflag = false, Rflag = false;  //��Ϊtrue����ʾ��ǰ�ڵ�������������ѱ�����
//	BinaryTreeNode<char>* prev = NULL;
//	while (!s.empty())
//	{
//		//������
//		BinaryTreeNode<char>* cur = s.top();
//		if (cur == x)
//		{
//			return true;
//		}
//		if (cur && cur->_left && !Lflag)
//		{
//			prev = cur;
//			cur = cur->_left;
//			s.push(cur);
//			Lflag = false;
//		}
//		else if(prev && prev->_right && !Rflag)
//		{
//			prev = cur;
//			cur = cur->_right;
//			s.push(cur);
//			Rflag = false;
//		}
//		else //(cur->_left == NULL && cur->_right == NULL)&& cur!=a/b
//		{
//			BinaryTreeNode<char>* tmp = s.top();
//			if (prev->_left == tmp)
//				Lflag = true;
//			else
//				Rflag = true;
//			s.pop();
//		}
//	}
//	return false;
//}
bool Path2(BinaryTreeNode<char>* root, BinaryTreeNode<char>* x, stack<BinaryTreeNode<char>*>& s)
{
	if (root == NULL)
		return false;

	s.push(root);

	bool left = Path2(root->_left, x, s);
	if (root == x)
		return true;

	bool right = Path2(root->_right, x, s);
	if (root == x)
		return true;

	if (left || right)
		return true;

	s.pop();
	return false;
}
//FNCA3
BinaryTreeNode<char>* FNCA3(BinaryTreeNode<char>* root, BinaryTreeNode<char>* a, BinaryTreeNode<char>* b)
{
	stack<BinaryTreeNode<char>*> s1; 
	Path2(root, a, s1);
	stack<BinaryTreeNode<char>*> s2; 
	Path2(root, b, s2);
	if (s1.empty() || s2.empty())
		return NULL;

	int Len1 = 0, Len2 = 0;
	if (s1.size() == s2.size())
	{
		Len1 = Len2 = 0;
	}
	else if (s1.size() > s2.size())
	{
		Len1 = s1.size() - s2.size();
	}
	else
	{
		Len2 = s2.size() - s1.size();
	}
	while (Len1)
	{
		s1.pop();
		Len1--;
	}
	while (Len2)
	{
		s2.pop();
		Len2--;
	}
	while (!s1.empty() && !s2.empty())
	{
		if (s1.top() == s2.top())
		{
			return s1.top();
		}
		s1.pop();
		s2.pop();
	}
	return NULL;
}


void TestNearestAncestor()
{
	char arr[] = { '1', '2', '#', '#', '3', '4', '#', '#', '5', '6' };
	BinaryTree<char> BT(arr, 10);
	BinaryTreeNode<char>* Ancestor = NULL;
	BinaryTreeNode<char> tmpa('3');
	BinaryTreeNode<char> tmpb('6');
	BinaryTreeNode<char>* a = BT.Find(tmpa);
	BinaryTreeNode<char>* b = BT.Find(tmpb);

	Ancestor = FNCA3(BT.Root(), a, b);
	cout << Ancestor->_data << endl;
}