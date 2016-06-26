#include <iostream>
#include <stdio.h>
using namespace std;

/*
* ����������ٷ������Թ�
* ���Թ��Ĺ��򣺵�ǰ������(i,j)��һ���������ĸ��������ߣ���������
*
*    ���Թ����� 0��ʶ�����ߣ�1��ʶ������ 2 ��ʶ�Ѿ��߹� 3��ʶ���˵�·
*
*
*
* ��ٷ��߳��Թ������ַ�����
*     1 ջ
*     2 �ݹ�
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

//�õݹ�ʵ���Թ�����
int recuirsion_maze(int x, int y)
{
	//ȷ���Ǹ��Թ�
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



//main����
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