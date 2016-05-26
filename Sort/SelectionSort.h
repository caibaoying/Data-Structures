#pragma once
using namespace std;

//选择排序
void SelectionSort(int* a, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		int MinIndex = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (a[j] < a[MinIndex])
			{
				MinIndex = j;
			}
		}
		swap(a[i], a[MinIndex]);
	}
}

void TestSelectionSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	SelectionSort(array, 10);
	cout << "SelectionSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//直接选择排序优化版，一次选出最大值和最小值
void SelectSort(int* a, size_t size, int left, int right)
{
	assert(a);
	int Left = left, Right = right;
	if (left >= right)
	{
		return;
	}
	if (a[left] > a[right])
	{
		swap(a[left], a[right]);
	}
	while (Left < Right)
	{
		if (a[Left + 1] >= a[Right - 1])
		{
			if (a[right] < a[Left + 1])
			{
				swap(a[right], a[Left + 1]);
			}
			else
			{
				--Right;
			}
			if (a[left] > a[Right - 1])
			{
				swap(a[left], a[Right - 1]);
			}
			else
			{
				++Left;
			}
		}
		if (a[Left + 1] < a[Right - 1])
		{
			if (a[right] < a[Right - 1])
			{
				swap(a[right], a[Right - 1]);
			}
			else
			{
				--Right;
			}
			if (a[left] > a[Left + 1])
			{
				swap(a[left], a[Left + 1]);
			}
			else
			{
				++Left;
			}
		}
	}
	SelectSort(a, size, ++left, --right);
}

void TestSelectSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	SelectSort(array, 10, 0, 9);
	cout << "SelectSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

//升序大堆
void AjustDown(int* a, size_t size, int root)
{
	assert(a);
	int parent = root;
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (a[child + 1] && a[child] < a[child + 1])
		{
			++child;
		}
		if (a[parent] < a[child])
		{
			swap(a[parent], a[child]);
			parent = child;
			child = child * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* a, size_t size)
{
	assert(a);
	for (int i = (size - 2) / 2; i >= 0; --i)
	{
		AjustDown(a, size, i);
	}
	for (int index = size - 1; index > 1; --index)
	{
		swap(a[index], a[0]);
		AjustDown(a, index-1, 0);
	}
}

void TestHeapSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	HeapSort(array, 10);
	cout << "HeapSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}