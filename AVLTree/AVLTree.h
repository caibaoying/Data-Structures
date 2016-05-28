#pragma once 

template <class K, class V>
//三叉链实现
struct AVLTreeNode
{
	//节点的左右孩子，父指针
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	//key,value
	K _key;
	V _value;

	//平衡因子
	int _bf;

	AVLTreeNode(const K& key = K(), const V& value = V())
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _bf(0)
	{

	}
};

template <class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	~AVLTree()
	{}

public:

	//insert思路：
	//1.空树
	//2.查找位置，插入节点
	//3.更新平衡因子，调整树
	//4.如果发生了旋转，将parent重新连接
	//备注：详细思考每种情况，考虑细节
	bool Insert(const K& key, const V& value)
	{
		//是否旋转
		bool IsRotate = false;
		return _Insert(key, value, IsRotate);
	}

	//查询节点
	Node* Find(const K& key)
	{
		return _Find(_root, key);
	}

	//中序遍历
	void InorderTree()
	{
		cout << "AVLTree INorder:";
		_InorderTree(_root);
		cout << endl;
	}

	//判断是不是平衡二叉树
	bool IsBalanceTree()
	{
		return _IsBalanceTree(_root);
	}
protected:
	bool _IsBalanceTree(Node* root)
	{
        //判断高度之差
		if (NULL == root)
		{
			return false;
		}

		int LeftHeight = _IsBalanceTree(root->_left) + 1;
		int RightHeight = _IsBalanceTree(root->_right) + 1;
		
		//右树减左树算出高度之差
		//判断平衡因子
		int subH = abs(RightHeight - LeftHeight);
		return (subH <= 1 && (abs(subH - root->_bf) == 0));
	}

	Node* _Find(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;

		if (root->_key == key)
		{
			return root;
		}
		else if (root->_key > key)
		{
			_Find(root->_left, key);
		}
		else if (root->_key < key)
		{
			_Find(root->_right, key);
		}
		else
		{
			return NULL;
		}
	}

	bool _Insert(const K& key, const V& value, bool& IsRorate)
	{
		//开始时树为空
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
		{
			cur = (Node*) new Node(key, value);
			prev->_left = cur;
			cur->_parent = prev;
		}
		if (flag == 1)    //向右
		{
			cur = (Node*) new Node(key, value);
			prev->_right = cur;
			cur->_parent = prev;
		}

		//此时节点已插入进来，需要调整平衡因子
		Node* parent = cur->_parent;
		//从parent一直调到_root根节点
		while (parent)
		{
			//调整平衡因子
			if (parent->_left == cur)
			{
				parent->_bf--;
				if (parent->_bf == 0)
					break;
			}
			if (parent->_right == cur)
			{
				parent->_bf++;
				if (parent->_bf == 0)
					break;
			}

			//调整树
			if (parent->_bf >1)
			{
				if (cur->_bf == 1)
				{
					//左单旋
					_RotateL(parent);
					IsRorate =  true;
				}
				if (cur->_bf == -1)
				{
					//右左双旋
					_RotateRL(parent);
					IsRorate =  true;
				}
			}
			if( parent->_bf < -1)
			{
				if (cur->_bf == -1)
				{
					//右单旋
					_RotateR(parent);
					IsRorate = true;
				}
				if (cur->_bf == 1)
				{
					//左右双旋
					_RotateLR(parent);
					IsRorate = true;
				}
			}
			Node* tmp = parent;
			cur = parent;
			parent = parent->_parent;
			if (IsRorate && parent)
			{
				if (parent->_key > tmp->_key)
				{
					parent->_left = tmp;
				}
				else
				{
					parent->_right = tmp;
				}
				break;
			}
		}
		return true;
	}

	//左单旋
	void _RotateL(Node*& parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		parent->_bf = subR->_bf = 0;
		parent = subR;
		if (parent->_parent == NULL)
		{
			_root = parent;
		}
	}

	//右单旋
	void _RotateR(Node*& parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		parent->_bf = subL->_bf = 0;
		parent = subL;
		if (parent->_parent == NULL)
		{
			_root = parent;
		}
	}

	//左右双旋
	void _RotateLR(Node*& parent)
	{
		//左旋
		//parent = parent->_left;
		Node* subP = parent->_left;
		Node* subR = parent->_left->_right;
		Node* subRL = subR->_left;

		subP->_right = subRL;
		if (subRL)
		{
			subRL->_parent = subP;
		}

		subR->_left = subP;
		subR->_parent = subP->_parent;
		subP->_parent = subR;
		parent->_left = subR;

		//右旋
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;
		subL->_parent = parent->_parent;
		parent->_parent = subL;

		if (subR->_bf == -1)
		{
			subP->_bf = 0;
			parent->_bf = 1;
		}
		else if (subR->_bf == 0)
		{
			parent->_bf = 0;
			subP->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subP->_bf = -1;
		}

		parent = subL;
		parent->_bf = 0;
		if (parent->_parent == NULL)
		{
			_root = parent;
		}
	}

	//右左双旋 
	void _RotateRL(Node*& parent)
	{
		//右旋
		//parent = parent->_right;
		Node* subP = parent->_right;
		Node* subL = parent->_right->_left;
		Node* subLR = subL->_right;

		subP->_left = subLR;
		if (subLR)
		{
			subLR->_parent = subP;
		}

		subL->_right = subP;
		subL->_parent = subP->_parent;
		subP->_parent = subL;
		parent->_right = subL;

		//////////////////////////////////////////
		//左旋
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		subR->_left = parent;
		subR->_parent = parent->_parent;
		parent->_parent = subR;

		if (subL->_bf == -1)
		{
			subP->_bf = 1;
			parent->_bf = 0;
		}
		else if (subL->_bf == 0)
		{
			parent->_bf = 0;
			subP->_bf = 0;
		}
		else
		{
			parent->_bf = -1;
			subP->_bf = 0;
		}

		parent = subR;
		parent->_bf = 0;

		if (parent->_parent == NULL)
		{
			_root = parent;
		}
	}

	//中序遍历
	void _InorderTree(Node* root)
	{
		if (NULL == root)
		{
			return;
		}
		_InorderTree(root->_left);
		cout << root->_key << " ";
		_InorderTree(root->_right);
	}
private:
	Node* _root;
};

