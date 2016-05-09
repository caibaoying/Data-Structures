#include "SList.h"
#include <stdio.h>
void test1()
{
	ListNode* MyList = NULL;
	printf("尾插\n");
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 8);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	Print(MyList);

	printf("逆置\n");
	Reverse(MyList);
	Print(MyList);

	printf("从尾到头打印单链表\n");
	TailToHead(MyList);
	printf("\n");
}

void test2()
{
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 3);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	Print(MyList);

	printf("删除无头单链表的非尾节点\n");
	ListNode* Pos = Find(MyList, 5);
	EraseNonHeadNode(Pos);
	Print(MyList);
}

void test3()
{
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 3);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	Print(MyList);

	printf("在无头链表的非头结点前插入一个节点\n");
	ListNode* Pos = Find(MyList, 6);
	InsertNonHeadNode(Pos, 7);
	Print(MyList);
}

void test4()
{
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 8);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	Print(MyList);
	printf("冒泡排序\n");
	Bubb_Sort(MyList);
	Print(MyList);
}

void test5()
{
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 3);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	Print(MyList);
	printf("查找倒数第K个节点\n");
	ListNode* Pos = Backward_Node(MyList, 1);
	if (Pos)
	{
		printf("%d\n", Pos->data);
	}
}

void test6()
{
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 8);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	Print(MyList);
	printf("冒泡排序优化\n");
	Bubb_List(MyList);
	Print(MyList);
}

//合并有序单链表
void test7()
{
	ListNode* MyList1 = NULL;
	printf("List1\n");
	PushBack(MyList1, 1);
	PushBack(MyList1, 2);
	PushBack(MyList1, 3);
	PushBack(MyList1, 4);
	PushBack(MyList1, 5);
	PushBack(MyList1, 6);
	Print(MyList1);
	printf("List2\n");
	ListNode* MyList2 = NULL;
	PushBack(MyList2, 1);
	PushBack(MyList2, 2);
	PushBack(MyList2, 3);
	PushBack(MyList2, 4);
	PushBack(MyList2, 5);
	PushBack(MyList2, 7);
	Print(MyList2);
	printf("merge\n");
	ListNode* NewHead = Merge(MyList1, MyList2);
	Print(NewHead);
}

//约瑟夫环
void test8()
{
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 3);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	ListNode* cur = MyList;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = MyList;
	Joseph(MyList, 3);
}

//判断单链表是否带环,带环返回相遇点，否则返回NULL
void test9()
{
	printf("无环时\n");
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 3);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	ListNode* Meet_Node = List_With_Circle(MyList);
	printf("%d\n", Meet_Node);

	printf("有环时\n");
	ListNode* MyList2 = NULL;
	PushBack(MyList2, 1);
	PushBack(MyList2, 2);
	PushBack(MyList2, 3);
	PushBack(MyList2, 4);
	PushBack(MyList2, 5);
	PushBack(MyList2, 6);
	Print(MyList2);
	ListNode* cur = MyList2;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = MyList2->next;  //调整入口点
    Meet_Node = List_With_Circle(MyList2);
	printf("%d\n", Meet_Node->data);
}

//环的长度
void test10()
{
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 3);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	ListNode* cur = MyList;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = MyList;
	DataType Length = Circle_Length(MyList);
	printf("环的长度:%d\n",Length);
}

//环的入口点
void test11()
{
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 3);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	ListNode* cur = MyList;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = MyList->next;
	ListNode* entry = Entry_Circle(MyList);
	printf("环的入口点:%d\n", entry->data);
}

//无环链表是否相交（相交求交点）
void test12()
{
	ListNode* MyList1 = NULL;
	PushBack(MyList1, 1);
	PushBack(MyList1, 2);
	PushBack(MyList1, 3);
	PushBack(MyList1, 4);
	PushBack(MyList1, 5);
	PushBack(MyList1, 6);

	ListNode* MyList2 = NULL;
	PushBack(MyList2, 1);
	PushBack(MyList2, 2);
	PushBack(MyList2, 3);
	//头不能丢
	ListNode* tmp = MyList2;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	//MyList1 可以用循环相交到理想的位置
	tmp->next = MyList1->next->next;

	ListNode* Head = No_Circle(MyList1, MyList2);
	if (Head)
	{
		printf("相交点：%d\n", Head->data);
	}
	else
	{
		printf("无相交点：%d\n", Head);
	}
}

//有环链表是否相交（相交求交点）
void test13()
{
	/*************入口相同**************/
	ListNode* MyList1 = NULL;
	PushBack(MyList1, 1);
	PushBack(MyList1, 2);
	PushBack(MyList1, 3);
	PushBack(MyList1, 4);
	PushBack(MyList1, 5);
	PushBack(MyList1, 6);
	ListNode* cur = MyList1;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = MyList1->next->next;

	ListNode* MyList2 = NULL;
	PushBack(MyList2, 1);
	PushBack(MyList2, 2);
	PushBack(MyList2, 3);
	//头不能丢
	ListNode* tmp = MyList2;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	//MyList1 可以用循环相交到理想的位置
	tmp->next = MyList1->next;

	ListNode**Entry = Exist_Circle(MyList1, MyList2);
	//第二个返回值有问题，应该为0
	printf("%d %d\n", (*(Entry + 0))->data, *(Entry + 1));

	/*************入口不同**************/
	ListNode* MyList3 = NULL;
	PushBack(MyList3, 1);
	PushBack(MyList3, 2);
	PushBack(MyList3, 3);
	PushBack(MyList3, 4);
	PushBack(MyList3, 5);
	PushBack(MyList3, 6);
    cur = MyList3;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = MyList3->next;

	ListNode* MyList4 = NULL;
	PushBack(MyList4, 1);
	PushBack(MyList4, 2);
	PushBack(MyList4, 3);
	//头不能丢
	tmp = MyList4;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	//MyList1 可以用循环相交到理想的位置
	tmp->next = MyList3->next->next;

	Entry = Exist_Circle(MyList3, MyList4);
	//另一个节点是个随机值
	printf("%d %d\n", (Entry[0])->data, (*(Entry + 1))->data);
}