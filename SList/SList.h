#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int DataType;
typedef struct ListNode
{
	DataType data;
	struct ListNode* next;
}ListNode;

void Print(ListNode* Head)
{
	ListNode* PHead = Head;
	while (PHead)
	{
		printf("%d ", PHead->data);
		PHead = PHead->next;
	}
	printf("\n");
}
/*
void Destory(ListNode*& Head)   //销毁链表
{
	ListNode* cur = Head;
	while (Head)
	{
		Head = Head->next;
		free(cur);
		cur = Head;
	}
}
*/
ListNode* BuyNode(DataType x)
{
	ListNode* List;
	List = (ListNode*)malloc(sizeof(ListNode));
	List->data = x;
	List->next = NULL;
	return List;
}

void PushBack(ListNode*& Head, DataType x)
{
	if (Head)
	{
		ListNode* List = Head;
		while (List->next)
		{
			List = List->next;
		}
		List->next = BuyNode(x);
	}
	else
	{
		Head = BuyNode(x);
	}
}

//单链表逆置
void Reverse(ListNode*& Head)
{
	ListNode* PHead = Head, *tmp = NULL, *NewHead = NULL;
	while (PHead)

	{
		tmp = PHead;
		PHead = PHead->next;
		tmp->next = NewHead;
		NewHead = tmp;
	}
	Head = NewHead;
}

//从尾到头打印单链表
void TailToHead(ListNode* Head)
{
	ListNode* PHead = Head;
	if (PHead)
	{
		TailToHead(PHead->next);
		printf("%d ", PHead->data);
	}
}

//查找指定节点
ListNode* Find(ListNode* Head, DataType x)
{
	if (Head == NULL)
	{
		printf("The SList IS Empty\n");
		return NULL;
	}
	else
	{
		ListNode* PHead = Head, *Node = BuyNode(x);
		while (PHead->data != x)
		{
			PHead = PHead->next;
		}
		return PHead;
	}
	return NULL;
}

//删除无头单链表的非尾节点
void EraseNonHeadNode(ListNode* Pos)
{
	assert(Pos);
	Pos->data = Pos->next->data;
	Pos->next = Pos->next->next;
}

//在无头链表的非头结点前插入一个节点
void InsertNonHeadNode(ListNode* Pos, DataType x)
{
	assert(Pos);
	ListNode* NewNode = BuyNode(Pos->data);
	NewNode->next = Pos->next;
	Pos->next = NewNode;
	Pos->data = x;
}

//求链表长度
int Get_Length(ListNode* Head)
{
	assert(Head);
	ListNode* PHead = Head;
	int Length = 0;
	while (PHead)
	{
		Length++;
		PHead = PHead->next;
	}
	return Length;
}

//冒泡排序  
void Bubb_Sort(ListNode*& Head)
{
	ListNode* PrevNode, *CurNode;
	int Length1, Length2;
	Length1 = Get_Length(Head);
	while (Length1 > 1)
	{
		PrevNode = Head;
		CurNode = PrevNode->next;
		Length2 = Length1;
		Length1--;
		while (Length2 > 1)
		{
			if (PrevNode->data > CurNode->data)   //交换
			{
				DataType temp = CurNode->data;
				CurNode->data = PrevNode->data;
				PrevNode->data = temp;

				PrevNode = CurNode;
				CurNode = CurNode->next;
			}
			else
			{
				PrevNode = CurNode;
				CurNode = CurNode->next;
			}
			Length2--;
		}
	}
}

//冒泡排序优化
void Bubb_List(ListNode*& PHead)
{
	/*assert(PHead);//断言不好*/
	if (PHead == NULL || PHead->next == NULL)//无节点或一个节点
	{
		return;
	}
	ListNode* prev = PHead;          //前一个
	ListNode* cur = PHead->next;     //当前
	ListNode* tail = NULL;           //尾标志
	DataType flag = 1;               //标记元素是否真正在冒泡
	while (tail != PHead)            //尾标志一直缩短，指向头节点则结束
	{
		prev = PHead;
		cur = PHead->next;
		while (cur != tail)    //cur最后为冒泡出来的最大值
		{
			if (prev->data > cur->data)
			{
				DataType temp = prev->data;
				prev->data = cur->data;
				cur->data = temp;
				flag = 0;
			}
			prev = cur;
			cur = cur->next;
		}
		//如果没有冒泡，说明原顺序有序 则退出该程序
		if (flag)
		{
			break;
		}
		tail = prev;      //将前一次冒泡的倒数第二个节点置为下一次冒泡的尾节点
	}
}

//倒数第K个元素,you  wen ti
ListNode* Backward_Node(ListNode* Head, DataType K)
{
	//有倒数第K个元素或没有倒数第K个元素
	assert(Head);
	ListNode* Tail = Head, *PrevTail = Head, *tmp = NULL;    
	while (K)
	{
		K--;
		Tail = Tail->next;
		if (!Tail)
		{
			printf("This Node NO Exist\n");
			break;
		}
	}
	while (Tail)
	{
		PrevTail = PrevTail->next;
		tmp = PrevTail;
		Tail = Tail->next;
	}
	return tmp;
}

//合并两个有序链表，合并后依然有序
ListNode*  Merge(ListNode* PHead1, ListNode* PHead2)
{
	assert(PHead1 || PHead2);
	ListNode* Head1 = PHead1;
	ListNode* Head2 = PHead2;
	ListNode* NewHead = NULL;
	ListNode* tail = NULL;            //定义一个变量指向新链表的尾

	//两个链表之一为空的解决方法
	if (PHead1 == NULL)
	{
		return PHead2;
	}
	if (PHead2 == NULL)
	{
		return PHead1;
	}

	//先拿出两个链表头结点的较小值，作为新节点的头
	if (PHead1->data < PHead2->data)
	{
		NewHead = PHead1;
		Head1 = Head1->next;
	}
	else
	{
		NewHead = PHead2;
		Head2 = Head2->next;
	}

	tail = NewHead;

	//两个链表都不为空,然后同时比较
	while (Head1 && Head2)
	{
		if (Head1->data > Head2->data)
		{
			tail->next = Head2;
			tail = tail->next;
			Head2 = Head2->next;
		}
		else
		{
			tail->next = Head1;
			tail = tail->next;
			Head1 = Head1->next;
		}
	}

	//其中一个链表为空后，另一个链表剩余元素接着链接
	if (Head1)
	{
		tail->next = Head1;
	}
	if (Head2)
	{
		tail->next = Head2;
	}
	return NewHead;
}

//约瑟夫环
void Joseph(ListNode*& PHead, DataType M)
{
	assert(PHead);
	ListNode* prev = PHead;
	ListNode* cur = PHead;
	while (cur->next != cur)
	{
		//本身已占一个节点，所以应该走 M-1 步，然后删除 cur 所在节点
		for (DataType i = 1; i < M; i++)
		{
			prev = cur;
			cur = cur->next;
		}
		prev->next = cur->next;
		printf("%d ", cur->data);
		free(cur);
		cur = prev->next;	
	}
	printf("%d\n",cur->data);
	free(cur);
}

//判断单链表是否带环,带环返回相遇点，否则返回NULL
ListNode* List_With_Circle(ListNode* PHead)
{
	if (NULL == PHead)
	{
		printf("This List Not Exist\n");
		return NULL;
	}
	//slow 进入环后一圈之内，必定追上
	ListNode* slow = PHead, *fast = PHead;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			return slow;
		}
	}
	return NULL;
}

//环的长度
DataType Circle_Length(ListNode* PHead)
{
	DataType Length = 1;  //cur->next != cur做判断条件，长度会少一，所以从1开始
	if (NULL == PHead)
	{
		printf("The List Not Exist\n");
		return NULL;
	}
	//从相遇点开始到相遇点结束
	ListNode* cur = List_With_Circle(PHead); 
	ListNode* tmp = cur;  //这里需要把cur的位置记录下来，不然cur的位置就变了
	while (cur->next != tmp)
	{
		Length++;
		cur = cur->next;
	}
	return Length;
}
             /*环的入口点*/
/**************************************/
/*    C:环长                          */
/*    L：相遇点到入口的距离           */
/*    X：起始到入口的距离             */
/*    2（X+L） =  X+L+n*C             */
/*       n*C = X+L                    */
/*       X = n*C-L                    */
/**************************************/
ListNode* Entry_Circle(ListNode* PHead)
{
	if (NULL == PHead)
	{
		printf("The List Not Exist\n");
		return NULL;
	}
	ListNode* Meet_Node = List_With_Circle(PHead);//从相遇点走起
	ListNode* Begin = PHead;                      //从起始点走起
	if (!Meet_Node)            //无环
	{
		return NULL;
	}
	while (Begin != Meet_Node)
	{
		Begin = Begin->next;
		Meet_Node = Meet_Node->next;
	}
	return Begin;
}

//无环链表的长度
DataType NO_Cir_Len(ListNode* PHead)
{
	DataType Length = 0;
	ListNode* Head = PHead;
	while (Head->next)
	{
		Head = Head->next;
		Length++;
	}
	return Length;
}

//判断链表的长度（谁大谁小），看谁先走，用于相交时找交点
ListNode* Judge_Len(ListNode* PHead1, ListNode* PHead2, DataType flag,DataType YesOrNO_Cir)
{
	ListNode* Head1 = PHead1;
	ListNode* Head2 = PHead2;
	DataType Length1 = 0, Length2 = 0;
	if (YesOrNO_Cir == 0)   //代表无环
	{
		//分别求出长度
		Length1 = NO_Cir_Len(PHead1);
		Length2 = NO_Cir_Len(PHead2);
	}
	if (YesOrNO_Cir == 1)   //代表you环
	{
		//求其起点到入口的距离即可，不需要求其环长
		ListNode* entry1 = Entry_Circle(PHead1);
		ListNode* entry2 = Entry_Circle(PHead2);
		while (Head1 != entry1)   //zhu yi zhe li
		{
			Head1 = Head1->next;
			Length1++;
		}

		while (Head2 != entry2)   //zhu yi zhe li
		{
			Head2 = Head2->next;
			Length2++;
		}
	}

	//注意这里需要重新指向头
	Head1 = PHead1;
	Head2 = PHead2;
	if (flag)        //相交
	{
		/***************************以下代码需要优化******************************/
		if (Length1 > Length2)
		{
			DataType overstep = Length1 - Length2;
			//长的先走overstep步，保持和短的一样长，然后齐步走
			while (overstep)
			{
				overstep--;
				Head1 = Head1->next;
			}
			while (Head1 != Head2)
			{
				Head1 = Head1->next;
				Head2 = Head2->next;
			}
			return Head1;
		}
		else if (Length1 < Length2)
		{
			DataType overstep = Length2 - Length1;
			while (overstep)
			{
				overstep--;
				Head2 = Head2->next;
			}
			while (Head1 != Head2)
			{
				Head1 = Head1->next;
				Head2 = Head2->next;
			}
			return Head1;
		}
		else
		{
			//长度相等
			while (Head1 != Head2)
			{
				Head1 = Head1->next;
				Head2 = Head2->next;
			}
			return Head1;
		}
		/***************************以上代码需要优化******************************/
	}
}

//无环链表是否相交（相交求交点）
ListNode* No_Circle(ListNode* PHead1, ListNode* PHead2)
{
	ListNode* Head1 = PHead1, *Head2 = PHead2;
	DataType flag = 0;    //相交为1，不相交为0
	while (Head1->next)
	{
		Head1 = Head1->next;
	}
	while (Head2->next)
	{
		Head2 = Head2->next;
	}
	if (Head1 == Head2)
	{
		printf("Intersect\n");
		flag = 1;
	}
	else
	{
		printf("No_Intersect\n");
		return NULL;
	}
	/////////////////////////////////////////////////////////////////////////
	return Judge_Len(PHead1, PHead2, flag,0);
}

//有环链表是否相交（相交求交点）
ListNode** Exist_Circle(ListNode* PHead1, ListNode* PHead2)
{
	if (PHead1 == NULL || PHead2 == NULL)
	{
		printf("One of them is not exist,So can't intersect\n");
		return NULL;
	}
	ListNode* Head1 = PHead1, *Head2 = PHead2;
	ListNode* entry1 = Entry_Circle(PHead1);
	ListNode* entry2 = Entry_Circle(PHead2);
	if (entry1 == entry2)
	{
		//一定相交
		ListNode* entry[2] = { Judge_Len(PHead1, PHead2, 1, 1),NULL};
		return entry;
	}
	if (entry1 != entry2)
	{
		//可能相交
		//先确定两个链表的相遇点
		ListNode* MeetNode1 = List_With_Circle(PHead1);
		ListNode* MeetNode2 = List_With_Circle(PHead2);
		//相遇点1找相遇点2，找到则相交，反之，不相交
		ListNode* tmp = MeetNode1;
		while (tmp->next != MeetNode2)
		{
			tmp = tmp->next;
			//找一圈没找到
			if (tmp->next == MeetNode1)
			{
				printf("NO intersect\n");
				break;
			}
		}
		printf("intersect\n");
		ListNode* entry[2] = {entry1,entry2};
		return entry;
	}
}

//判断两个链表是否相交
void List_InterSect(ListNode* PHead1, ListNode* PHead2)
{
	if (PHead1 == NULL || PHead2 == NULL)
	{
		printf("One of them is not exist,So can't intersect\n");
		return;
	}
	////////////////////////////////////////////////////////////
	//无环相交
	No_Circle(PHead1, PHead2);
	//有环相交
	Exist_Circle(PHead1, PHead2);
}