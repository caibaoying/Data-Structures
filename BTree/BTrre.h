#pragma once

template <class K, int M = 3>
//M阶的节点表示,key最多有M-1个
//subs比key多一个，subs有M个
struct BTreeNode
{
	K _key[M];                      //关键字数组，多一个插入的时候直接插入，完后再调整，编码相对简单
	BTreeNode<K, M>* _subs[M + 1];  //孩子数组
	int _size;                      //关键字的个数  

	BTreeNode<K, M>* _parent;       //父节点
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
	K _first;   //所在的key
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
			//在key中找
			while (index < cur->_size && cur->_key[index] < key)
			{
				++index;
			}

			//已存在
			if (cur->_key[index] == key)
			{
				return Pair<Node*, int>(cur, index);
			}
			parent = cur;
			cur = cur->_subs[index];
		}

		//找到该位置parent,cur此时指向NULL
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
		//找位置
		Pair<Node*, int> ret = Find(key);
		if (ret._second != -1)
		{
			return false;
		}

		//_InsertKey(cur,key,sub);
		_InsertKey(key, ret);
		while (1)
		{
			//插入后检查
			//插入后仍然满足
			if (ret._first->_size < M)
			{
				return true;
			}

			//分裂
			Node* tmp = new Node;
			int binary = M/2 + 1;
			int index = 0;
			int size = ret._first->_size;
			while (binary < size)
			{
				tmp->_key[index] = ret._first->_key[binary];

				//叶子节点也要连上
				tmp->_subs[index] = ret._first->_subs[binary];
				tmp->_subs[index + 1] = ret._first->_subs[binary + 1];
				tmp->_size++;

				++binary;
				++index;
				--ret._first->_size;
			}

			//根节点
			//判断根节点为不为空，如果为空，新建，不为空，将中间节点放到根节点的——key中
			Node* parent = ret._first->_parent;
			Node* sub = NULL;
			if (parent == NULL)
			{
				_root = new Node;
				_root->_key[0] = ret._first->_key[M / 2];

				//叶子节点
				_root->_subs[0] = ret._first;
				ret._first->_parent = _root;
				_root->_subs[1] = tmp;
				tmp->_parent = _root;

				++_root->_size;
				--ret._first->_size;

				return true;
			}
			
			//不为空，将中间节点放到根节点的_key中
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
		//得到该位置的size大小
		int index = ret._first->_size - 1;
		//要插入的节点小于当前节点
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


