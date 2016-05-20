#pragma once 

//LSD-- Least Significant Digit first
void RadixSort(int* a, size_t size)
{
	//����λ��
	int max = 10;
	int digit = 1;
	int radix = 1;
	for (size_t i = 0; i < size; ++i)
	{
		while (a[i] >= max)
		{
			++digit;
			max *= 10;
		}
	}

	int* count = new int[10];
	int* start = new int[10];
	int* tmp = new int[size];
	while (digit)
	{
		memset(count, 0, sizeof(int)*10);
		memset(start, 0, sizeof(int)*10);
		memset(tmp, 0, sizeof(int)*size);
		//�ȷ��䵽���Ե�λ��
		for (int i = 0; i < size; ++i)
		{
			int tmp = a[i];
			int unit = (tmp/radix) % 10;
			++count[unit];
		}
		
		//�����start����ε���ʼλ�ü���֮ǰ������Ԫ�ظ��������Ǹ�Ԫ�ص����λ��
		start[0] = 0;
		for (size_t i = 1; i < 10; ++i)
		{
			start[i] = count[i - 1] + start[i - 1];
		}
		
		//����
		for (size_t i = 0; i < size; ++i)
		{
			int index = (a[i] / radix) % 10;
			tmp[start[index]++] = a[i];
		}

		//����a
		for (int i = 0; i < size; ++i)
		{
			a[i] = tmp[i];
		}
		radix *= 10;
		--digit;
	}
	delete[] count;
	delete[] start;
	delete[] tmp;
}

void TestRadixSort()
{
	int array[] = { 287, 5089, 44, 9, 39, 6, 8, 7, 1, 0,123};
	RadixSort(array, sizeof(array)/sizeof(int));
	cout << "RadixSort:";
	for (int i = 0; i < sizeof(array) / sizeof(int); i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}