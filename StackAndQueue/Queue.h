#include <iostream>
using namespace std;

template <class T>
struct Node
{
	Node(const T& data)
	:_data(data)
	, _next(NULL)
	{}
	T _data;
	Node<T>* _next;
};

template <class T>
class Queue
{
public:
	Queue()
		: _head(NULL)
		, _tail(NULL)
	{}
	Queue(const Queue<T>& q)
	{
		Node<T>* q1 = q._head;
		_head = new Node<T>(q._head->_data);
		_tail = _head;
		q1 = q1->_next;
		while (q1)
		{
			_tail->_next = new Node<T>(q1->_data);
			_tail = _tail->_next;
			q1 = q1->_next;
		}
	}
	Queue<T>& operator=(const Queue<T>& q)
	{
		if (_head != NULL)
		{
			Destory();
		}
		Node<T>* q1 = q._head;
		_head = new Node<T>(q._head->_data);
		_tail = _head;
		q1 = q1->_next;
		while (q1)
		{
			_tail->_next = new Node<T>(q1->_data);
			_tail = _tail->_next;
			q1 = q1->_next;
		}
		return *this;
	}
	~Queue()
	{
		Destory();
	}
public:
	//为空或不为空
	void Push(const T& x)
	{
		if (NULL == _head)
		{
			_head = new Node<T>(x);
			_tail = _head;
			_tail->_next = NULL;
		}
		else
		{
			_tail->_next = new Node<T>(x);
			_tail = _tail->_next;
			_tail->_next = NULL;
		}
	}
	T& Pop()
	{
		if (NULL == _head)
		{
			cout << "该队列为空" << endl;
		}
		else
		{
			Node<T>* tmp = _head;
			_head = _head->_next;
			return tmp->_data;
			delete tmp;
		}
	}
	void Print()
	{
		Node<T>* tmp = _head;
		while (tmp)
		{
			cout << tmp->_data << "<-";
			tmp = tmp->_next;
		}
		cout << endl;
	}
	
private:
	void Destory()
	{
		Node<T>* begin = _head;
		while (begin)
		{
			Node<T>* tmp = begin;
			begin = begin->_next;
			delete tmp;
			tmp = NULL;
		}
		_tail = _head = NULL;
	}
private:
	Node<T>* _head;
	Node<T>* _tail;
};