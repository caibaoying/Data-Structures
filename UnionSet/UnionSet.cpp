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

		//���ظ��ڵ�
		return child;
	}
	void Set(int root1, int root2)
	{
		root1 = Find(root1);
		root2 = Find(root2);

		//�����ڵ���±���Ϊ����
		_array[root1] += _array[root2];
		if (root1 != root2)
		{
			//Ҷ�ӽڵ��ֵ���
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
	int* _array;          //���ϸ���
	int _block;            //��
};

//����Ȧ����
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