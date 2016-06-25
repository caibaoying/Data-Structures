#pragma once 

#include <string>

//�٣��ڣ��Ӿ���
template <class V, class W>
class GraphMatrix
{
public:
	GraphMatrix(V* array, const int& size)
		:_size(size)
		, _array(new V[size])
	{
		for (int i = 0; i < size; ++i)
		{
			_array[i] = array[i];
		}

		_edges = new W*[size];
		for (int i = 0; i < size; ++i)
		{
			_edges[i] = new W[size];
			for (int j = 0; j < size; ++j)
			{
				_edges[i][j] = W();
			}
		}
	}

	//flagΪ��־λ��Ĭ������ͼ
	void AddEdge(const V& src, const V& dest, const W& weight, bool flag = true)
	{
		if (src == dest)
		{
			return;
		}
		int srcIndex = FindIndex(src);
		int destIndex = FindIndex(dest);

		_edges[srcIndex][destIndex] = weight;
		if (flag)
			_edges[destIndex][srcIndex] = weight;
	}

	void Display()
	{
		if (_edges)
		{
			for (int i = 0; i < _size; ++i)
			{
				for (int j = 0; j < _size; ++j)
				{
					cout << _edges[i][j] << "   ";
				}
				cout << endl;
			}
		}
	}
	~GraphMatrix()
	{
		if (_array)
		{
			delete[] _array;
		}
		if (_edges)
		{
			for (int i = 0; i < _size; ++i)
			{
				delete[] _edges[i];
			}
			delete[] _edges;
		}
	}
protected:
	//���±�
	int FindIndex(const V& element)
	{
		for (int i = 0; i < _size; ++i)
		{
			if (_array[i] == element)
			{
				return i;
			}
		}
	}

protected:
	V* _array;             //���㼯��
	size_t _size;
	W** _edges;           //�ڽӾ���洢�ߵĹ�ϵ��Ҳ���Ǵ洢Ȩֵ
};

void TestMatrix()
{
	/*int array[] = { 1, 2, 3, 4, 5 };
	GraphMatrix<int, int> GM(array, sizeof(array)/sizeof(int));
	GM.AddEdge(2, 3, 10, true);
	GM.Display();*/

	string a[] = { "1234", "3456", "6768", "565", "675" };
	GraphMatrix<string, string> GM(a, sizeof(a)/sizeof(string));
	GM.AddEdge("1234", "3456", "wefwf", false);
	GM.Display();
}