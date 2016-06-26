#include <iostream>
#include <stdio.h>
using namespace std;

/*
* 下面是用穷举法来走迷宫
* 走迷宫的规则：当前坐标是(i,j)下一步可以往四个方向行走，上下左右
*
*    在迷宫数组 0标识可以走，1标识不能走 2 标识已经走过 3标识回退的路
*
*
*
* 穷举法走出迷宫有两种方法：
*     1 栈
*     2 递归
*/

#include <stdio.h>

int maze[10][10] =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 1, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

//用递归实现迷宫问题
int recuirsion_maze(int x, int y)
{
	//确保是个迷宫
	if (x == 1 && y == 1)
	{
		maze[x][y] = 2;
		return 1;
	}
	else if (maze[x][y] == 0)
	{
		maze[x][y] = 2;
		if ((recuirsion_maze(x - 1, y) +
			recuirsion_maze(x + 1, y) +
			recuirsion_maze(x, y - 1) +
			recuirsion_maze(x, y + 1)) > 0)
			return 1;
		else
		{
			maze[x][y] = 0;
			return 0;
		}
	}
	else
		return 0;
}



//main方法
void test()
{
	int i, j;
	recuirsion_maze(8, 8);
	for (i = 0; i<10; i++)
	{
		for (j = 0; j<10; j++)
		{
			printf("%d", maze[i][j]);
		}
		printf("\n");
	}

}