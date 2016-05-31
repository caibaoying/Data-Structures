#pragma once

//״̬��
enum color
{
	RED,
	BLACK
};

template <class K, class V>
struct RBTreeNode
{
	//������ʵ��
	RBTreeNode<K, V>* _parent;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;

	color _color;     //��ɫ

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
	//���ڽڵ���ɫ������ͬ
	//��ɫ�ڵ�ĸ�����ȣ�
	bool _IsBlance(Node* root)
	{
		if (NULL == root)
		{
			return false;
		}

		//ֻ��һ���ڵ�
		if (root->_left == NULL && root->_right == NULL)
		{
			return true;
		}

		//���������Ͻڵ�
		return ColorUnSame(root) && BCountSame(root);
	}

	//�����������ɫ��ͬ
	bool ColorUnSame(Node* root)
	{
		return _ColorSame(root);
	}

	//ÿ���ڵ�����������ĺڽڵ������ͬ
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

		//����֮�����
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
		//��һ�����
		/* cur Ϊ�죬pΪ�죬gΪ�ڣ�u������Ϊ�죬
		��p,u��Ϊ�ڣ�g ��Ϊ�죬Ȼ���g����cur,�������ϵ���*/
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
		//�ڶ������
		/*curΪ�죬pΪ��,gΪ�ڣ�u�����ڻ�Ϊ�ڣ�
		if(p = g->_left && cur = p->_left)  �ҵ���ת
		if(p = g->_right && cur = p->right)  ����ת
		p,g��ɫ��p���,g ���
		*/
		if (cur->_color == RED && parent->_color == RED && grandpa 
			&& grandpa->_color == BLACK && (!uncle || uncle->_color == BLACK))
		{
			if (parent->_left == cur && grandpa->_left == parent)
			{
				//��g�ҵ���ת
				_RotateR(grandpa);
				_Link(grandpa, key);
				grandpa = parent->_right;

				parent->_color = BLACK;
				grandpa->_color = RED;
				return;
			}
			else if (parent->_right == cur && grandpa->_right == parent)
			{
				//��g����ת
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
		//���������
		/**/
		if (cur->_color == RED && parent->_color == RED && grandpa 
			&& grandpa->_color == BLACK && (!uncle || uncle->_color == BLACK))
		{
			if (parent->_right == cur && grandpa->_left == parent)
			{
				//��p����ת
				_RotateL(parent);
				_Link(parent, key);

				//����֮��cur�����˱仯
				cur = parent->_left;
				//_AjustTwo(cur, grandpa, parent, uncle, key);
				_AjustTwo(cur, grandpa, parent, uncle, key);

				return;
			}
			else if (parent->_left == cur && grandpa->_right == parent)
			{
				//��p�ҵ���ת
				_RotateR(parent);
				_Link(parent, key);

				cur = parent->_right;
				_AjustTwo(cur, grandpa, parent, uncle, key);
				return;
			}
		}
	}

	//����
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

	//�ҵ���
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
		//û����
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