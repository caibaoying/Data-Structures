#pragma once 

#include <string>
#include <vector>

template <class V, class W>
struct LinkEdge
{
	W _weight;
	size_t _index;

	LinkEdge<V, W>* _next;

	LinkEdge(const W& weight, const size_t& index)
		: _index(index)
		, _weight(weight)
		, _next(NULL)
	{}
};

template <class V, class W>
class GraphLink
{
	typedef LinkEdge<V, W> Edge;
public:
	GraphLink(V* array, const size_t& size)
		:_size(size)
		, _edges(new LinkEdge<V, W>*[size])
		, _value(new V[size])
		, _flag(false)
	{
		for (int i = 0; i < size; ++i)
		{
			_value[i] = array[i]; 
			_edges[i] = NULL;
		}
	}

	//默认为有向图
	void AddEdge(const V& src, const V& dst, const W& weight)
	{
		if (src == dst)
		{
			return;
		}

		int srcIndex = FindIndex(src);
		int dstIndex = FindIndex(dst);

		_Link(srcIndex, dstIndex, weight);
		if (_flag)
		{
			_Link(dstIndex, srcIndex, weight);
		}
	}

	//深度优先遍历
	void DFS()
	{
		bool* visited = new bool[_size];
		memset(visited, false, _size);
		
		int size = 1;

		for (int i = 0; i < _size; ++i)
		{
			if (visited[i] == false)
				_DFS(i, visited, size);
		}
	}

	//广度优先遍历
	void BFS()
	{
		_BFS();
	}

	void Display()
	{
		if (_value)
		{
			for (int i = 0; i < _size; ++i)
			{
				cout << _value[i] << "[" << i << "]  ";
			}
			cout << endl;
		}

		if (_edges)
		{
			for (int i = 0; i < _size; ++i)
			{
				cout << _value[i] << "[" << i << "]->";
				LinkEdge<V, W>* begin = _edges[i];
				while (begin)
				{
					cout << begin->_weight << "[" << begin->_index << "]->";
					begin = begin->_next;
				}
				cout << endl;
			}
		}
	}

	~GraphLink()
	{
		if (_value)
		{
			delete[] _value;
		}
		if (_edges)
		{
			for (int i = 0; i < _size; ++i)
			{
				LinkEdge<V, W>* cur = _edges[i];
				while (cur)
				{
					LinkEdge<V, W>* tmp = cur;
					cur = cur->_next;
					delete tmp;
				}
			}
			delete[] _edges;
		}
	}
protected:
	const int& _FindNVisite(const int& index,bool*& visited)
	{
		Edge* begin = NULL;
		if (index > -1)
		    begin = _edges[index];
		while (begin)
		{
			if (visited[begin->_index] == false)
			{
				return begin->_index;
			}
			begin = begin->_next;
		}
		return -1;
	}

	void _DFS(const int& index, bool*& visited, int& size)
	{
		if (size > _size)
		{
			return;
		}
		const int NVIndex = _FindNVisite(index, visited);
		cout << _value[NVIndex] << "[" << NVIndex << "]->";
		visited[NVIndex] = true;
		++size;

		_DFS(NVIndex, visited, size);
	}

	void _BFS()
	{}

	void _Link(const int& src, const int& dst,const W& weight)
	{
		LinkEdge<V, W>* next = new LinkEdge<V, W>(weight, dst);

		//头插
		next->_next = _edges[src];
		_edges[src] = next;
	}

	int FindIndex(const V& element)
	{
		for (int i = 0; i < _size; ++i)
		{
			if (_value[i] == element)
			{
				return i;
			}
		}
		return -1;
	}

protected:
	LinkEdge<V, W>** _edges;
	V* _value;
	size_t _size;
	bool _flag;
};

void TestLink()
{
	int array[] = { 0, 1, 2, 3, 4 };
	GraphLink<int,int> GL(array, sizeof(array) / sizeof(int));
	GL.AddEdge(4, 0, 20);
	GL.AddEdge(0, 3, 10);
	GL.AddEdge(3, 1, 20);
	GL.AddEdge(4, 1, 30);
	GL.AddEdge(1, 2, 10);
	GL.AddEdge(2, 4, 40);
	GL.Display();

	/*string a[] = { "1234", "3456", "6768", "565", "675" };
	GraphLink<string, string> GM(a, sizeof(a) / sizeof(string));
	GM.AddEdge("1234", "3456", "wefwf");
	GM.AddEdge("1234", "6768", "sfgsfg");
	GM.Display();*/

	GL.DFS();
}