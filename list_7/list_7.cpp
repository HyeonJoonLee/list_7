#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct { int length; int list[1000]; } alist;
typedef struct  slist { int data; struct  slist* link; }slist;
typedef struct dlist { int data; struct dlist* llink; struct dlist* rlink; }dlist;
int count;

void init(alist* L) //배열리스트 초기화 함수
{
	L->length = 0;
}

int is_empty(alist* L)
{
	return (L->length == 0);
}

int is_full(alist* L)
{
	return (L->length == 1000);
}

void display(alist* L)
{
	for (int i = 0; i < L->length; i++)
		printf("%d --> ", L->list[i]);
	printf("끝");
}

void add(alist* L, int pos, int item)
{
	if (!is_full(L) && pos >= 0 && pos <= L->length)   //삽입할 때의 조건 3가지
	{
		if (L->length == 0)  //빈 리스트이면 바로 저장
		{
			L->list[0] = item; L->length++;
		}
		else { //빈 리스트가 아니면, pos 위치에 저장
			for (int i = L->length; i > pos; i--)
				L->list[i] = L->list[i - 1];  //i번째 요소  i+1번째(뒤로 이동)
			L->list[pos] = item;    //pos 위치에 저장
			L->length++;           //리스트의 데이터 개수는 1 증가
		}
	}
	else  printf("\n 리스트가 꽉 찼거나 삽입 위치의 오류 : 삽입저장 불가\n\n ");

}


//검색함수 : 삽입, 삭제, 대체 위치를 찾는 함수
int  ret_insert(alist* L, int item)  //삽입위치를 찾는 함수
{
	int  i;
	if (L->length > 0) {
		for (i = 0; i < L->length; i++)
			if (item < L->list[i])  return  i;  // i번째 앞에 삽입예정
		return i;   //for문을 빠져나왔다는 것은 맨끝에 삽입예정
	}
	else return 0;  //빈 리스트이므로 첫번째 위치에 삽입예정 
}

int del(alist* L, int pos) //리스트에서 pos 위치의 값을 삭제 & 리턴
{
	int  i, item;
	if (!is_empty(L) && pos >= 0 && pos < L->length)
	{
		item = L->list[pos];    //삭제할 값을 item에 저장
		for (i = pos + 1; i < L->length; i++)
			L->list[i - 1] = L->list[i];  //i번째 --> i-1번째(앞으로 이동)
		L->length--;
		return item;  //방금 삭제된 값을 리턴	
	}
	else  printf("\n빈 리스트이거나 삭제 위치가 오류!!!");
	return -1;
}
int ret_del(alist* L, int item) //리스트에서 item이 저장되어 있는 pos 리턴
{
	for (int i = 0; i < L->length; i++)
		if (item == L->list[i]) return i; //검색값과 일치하면 첨자 i를 리턴
	return -1;    //검색값이 없을 경우 -1 리턴
}

void arraylist()  //배열리스트의 메뉴를 지정하는 메인함수
{
	int i, menu, item, pos;
	alist* L;  //구조체를 포인터변수로 접근 
	L = (alist*)malloc(sizeof(alist));
	init(L);

	while (1) //무한루프
	{
		printf("\n\n 배열리스트 1)삽입 2)삭제 3)출력 4)검색 5)개수 6)대체 7)연산 8)종료: ");
		scanf_s("%d", &menu);
		if (menu == 8) break;
		switch (menu) {
		case 1: //삽입할 item 입력, item의 삽입될 위치를 검색, 삽입함수 호출 
			printf("\n 배열 리스트에 삽입할 아이템 : ");
			scanf_s("%d", &item);
			add(L, ret_insert(L, item), item);
			break;
		case 2:  //삭제할 item 입력, item위치 확보, 삭제함수 호출
			printf("\n 배열 리스트에서 삭제할 아이템 : ");
			scanf_s("%d", &item);
			i = del(L, ret_del(L, item));
			printf("\n 방금 리스트에서 %d가 삭제됨", i);
			break;
		case 3: display(L); break;
		case 4: //검색
			printf("\n 배열 리스트에서 검색할 아이템 : ");
			scanf_s("%d", &item);
			i = ret_del(L, item);
			if (i >= 0) printf("\n %d는 리스트 %d번에 있음", item, i);
			else        printf("\n %d는 리스트에 없음", item);
			break;
		case 5: //리스트의 값 개수 출력
			printf("\n리스트의 길이 = %d개", L->length);
			break;
		case 6: //.대체될 값 입력 및 위치검색, 대체할 값 입력 및 저장
			printf("\n 배열 리스트에서 대체될 아이템 : ");
			scanf_s("%d", &i);
			printf("\n 배열 리스트에서 대체할 아이템 : ");
			scanf_s("%d", &item);
			L->list[ret_del(L, i)] = item;
			break;

		default:  printf("\n 메뉴선택 오류. 다시 선택하시오...\n\n");
			break;
		}
	}
}



slist* linkinsert(slist* LL, int item)
{ //입력값을 리스트의 제자리에 삽입(삽입위치 검색 포함)
	slist* before, * after, * n;
	after = LL; before = NULL;
	n = (slist*)malloc(sizeof(slist));
	n->data = item; n->link = NULL;

	if (LL == NULL) //1) 첫 노드를 삽입하는 경우
	{
		LL = n; return LL;
	}
	else { //리스트가 존재하므로 after, before를 이용해서 삽입위치 검색
		while (after != NULL && after->data < n->data)
		{
			before = after; after = after->link;
		}
		if (before == NULL) //2)맨앞에 삽입위치
		{
			n->link = LL; LL = n;	return LL;
		}
		else   //3)일반적인 삽입위치
		{
			n->link = before->link; before->link = n; return LL;
		}
	}
}

slist* linkdel(slist* LL, int item) //연결리스트에서 검색값을 삭제
{
	slist* before, * after;
	after = LL; before = NULL;
	//체크할 기준 4가지 : 빈 리스트, 없든지, 맨앞 노드, 일반적 
	if (LL == NULL)  //1)
	{
		printf("\n\n 빈 리스트이므로 삭제불가"); return LL;
	}
	else {
		while (after != NULL && after->data != item)
		{
			before = after; after = after->link;
		}
		if (after == NULL) //2)
		{
			printf("\n\n 리스트에 없으므로 삭제불가"); return LL;
		}
		else if (before == NULL)  //3)
		{
			LL = after->link; free(after);  return LL;
		}
		else  //4)
		{
			before->link = after->link; free(after); return LL;
		}
	}
}

slist* reverse(slist* LL) //연결리스트의 연결순서를 반대로 재구성
{
	slist* p = LL, * q = NULL, * r = NULL;
	while (p != NULL)
	{
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

void linkedlist() //단순 연결리스트에 대한 메뉴 실행
{
	int i, menu, item, count = 0;
	slist* before, * after, * p, * LL = NULL; //연결리스트 헤드포인터 선언 및 초기화

	while (1) //무한루프
	{
		printf("\n\n 연결리스트 1)삽입 2)삭제 3)출력 4)검색 5)개수 6)대체 7)역순 8)종료: ");
		scanf_s("%d", &menu);
		if (menu == 8) break;
		switch (menu) {
		case 1: //단순 연결리스트에 입력값을 노드로 제자리 삽입
			printf("\n 연결리스트에 삽입할 아이템 : ");
			scanf_s("%d", &item);
			LL = linkinsert(LL, item);
			break;
		case 2: //연결리스트에서 삭제할 값 입력
			printf("\n 연결리스트에서 삭제할 아이템 : ");
			scanf_s("%d", &item);
			LL = linkdel(LL, item);
			break;

		case 3:  //연결리스트 출력
			p = LL;
			printf("\n 연결리스트 출력 : ");
			while (p != NULL)
			{
				printf("%d --> ", p->data);
				p = p->link;
			}
			printf("끝 \n");
			break;
		case 4: //검색
			printf("\n 연결리스트에서 검색할 아이템 : ");
			scanf_s("%d", &item);

			after = LL;
			while (after != NULL && after->data != item)
			{
				before = after; after = after->link; count++;
			}
			if (after == NULL) printf("\n\n 리스트에 없음");
			else printf("\n 리스트에 있음 : 순서=%d번째(%p번지)",
				count + 1, after);
			break;

		case 5: //개수 카운팅
			count = 0;
			p = LL;

			while (p != NULL)
			{
				count++; p = p->link;
			}
			printf("\n\n 리스트 길이 = %d ", count);
			break;

		case 6: //교체
			printf("\n 연결리스트에서 대체될 아이템 : ");
			scanf_s("%d", &i);
			printf("\n 연결리스트에서 대체할 아이템 : ");
			scanf_s("%d", &item);

			after = LL;
			while (after != NULL && after->data != i)
			{
				before = after; after = after->link;
			}
			if (after == NULL) printf("\n\n 리스트에 없으므로 대체 불가");
			else after->data = item;
			break;

		case 7: //역순 연결 1->2->3->NULL 을  3->2->1->NULL 링크 변경
			LL = reverse(LL);
			break;
		default:  printf("\n 메뉴선택 오류. 다시 선택하시오...\n\n");
			break;
		}
	}
}

dlist* dinsert(dlist* DL, int item) //값을 노드로 삽입하고 헤드주소를 리턴
{//삽입위치는 4가지 1)빈 2)맨앞 3)맨뒤 4)일반
	dlist* before = NULL, * after = DL, * n;
	n = (dlist*)malloc(sizeof(dlist));
	n->data = item; n->llink = NULL; n->rlink = NULL;

	if (DL == NULL) //1) 첫 노드를 삽입하는 경우
	{
		DL = n;
		return DL;
	}
	else
	{ //리스트가 존재하므로 after, before를 이용해서 삽입위치 검색
		while (after != NULL && after->data <= n->data)
		{
			before = after;
			after = after->rlink;
		}
		if (before == NULL) //2)맨앞에 삽입위치
		{
			n->rlink = DL;
			DL = n;
			return DL;
		}
		else if (after == NULL) //맨뒤에 삽입
		{
			n->llink = before;
			before->rlink = n;
			return DL;
		}
		else  //3)일반적인 삽입위치
		{
			n->rlink = before->rlink;
			n->llink = before;
			before->rlink->llink = n;
			before->rlink = n;
			return DL;
		}
	}
}

dlist* ddel(dlist* DL, int item) //연결리스트에서 검색값을 삭제
{
	dlist* before = NULL, * remove = DL;
	//체크할 기준 4가지 : 빈 리스트, 없든지, 맨앞 노드, 맨끝 노드, 일반적 
	if (DL == NULL)  //1)빈 리스트
	{
		printf("\n\n 빈 리스트이므로 삭제불가"); return DL;
	}
	while (remove != NULL && remove->data != item)
	{
		before = remove;
		remove = remove->rlink;
	}
	if (remove == NULL) //2)값이 없음
	{
		printf("\n\n 리스트에 없으므로 삭제불가"); return DL;
	}
	if (before == NULL)  //3)맨앞 노드
	{
		remove->rlink->llink = NULL;
		DL = remove->rlink;
		free(remove);
		return DL;
	}
	else if (remove->rlink == NULL) //4)맨끝 노드
	{
		before->rlink = NULL;
		free(remove);
		return DL;
	}
	else //일반적
	{
		before->rlink = remove->rlink;
		remove->rlink->llink = before;
		free(remove);
		return DL;
	}
}

dlist* dsearch(dlist* DL, int item)
{
	count = 0;
	dlist* p = DL;
	while (p != NULL && p->data != item)
	{
		count++;
		p = p->rlink;
	}
	return p;
}

void dlinkedlist() //이중 연결리스트에 대한 모든 매뉴 수행
{
	int i, menu, item;
	dlist* DL = NULL, * p, * after, * before;

	while (1) //무한루프
	{
		printf("\n\n 이중 연결리스트 1)삽입 2)삭제 3)출력 4)검색 5)개수 6)대체 7)역순 8)종료: ");
		scanf_s("%d", &menu);
		if (menu == 8) break;
		switch (menu) {
		case 1: //이중 연결리스트에 입력값을 삽입
			printf("\n 이중 연결리스트에 삽입할 아이템 : ");
			scanf_s("%d", &item);
			DL = dinsert(DL, item);
			break;
		case 2: //이중 연결리스트에서 삭제할 값 입력
			printf("\n 이중 연결리스트에서 삭제할 아이템 : ");
			scanf_s("%d", &item);
			DL = ddel(DL, item);
			break;
		case 3:  //이중 연결리스트 출력
			p = DL;
			printf("\n 이중 연결리스트 출력 : ");
			while (p != NULL)
			{
				printf("%d --> ", p->data);
				p = p->rlink;
			}
			printf("끝 \n");
			break;
		case 4: //검색
			printf("\n 이중 연결리스트에서 검색할 아이템 : ");
			scanf_s("%d", &item);
			p = dsearch(DL, item);
			if (p == NULL) //리스트에 검색값이 없을 때
			{
				printf("\n 리스트에 검색값이 없음 ");
			}
			else
			{
				printf("\n 리스트에 %d번째에 있음(%p번지)", count + 1, p);
			}
			break;
		case 5: //개수 카운팅
			count = 0;
			p = DL;

			while (p != NULL)
			{
				count++; p = p->rlink;
			}
			printf("\n\n 리스트 길이 = %d ", count);
			break;
		case 6: //교체
			printf("\n 이중 연결리스트에서 대체될 아이템 : ");
			scanf_s("%d", &i);
			printf("\n 이중 연결리스트에서 대체할 아이템 : ");
			scanf_s("%d", &item);

			after = DL;
			while (after != NULL && after->data != i)
			{
				before = after; after = after->rlink;
			}
			if (after == NULL) printf("\n\n 리스트에 없으므로 대체 불가");
			else after->data = item;
			break;
		case 7: //역순 연결 1->2->3->NULL 을  3->2->1->NULL 링크 변경

			break;
		default:  printf("\n 메뉴선택 오류. 다시 선택하시오...\n\n");
			break;
		}
	}
}

void main() //메인함수 메뉴 변경 => 1)배열리스트  2)연결리스트  3)종료
{
	int i, menu;
	while (1) //무한루프
	{
		printf("\n\n\n 1)배열리스트  2)연결리스트  3)이중연결리스트  4)종료: ");
		scanf_s("%d", &menu);
		if (menu == 4) break;
		switch (menu) {
		case 1:  arraylist();  break;
		case 2:  linkedlist();  break;
		case 3:  dlinkedlist();  break;
		default:  printf("\n 메뉴선택 오류. 다시 선택하시오...\n\n");
			break;
		}
	}
}