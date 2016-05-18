#pragma once 
#include <iostream>
using namespace std;
//思想：拿一个数插入一个数,有序

void DictInsertSort(int* a, int n)
{
	assert(a);
	for (int i = 1; i < n; ++i)
	{
		int tmp = a[i];
		for (int j = i; j >= 0; --j)
		{
			if (tmp < a[j - 1])
			{
				a[j] = a[j - 1];
			}
			else
			{
				a[j] = tmp;
				break;
			}
		}
	}
}

void TestDictInsertSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	DictInsertSort(array, 10);
	cout << "DictInsertSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

void ShellSort(int* a, size_t size)
{
	assert(a);
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (size_t i = gap; i < size; ++i)
		{
			int index = i;
			int tmp = a[index];
			int end = index - gap;
			while (end >= 0 && tmp < a[end])
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}

void TestShellSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	ShellSort(array, 10);
	cout << "ShellSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}