#pragma once 
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <class K,class V>
struct KeyValueNode
{
	KeyValueNode(const K& key, const V& value)
	:_key(key)
	, _value(value)
	, _next(NULL)
	{}
	K _key;
	V _value;
	KeyValueNode<K, V>* _next;
};

template <class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template <>
struct HashFunc<string>
{
	size_t BKDRHash(const char* str)
	{
		size_t seed = 131;
		size_t hash = 0;
		while (*str)
		{
			hash = hash*seed + (*str++);
		}
		return (hash & 0x7FFFFFFF);
	}
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str())%key.size();
	}
};

template <class K, class V, class HashFun = HashFunc<K>> 
class HashBucket
{
	typedef KeyValueNode<K, V> KVNode;
public:
	HashBucket()
		: _size(0)
	{}
	HashBucket(size_t size)
		: _size(0)
	{
		_table.resize(size);
	}
	HashBucket(const HashBucket<K, V, HashFun>& ht)
	{
		this->_size = ht._size;
		this->_table.resize(ht._table.size());
		for (size_t i = 0; i < ht._table.size(); ++i)
		{
			KVNode* cur = ht._table[i];
			KVNode* & head = this->_table[i];

			while (cur)
			{
				//this->Insert(cur->_key, cur->_value);   // capacity为0，NO

				//头插
				KVNode* tmp = new KVNode(cur->_key, cur->_value);
				tmp->_next = head;
				head = tmp;

				cur = cur->_next;
			}
		}
	}
	HashBucket<K, V>& operator = (const HashBucket<K, V, HashFun>& ht)
	{
		HashBucket<K, V, HashFun> tmp(ht);
		this->Swap(tmp);
		return *this;
	}
	bool Insert(const K& key, const V& value)
	{
		_CheckCapacity();
		size_t index = _HashPos(key,_table.size());
		KVNode* cur = _table[index];
		if (NULL == cur)
		{
			KVNode* tmp = new KVNode(key, value);
			tmp->_next = _table[index];
			_table[index] = tmp;
			++_size;
			return true;
		}
		else
		{
			while (cur)
			{
				if (cur->_key == key)
				{
					return false;
				}
				cur = cur->_next;
			}
			KVNode* tmp = new KVNode(key, value);
			tmp->_next = _table[index];
			_table[index] = tmp;
			return true;
		}
		
	}
	bool Remove(const K& key)
	{
		size_t index = _HashPos(key,_table.size());
		KVNode* cur = _table[index];
		KVNode* prev = cur;
		if (NULL == cur)
		{
			return false;
		}
		size_t flag = 0;
		while (cur)
		{
			++flag;
			if (cur->_key == key)
			{
				if (flag == 1)         //如果只有一个元素，就标记，直接删
				{
					KVNode* tmp = _table[index];
					_table[index] = _table[index]->_next;
					delete tmp;
					tmp = NULL;
					return true;
					/*if (cur->_next)
					{
						cur = cur->_next;
						swap(prev->_key, cur->_key);
						swap(prev->_value, cur->_value);
					}
					else
					{
						delete cur;
						cur = NULL;
						_table[index] = NULL;
						return true;
					}*/
				}
				KVNode* tmp = cur;
				//cur = cur->_next;
				prev->_next = cur->_next;
				delete tmp;
				tmp = NULL;
				return true;
			}
			prev = cur;
			cur = cur->_next;
		}
		return false;
	}

	bool Find(const K& key)
	{
		size_t index = _HashPos(key, _table.size());
		KVNode* cur = _table[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return true;
			}
			cur = cur->_next;
		}
		return false;
	}

	void Display()
	{
		size_t index = 0;
		while (index < _table.size())
		{
			KVNode* cur = _table[index];
			printf("table[%d]:",index);
			while (cur)
			{
				cout << cur->_key << ":" << cur->_value<<"-->";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
			++index;
		}
		cout << endl;
	}
	~HashBucket()
	{
		for (size_t i = 0; i < _table.size(); ++i)
		{
			KVNode* cur = _table[i];
			while (cur)
			{
				KVNode*tmp = cur;
				cur = cur->_next;
				delete tmp;
				tmp = NULL;
			}
			--_size;
		}
	}
protected:
	void Swap(HashBucket<K, V, HashFun>& ht)
	{
		swap(ht._size, _size);
		swap(ht._table, _table);
	}
	void _CheckCapacity()
	{
		// 使用素数表对齐做哈希表的容量，降低哈希冲突
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,

			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,

			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,

			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,

			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,

			1610612741ul, 3221225473ul, 4294967291ul
		};
		
		if (_size == _table.size())
		{
			HashBucket<K, V,HashFun> hb;
			for (size_t i = 0; i < _PrimeSize; ++i)
			{
				if (_size < _PrimeList[i])
				{
					hb._table.resize(_PrimeList[i]);
					break;
				}
			}

			for (size_t i = 0; i < _table.size(); ++i)
			{
				KVNode* cur = _table[i];
				while (cur)
				{
					KVNode* tmp = cur;
					size_t NewIndex = _HashPos(tmp->_key , hb._table.size());
					tmp = new KVNode(tmp->_key,tmp->_value);   //深拷贝
					tmp->_next = hb._table[NewIndex];
					hb._table[NewIndex] = tmp;	
					cur = cur->_next;
				}
			}
			this->Swap(hb);
		}
	}
	size_t _HashPos(const K& key , size_t capacity)
	{
		return (HashFun()(key)) % capacity;
	}
private:
	vector<KVNode*> _table;
	size_t _size;
};

void TestHashBucket1()
{
	HashBucket<int, int> hb(53);
	hb.Insert(0, 0);
	hb.Insert(53, 53);
	hb.Insert(106, 106);
	hb.Insert(2, 2);
	hb.Insert(55, 55);
	hb.Insert(3, 3);
	hb.Insert(52, 52);
	hb.Insert(105, 105);
	hb.Insert(51, 51);
	hb.Display();
	

	cout << endl;
	hb.Remove(2);
	hb.Display();

	cout << endl;
	HashBucket<int, int> hb1(hb);
	hb1.Display();

	cout << endl;
	HashBucket<string, string> hb2(53);
	hb2.Insert("bucket", "桶");
	hb2.Insert("beautiful", "美丽");
	hb2.Insert("ugly", "丑陋");
	hb2.Insert("train", "训练");
	hb2.Insert("learn", "学习");
	hb2.Insert("key", "钥匙");
	hb2.Display();

	size_t index = hb2.Find("bucket");
	cout << "Find:" << index << endl;

	cout << endl;
	hb2.Remove("bucket");
	hb2.Display();

	cout << endl;
	HashBucket<string, string> hb3(hb2);
	hb3.Display();

	HashBucket<string, string> hb4;
	hb4 = hb3;
	cout << "hb4:" << endl;
	hb4.Display();

	cout << "----------------------------------------------------" << endl;
}

void TestHashBucket2()
{
	HashBucket<int, int> hbb(53);
	for (int index = 0; index < 54; ++index)
	{
		hbb.Insert(index, index);
	}
	hbb.Display();
}