#include <iostream>
#include <windows.h>
#include <assert.h>
using namespace std;


///////////////////双向链表//////////////////////

typedef int DataType;

//节点
struct BlistNode
{
	BlistNode(const DataType& data)
	    :_data(data)
	    , _prev(NULL)
	    , _next(NULL)
	{}
	DataType _data;
	BlistNode* _prev;
	BlistNode* _next;
};

class Blist
{
public:
	Blist()
	    :_head(NULL)
	    ,_tail(NULL)
	{}
	//拷贝构造
	Blist(const Blist& s)
	{
		BlistNode* s1 = s._head;
		_head = new BlistNode(s1->_data);
		_head->_prev = NULL;
		_head->_next = NULL;
		_tail = _head;
		s1 = s1->_next;
		while (s1)
		{
			BlistNode* tmp = new BlistNode(s1->_data);
			_tail->_next = tmp;
			tmp->_prev = _tail;
			_tail = _tail->_next;
			s1 = s1->_next;
		}
	}

	//赋值运算符重载
	Blist& operator = (const Blist& s)
	{
		if (_head != NULL)
		{
			Destory();
		}
		if (this != &s)
		{
			BlistNode* s1 = s._head;
			_head = new BlistNode(s1->_data);
			_head->_prev = NULL;
			_head->_next = NULL;
			_tail = _head;
			s1 = s1->_next;
			while (s1)
			{
				BlistNode* tmp = new BlistNode(s1->_data);
				_tail->_next = tmp;
				tmp->_prev = _tail;
				_tail = _tail->_next;
				s1 = s1->_next;
			}
		}
		return *this;
	}

	//析构函数
	~Blist()
	{
		Destory();
	}

	//打印结果
	void Display()
	{
		BlistNode* begin = _head;
		cout << "NULL  - ";
		while (begin)
		{
			cout << begin->_data << " - ";
			begin = begin->_next;
		}
		cout << "NULL" << endl;
	}
public:
	//尾插
	void PushBack(const DataType& x)
	{
		if (_head == NULL)
		{
			_head = new BlistNode(x);
			_head->_next = NULL;
			_head->_prev = NULL;
			_tail = _head;
		}
		else
		{
			BlistNode* tmp = new BlistNode(x);
			_tail->_next = tmp;
			tmp->_prev = _tail;
			_tail = _tail->_next;
		}
	}

	//尾删
	void PopBack()
	{
		assert(_head);
		if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			BlistNode* tmp = _head;
			_head = _head->_next;
			delete tmp;
			tmp = NULL;
		}
	}

	//头插
	void PushFront(const DataType& x)
	{
		if (_head == NULL)
		{
			_head = new BlistNode(x);
			_head->_next = NULL;
			_head->_prev = NULL;
			_tail = _head;
		}
		else
		{
			BlistNode* tmp = new BlistNode(x);
			tmp->_prev = NULL;
			tmp->_next = _head;
			_head->_prev = tmp;
			_head = tmp;
		}
	}

	//头删
	void PopFront()
	{
		assert(_head);
		if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			BlistNode* tmp = _head;
			_head = _head->_next;
			delete tmp;
			tmp = NULL;
		}
	}

	//查找
	BlistNode* Find(size_t pos)
	{
		BlistNode* begin = _head;
		size_t i = 1;
		while (begin)
		{
			if (i == pos)
			{
				return begin;
			}
			begin = begin->_next;
			++i;
		}
		return NULL;
	}

	//插入
	void Insert(BlistNode* pos, const DataType& x)
	{
		assert(pos);
		if (pos->_next == NULL)
		{
			BlistNode* tmp = new BlistNode(x);
			pos->_next = tmp;
			tmp->_prev = pos;
			_tail = _tail->_next;
			_tail->_next = NULL;
		}
		else if (pos->_next == NULL)
		{
			BlistNode* tmp = new BlistNode(x);
			_head->_next = tmp;
			tmp->_prev = _head;
			_tail = _tail->_next;
		}
		else
		{
			BlistNode* tmp = new BlistNode(x);
			BlistNode* tmp1 = pos->_next;
			pos->_next = tmp;
			tmp->_next = tmp1;
			tmp1->_prev = tmp;
			tmp->_prev = pos;
		}
	}

	//反转
	void Reverse()
	{
		BlistNode* cur = _head;
		while (cur)
		{
			swap(cur->_next, cur->_prev);
			cur = cur->_next;
		}
	}

private:
	//释放空间
	void Destory()
	{
		BlistNode* begin = _head;
		while (begin)
		{
			BlistNode* tmp = begin;
			begin = begin->_next;
			delete tmp;
			tmp = NULL;
		}
		_head = _tail = NULL;
	}
private:
	BlistNode* _head;
	BlistNode* _tail;
};

void test1()
{
	Blist L1;
	L1.PushBack(1);
	L1.PushBack(2);
	L1.PushBack(3);
	L1.Display();

	Blist L2(L1);
	L2.Display();

	Blist L3;
	L3 = L1;
	L3.Display();
}

void test2()
{
	Blist L1;
	L1.PushBack(1);
	L1.PushBack(2);
	L1.PushBack(3);
	L1.Display();

	L1.PopFront();
	L1.PopFront();
	L1.PopFront();
	L1.Display();

	L1.PushFront(1);
	L1.PushFront(2);
	L1.PushFront(3);
	L1.Display();

	L1.PopBack();
	L1.PopBack();
	L1.PopBack();
	L1.Display();
}

void test3()
{
	Blist L1;
	L1.PushBack(1);
	L1.Display();
	BlistNode* tmp1 = L1.Find(1);
	L1.Insert(tmp1, 4);
	L1.Display();

	Blist L2;
	L2.PushBack(1);
	L2.PushBack(2);
	L2.PushBack(3);
	L2.Display();
	BlistNode* tmp2 = L2.Find(2);
	L2.Insert(tmp2, 4);
	L2.Display();

	BlistNode* tmp3 = L2.Find(4);
	L2.Insert(tmp3, 5);
	L2.Display();
}

void test4()
{
	Blist L1;
	L1.PushBack(1);
	L1.PushBack(2);
	L1.PushBack(3);
	L1.Display();

	L1.Reverse();
	L1.Display();
}

int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	system("pause");
	return 0;
}