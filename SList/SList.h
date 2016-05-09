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
void Destory(ListNode*& Head)   //��������
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

//����������
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

//��β��ͷ��ӡ������
void TailToHead(ListNode* Head)
{
	ListNode* PHead = Head;
	if (PHead)
	{
		TailToHead(PHead->next);
		printf("%d ", PHead->data);
	}
}

//����ָ���ڵ�
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

//ɾ����ͷ������ķ�β�ڵ�
void EraseNonHeadNode(ListNode* Pos)
{
	assert(Pos);
	Pos->data = Pos->next->data;
	Pos->next = Pos->next->next;
}

//����ͷ����ķ�ͷ���ǰ����һ���ڵ�
void InsertNonHeadNode(ListNode* Pos, DataType x)
{
	assert(Pos);
	ListNode* NewNode = BuyNode(Pos->data);
	NewNode->next = Pos->next;
	Pos->next = NewNode;
	Pos->data = x;
}

//��������
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

//ð������  
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
			if (PrevNode->data > CurNode->data)   //����
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

//ð�������Ż�
void Bubb_List(ListNode*& PHead)
{
	/*assert(PHead);//���Բ���*/
	if (PHead == NULL || PHead->next == NULL)//�޽ڵ��һ���ڵ�
	{
		return;
	}
	ListNode* prev = PHead;          //ǰһ��
	ListNode* cur = PHead->next;     //��ǰ
	ListNode* tail = NULL;           //β��־
	DataType flag = 1;               //���Ԫ���Ƿ�������ð��
	while (tail != PHead)            //β��־һֱ���̣�ָ��ͷ�ڵ������
	{
		prev = PHead;
		cur = PHead->next;
		while (cur != tail)    //cur���Ϊð�ݳ��������ֵ
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
		//���û��ð�ݣ�˵��ԭ˳������ ���˳��ó���
		if (flag)
		{
			break;
		}
		tail = prev;      //��ǰһ��ð�ݵĵ����ڶ����ڵ���Ϊ��һ��ð�ݵ�β�ڵ�
	}
}

//������K��Ԫ��,you  wen ti
ListNode* Backward_Node(ListNode* Head, DataType K)
{
	//�е�����K��Ԫ�ػ�û�е�����K��Ԫ��
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

//�ϲ��������������ϲ�����Ȼ����
ListNode*  Merge(ListNode* PHead1, ListNode* PHead2)
{
	assert(PHead1 || PHead2);
	ListNode* Head1 = PHead1;
	ListNode* Head2 = PHead2;
	ListNode* NewHead = NULL;
	ListNode* tail = NULL;            //����һ������ָ���������β

	//��������֮һΪ�յĽ������
	if (PHead1 == NULL)
	{
		return PHead2;
	}
	if (PHead2 == NULL)
	{
		return PHead1;
	}

	//���ó���������ͷ���Ľ�Сֵ����Ϊ�½ڵ��ͷ
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

	//����������Ϊ��,Ȼ��ͬʱ�Ƚ�
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

	//����һ������Ϊ�պ���һ������ʣ��Ԫ�ؽ�������
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

//Լɪ��
void Joseph(ListNode*& PHead, DataType M)
{
	assert(PHead);
	ListNode* prev = PHead;
	ListNode* cur = PHead;
	while (cur->next != cur)
	{
		//������ռһ���ڵ㣬����Ӧ���� M-1 ����Ȼ��ɾ�� cur ���ڽڵ�
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

//�жϵ������Ƿ����,�������������㣬���򷵻�NULL
ListNode* List_With_Circle(ListNode* PHead)
{
	if (NULL == PHead)
	{
		printf("This List Not Exist\n");
		return NULL;
	}
	//slow ���뻷��һȦ֮�ڣ��ض�׷��
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

//���ĳ���
DataType Circle_Length(ListNode* PHead)
{
	DataType Length = 1;  //cur->next != cur���ж����������Ȼ���һ�����Դ�1��ʼ
	if (NULL == PHead)
	{
		printf("The List Not Exist\n");
		return NULL;
	}
	//�������㿪ʼ�����������
	ListNode* cur = List_With_Circle(PHead); 
	ListNode* tmp = cur;  //������Ҫ��cur��λ�ü�¼��������Ȼcur��λ�þͱ���
	while (cur->next != tmp)
	{
		Length++;
		cur = cur->next;
	}
	return Length;
}
             /*������ڵ�*/
/**************************************/
/*    C:����                          */
/*    L�������㵽��ڵľ���           */
/*    X����ʼ����ڵľ���             */
/*    2��X+L�� =  X+L+n*C             */
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
	ListNode* Meet_Node = List_With_Circle(PHead);//������������
	ListNode* Begin = PHead;                      //����ʼ������
	if (!Meet_Node)            //�޻�
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

//�޻�����ĳ���
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

//�ж�����ĳ��ȣ�˭��˭С������˭���ߣ������ཻʱ�ҽ���
ListNode* Judge_Len(ListNode* PHead1, ListNode* PHead2, DataType flag,DataType YesOrNO_Cir)
{
	ListNode* Head1 = PHead1;
	ListNode* Head2 = PHead2;
	DataType Length1 = 0, Length2 = 0;
	if (YesOrNO_Cir == 0)   //�����޻�
	{
		//�ֱ��������
		Length1 = NO_Cir_Len(PHead1);
		Length2 = NO_Cir_Len(PHead2);
	}
	if (YesOrNO_Cir == 1)   //����you��
	{
		//������㵽��ڵľ��뼴�ɣ�����Ҫ���价��
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

	//ע��������Ҫ����ָ��ͷ
	Head1 = PHead1;
	Head2 = PHead2;
	if (flag)        //�ཻ
	{
		/***************************���´�����Ҫ�Ż�******************************/
		if (Length1 > Length2)
		{
			DataType overstep = Length1 - Length2;
			//��������overstep�������ֺͶ̵�һ������Ȼ���벽��
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
			//�������
			while (Head1 != Head2)
			{
				Head1 = Head1->next;
				Head2 = Head2->next;
			}
			return Head1;
		}
		/***************************���ϴ�����Ҫ�Ż�******************************/
	}
}

//�޻������Ƿ��ཻ���ཻ�󽻵㣩
ListNode* No_Circle(ListNode* PHead1, ListNode* PHead2)
{
	ListNode* Head1 = PHead1, *Head2 = PHead2;
	DataType flag = 0;    //�ཻΪ1�����ཻΪ0
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

//�л������Ƿ��ཻ���ཻ�󽻵㣩
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
		//һ���ཻ
		ListNode* entry[2] = { Judge_Len(PHead1, PHead2, 1, 1),NULL};
		return entry;
	}
	if (entry1 != entry2)
	{
		//�����ཻ
		//��ȷ�����������������
		ListNode* MeetNode1 = List_With_Circle(PHead1);
		ListNode* MeetNode2 = List_With_Circle(PHead2);
		//������1��������2���ҵ����ཻ����֮�����ཻ
		ListNode* tmp = MeetNode1;
		while (tmp->next != MeetNode2)
		{
			tmp = tmp->next;
			//��һȦû�ҵ�
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

//�ж����������Ƿ��ཻ
void List_InterSect(ListNode* PHead1, ListNode* PHead2)
{
	if (PHead1 == NULL || PHead2 == NULL)
	{
		printf("One of them is not exist,So can't intersect\n");
		return;
	}
	////////////////////////////////////////////////////////////
	//�޻��ཻ
	No_Circle(PHead1, PHead2);
	//�л��ཻ
	Exist_Circle(PHead1, PHead2);
}