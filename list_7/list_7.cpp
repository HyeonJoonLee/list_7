//전처리 문장
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <iostream>
#define M 1000

//선언문
typedef struct {
	int list[M];
	int length;
}ArrayListType;

typedef struct slist {	//단순 연결리스트의 노드 구조
	int data; // 정수형으로 가정
	struct slist* link;
} slist;



//함수선언문
int is_empty(ArrayListType* L) //배열 리스트가 비었는지 검사(리스트에서 삭제하고 싶을 때)
{
	if (L->length == 0) return 1;
	else return 0;
}

int is_full(ArrayListType* L) //배열 리스트가 꽉찼는지 검사(리스트에서 추가하고 싶을 때)
{
	if (L->length == M) return 1;
	else return 0;
}

void display(ArrayListType* L)//리스트의 모든 멤버들을 출력(삭제 없이)
{
	int i;
	if (is_empty(L) == 1) std::cout << "\n리스트가 비었으므로 출력 불가\n";
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
	else std::cout << "\n 리스트가 꽉찼거나 삭제위치가 오류!!! \n";
}

int ret_insert(ArrayListType* L, int item) //삽입할 값의 위치를 찾는 함수
{
	int i;
	if (L->length > 0) {
		for (i = 0; i < L->length; i++)
			if (item < L->list[i]) return i; // i번째 요소의 앞(pos=i)에 삽입예정
		return i; //리스트에는 작은 값만 있으므로 맨 끝(pos=L->length)에 추가해야 함
	}
	else return 0; // lenhth<=0일 경우, 빈 리스트이므로 맨 앞에 삽입(pos=0) 예정
}

int ret_del(ArrayListType* L, int item) //삭제(대체)할 값의 위치를 찾는 함수
{
	int i;
	for (i = 0; i < L->length; i++)
		if (item == L->list[i]) return i; //리스트 요소와 검색 값과 일치하면 위치 i를 리턴
	return -1; //리스트에 검색 값이 없다는 의미이므로 -1 리턴
}

void arraylist() //배열리스트의 각종 메뉴 7가지 실행하는 함수
{
	int i, menu, item, pos;
	ArrayListType* L = (ArrayListType*)malloc(sizeof(ArrayListType)); //배열리스트는 구조체이므로 포인터 변수 L 사용
	L->length = 0; //배열리스트의 초기화
	while (1) {
		printf("\n\n 배열리스트 메뉴 1)삽입 2)삭제 3)출력 4)검색 5)개수 6)대체 7)기타 8)종료: ");
		scanf_s("%d", &menu); if (menu == 8) break;
		switch (menu) {
		case 1: //삽입할 item 입력, item의 삽입될 위치를 검색, 삽입함수 호출
			printf("\n 리스트에 삽입할 데이터 입력 : ");
			scanf_s("%d", &item);
			pos = ret_insert(L, item);
			add(L, pos ,item);
			break;
		case 2: //삭제할 item 입력, item위치 확보, 삭제함수 호출
			printf("\n 리스트에서 삭제할 데이터 입력 : ");
			scanf_s("%d", &item);
			pos = ret_del(L, item);
			if (pos == -1) printf("\n\n 리스트에 삭제할 값이 없음...");
			else del(L, pos);
			break;
		case 3: //리스트 출력
			display(L);
			break;
		case 4: //검색값 입력 및 위치 검색
			printf("\n 리스트에서 검색할 데이터 입력 : ");
			scanf_s("%d", &item);
			pos = ret_del(L,item);
			if (pos == -1) printf("\n\n 리스트에 검색할 값이 없음...");
			else printf("\n\n 리스트에 %d번째에 있음", pos + 1);
			break;
		case 5: //리스트의 값 개수 출력
			printf("\n\n 리스트에는 %d개의 요소가 있음", L->length);
			break;
		case 6: //대체될 값/대체할 값 입력, 위치 검색 후 대체
			printf("\n 리스트에서 대체될 데이터 입력 : ");
			scanf_s("%d", &item);
			pos = ret_del(L, item);
			if (pos == -1) printf("\n\n 리스트에 대체될 값이 없음...");
			else
			{
				printf("\n 리스트에서 대체할 데이터 입력 : ");
				scanf_s("%d", &item);
				L->list[pos] = item;
			}
			break;
		case 7: // 기타 연산 적용

			break;
		default: printf("\n 메뉴선택 오류. 다시 선택하시오...\n\n"); break;
		}
	}
}

//단순 연결리스트에 입력한 정수를 노드 삽입하고 헤드포인터를 리턴하는 함수
slist* linkinsert(slist* LL, int item) 
{
	slist* before, * after, * n;
	before = NULL;
	after = LL;
	n = (slist*)malloc(sizeof(slist*));
	n->data = item; n->link = NULL;
	//삽입경우는 3가지 1)빈 리스트 2)맨 앞에 3)일반적
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
			//while문을 빠져나온 이유는 2가지 : 끝까지 검사했거나 before를 찾았거나
		}
		if (before == NULL) //맨 앞에 삽입되어야 할 경우
		{
			n->link = LL;
			LL = n;
			return LL;
		}
		else //일반적인 삽입 경우
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
	printf("\n\n 연결리스트 요소 : ");
	while (p != NULL)
	{
		printf("%d --> ", p->data);
		p = p->link;
	}
	printf(" 끝 ");
}

slist* linkdel(slist* LL, int item) //연결리스트에서 검색값을 삭제
{
	slist* before, * after;
	after = LL; before = NULL;
	//체크할 기준 4가지 : 빈 리스트, 없던지, 맨앞 노드, 일반적

	if (LL == NULL) //빈 리스트
	{
		printf("\n\n 빈 리스트이므로 삭제 불가");
		return LL;
	}
	else
	{
		while (after != NULL && after->data != item)
		{
			before = after;
			after = after->link;
		}
		if (after == NULL) //없던지
		{
			printf("\n\n 리스트에 없으므로 삭제 불가");
			return LL;
		}
		else if(before == NULL) //맨앞 노드
		{
			LL = after->link;
			return LL;
		}
		else //일반적
		{
			before->link = after->link;
			return LL;
		}
	}

}



void linkedlist() //단순 연결리스트의 각종 메뉴 7가지 실행하는 함수
{
	int i, menu, item, count;

	slist* LL, * p,*after,*before;	//LL은 연결리스트의 헤드포인터, p는 출력할 때 임시로 사용
	LL = NULL;	//단순 연결리스트의 초기화

	while (1) {
		printf("\n\n 연결리스트 메뉴 1)삽입 2)삭제 3)출력 4)검색 5)개수 카운팅 6)교체 7)역순 연결 8)종료: ");
		scanf_s("%d", &menu); if (menu == 8) break;
		switch (menu) {
		case 1: //삽입할 item 입력, item의 삽입될 위치를 검색, 삽입함수 호출
			printf("\n 리스트에 삽입할 데이터 입력 : ");
			scanf_s("%d", &item);
			LL = linkinsert(LL, item);
			break;
		case 2: //삭제할 item 입력
			printf("\n 리스트에서 삭제할 데이터 입력 : ");
			scanf_s("%d", &item);
			LL = linkdel(LL,item);
			break;
		case 3: //리스트 출력
			linkdisplay(LL);
			break;
		case 4: //검색
			count = 0;
			printf("\n 리스트에서 검색할 데이터 입력 : ");
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
				printf("\n\n 리스트에 없음");
			}
			else
			{
				printf("\n\n 리스트에 있음 : 순서=%d번쨰(%p번지)",count, after);
			}
			break;
		case 5: //개수 카운팅
			count = 0;
			p = LL;
			while (p != NULL)
			{
				count++;
				p = p->link;
			}
			printf("\n\n 리스트 길이 = %d",count);
			break;
		case 6: //교체
			printf("\n 리스트에서 대체될 아이템 : ");
			scanf_s("%d", &i);
			printf("\n 리스트에서 대체할 아이템 : ");
			scanf_s("%d", &item);

			after = LL;
			while (after != NULL && after->data != i)
			{
				before = after;
				after = after->link;
			}
			if (after == NULL)
			{
				printf("\n\n 리스트에 없음");
			}
			else
			{
				after->data = item;
			}
			break;
		case 7: //역순 연결

			break;
		default: printf("\n 메뉴선택 오류. 다시 선택하시오...\n\n"); break;
		}
	}
}

void main()
{
	int i, menu;

	ArrayListType* L = (ArrayListType*)malloc(sizeof(ArrayListType));
	L->length = 0; //리스트 초기화

	while (1) //무한루프
	{
		printf("\n\n\n 메뉴 1)배열리스트  2)단순 연결리스트  3)이중 연결리스트  4)종료: ");
		scanf_s("%d", &menu);
		if (menu == 4) break;
		switch (menu) {
		case 1: //배열리스트에서의 연산들
			arraylist();
			break;
		case 2: //연결리스트에서의 연산들
			linkedlist();
			break;
		case 3: //이중 연결리스트에서의 연산들
			//dlinkedlist();
			break;
		default: printf("\n 메뉴선택 오류. 다시 선택하시오...\n\n");
		}
	}
}