#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

#include "UnionSet.h"

class UnionSet
{
public:
	UnionSet(const int& size)
		:_array(new int[size])
		, _block(size)
	{
		for (int i = 0; i < size; ++i)
		{
			_array[i] = -1;
		}
	}
	int Find(int child)
	{
		while (_array[child] > -1)
		{
			child = _array[child];
		}

		//返回根节点
		return child;
	}
	void Set(int root1, int root2)
	{
		root1 = Find(root1);
		root2 = Find(root2);

		//将根节点的下标置为次数
		_array[root1] += _array[root2];
		if (root1 != root2)
		{
			//叶子节点的值存根
			_array[root2] = root1;
		}
		
		--_block;
	}

	int GetSize()
	{
		return _block;
	}

	~UnionSet()
	{/*
		if (_array)
			delete[] _array;
		_array = NULL;
		*/
	}
protected:
	int* _array;          //集合个数
	int _block;            //块
};

//朋友圈问题
int friends()
{
	UnionSet US(9);
	int array[][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, { 7, 8 }, { 4, 9 } };
	for (int i = 0; i <5; ++i)
	{
		int root1 = array[i][0];
		int root2 = array[i][1];
		US.Set(root1, root2);
	}
	
	return US.GetSize();
}

int main()
{
	cout << "C++  " << _friends_() << endl;
	cout << "C    " << friends() << endl;
	system("pause");
	return 0;
}