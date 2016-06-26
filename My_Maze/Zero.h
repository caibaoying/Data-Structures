#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;
#define _ROW_ 10
#define _COL_ 10

//0：可以走 1：走不了 2：走过的  3：返回的

void GetMazeMap(int* a, int row, int col)
{
	FILE* fOut;
	fopen_s(&fOut,"MazeMap.txt", "r");
	assert(fOut);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col;)
		{
			//a[i][j] = fgetc(fOut) - '0';
			char ch = fgetc(fOut);
			if (ch == '0' || ch == '1')
			{
				a[i*col + j] = ch - '0';
				++j;
			}
		}
	}
	fclose(fOut);
}

void PrintMaze(int* a, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cout << a[i*col + j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}

struct Pos
{
	int row;
	int col;
};

bool CheckIsAccess(int* a, int rowSize, int colSize, Pos cur)
{
	if (cur.row < rowSize && cur.col < colSize
		&& a[cur.row*colSize + cur.col] == 0)
	{
		return true;
	}

	return false;
}

bool IsPosEqual(Pos p1, Pos p2)
{
	return (p1.col == p2.col && p1.row == p2.row);
}


stack<Pos> GetMazePath(int* a, int rowSize, int colSize, Pos entry)
{
	stack<Pos> paths;
	paths.push(entry);
	a[entry.row * colSize + entry.col] = 2;


	while (!paths.empty())
	{
		Pos cur = paths.top();
		Pos next = cur;
		//从起点走，而且已经出来了
		if (next.row == rowSize - 1 || next.col == colSize - 1 ||
			(next.row == 0 || next.col == 0) && !IsPosEqual(next, entry))
		{
			return paths;
		}

		// 左
		next = cur;
		next.col--;
		if (CheckIsAccess(a, rowSize, colSize, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		// 右
		next = cur;
		next.col++;
		if (CheckIsAccess(a, rowSize, colSize, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		// 上
		next = cur;
		next.row--;
		if (CheckIsAccess(a, rowSize, colSize, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		// 下
		next = cur;
		next.row++;
		if (CheckIsAccess(a, rowSize, colSize, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		Pos top = paths.top();
		a[top.row * colSize + top.col] = 3;
		paths.pop();                     //内存溢出
		/*if (paths.empty())
		{
			paths.push(entry);
			break;
		}*/
	}
	cout << "没有" << endl;
	return paths;
}

stack<Pos> shortest_path;
stack<Pos> GetMazePath_Shortest(int* a, int rowSize, int colSize, Pos entry)
{
	stack<Pos> paths;
	paths.push(entry);
	a[entry.row * colSize + entry.col] = 2;

	int Count = 0;
	while (!paths.empty())
	{
		Pos cur = paths.top();
		Pos next = cur;
		//从起点走，而且已经出来了
		if (next.row == rowSize - 1 || next.col == colSize - 1 ||
			(next.row == 0 || next.col == 0) && !IsPosEqual(next, entry))
		{
			++Count;
			if (Count == 1)
			{
				shortest_path = paths;
			}
			else
			{
				if (paths.size() < shortest_path.size())
				{
					shortest_path = paths;
				}
			}
			a[next.row * colSize + next.col] = 4;
			paths.pop();
			//return paths;
		}

		// 左
		next = cur;
		next.col--;
		if (CheckIsAccess(a, rowSize, colSize, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		// 右
		next = cur;
		next.col++;
		if (CheckIsAccess(a, rowSize, colSize, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		// 上
		next = cur;
		next.row--;
		if (CheckIsAccess(a, rowSize, colSize, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		// 下
		next = cur;
		next.row++;
		if (CheckIsAccess(a, rowSize, colSize, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		Pos top = paths.top();
		a[top.row * colSize + top.col] = 3;
		paths.pop();                     //内存溢出
		/*if (paths.empty())
		{
		paths.push(entry);
		break;
		}*/
	}
	//cout << "没有" << endl;
	return paths;
}

void TestMaze()
{
	int a[10][10];
	GetMazeMap((int*)a, _ROW_, _COL_);
	PrintMaze((int*)a, _ROW_, _COL_);
	Pos entry = { 2, 0 };
	
	GetMazePath_Shortest((int*)a, _ROW_, _COL_, entry);
	PrintMaze((int*)a, _ROW_, _COL_);
}