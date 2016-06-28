#pragma once
#pragma warning(disable:4018)
#include <assert.h>

//�����������Ľṹ
template <class K, class V>
struct  BinarySearchNode
{
	BinarySearchNode<K,V>* _left;    //����
	BinarySearchNode<K,V>* _right;   //�Һ���
	K _key;                          //�ؼ���
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

    //�ǵݹ����
	bool Insert(const K& key, const V& value)
	{
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
			prev->_left = (Node*) new Node(key, value);
		if (flag == 1)    //����
			prev->_right = (Node*) new Node(key, value);
	}

	//�ǵݹ�
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
				//�ҵ���,���������
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
					//ɾ���Ľڵ����Һ��Ӷ���Ϊ��
					//���ҵ�������������ĵ�һ���ڵ�tmp
					Node* tmp = cur->_right;
					prev = cur;
					while (tmp && tmp->_left)
					{
						prev = tmp;
						tmp = tmp->_left;
					}
					swap(cur->_key,tmp->_key);
					swap(cur->_value, tmp->_value);
					//ɾ��tmp
					//�ҵ������Ӷ�Ϊ��
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

	//�ݹ�ɾ��
	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}

	

	//�ǵݹ��ҽڵ�
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

	//�ݹ����
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

	//�ݹ����
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

	//���������������
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
	
	cout << "�ǵݹ齨����";
	BS.Create(a, sizeof(a) / sizeof(int));
	BS.InorderTree();
	cout << endl;

	cout << "�ݹ齨����";
	BS.Create_R(a, sizeof(a) / sizeof(int));
	BS.InorderTree();
	cout << endl;

	cout << "�ǵݹ�ɾ����";
	//BS.Remove(4);
	BS.Remove(5);
	BS.InorderTree();
	cout << endl;

	cout << "�ݹ�ɾ����";
	BS.Remove_R(5);
	BS.InorderTree();
	cout << endl;

	cout << "�ǵݹ�FIND��";
	BinarySearchNode<int, int>* Node = BS.Find(7);
	cout << Node->_key << ":" << Node->_value << endl;

	cout << "�ݹ�FIND��";
	Node = BS.Find_R(7);
	cout << Node->_key << ":" << Node->_value << endl;
}