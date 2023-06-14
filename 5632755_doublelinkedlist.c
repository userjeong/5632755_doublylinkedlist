#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//이중연결리스트 헤드는 포인터가 아니라 하나의 노드 (헤드노드)
//데이터 저장x, 첫번째 link는 마지막노드를 가리키고
//뒤의 link는 첫번째 노드를 가리키고 있고 마지막 노드의 링크는 헤드의
//노드를 가리켜야 한다.
//첫번째 노드와 마지막 노드는 head를 가리킴

typedef char element[100];
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode;

DListNode* current;

void dinsert(DListNode* before, element data);
void ddelete(DListNode* head, DListNode* removed);
void print_dlist(DListNode* phead);
void init(DListNode* phead);
int main(void)
{
	char ch;
	char fruit[100];
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	/*dinsert(head, "Mamamia");
	dinsert(head, "Dancing Queen");
	dinsert(head, "Fernado");*/

	current = head->rlink;
	print_dlist(head);

	do
	{
		printf("===== $과일 관리 메뉴$ =====\n");
		printf("n)다음 과일을 선택합니다\n");
		printf("p)이전 과일을 선택합니다\n");
		printf("d)현재 선택된 과일을 삭제합니다\n");
		printf("i)현재 선택된 과일 다음에 과일을 추가합니다\n");
		printf("o)과일 리스트를 출력합니다(현재 선택된 과일 : o)\n");
		printf("e)프로그램을 종료합니다.\n");
		printf("====================\n");
		printf("메뉴를 선택해주세요.");
		ch = getchar();

		if (ch == 'n')
		{
			current = current->rlink;
			if (current == head)
				current = current->rlink;
		}
		else if (ch == 'p')
		{
			current = current->llink;
			if (current == head)
				current = current->llink;
		}
		else if (ch == 'i')
		{
			printf("추가할 과일의 이름을 입력하세요: ");
			scanf("%s", fruit);
			if (head->rlink == head->llink)
			{
				dinsert(head, fruit);
				current = head->rlink;
			}
			else
			{
				dinsert(head, fruit);
			}
		}
		else if (ch == 'd')
		{
			ddelete(head, current);
		}
		else if (ch == 'o')
		{
			print_dlist(head);
		}
		else
			printf("존재하지 않는 메뉴입니다. 다시 입력해주세요.\n\n");
		getchar();
	} while (ch != 'e');
}
	/*do
	{
		printf("\n명령어를 입력하시오(<, >, q): ");
		ch = getchar();
		if (ch == '<') {
			current = current->llink;
			if (current == head)
				current = current->llink;
		}
		else if (ch == '>') {
			current = current->rlink;
			if (current == head)
				current = current->rlink;
		}
		print_dlist(head);
		getchar();
	} while (ch != 'q');
	free(head);*/

void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

//rlink는 오른쪽, llink는 왼쪽을 가리키고 있는데 중간에 하나의 노드를 추가
//삽입된 노드의 1번은 왼쪽, 2번은 오른쪽 가리키고
//앞의 rlink가 삽입된 노드 가리키고 뒤의 llink도 삽입된 노드 가리킴
void dinsert(DListNode* before, element data) //before -> previous
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode)); //새로운 노드를
	//가리킬 수 있는 변수를 만들고 DListNode를 생성한 후 포인터가 새 노드를 가리킨다.
	strcpy(newnode->data, data); //data값을 새로 만들어진 노드의 data값에 대입
	//우선 새로운 노드가 앞뒤를 가리키게 만들어야함
	newnode->llink = before; //before값을 새로운 노드의 왼쪽link에 대입(1)
	newnode->rlink = before->rlink;//before가 가리키고 있는
	//rlink값(원래before다음에 있던 노드)을 새로운 노드의 오른쪽link에 대입(2)
	//llink가 새로운 노드를 가리켜야함
	before->rlink->llink = newnode;
	//newnode가 가리키고 있는 것(삽입할 노드)의 rlink가 가리키고 있는 llink가
	//가리키고 있는 것에 대입
	before->rlink = newnode;
	//before노드의 rlink값에 삽입할 노드의 주소 대입

}


void ddelete(DListNode* head, DListNode* removed)
{
	//head는 없어지면 안됨
	if (removed == head) return;
	//removed로 쫒아가야함
	removed->llink->rlink = removed->rlink;//before노드가 삭제할 노드
	//다음 도느를 가리킴
	removed->rlink->llink = removed->llink;
	//removed가 가리키는 것의 llink값을 대입(삭제할 노드의 다음 노드가 before노드
	//가리킴
	//삭제할 노드를 삭제해줌
	free(removed);
}

void print_dlist(DListNode*phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
	{
		if (p == current)
			printf("\n%s [O]", p->data);
		else
			printf("\n%s", p->data);
	}
	printf("\n");

}