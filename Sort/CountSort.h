#pragma once 
#include <memory>

//计数排序
void CountSort(int* a,size_t size)
{
	assert(a);
	int min = a[0];
	int max = a[0];
	//选出最大最小
	for (size_t i = 0; i < size; ++i)
	{
		if (a[i] <= min)
		{
			min = a[i];
		}
		if (a[i] >= max)
		{
			max = a[i];
		}
	}

	//求出范围
	int range = max - min + 1;
	int* array = new int[range];
	memset(array, 0, sizeof(int)*range);
	//a[i]-min为相对位置
	for (size_t i = 0; i < size; ++i)
	{
		++array[a[i]-min];
	}

	int index = 0;
	for (size_t i = 0; i < range; ++i)
	{
		int tmp = array[i];
		while (tmp)
		{
			a[index++] = i + min;
			--tmp;
		}
	}
}

void TestCountSort()
{
	int array[] = { 21, 5, 4, 99, 34, 65555, 8, 77, 18, 100,999 };
	CountSort(array, 11);
	cout << "CountSort:";
	for (int i = 0; i < 11; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}