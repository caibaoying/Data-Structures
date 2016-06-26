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

template <class K, class V>
struct KeyValueNode
{
	K _key;
	V _value;
	KeyValueNode()
	{}
	KeyValueNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
	{}
};

template <class K , class V , class HashFun = HashType<K>>
class HashTable
{
	typedef KeyValueNode<K,V> KVNode;
public:
	HashTable()
		:_table(NULL)
		, _size(0)
		, _capacity(0)
		, _status(NULL)
	{}
	HashTable(size_t capacity)
		:_table(new KVNode[capacity])
		, _size(0)
		, _capacity(capacity)
		, _status(new Status[capacity])
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			_status[i] = EMPTY;
		}
	}
	//HashTable()
	bool Insert(const K& key , const V& value)
	{
		// 增容问题
		_CheakCapaCity();
		//如果容量够得话
		size_t add = 1;
		size_t index = _HashPos0(key);
		while (_status[index] == EXIST)
		{
			index = _HashPos2(index,add++);
			if (index >= _capacity)
			{
				index = 0;
			}
			if (_table[index]._key == key)
			{
				return false;
			}
		}
		_table[index]._key = key;
		_table[index]._value = value;
		_status[index] = EXIST;
		_size++;
		return true;
	}
	bool Remove(const K& key)
	{
		size_t add = 1;
		size_t index = _HashPos0(key);
		while (_status[index] != EMPTY)
		{
			if (_table[index]._key == key)
			{
				if (_status[index] != DELETED)
				{
					_status[index] = DELETED;
					_size--;
					return true;
				}
			}
			index = _HashPos2(index,add++);
			if (index >= _capacity)
			{
				index = 0;
			}
		}
		return false;
	}
	V& Find(const K& key)
	{
		size_t add = 1;
		size_t index = _HashPos0(key);
		while (_table[index]._key != key)
		{
			if (index >= _capacity)
			{
				exit(-1);
			}
			index = _HashPos2(index,add++);
		}
		return _table[index]._value;
	}
	void Display1()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << _status[i] << ":";
			cout << _table[i]._key << ":";
			cout << _table[i]._value << "    ";
		}
		cout << endl;
	}
	void Display2()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << _status[i] << ":";
			cout << (_table[i]._key).c_str() << "    ";
			cout << (_table[i]._value).c_str() << "    ";
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
	void Swap(HashTable<K, V, HashFun>& ht)
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
			HashTable<K, V, HashFun> NewTable(_capacity * 2);
			for (size_t i = 0; i < _capacity; ++i)
			{
				if (_status[i] == EXIST)
				{
					NewTable.Insert(_table[i]._key,_table[i]._value);
				}
			}
			Swap(NewTable);
		}
	}
	size_t _HashPos0(const K& elem)
	{
		return (HashFun()(elem)) % _capacity;
	}
	size_t _HashPos2(size_t index,size_t i)
	{
		return (index + 2*i-1);
	}
private:
	KVNode* _table;       //元素所存储的地方
	size_t _size;         //有效长度
	size_t _capacity;     //容量
	Status* _status;      //状态 
};

void test2()
{
	HashTable<int,int> ht(3);
	ht.Insert(1,1);
	ht.Insert(2,2);
	ht.Insert(3,3);
	ht.Insert(4,4);
	ht.Insert(5,5);
	ht.Display1();

	ht.Remove(1);
	ht.Remove(5);
	ht.Display1();
	
	HashTable<string, string> ht1(5);
	ht1.Insert("交换" , "exchange");
	ht1.Insert("加入" , "join");
	ht1.Display2();

	string tmp = ht1.Find("交换");
	cout <<"查找："<< tmp.c_str() << endl;
}
