#pragma once
int Find(int* array,int child)
{
	while (array[child] > -1)
	{
		child = array[child];
	}

	//返回根节点
	return child;
}
void Set(int* array,int& block, int root1, int root2)
{
	root1 = Find(array, root1);
	root2 = Find(array, root2);

	//将根节点的下标置为次数
	array[root1] += array[root2];
	if (root1 != root2)
	{
		//叶子节点的值存根
		array[root2] = root1;
	}

	--block;
}
//朋友圈问题
int _friends_()
{
	int a[10];
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		a[i] = -1;
	}
	int block = 9;
	int array[][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, { 7, 8 }, { 4, 9 } };
	for (int i = 0; i < sizeof(array) / (2 * sizeof(int)); ++i)
	{
		int root1 = array[i][0];
		int root2 = array[i][1];
		Set(a, block, root1, root2);
	}
	return block;
}