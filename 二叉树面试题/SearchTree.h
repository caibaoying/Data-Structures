#pragma once
#pragma warning(disable:4018)
#include <assert.h>

//搜索二叉树的结构
template <class K, class V>
struct  BinarySearchNode
{
	BinarySearchNode<K,V>* _left;    //左孩子
	BinarySearchNode<K,V>* _right;   //右孩子
	K _key;                          //关键码
	V _value;
	BinarySearchNode(const K& key,const V& value)
		:_left(NULL)
		, _right(NULL)
		, _key(key)
		, _value(value)
	{}
};

template <class K, class V>
class BinarySearchTree
{
	typedef BinarySearchNode<K,V> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}

	Node* Root()
	{
		return _root;
	}

	~BinarySearchTree()
	{}

public:
	void Create_R(const K* a, size_t size)
	{
		assert(a);
		for (size_t i = 0; i < size; ++i)
		{
			Insert_R(_root, a[i], a[i]);
		}
	}
	void Create(const K* a, size_t size)
	{
		assert(a);
		for (size_t i = 0; i < size; ++i)
		{
			Insert(a[i], a[i]);
		}
	}

    //非递归插入
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = (Node*) new Node(key, value);
			return true;
		}
		
		Node* cur = _root;     //保存头节点
		Node* prev = NULL;
		int flag = -1;

		while (cur)
		{
			if (key > cur->_key)
			{
				prev = cur;     //保存前一个
				flag = 1;        //标志位，向右
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				prev = cur;
				flag = 0;         //向左
				cur = cur->_left;
			}
			else
			{
				break;
			}				
		}

		if (flag == 0)    //向左
			prev->_left = (Node*) new Node(key, value);
		if (flag == 1)    //向右
			prev->_right = (Node*) new Node(key, value);
	}

	//非递归
	bool Remove(const K& key)
	{
		Node* cur = _root;
		Node* prev = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				prev = cur;
				cur = cur->_right;
			}
			else
			{
				//找到了,分两种情况
				if (cur->_left == NULL)
				{
					if (prev->_left == cur)
					{
						prev->_left = cur->_right;
						return true;
					}
					if (prev->_right == cur)
					{
						prev->_right = cur->_right;
						return true;
					}
				}
				else if (cur->_right == NULL)
				{
					if (prev->_left == cur)
					{
						prev->_left = cur->_left;
						return true;
					}
					if (prev->_right == cur)
					{
						prev->_right = cur->_left;
						return true;
					}
				}
				else
				{
					//删除的节点左右孩子都不为空
					//先找到右树中序遍历的第一个节点tmp
					Node* tmp = cur->_right;
					prev = cur;
					while (tmp && tmp->_left)
					{
						prev = tmp;
						tmp = tmp->_left;
					}
					swap(cur->_key,tmp->_key);
					swap(cur->_value, tmp->_value);
					//删除tmp
					//找到了左孩子定为空
					if (prev && prev->_left == tmp)
					{
						prev->_left = tmp->_right;
						return true;
					}
					if (prev && prev->_right == tmp)
					{
						prev->_right = tmp->_right;
						return true;
					}
				}
			}
		}
		delete cur;
		return false;
	}

	//递归删除
	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}

	

	//非递归找节点
	Node* Find(const K& key)
	{
		if (_root == NULL)
		{
			return NULL;
		}
		
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}

	//递归查找
	Node* Find_R(const K& key)
	{
		return _Find_R(_root, key);
	}

	void InorderTree()
	{
		_InorderTree(_root);
	}

protected:
	Node* _Find_R(Node* root, const K& key)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->_key > key)
		{
			_Find_R(root->_left, key);
		}
		else if (root->_key < key)
		{
			_Find_R(root->_right, key);
		}
		else
		{
			return root;
		}
	}

	bool _Remove_R(Node*& root, const K& key)
	{
		if (NULL == root)
		{
			return false;
		}

		Node* cur = root;
		if (cur->_key > key)
		{
			_Remove_R(cur->_left, key);
		}
		else if (cur->_key < key)
		{
			_Remove_R(cur->_right, key);
		}
		else
		{
			if (cur->_left == NULL)
			{
				cur = cur->_right;
				return true;
			}
			else if (cur->_right == NULL)
			{
				cur = cur->_left;
				return true;
			}
			else
			{
				Node* tmp = cur->_right;
				Node* prev = cur;
				while (tmp->_left)
				{
					prev = tmp;
					tmp = tmp->_left;
				}
				swap(cur->_key, tmp->_key);
				swap(cur->_value, tmp->_value);
				prev->_left = tmp->_right;
			}
		}
	}

	//递归插入
	bool Insert_R(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = (Node*)new Node(key, value);
			return true;
		}
		else if (root->_key < key)
		{
			Insert_R(root->_right, key, value);
		}
		else if (root->_key > key)
		{
			Insert_R(root->_left, key, value);
		}
		else
		{
			return false;
		}
	}

	//中序遍历可以排序
	void _InorderTree(const Node* root)
	{
		const Node* cur = root;
		if (cur == NULL)
		{
			//cout << cur->_key << " ";
			return;
		}
		_InorderTree(cur->_left);
		cout << cur->_value << " ";
		_InorderTree(cur->_right);
	}
private:
	Node* _root;
};

void Test()
{
	int a[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BinarySearchTree<int,int> BS;
	
	cout << "非递归建树：";
	BS.Create(a, sizeof(a) / sizeof(int));
	BS.InorderTree();
	cout << endl;

	cout << "递归建树：";
	BS.Create_R(a, sizeof(a) / sizeof(int));
	BS.InorderTree();
	cout << endl;

	cout << "非递归删除：";
	//BS.Remove(4);
	BS.Remove(5);
	BS.InorderTree();
	cout << endl;

	cout << "递归删除：";
	BS.Remove_R(5);
	BS.InorderTree();
	cout << endl;

	cout << "非递归FIND：";
	BinarySearchNode<int, int>* Node = BS.Find(7);
	cout << Node->_key << ":" << Node->_value << endl;

	cout << "递归FIND：";
	Node = BS.Find_R(7);
	cout << Node->_key << ":" << Node->_value << endl;
}