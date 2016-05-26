#pragma once 
#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

//冒泡排序
void BubbSort(int* a, size_t size)
{
	assert(a);
	int flag = 1;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 1; j < size - i; ++j)
		{
			//升序
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				flag = 0;
			}
		}
		if (flag)
			break;
	}
}

void TestBubbSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	BubbSort(array, 10);
	cout << "BubbSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//冒泡排序优化版
void BubbOptimizaSort(int* a, size_t size)
{
	assert(a);
	int cur = size;
	while (cur > 0)
	{
		int tmp = cur;
		cur = 0;
		for (int j = 1; j < tmp; ++j)
		{
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1], a[j]);
				cur = j;
			}
		}
	}
}

void TestBubbOptimizaSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	BubbOptimizaSort(array, 10);
	cout << "BubbOptimizaSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//三数取中法（优化）
int ThreeMid(int* a, int left, int right)
{
	assert(a);
	int mid = left + (right - left) / 2;
	if (a[left] > a[right])
	{
		if (a[right] > a[mid])
		{
			return right;
		}
		else if (a[mid] > a[left])
		{
			return left;
		}
		else
			return mid;
	}
	// (a[left] < a[right])
	else
	{
		if (a[right] < a[mid])
		{
			return right;
		}
		else if (a[mid] < a[left])
		{
			return left;
		}
		else
			return mid;
	}
}

//[0,9]
//右边比他大，左边比他小，从左取大，从右取小，交换
//容易出的错误：逻辑不严谨（考虑相等的情况，交换是要判断，注意界限等）
void QuickSort(int* a, int left,int right)
{
	assert(a);
	int mid = ThreeMid(a, left, right);
	swap(a[mid], a[right]);
	int last = right;         //[0,9]
	int key = a[right];
	if (left >= last)
	{
		return;
	}
	while (left < last)
	{
		while (left < last && a[left] <= key)
		{
			++left;
		}
		while (left < last && a[last] >= key)
		{
			--last;
		}
		if (left < last)
		{
			swap(a[left], a[last]);
		}
	}
	if (a[left] >= key)
	{
		swap(a[left], a[right]);
	}
	if (left - 1 >= 0)    //防止下标越界
	{
		QuickSort(a, 0, left - 1);
	}
	QuickSort(a, left + 1, right);
}

void TestQuickSort()
{
	int array[] = { 2, 123, 4123, 9, 334, 632, 8, 753, 1324, 10};
	QuickSort(array, 0, 9);
	cout << "QuickSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//快排的另一种思路：挖坑+分治
//实现单链表的排序,另一种思路
void QuickSort2(int* a, int left, int right)
{
	assert(a);
	int mid = ThreeMid(a, left, right); //遍历
	swap(a[mid], a[right]);
	int key = a[right];
	int cur = left;
	int prev = left - 1;
	if (cur >= right)
	{
		return;
	}
	
	while (cur < right)
	{
		if (a[cur] < key && ++prev != cur)
		{
			swap(a[cur], a[prev]);
		}
		++cur;
	}
	if (a[prev + 1] > a[right])
	{
		swap(a[++prev], a[right]);
	}

	if (prev - 1 >= 0) //防止下标越界
	{
		QuickSort2(a, left, prev - 1);
	}
	QuickSort2(a, prev + 1, right);
}

void TestQuickSort2()
{
	int array[] = { 2, 5, 4546, 9, 3, 8876, 8, 7,2341, 0 };
	QuickSort2(array, 0, 9);
	cout << "QuickSort2:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//快排的非递归
int Partition(int* a, int left, int right)
{
	assert(a);
	//int mid = ThreeMid(a, left, right); //遍历
	//swap(a[mid], a[right]);
	int key = a[right];
	int cur = left;
	int prev = left - 1;

	while (cur < right)
	{
		if (a[cur] < key && ++prev != cur)
		{
			swap(a[cur], a[prev]);
		}
		++cur;
	}
	/*if (a[prev + 1], a[right])*/
	swap(a[++prev], a[right]);
	return prev;
}
void quickSortNonRecursive(int* a, int left, int right)
{
	assert(a);
	stack<int> Stack;
	if (left >= right)
	{
		return;
	}
	if (left < right)
	{
		int binary = Partition(a, left, right);

		if (binary - 1 >= left)
		{
			Stack.push(left);
			Stack.push(binary - 1);
		}
		if (binary + 1 <= right)
		{
			Stack.push(binary + 1);
			Stack.push(right);
		}

		while (!Stack.empty())
		{
			int Right = Stack.top();
			Stack.pop();
			int Left = Stack.top();
			Stack.pop();

			binary = Partition(a, Left, Right);

			if (binary - 1 > Left)
			{
				Stack.push(Left);
				Stack.push(binary - 1);
			}
			if (binary + 1 < Right)
			{
				Stack.push(binary + 1);
				Stack.push(Right);
			}
		}
	}
}

void TestNonRecursive()
{
	int array[] = { 2, 5, 4345, 923, 3243, 631, 8, 753, 1, 0 };
	quickSortNonRecursive(array, 0, 9);
	cout << "quickSortNonRecursive:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}