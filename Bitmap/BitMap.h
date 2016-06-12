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
		//����5λ���൱�ڳ�32������ʣ�༸����+1
		_arrays.resize((size >> 5) + 1);
	}
	bool Set(size_t size)
	{
		//ѡ�������������е�����λ��
		size_t index = size >> 5;
		//ѡ����������һλ
		size_t n = size % 32;

		//���������ڲŶԸ�������
		if (_arrays[index] & (1 << n))
		{
			return false;
		}

		//����nλ���λ��
		_arrays[index] |= (1 << n);
		++_size;
		return true;
	}

	//��0��
	bool ReSet(size_t size)
	{
		size_t index = size >> 5;
		size_t n = size % 32;
		//��λ����
		if (_arrays[index] & (1 << n))
		{
			_arrays[index] &= ~(1 << n);
			--_size;
			return true;
		}
		return false;
	}

	//��ĳһλ���㻹��һ
	bool Test(size_t size)
	{
		size_t index = size >> 5;
		size_t n = size % 32;

		return _arrays[index] & (1 << n);
	}

	//��Testһģһ��
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
