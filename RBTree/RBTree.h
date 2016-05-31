#pragma once

//状态机
enum color
{
	RED,
	BLACK
};

template <class K, class V>
struct RBTreeNode
{
	//三叉链实现
	RBTreeNode<K, V>* _parent;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;

	color _color;     //颜色

	//key,value
	K _key;
	V _value;
	RBTreeNode(const K& key, const V& value, color Color = RED)
		:_parent(NULL)
		, _left(NULL)
		, _right(NULL)
		, _key(key)
		, _value(value)
		, _color(Color)
	{}
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		return _Insert(key, value);
	}

	void Inorder()
	{
		cout << "Inorder:";
		_Inorder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		return _IsBlance(_root);
	}
	~RBTree()
	{}

protected:
	//相邻节点颜色不能相同
	//黑色节点的个数相等，
	bool _IsBlance(Node* root)
	{
		if (NULL == root)
		{
			return false;
		}

		//只有一个节点
		if (root->_left == NULL && root->_right == NULL)
		{
			return true;
		}

		//两个及以上节点
		return ColorUnSame(root) && BCountSame(root);
	}

	//相邻两点的颜色不同
	bool ColorUnSame(Node* root)
	{
		return _ColorSame(root);
	}

	//每个节点的左右子树的黑节点个数相同
	bool BCountSame(Node* root)
	{
		int CountL = 0, CountR = 0;
		return _BCountSame(root, CountL, CountR);
	}

	bool _ColorSame(Node* root)
	{
		if (root == NULL)
		{
			return true;
		}

		_ColorSame(root->_left);

		//root->parent
		Node* cur = root;
		Node* parent = cur;
		if (cur && cur->_parent)
		parent = cur->_parent;
		if (cur && parent && ((parent->_color == RED && cur->_color == BLACK) 
			|| (parent->_color == BLACK && cur->_color == RED) 
			|| (parent->_color == BLACK && cur->_color == BLACK)
			|| (cur->_key == parent->_key)))
		{
			return true;
		}
		else
		{
			return false;
		}

		_ColorSame(root->_right);
	}

	bool _BCountSame(Node* root, int& CountL, int& CountR)
	{
		if (root == NULL)
		{
			return true;
		}

		if (root->_color == BLACK)
		{
			CountL = _BCountSame(root->_left, CountL, CountR) + 1;
			CountR = _BCountSame(root->_right, CountL, CountR) + 1;
		}
		else
		{
			_BCountSame(root->_left, CountL, CountR);
			_BCountSame(root->_right, CountL, CountR);
		}
		if (CountL == CountR)
			return true;
		return false;
	}

	bool _Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = (Node*) new Node(key, value, BLACK);
			return true;
		}
		
		Node* prev = NULL;
		Node* cur = _root;
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
				return false;
			}
		}

		if (prev->_key > key)
		{
			cur = (Node*) new Node(key, value, RED);
			prev->_left = cur;
			cur->_parent = prev;
		}
		else
		{
			cur = (Node*) new Node(key, value, RED);
			prev->_right = cur;
			cur->_parent = prev;
		}

		//插入之后调整
		Node* parent = prev;

		Node* grandpa = cur->_parent->_parent;
		parent = cur->_parent;
		Node* uncle = NULL;
		if (grandpa && grandpa->_left == parent)
			uncle = grandpa->_right;
		if (grandpa && grandpa->_right == parent)
			uncle = grandpa->_left;
		
		while (cur != _root && parent->_color == RED)
		{
			_AjustOne(cur, grandpa, parent, uncle, key);
			_AjustTwo(cur, grandpa, parent, uncle, key);
		    _AjustThree(cur, grandpa, parent, uncle, key);
		}
		_root->_color = BLACK;
	    return true;
    }

	void _AjustOne(Node*& cur, Node*& grandpa, Node*& parent, Node*& uncle, const K& key)
	{
		//第一种情况
		/* cur 为红，p为红，g为黑，u存在且为红，
		则将p,u改为黑，g 改为红，然后把g当成cur,继续向上调整*/
		if (cur->_color == RED && parent->_color == RED && grandpa 
			&& grandpa->_color == BLACK && uncle && uncle->_color == RED)
		{
			parent->_color = uncle->_color = BLACK;
			grandpa->_color = RED;
			if (grandpa->_parent && grandpa->_parent->_parent)
			{
				cur = grandpa;
				parent = cur->_parent;
				grandpa = cur->_parent->_parent;
				if (grandpa && grandpa->_left == parent)
					uncle = grandpa->_right;
				if (grandpa && grandpa->_right == parent)
					uncle = grandpa->_left;
			}
		}
	}

	void _AjustTwo(Node*& cur, Node*& grandpa, Node*& parent, Node*& uncle, const K& key)
	{
		//第二种情况
		/*cur为红，p为红,g为黑，u不存在或为黑，
		if(p = g->_left && cur = p->_left)  右单旋转
		if(p = g->_right && cur = p->right)  左单旋转
		p,g变色，p变黑,g 变红
		*/
		if (cur->_color == RED && parent->_color == RED && grandpa 
			&& grandpa->_color == BLACK && (!uncle || uncle->_color == BLACK))
		{
			if (parent->_left == cur && grandpa->_left == parent)
			{
				//对g右单旋转
				_RotateR(grandpa);
				_Link(grandpa, key);
				grandpa = parent->_right;

				parent->_color = BLACK;
				grandpa->_color = RED;
				return;
			}
			else if (parent->_right == cur && grandpa->_right == parent)
			{
				//对g左单旋转
				_RotateL(grandpa);
				_Link(grandpa, key);

				grandpa = parent->_left;
				parent->_color = BLACK;
				grandpa->_color = RED;
				return;
			}
		}
	}

	void _AjustThree(Node*& cur, Node*& grandpa, Node*& parent, Node*& uncle, const K& key)
	{
		//第三种情况
		/**/
		if (cur->_color == RED && parent->_color == RED && grandpa 
			&& grandpa->_color == BLACK && (!uncle || uncle->_color == BLACK))
		{
			if (parent->_right == cur && grandpa->_left == parent)
			{
				//对p左单旋转
				_RotateL(parent);
				_Link(parent, key);

				//调整之后cur发生了变化
				cur = parent->_left;
				//_AjustTwo(cur, grandpa, parent, uncle, key);
				_AjustTwo(cur, grandpa, parent, uncle, key);

				return;
			}
			else if (parent->_left == cur && grandpa->_right == parent)
			{
				//对p右单旋转
				_RotateR(parent);
				_Link(parent, key);

				cur = parent->_right;
				_AjustTwo(cur, grandpa, parent, uncle, key);
				return;
			}
		}
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

		parent = subL;
		if (parent->_parent == NULL)
		{
			_root = parent;
		}
	}

	void _Link(Node*& parent,const K& key)
	{
		Node* tmp = parent->_parent;
		//没连上
		if (tmp && tmp->_key > key)
		{
			tmp->_left = parent;
		}
		if (tmp && tmp->_key < key)
		{
			tmp->_right = parent;
		}
	}

	void _Inorder(Node* root)
	{
		if (root == NULL)
			return;
		_Inorder(root->_left);
		cout << root->_key << " ";
		_Inorder(root->_right);
	}
private:
	Node* _root;
};