#pragma once 

template <class K, class V>
//������ʵ��
struct AVLTreeNode
{
	//�ڵ�����Һ��ӣ���ָ��
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	//key,value
	K _key;
	V _value;

	//ƽ������
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

	//insert˼·��
	//1.����
	//2.����λ�ã�����ڵ�
	//3.����ƽ�����ӣ�������
	//4.�����������ת����parent��������
	//��ע����ϸ˼��ÿ�����������ϸ��
	bool Insert(const K& key, const V& value)
	{
		//�Ƿ���ת
		bool IsRotate = false;
		return _Insert(key, value, IsRotate);
	}

	//��ѯ�ڵ�
	Node* Find(const K& key)
	{
		return _Find(_root, key);
	}

	//�������
	void InorderTree()
	{
		cout << "AVLTree INorder:";
		_InorderTree(_root);
		cout << endl;
	}

	//�ж��ǲ���ƽ�������
	bool IsBalanceTree()
	{
		return _IsBalanceTree(_root);
	}
protected:
	bool _IsBalanceTree(Node* root)
	{
        //�жϸ߶�֮��
		if (NULL == root)
		{
			return false;
		}

		int LeftHeight = _IsBalanceTree(root->_left) + 1;
		int RightHeight = _IsBalanceTree(root->_right) + 1;
		
		//��������������߶�֮��
		//�ж�ƽ������
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
		//��ʼʱ��Ϊ��
		if (_root == NULL)
		{
			_root = (Node*) new Node(key, value);
			return true;
		}

		Node* cur = _root;     //����ͷ�ڵ�
		Node* prev = NULL;
		int flag = -1;

		while (cur)
		{
			if (key > cur->_key)
			{
				prev = cur;     //����ǰһ��
				flag = 1;        //��־λ������
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				prev = cur;
				flag = 0;         //����
				cur = cur->_left;
			}
			else
			{
				break;
			}
		}

		if (flag == 0)    //����
		{
			cur = (Node*) new Node(key, value);
			prev->_left = cur;
			cur->_parent = prev;
		}
		if (flag == 1)    //����
		{
			cur = (Node*) new Node(key, value);
			prev->_right = cur;
			cur->_parent = prev;
		}

		//��ʱ�ڵ��Ѳ����������Ҫ����ƽ������
		Node* parent = cur->_parent;
		//��parentһֱ����_root���ڵ�
		while (parent)
		{
			//����ƽ������
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

			//������
			if (parent->_bf >1)
			{
				if (cur->_bf == 1)
				{
					//����
					_RotateL(parent);
					IsRorate =  true;
				}
				if (cur->_bf == -1)
				{
					//����˫��
					_RotateRL(parent);
					IsRorate =  true;
				}
			}
			if( parent->_bf < -1)
			{
				if (cur->_bf == -1)
				{
					//�ҵ���
					_RotateR(parent);
					IsRorate = true;
				}
				if (cur->_bf == 1)
				{
					//����˫��
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

		parent->_bf = subR->_bf = 0;
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

		parent->_bf = subL->_bf = 0;
		parent = subL;
		if (parent->_parent == NULL)
		{
			_root = parent;
		}
	}

	//����˫��
	void _RotateLR(Node*& parent)
	{
		//����
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

		//����
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

	//����˫�� 
	void _RotateRL(Node*& parent)
	{
		//����
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
		//����
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

	//�������
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

