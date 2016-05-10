#include <iostream>
#include <memory.h>
#include <assert.h>
using namespace std;

typedef int DataType;

class SeqList
{
public:
	SeqList()
		:_array(NULL)
		, _size(0)
		, _capacity(0)
	{}

	SeqList(DataType* array, size_t size)
		:_array(new DataType[size])
		, _size(size)
		, _capacity(size)
	{
		memcpy(_array, array, sizeof(DataType)*size);
	}

	SeqList(const SeqList& s)
		:_array(NULL)
	{
		SeqList tmp(s._array, s._size);
		//_array 和 tmp交换以后，就需要释放tmp,tmp这时并没有初始化，所以指针指向的空间随机
		Swap(tmp);
	}

	SeqList& operator = (const SeqList& s)
	{
		if (_array != s._array)
		{
			SeqList tmp(s._array, s._size);
			Swap(tmp);
		}
		return *this;
	}

	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			_array = NULL;
		}
	}

	void Display()
	{
		int i = 0;
		while (i < _size)
		{
			cout << _array[i] << "    ";
			i++;
		}
		cout << endl;
	}
public:
	void PushBack(const DataType& x)
	{
		_CheckCapacity();
		_array[_size++] = x;
	}
	void PushFront(const DataType& x)
	{
		_CheckCapacity();
		int end = _size;
		while (end)
		{
			_array[end] = _array[end - 1];
			end--;
		}
		_array[end] = x;
		++_size;
	}
	void PopBack()
	{
		--_size;
	}
	void PopFront()
	{
		int begin = 0;
		while (begin < _size)
		{
			_array[begin] = _array[begin + 1];
			++begin;
		}
		--_size;
	}
	void Insert(size_t pos, const DataType& x)
	{
		_CheckCapacity();
		assert(pos <= _size);
		size_t end = _size;
		while (end >= pos)
		{
			_array[end] = _array[end - 1];
			--end;
		}
		_array[end] = x;
		++_size;
	}

	int Find(const DataType& x)
	{
		int begin = 0;
		while (begin < _size)
		{
			if (_array[begin] == x)
			{
				return begin;
			}
			++begin;
		}
		return -1;
	}

	void Erase(size_t pos)
	{
		assert(pos <= _size);
		int begin = pos - 1;
		while (begin <= _size)
		{
			_array[begin] = _array[begin + 1];
			++begin;
		}
		--_size;
	}

	DataType& operator [] (size_t index)
	{
		assert(index <= _size);
		return _array[index];
	}

	size_t Size()
	{
		return _size;
	}

	size_t Capacity()
	{
		return _capacity;
	}

	void Reserve(size_t size)
	{
		if (_size > _capacity)
		{
			_capacity = _capacity + size;
			DataType* tmp = new DataType[_capacity];
			memcpy(tmp, _array, sizeof(DataType)*_size);
			delete[] _array;
			_array = tmp;
		}
	}
private:
	void _CheckCapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = _capacity * 2 + 3;
			DataType* tmp = new DataType[_capacity];
			memcpy(tmp, _array, sizeof(DataType)*_size);
			delete[] _array;
			_array = tmp;
		}
	}
	void Swap(SeqList& s)
	{
		swap(_array, s._array);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}



private:
	DataType* _array;
	size_t _size;
	size_t _capacity;
};

void test1()
{
	DataType array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);

	SeqList s2 = s1;


	SeqList s3;
	s3 = s2;

	s1.Display();
	s2.Display();
	s3.Display();
}

void test2()
{
	DataType array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);
	s1.Display();

	s1.PushBack(6);
	s1.Display();

	s1.PushFront(0);
	s1.Display();

	s1.PopBack();
	s1.Display();

	s1.PopFront();
	s1.Display();

	s1.Insert(1, 7);
	s1.Display();

	cout << s1.Find(1) << endl;
	cout << s1.Find(9) << endl;

	s1.Erase(1);
	s1.Display();
}

void test3()
{
	DataType array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);
	SeqList s2 = s1;
	SeqList s3;
	s3 = s1;

	cout << s1[0] << endl;;
	s1[1] = 10;
	s1.Display();
	s2.Display();
	s3.Display();
}

void test4()
{
	DataType array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);

	cout << s1.Size() << endl;
	cout << s1.Capacity() << endl;
}

int main()
{
	//test1();
	//test2();
	test3();
	test4();
	system("pause");
	return 0;
}