#pragma once 

//[]
void _MergeSection(int* a, int* tmp, int left1, int right1, int left2, int right2)
{
	int first1 = left1;
	int first2 = left2;
	int last1 = right1;
	int last2 = right2;

	int index = 0;
	while (first1 <= last1 && first2 <= last2)
	{
		if (a[first1] >= a[first2])
		{
			tmp[index++] = a[first2++];
		}
		else
			tmp[index++] = a[first1++];
	}
	while (first1 <= last1)
	{
		tmp[index++] = a[first1++];
	}
	while (first2 <= last2)
	{
		tmp[index++] = a[first2++];
	}

	for (int i = 0; i < index; ++i)
	{
		a[left1 + i] = tmp[i];
	}
}

void _MergeSort(int* a, int* tmp, int left, int right)
{
	assert(tmp);
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		_MergeSort(a, tmp, left, mid);
		_MergeSort(a, tmp, mid + 1, right);
		_MergeSection(a, tmp, left, mid, mid + 1, right);
	}
}

//[]
void MergeSort(int* a, size_t size)
{
	assert(a);
	int* tmp = new int[size];
	_MergeSort(a, tmp, 0, size - 1);
	delete tmp;
}

void TestMergeSort()
{
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	MergeSort(array, 10);
	cout << "MergeSort:";
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}