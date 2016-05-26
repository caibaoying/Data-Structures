#include <iostream>
#include <assert.h>
#include <Windows.h>
#include "InsertSort.h"
#include "SelectionSort.h"
#include "ExchangeSort.h"
#include "MergeSort.h"
#include "CountSort.h"
#include "RadixSort.h"
using namespace std;

int main()
{
	TestDictInsertSort();
	TestShellSort();

	TestSelectionSort();
	TestSelectSort();
	TestHeapSort();
	TestBubbSort();
	TestBubbOptimizaSort();
	TestMergeSort();
	TestQuickSort();
	TestQuickSort2();
	TestNonRecursive();
	TestCountSort();
	TestRadixSort();
	system("pause");
	return 0;
}