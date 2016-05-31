#include <iostream>
#include "RBTree.h"

using namespace std;

void Test()
{
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int, int> RBT;
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		RBT.Insert(a[i], a[i]);
	}
	RBT.Inorder();
	cout << "Isblance?  " << RBT.IsBalance() << endl;
}