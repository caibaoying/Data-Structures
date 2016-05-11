#include <iostream>
#include <string>
using namespace std;

template <class T>
class Stack
{
public:
	Stack();
	Stack(const Stack<T>& s);
	Stack<T>& operator=(const Stack<T>& s);
	~Stack();
public:
	void Push(const T& x);
	T& Pop();
	void Print();
private:
	void _CheckCapacity();
private:
	T* _array;
	size_t _size;
	size_t _capacity;
};

template <class T>
Stack<T>::Stack()    //类外声明要加上<class T>
:_array(NULL)
, _size(0)
, _capacity(0)
{}

template <class T>
Stack<T>::Stack(const Stack<T>& s)
{
	_array = new T[s._size];
	//memcpy(_array, array, sizeof(T)*s._size);
	for (size_t i = 0; i < s._size; ++i)
	{
		_array[i] = s._array[i];
	}
	_size = s._size;
	_capacity = s._size;
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
	if (_array != s._array)
	{
		_array = new T[s._size];
		for (size_t i = 0; i < s._size; ++i)
		{
			_array[i] = s._array[i];
		}
		_size = s._size;
		_capacity = s._size;
	}
	return *this;
}

template <class T>
Stack<T>::~Stack()
{
	if (_array)
	{
		delete[] _array;
		_array = NULL;
	}
}

template <class T>
void Stack<T>::_CheckCapacity()
{
	if (_size >= _capacity)
	{
		_capacity = 2 * _capacity + 3;
		T* tmp = new T[_capacity];
		if (_array)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				tmp[i] = _array[i];
			}
			delete[] _array;
		}
		_array = tmp;
	}
}

template <class T>
void Stack<T>::Push(const T& x)
{
	_CheckCapacity();
	_array[_size++] = x;
}

template <class T>
T& Stack<T>::Pop()
{
	if (_array)
	{
		return _array[--_size];
	}
	else
	{
		delete[] _array;
		_array = NULL;
	}
}

template <class T>
void Stack<T>::Print()
{
	if (_array)
	{
		cout << "依照进栈顺序:";
		for (size_t i = 0; i < _size; ++i)
		{
			cout << " " << _array[i] ;
		}
		cout << endl;
	}
}