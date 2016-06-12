#pragma once

template <class K, int M = 3>
//M�׵Ľڵ��ʾ,key�����M-1��
//subs��key��һ����subs��M��
struct BTreeNode
{
	K _key[M];                      //�ؼ������飬��һ�������ʱ��ֱ�Ӳ��룬����ٵ�����������Լ�
	BTreeNode<K, M>* _subs[M + 1];  //��������
	int _size;                      //�ؼ��ֵĸ���  

	BTreeNode<K, M>* _parent;       //���ڵ�
	BTreeNode()
		:_parent(NULL)
		, _size(0)
	{
		for (int i = 0; i < M + 1; ++i)
		{
			_subs[i] = NULL;
		}
	}
};

template <class K, class V>
struct Pair
{
	K _first;   //���ڵ�key
	V _second;  // pos 
	Pair(const K& k = K(), const V& v = V())
		:_first(k)
		, _second(v)
	{}
};

template <class K, int M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	Pair<Node*, int> Find(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;

		while (cur)
		{
			int index = 0;
			//��key����
			while (index < cur->_size && cur->_key[index] < key)
			{
				++index;
			}

			//�Ѵ���
			if (cur->_key[index] == key)
			{
				return Pair<Node*, int>(cur, index);
			}
			parent = cur;
			cur = cur->_subs[index];
		}

		//�ҵ���λ��parent,cur��ʱָ��NULL
		return Pair<Node*, int>(parent, -1);
	}

	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			++_root->_size;

			return true;
		}
		//��λ��
		Pair<Node*, int> ret = Find(key);
		if (ret._second != -1)
		{
			return false;
		}

		//_InsertKey(cur,key,sub);
		_InsertKey(key, ret);
		while (1)
		{
			//�������
			//�������Ȼ����
			if (ret._first->_size < M)
			{
				return true;
			}

			//����
			Node* tmp = new Node;
			int binary = M/2 + 1;
			int index = 0;
			int size = ret._first->_size;
			while (binary < size)
			{
				tmp->_key[index] = ret._first->_key[binary];

				//Ҷ�ӽڵ�ҲҪ����
				tmp->_subs[index] = ret._first->_subs[binary];
				tmp->_subs[index + 1] = ret._first->_subs[binary + 1];
				tmp->_size++;

				++binary;
				++index;
				--ret._first->_size;
			}

			//���ڵ�
			//�жϸ��ڵ�Ϊ��Ϊ�գ����Ϊ�գ��½�����Ϊ�գ����м�ڵ�ŵ����ڵ�ġ���key��
			Node* parent = ret._first->_parent;
			Node* sub = NULL;
			if (parent == NULL)
			{
				_root = new Node;
				_root->_key[0] = ret._first->_key[M / 2];

				//Ҷ�ӽڵ�
				_root->_subs[0] = ret._first;
				ret._first->_parent = _root;
				_root->_subs[1] = tmp;
				tmp->_parent = _root;

				++_root->_size;
				--ret._first->_size;

				return true;
			}
			
			//��Ϊ�գ����м�ڵ�ŵ����ڵ��_key��
			K k = ret._first->_key[M / 2];
			Node* temp = ret._first;
			ret._first = parent;
			_InsertKey(k, ret);

			Pair<Node*, int> p = Find(k);
			int i = p._second;
			ret._first->_subs[i + 1] = tmp;
			tmp->_parent = ret._first;

			--temp->_size;
		}
	}

	void Inorder()
	{
		_Inorder(_root);
	}

	~BTree()
	{}
protected:
	void _Inorder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		for (int i = 0; i < root->_size; ++i)
		{
			_Inorder(root->_subs[i]);
			cout << root->_key[i] << " ";
		}

		_Inorder(root->_subs[root->_size]);
	}
	void _InsertKey(const K& key, Pair<Node*, int> ret)
	{
		//�õ���λ�õ�size��С
		int index = ret._first->_size - 1;
		//Ҫ����Ľڵ�С�ڵ�ǰ�ڵ�
		while (1)
		{
			if (key > ret._first->_key[index])
			{
				ret._first->_key[index + 1] = key;
				ret._first->_size++;
				return;
			}
			ret._first->_key[index + 1] = ret._first->_key[index];
			ret._first->_subs[index + 2] = ret._first->_subs[index + 1];

			index--;
		}
	}
private:
	Node* _root;
};


