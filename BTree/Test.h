#include <iostream>
using namespace std;

#include "BTrre.h"

void Test()
{
	int a[] = { 53, 75, 139, 49, 145, 36, 101, 12, 13, 14, 15, 88, 77 };

	BTree<int, 3> bt;
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		bt.Insert(a[i]);
	}

	bt.Inorder();
}