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
			//linkedlist();
			break;
		case 3: //���� ���Ḯ��Ʈ������ �����
			//dlinkedlist();
			break;
		default: printf("\n �޴����� ����. �ٽ� �����Ͻÿ�...\n\n");
		}
	}
}