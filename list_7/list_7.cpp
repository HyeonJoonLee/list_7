//��ó�� ����
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <iostream>
#define M 1000

//����
typedef struct {
	int list[M];
	int length;
}ArrayListType;

typedef struct slist {	//�ܼ� ���Ḯ��Ʈ�� ��� ����
	int data; // ���������� ����
	struct slist* link;
} slist;



//�Լ�����
int is_empty(ArrayListType* L) //�迭 ����Ʈ�� ������� �˻�(����Ʈ���� �����ϰ� ���� ��)
{
	if (L->length == 0) return 1;
	else return 0;
}

int is_full(ArrayListType* L) //�迭 ����Ʈ�� ��á���� �˻�(����Ʈ���� �߰��ϰ� ���� ��)
{
	if (L->length == M) return 1;
	else return 0;
}

void display(ArrayListType* L)//����Ʈ�� ��� ������� ���(���� ����)
{
	int i;
	if (is_empty(L) == 1) std::cout << "\n����Ʈ�� ������Ƿ� ��� �Ұ�\n";
	else
		for (i = 0; i < L->length; i++)
			std::cout << L->list[i] << " ";
}

void add(ArrayListType* L, int pos, int item)
{
	int i;
	if (is_full(L) != 1 && pos > -1 && pos <= L->length)
	{
		for (i = L->length - 1; i >= pos; i--)
		{
			L->list[i + 1] = L->list[i];
		}
		L->list[pos] = item;
		L->length++;
	}

}

int del(ArrayListType* L, int pos)
{
	int i, item;

	if ((is_empty(L) != 1) && (pos > -1) && (pos < L->length))
	{
		item = L->list[pos];
		for (i = pos; i < L->length; i++)
			L->list[i] = L->list[i + 1];
		L->length--;
		return item;
	}
	else std::cout << "\n ����Ʈ�� ��á�ų� ������ġ�� ����!!! \n";
}

int ret_insert(ArrayListType* L, int item) //������ ���� ��ġ�� ã�� �Լ�
{
	int i;
	if (L->length > 0) {
		for (i = 0; i < L->length; i++)
			if (item < L->list[i]) return i; // i��° ����� ��(pos=i)�� ���Կ���
		return i; //����Ʈ���� ���� ���� �����Ƿ� �� ��(pos=L->length)�� �߰��ؾ� ��
	}
	else return 0; // lenhth<=0�� ���, �� ����Ʈ�̹Ƿ� �� �տ� ����(pos=0) ����
}

int ret_del(ArrayListType* L, int item) //����(��ü)�� ���� ��ġ�� ã�� �Լ�
{
	int i;
	for (i = 0; i < L->length; i++)
		if (item == L->list[i]) return i; //����Ʈ ��ҿ� �˻� ���� ��ġ�ϸ� ��ġ i�� ����
	return -1; //����Ʈ�� �˻� ���� ���ٴ� �ǹ��̹Ƿ� -1 ����
}

void arraylist() //�迭����Ʈ�� ���� �޴� 7���� �����ϴ� �Լ�
{
	int i, menu, item, pos;
	ArrayListType* L = (ArrayListType*)malloc(sizeof(ArrayListType)); //�迭����Ʈ�� ����ü�̹Ƿ� ������ ���� L ���
	L->length = 0; //�迭����Ʈ�� �ʱ�ȭ
	while (1) {
		printf("\n\n �迭����Ʈ �޴� 1)���� 2)���� 3)��� 4)�˻� 5)���� 6)��ü 7)��Ÿ 8)����: ");
		scanf_s("%d", &menu); if (menu == 8) break;
		switch (menu) {
		case 1: //������ item �Է�, item�� ���Ե� ��ġ�� �˻�, �����Լ� ȣ��
			printf("\n ����Ʈ�� ������ ������ �Է� : ");
			scanf_s("%d", &item);
			pos = ret_insert(L, item);
			add(L, pos ,item);
			break;
		case 2: //������ item �Է�, item��ġ Ȯ��, �����Լ� ȣ��
			printf("\n ����Ʈ���� ������ ������ �Է� : ");
			scanf_s("%d", &item);
			pos = ret_del(L, item);
			if (pos == -1) printf("\n\n ����Ʈ�� ������ ���� ����...");
			else del(L, pos);
			break;
		case 3: //����Ʈ ���
			display(L);
			break;
		case 4: //�˻��� �Է� �� ��ġ �˻�
			printf("\n ����Ʈ���� �˻��� ������ �Է� : ");
			scanf_s("%d", &item);
			pos = ret_del(L,item);
			if (pos == -1) printf("\n\n ����Ʈ�� �˻��� ���� ����...");
			else printf("\n\n ����Ʈ�� %d��°�� ����", pos + 1);
			break;
		case 5: //����Ʈ�� �� ���� ���
			printf("\n\n ����Ʈ���� %d���� ��Ұ� ����", L->length);
			break;
		case 6: //��ü�� ��/��ü�� �� �Է�, ��ġ �˻� �� ��ü
			printf("\n ����Ʈ���� ��ü�� ������ �Է� : ");
			scanf_s("%d", &item);
			pos = ret_del(L, item);
			if (pos == -1) printf("\n\n ����Ʈ�� ��ü�� ���� ����...");
			else
			{
				printf("\n ����Ʈ���� ��ü�� ������ �Է� : ");
				scanf_s("%d", &item);
				L->list[pos] = item;
			}
			break;
		case 7: // ��Ÿ ���� ����

			break;
		default: printf("\n �޴����� ����. �ٽ� �����Ͻÿ�...\n\n"); break;
		}
	}
}

//�ܼ� ���Ḯ��Ʈ�� �Է��� ������ ��� �����ϰ� ��������͸� �����ϴ� �Լ�
slist* linkinsert(slist* LL, int item) 
{
	slist* before, * after, * n;
	before = NULL;
	after = LL;
	n = (slist*)malloc(sizeof(slist*));
	n->data = item; n->link = NULL;
	//���԰��� 3���� 1)�� ����Ʈ 2)�� �տ� 3)�Ϲ���
	if (LL == NULL)
	{
		LL = n;
		return LL;
	}
	else
	{
		while (after != NULL && after->data <= n->data)
		{
			before = after;
			after = after->link;
			//while���� �������� ������ 2���� : ������ �˻��߰ų� before�� ã�Ұų�
		}
		if (before == NULL) //�� �տ� ���ԵǾ�� �� ���
		{
			n->link = LL;
			LL = n;
			return LL;
		}
		else //�Ϲ����� ���� ���
		{
			n->link = before->link;
			before->link = n;
			return LL;
		}
	}
}

void linkdisplay(slist* LL)
{
	slist* p = LL;
	printf("\n\n ���Ḯ��Ʈ ��� : ");
	while (p != NULL)
	{
		printf("%d --> ", p->data);
		p = p->link;
	}
	printf(" �� ");
}

slist* linkdel(slist* LL, int item) //���Ḯ��Ʈ���� �˻����� ����
{
	slist* before, * after;
	after = LL; before = NULL;
	//üũ�� ���� 4���� : �� ����Ʈ, ������, �Ǿ� ���, �Ϲ���

	if (LL == NULL) //�� ����Ʈ
	{
		printf("\n\n �� ����Ʈ�̹Ƿ� ���� �Ұ�");
		return LL;
	}
	else
	{
		while (after != NULL && after->data != item)
		{
			before = after;
			after = after->link;
		}
		if (after == NULL) //������
		{
			printf("\n\n ����Ʈ�� �����Ƿ� ���� �Ұ�");
			return LL;
		}
		else if(before == NULL) //�Ǿ� ���
		{
			LL = after->link;
			return LL;
		}
		else //�Ϲ���
		{
			before->link = after->link;
			return LL;
		}
	}

}



void linkedlist() //�ܼ� ���Ḯ��Ʈ�� ���� �޴� 7���� �����ϴ� �Լ�
{
	int i, menu, item, count;

	slist* LL, * p,*after,*before;	//LL�� ���Ḯ��Ʈ�� ���������, p�� ����� �� �ӽ÷� ���
	LL = NULL;	//�ܼ� ���Ḯ��Ʈ�� �ʱ�ȭ

	while (1) {
		printf("\n\n ���Ḯ��Ʈ �޴� 1)���� 2)���� 3)��� 4)�˻� 5)���� ī���� 6)��ü 7)���� ���� 8)����: ");
		scanf_s("%d", &menu); if (menu == 8) break;
		switch (menu) {
		case 1: //������ item �Է�, item�� ���Ե� ��ġ�� �˻�, �����Լ� ȣ��
			printf("\n ����Ʈ�� ������ ������ �Է� : ");
			scanf_s("%d", &item);
			LL = linkinsert(LL, item);
			break;
		case 2: //������ item �Է�
			printf("\n ����Ʈ���� ������ ������ �Է� : ");
			scanf_s("%d", &item);
			LL = linkdel(LL,item);
			break;
		case 3: //����Ʈ ���
			linkdisplay(LL);
			break;
		case 4: //�˻�
			count = 0;
			printf("\n ����Ʈ���� �˻��� ������ �Է� : ");
			scanf_s("%d", &item);

			after = LL;
			while (after != NULL && after->data != item)
			{
				before = after;
				after = after->link;
				count++;
			}
			if (after == NULL)
			{
				printf("\n\n ����Ʈ�� ����");
			}
			else
			{
				printf("\n\n ����Ʈ�� ���� : ����=%d����(%p����)",count, after);
			}
			break;
		case 5: //���� ī����
			count = 0;
			p = LL;
			while (p != NULL)
			{
				count++;
				p = p->link;
			}
			printf("\n\n ����Ʈ ���� = %d",count);
			break;
		case 6: //��ü
			printf("\n ����Ʈ���� ��ü�� ������ : ");
			scanf_s("%d", &i);
			printf("\n ����Ʈ���� ��ü�� ������ : ");
			scanf_s("%d", &item);

			after = LL;
			while (after != NULL && after->data != i)
			{
				before = after;
				after = after->link;
			}
			if (after == NULL)
			{
				printf("\n\n ����Ʈ�� ����");
			}
			else
			{
				after->data = item;
			}
			break;
		case 7: //���� ����

			break;
		default: printf("\n �޴����� ����. �ٽ� �����Ͻÿ�...\n\n"); break;
		}
	}
}

void main()
{
	int i, menu;

	ArrayListType* L = (ArrayListType*)malloc(sizeof(ArrayListType));
	L->length = 0; //����Ʈ �ʱ�ȭ

	while (1) //���ѷ���
	{
		printf("\n\n\n �޴� 1)�迭����Ʈ  2)�ܼ� ���Ḯ��Ʈ  3)���� ���Ḯ��Ʈ  4)����: ");
		scanf_s("%d", &menu);
		if (menu == 4) break;
		switch (menu) {
		case 1: //�迭����Ʈ������ �����
			arraylist();
			break;
		case 2: //���Ḯ��Ʈ������ �����
			linkedlist();
			break;
		case 3: //���� ���Ḯ��Ʈ������ �����
			//dlinkedlist();
			break;
		default: printf("\n �޴����� ����. �ٽ� �����Ͻÿ�...\n\n");
		}
	}
}