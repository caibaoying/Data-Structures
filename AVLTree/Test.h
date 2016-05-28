#include "AVLTree.h"
#include <iostream>
using namespace std;

void Test()
{
	AVLTree<int, int> AT;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		AT.Insert(a[i], a[i]);
	}
	AT.InorderTree();
	cout << "IsBalanceTree?" << AT.IsBalanceTree() << endl;

	//AVLTreeNode<int,int>* cur = AT.Find(16);
	AVLTreeNode<int, int>* cur = AT.Find(3);
	if (cur)
		cout << "Find:" << cur->_key << endl;
	else
		cout << "Find:NULL" << endl;
}

void Test2()
{
	AVLTree<int, int> AT;
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		AT.Insert(a[i], a[i]);
	}
	AT.InorderTree();
	AT.IsBalanceTree();
	cout << "IsBalanceTree?" << AT.IsBalanceTree() << endl;
}