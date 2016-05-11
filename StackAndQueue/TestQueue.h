#include <iostream>
#include "Queue.h"
using namespace std;

void test_queue1()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	q.Push(5);
	q.Push(6);
	q.Print();

	int a;
	a = q.Pop();
	cout << "出队列元素:" << a << endl;
	a = q.Pop();
	cout << "出队列元素:" << a << endl;
	a = q.Pop();
	cout << "出队列元素:" << a << endl;
	q.Print();
	a = q.Pop();
	cout << "出队列元素:" << a << endl;
	a = q.Pop();
	cout << "出队列元素:" << a << endl;
	a = q.Pop();
	cout << "出队列元素:" << a << endl;
}

void test_queue2()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Print();
	Queue<int> q1(q);
	q1.Print();
	Queue<int> q2;
	q2 = q1;
	q2.Print();
}