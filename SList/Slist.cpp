#include <iostream>
#include <windows.h>
#include <assert.h>
using namespace std;

typedef int DataType;
struct SlistNode
{
	SlistNode(DataType data = 0)
	:_data(data)
	, _next(NULL)
	{}
	DataType _data;
	SlistNode* _next;
};

class Slist
{
public:
	Slist()
		:_head(NULL)
		,_tail(NULL)
	{} 
	Slist(const Slist& s)
	{
		SlistNode* s1 = s._head;
		_head = new SlistNode(s._head->_data);
		_tail = _head;
		s1 = s1->_next;
		while (s1)
		{
			_tail->_next = new SlistNode(s1->_data);
			_tail = _tail->_next;
			s1 = s1->_next;
		}
	}
	Slist& operator = (const Slist& s)
	{
		if (_head != NULL)
		{
			Destory();
		}
		SlistNode* s1 = s._head;
		_head = new SlistNode(s._head->_data);
		_tail = _head;
		s1 = s1->_next;
		while (s1)
		{
			_tail->_next = new SlistNode(s1->_data);
			_tail = _tail->_next;
			s1 = s1->_next;
		}
		return *this;
	}
	~Slist()
	{
		Destory();
	}

	void Display()
	{
		SlistNode* tmp = _head;
		while (tmp)
		{
			cout << tmp->_data << "->";
			tmp = tmp->_next;
		}
		cout << "NULL" << endl;
	}
public:
	void PushBack(const DataType& x)
	{
		//为空，不为空
		if (_head == NULL)
		{
			_head = new SlistNode(x);
			_head->_next = NULL;
			_tail = _head;
		}
		else
		{
			_tail->_next = new SlistNode(x);
			_tail = _tail->_next;
			_tail->_next = NULL;
		}
	}

	void PopFront()
	{
		assert(_head);
		if (_head->_next == NULL)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			SlistNode* tmp = _head;
			_head = _head->_next;
			delete tmp;
		}
	}

	void PushFront(const DataType& x)
	{
		if (_head == NULL)
		{
			_head = new SlistNode(x);
			_tail = _head;
		}
		else
		{
			SlistNode* tmp = new SlistNode(x);
			tmp->_next = _head;
			_head = tmp;
		}
	}

	void PopBack()
	{
		assert(_head);
		if (_head->_next == NULL)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			//找到倒数第二个节点
			SlistNode* tmp = _head;
			while (tmp->_next != _tail)
			{
				tmp = tmp->_next;
			}
			delete _tail;
			_tail = tmp;
			_tail->_next = NULL;
		}
	}

	SlistNode* Find(size_t pos)
	{
		SlistNode* begin = _head;
		size_t flagPos = 1;     //标记位
		while (begin)
		{
			if (flagPos == pos)
			{
				return begin;
			}
			begin = begin->_next;
			++flagPos;
		}
		return NULL;
	}

	//在pos后插入一个数据，
	void Insert(SlistNode* pos, const DataType& x)
	{
		assert(pos);
		//是否为尾插
		if (pos->_next == NULL)
		{
			pos->_next = new SlistNode(x);
			_tail = _tail->_next;
		}
		else
		{
			SlistNode* tmp = new SlistNode(x);
			tmp->_next = pos->_next;
			pos->_next = tmp;
		}
	}
private:
	void Destory()
	{
		SlistNode* begin = _head;
		while (begin)
		{
			SlistNode* tmp = begin;
			begin = begin->_next;
			delete tmp;
			tmp = NULL;
		}
		_tail = _head = NULL;
	}
private:
	SlistNode* _head;
	SlistNode* _tail;
};

void test1()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.Display();

	s1.PopFront();
	s1.PopFront();
	s1.PopFront();
	s1.Display();

	s1.PushFront(1);
	s1.PushFront(2);
	s1.PushFront(3);
	s1.Display();

	s1.PopBack();
	s1.PopBack();
	s1.PopBack();
	s1.Display();
}

void test2()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.Display();

	SlistNode* tmp = s1.Find(3);
	s1.Insert(tmp, 4);
	s1.Display();
}

void test3()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.Display();

	Slist s2(s1);
	s2.Display();

	Slist s3;
	s3 = s1;
	s3.Display();

	Slist s4;
	s4.PushBack(4);
	s4 = s1;
	s4.Display();
}
int main()
{
	//test1();
	test2();
	test3();
	system("pause");
	return 0;
}