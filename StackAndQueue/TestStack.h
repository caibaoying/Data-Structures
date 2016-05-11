#include <iostream>
#include "Stack.h"
using namespace std;

void test_stack1()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);
	s1.Push(6);
	s1.Print();

	Stack<string> s2;
	s2.Push("x1");
	s2.Push("x2222222222222222222222222222222222222");
	s2.Push("x3");
	s2.Push("x4");
	s2.Print();

	Stack<string> s3(s2);
	s3.Print();
	Stack<string> s4;
	s4 = s3;
	s4.Print();
}

void test_stack2()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);
	s1.Push(6);
	s1.Print();

	int a1 = s1.Pop();
	cout << "出栈元素为：" << a1 << endl;
	a1 = s1.Pop();
	cout << "出栈元素为：" << a1 << endl;
	a1 = s1.Pop();
	cout << "出栈元素为：" << a1 << endl;
	s1.Print();
	a1 = s1.Pop();
	cout << "出栈元素为：" << a1 << endl;
	a1 = s1.Pop();
	cout << "出栈元素为：" << a1 << endl;
	a1 = s1.Pop();
	cout << "出栈元素为：" << a1 << endl;
	s1.Print();
}

void test_stack3()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Print();
	Stack<int> s2(s1);
	s2.Print();
	Stack<int> s3;
	s3 = s2;
	s3.Print();
}