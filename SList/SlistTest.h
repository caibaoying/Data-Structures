#include "SList.h"
#include <stdio.h>
void test1()
{
	ListNode* MyList = NULL;
	printf("β��\n");
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 8);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	Print(MyList);

	printf("����\n");
	Reverse(MyList);
	Print(MyList);

	printf("��β��ͷ��ӡ������\n");
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

	printf("ɾ����ͷ������ķ�β�ڵ�\n");
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

	printf("����ͷ����ķ�ͷ���ǰ����һ���ڵ�\n");
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
	printf("ð������\n");
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
	printf("���ҵ�����K���ڵ�\n");
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
	printf("ð�������Ż�\n");
	Bubb_List(MyList);
	Print(MyList);
}

//�ϲ���������
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

//Լɪ��
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

//�жϵ������Ƿ����,�������������㣬���򷵻�NULL
void test9()
{
	printf("�޻�ʱ\n");
	ListNode* MyList = NULL;
	PushBack(MyList, 1);
	PushBack(MyList, 2);
	PushBack(MyList, 3);
	PushBack(MyList, 4);
	PushBack(MyList, 5);
	PushBack(MyList, 6);
	ListNode* Meet_Node = List_With_Circle(MyList);
	printf("%d\n", Meet_Node);

	printf("�л�ʱ\n");
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
	cur->next = MyList2->next;  //������ڵ�
    Meet_Node = List_With_Circle(MyList2);
	printf("%d\n", Meet_Node->data);
}

//���ĳ���
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
	printf("���ĳ���:%d\n",Length);
}

//������ڵ�
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
	printf("������ڵ�:%d\n", entry->data);
}

//�޻������Ƿ��ཻ���ཻ�󽻵㣩
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
	//ͷ���ܶ�
	ListNode* tmp = MyList2;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	//MyList1 ������ѭ���ཻ�������λ��
	tmp->next = MyList1->next->next;

	ListNode* Head = No_Circle(MyList1, MyList2);
	if (Head)
	{
		printf("�ཻ�㣺%d\n", Head->data);
	}
	else
	{
		printf("���ཻ�㣺%d\n", Head);
	}
}

//�л������Ƿ��ཻ���ཻ�󽻵㣩
void test13()
{
	/*************�����ͬ**************/
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
	//ͷ���ܶ�
	ListNode* tmp = MyList2;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	//MyList1 ������ѭ���ཻ�������λ��
	tmp->next = MyList1->next;

	ListNode**Entry = Exist_Circle(MyList1, MyList2);
	//�ڶ�������ֵ�����⣬Ӧ��Ϊ0
	printf("%d %d\n", (*(Entry + 0))->data, *(Entry + 1));

	/*************��ڲ�ͬ**************/
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
	//ͷ���ܶ�
	tmp = MyList4;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	//MyList1 ������ѭ���ཻ�������λ��
	tmp->next = MyList3->next->next;

	Entry = Exist_Circle(MyList3, MyList4);
	//��һ���ڵ��Ǹ����ֵ
	printf("%d %d\n", (Entry[0])->data, (*(Entry + 1))->data);
}