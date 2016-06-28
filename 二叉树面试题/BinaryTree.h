#pragma once 
#include <vector>
#include <queue>
#include <assert.h>
#include <stack>
#include <iostream>
using namespace std;
//关注结构

template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode<T>* _parent;
	BinaryTreeNode(T data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* a, size_t size)
	{
		size_t index = 0;
		_root = _Create(a,size,index); 
	}

	BinaryTreeNode<T>* Root()
	{
		return _root;
	}

	~BinaryTree()
	{}
	void PrevOrder()
	{
		_PrevOrder(_root);
	}
	void InOrder()
	{
		_InOrder(_root);
	}
	void PastOrder()
	{
		_PastOrder(_root);
	}
	void LevelOrder()
	{
		if (_root == NULL)
		{
			return;
		}
		queue<BinaryTreeNode<T>*> cur;
		cur.push(_root);
		
		while (!cur.empty())
		{
			BinaryTreeNode<T>* front = cur.front();
			if (front->_left)
			{
				cur.push(front->_left);
			}
			if (front->_right)
			{
				cur.push(front->_right);
			}
			cout << front->_data << " ";
			cur.pop();
		}
		cout << endl;
	}
	int Size()
	{
		return _Size(_root);
	}
	int Depth1()
	{
		return _Depth1(_root);
	}
	BinaryTreeNode<T>* Find(BinaryTreeNode<T>& x)
	{
		if (_root == NULL)
		{
			return NULL;
		}
		queue<BinaryTreeNode<T>*> cur;
		cur.push(_root);
		while (!cur.empty())
		{
			BinaryTreeNode<T>* tmp = cur.front();
			if (tmp->_data == x._data )      //   ?????????
			{
				return tmp;
			}
			if (tmp->_left)
			{
				cur.push(tmp->_left);
			}
			if (tmp->_right)
			{
				cur.push(tmp->_right);
			}
			cur.pop();
		}
		return _root;
	}
	//先序遍历的非递归实现
	void Prev_NonR()
	{
		_Prev_NonR(_root);
	}
	//中序遍历的非递归实现
	void In_NonR()
	{
		_In_NonR(_root);
	}
	//后续遍历的非递归实现,两个指针
	void Past_NonR()
	{
		_Past_NonR(_root);
	}
	/*int Depth2()
	{
		if (_root == NULL)
		{
			return 0;
		}
		
		return _Depth2(_root->_left, _root->_right) + 1;
	}*/
protected:
	void _Past_NonR(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		stack<BinaryTreeNode<T>*> Stack;
		BinaryTreeNode<T> *cur;                      //当前结点 
		BinaryTreeNode<T> *pre = NULL;                 //前一次访问的结点 
		Stack.push(root);
		while (!Stack.empty())
		{
			cur = Stack.top();
			if ((cur->_left == NULL && cur->_right == NULL) ||
				(pre && (pre == cur->_left || pre == cur->_right)))
			{
				cout << cur->_data << " ";  //如果当前结点没有孩子结点或者孩子节点都已被访问过 
				Stack.pop();
				pre = cur;
			}
			else
			{
				if (cur->_right != NULL)
					Stack.push(cur->_right);
				if (cur->_left != NULL)
					Stack.push(cur->_left);
			}
		}
		cout << endl;
	}
	void _In_NonR(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		stack<BinaryTreeNode<T>*> Stack;
		BinaryTreeNode<T>* ROOT = root;
		BinaryTreeNode<T>* cur = NULL; 
		//先把左边不为空的节点依次入栈
		Stack.push(ROOT);
		while (!Stack.empty())
		{
			while (ROOT->_left)
			{
				ROOT = ROOT->_left;
				Stack.push(ROOT);
			}
			//到达了最左边最后一个子节点
			//if (ROOT)
			//{
			//	/*BinaryTreeNode<T>* tmp;*/
			//	cout << Stack.top()->_data << " ";
			//	Stack.pop();
			//}
			if (!Stack.empty())
			{
				if (cur != Stack.top()->_right && Stack.top()->_right != NULL)
				{
					cur = Stack.top();
					cur = cur->_right;
					cout << Stack.top()->_data << " ";
					Stack.pop();
					Stack.push(cur);
					ROOT = cur;
				}
			}
		}
		cout << endl;
	}
	void _Prev_NonR(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		stack<BinaryTreeNode<T>*> cur;
		cur.push(root);
		while (!cur.empty())
		{
			BinaryTreeNode<T>* top = cur.top();
			cur.pop();
			if (top->_right)
			{
				cur.push(top->_right);
			}
			if (top->_left)
			{
				cur.push(top->_left);
			}
			cout << top->_data << " ";
		}
	}
	int _Depth1(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		BinaryTreeNode<T>* cur = root;
		if (cur)
		{
			int Ldepth = _Depth1(cur->_left);
			int Rdepth = _Depth1(cur->_right);
			return ((Ldepth > Rdepth) ? Ldepth : Rdepth) + 1;
		}
		return 0;
	}
	/*int _Depth2(BinaryTreeNode<T>* left, BinaryTreeNode<T>* right)
	{
		if (left)
		{
			return depth1 = _Depth(left->_left, left->_right)+1;
		}
		if (right)
		{
			int depth2 = _Depth(left->_left, left->_right) + 1;
		}
		if (depth1 > depth2)
		{
			return depth1;
		}
		return depth2;
	}*/
	int _Size(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		return _Size(root->_left) + _Size(root->_right) + 1;

	}
	void _PastOrder(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* cur = root;
		if (cur == NULL)
		{
			//cout << "NULL";
			return;
		}
		_PastOrder(cur->_left);
		_PastOrder(cur->_right);
		cout << cur->_data << " ";
	}
	void _InOrder(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* cur = root;
		if (cur == NULL)
		{
			//cout << "NULL";
			return;
		}
		_InOrder(cur->_left);
		cout << cur->_data << " ";
		_InOrder(cur->_right);
	}
	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* cur = root;
		if (cur == NULL)
		{
			//cout << "NULL";
			return;
		}
		cout << cur->_data << " ";
		_PrevOrder(cur->_left);
		_PrevOrder(cur->_right);
	}
	BinaryTreeNode<T>* _Create(const T* a, size_t size, size_t& index)
	{
		assert(a);
		BinaryTreeNode<T>* root = NULL;
		//先序遍历
		if (index < size && a[index] != '#')    //遍历
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _Create(a, size, ++index);
			root->_right = _Create(a, size, ++index);
		}
		return root;
	}
private:
	BinaryTreeNode<T>* _root; 
};

void TestBinary()
{
	char arr[] = { '1', '2', '#','#', '3', '4', '#', '#','5','6'};
	BinaryTree<char> bt(arr,10);
	cout << "先序遍历：" << endl;
	bt.PrevOrder();
	cout << endl;
	cout << "中序遍历：" << endl;
	bt.InOrder();
	cout << endl;
	cout << "后序遍历：" << endl;
	bt.PastOrder();
	cout << endl;
	cout << "层次遍历：" << endl;
	bt.LevelOrder();
	cout << "树大小：" << endl;
	cout << bt.Size() << endl;
	cout << "树深度：" << endl;
	cout << bt.Depth1() << endl;
	BinaryTreeNode<char> x('1');
	BinaryTreeNode<char>* t = bt.Find(x);
	cout << "找到指定节点：" << endl;
	cout << t->_data<< endl;
	cout << "非递归先序遍历：" << endl;
	bt.Prev_NonR();
	cout << endl;
	cout << "非递归中序遍历：" << endl;
	bt.In_NonR();
	cout << "非递归后序遍历：" << endl;
	bt.Past_NonR();
}