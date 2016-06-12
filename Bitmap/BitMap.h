#pragma once
#include <vector>
using namespace std;

class BitMap
{
public:
	BitMap()
		:_size(0)
	{}
	BitMap(size_t size)
		:_size(0)
	{
		//右移5位，相当于除32，可能剩余几个数+1
		_arrays.resize((size >> 5) + 1);
	}
	bool Set(size_t size)
	{
		//选出该数在数组中的所在位置
		size_t index = size >> 5;
		//选出具体在哪一位
		size_t n = size % 32;

		//该数不存在才对该数操作
		if (_arrays[index] & (1 << n))
		{
			return false;
		}

		//左移n位向高位移
		_arrays[index] |= (1 << n);
		++_size;
		return true;
	}

	//和0与
	bool ReSet(size_t size)
	{
		size_t index = size >> 5;
		size_t n = size % 32;
		//该位存在
		if (_arrays[index] & (1 << n))
		{
			_arrays[index] &= ~(1 << n);
			--_size;
			return true;
		}
		return false;
	}

	//检某一位是零还是一
	bool Test(size_t size)
	{
		size_t index = size >> 5;
		size_t n = size % 32;

		return _arrays[index] & (1 << n);
	}

	//和Test一模一样
	bool operator[](size_t size)
	{
		size_t index = size >> 5;
		size_t n = size % 32;

		return _arrays[index] & (1 << n);
	}
private:
	vector<size_t> _arrays;
	size_t _size;
};

void TestSet()
{
	BitMap bm(65);
	bm.Set(1);
	bm.Set(4);
	bm.Set(64);
	cout <<"operator:"<< bm[1] << endl;
	cout << bm.Test(1) << endl;
	cout << bm.Test(4) << endl;
	cout << bm.Test(2) << endl;

	bm.ReSet(1);
	
	cout << bm.Test(4) << endl;
}

void Test2()
{
	BitMap bm(-1);
	bm.Set(-1);
	cout << "operator" << bm[-1];
}
