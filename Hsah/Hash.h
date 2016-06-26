#pragma once 
#include <iostream>
using namespace std;
//-------------线性存储-------------//
enum Status
{
	EXIST,
	DELETED,
	EMPTY,
};

static size_t BKDRHash(const char* str)
{
	size_t seed = 131;
	size_t hash = 0;
	while (*str)
	{
		hash = hash *seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

template <class K>
struct HashType
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template <>
struct HashType<string>
{
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};

template <class K ,class HashFun = HashType<K>>
class HashTable
{
public:
	HashTable()
		:_table(NULL)
		, _size(0)
		, _capacity(0)
		, _status(NULL)
	{}
	HashTable(size_t capacity)
		:_table(new K[capacity])
		, _size(0)
		, _capacity(capacity)
		, _status(new Status[capacity])
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			_status[i] = EMPTY;
		}
	}
	bool Insert(const K& elem)
	{
		// 增容问题
		_CheakCapaCity();
		//如果容量够得话
		size_t index = _HashPos(elem);
		while (_status[index] == EXIST)
		{
			index++;
			if (index == _capacity)
			{
				index = 0;
			}
			if (_table[index] == elem)
			{
				return flase;
			}
		}
		_table[index] = elem;
		_status[index] = EXIST;
		_size++;
		return true;
	}
	bool Remove(const K& elem)
	{
		size_t index = _HashPos(elem);
		while (_status[index] != EMPTY)
		{
			if (_table[index] == elem)
			{
				if (_status[index] != DELETED)
				{
					_status[index] = DELETED;
					_size--;
					return true;
				}
			}
			++index;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return false;
	}
	K& Find(const K& key)
	{
		size_t index = _HashPos(key);
		while (_status[index] != EMPTY)
		{
			if (index == _capacity)
			{
				index = 0;
			}
			if (_table[index] == key)
			{
				return _table[index];
			}
			++index;
		}
		exit(-1);
	}
	void Display1()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << _status[i] << ":";
			cout << _table[i] << "    ";
		}
		cout << endl;
	}
	void Display2()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << _status[i] << ":";
			cout << _table[i].c_str() << "    ";
		}
		cout << endl;
	}
	~HashTable()
	{
		if (_table)
		{
			delete[] _table;
			_table = NULL;
		}
    }
protected:
	void Swap(HashTable<K>& ht)
	{
		swap(ht._capacity, _capacity);
		swap(ht._size, _size);
		swap(ht._status, _status);
		swap(ht._table, _table);
	}
	void _CheakCapaCity()
	{
		if (_size * 10 / _capacity >= 8)
		{
			HashTable<K , HashFun> NewTable(_capacity * 2);
			for (size_t i = 0; i < _capacity; ++i)
			{
				if (_status[i] == EXIST)
				{
					NewTable.Insert(_table[i]);
				}
			}
			Swap(NewTable);
		}
	}
	size_t _HashPos(const K& elem)
	{
		return (HashFun()(elem)) % _capacity;
	}
private:
	K* _table;       //元素所存储的地方
	size_t _size;    //有效长度
	size_t _capacity;//容量
	Status* _status; //状态
};

void test()
{
	HashTable<int , HashType<int>> ht(3);
	ht.Insert(1);
	ht.Insert(2);
	ht.Insert(3);
	ht.Insert(4);
	ht.Insert(5);
	ht.Display1();

	ht.Remove(1);
	ht.Remove(5);
	ht.Display1();

	size_t tmp = ht.Find(2);
	cout << tmp << endl;

	HashTable<string , HashType<string>> ht1(1);
	ht1.Insert("呼呼呼的");
	ht1.Insert("aefefefewfew");
	ht1.Display2();
	cout << (ht1.Find("aefefefewfew")).c_str() << endl;
}
