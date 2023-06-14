#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//���߿��Ḯ��Ʈ ���� �����Ͱ� �ƴ϶� �ϳ��� ��� (�����)
//������ ����x, ù��° link�� ��������带 ����Ű��
//���� link�� ù��° ��带 ����Ű�� �ְ� ������ ����� ��ũ�� �����
//��带 �����Ѿ� �Ѵ�.
//ù��° ���� ������ ���� head�� ����Ŵ

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
		printf("===== $���� ���� �޴�$ =====\n");
		printf("n)���� ������ �����մϴ�\n");
		printf("p)���� ������ �����մϴ�\n");
		printf("d)���� ���õ� ������ �����մϴ�\n");
		printf("i)���� ���õ� ���� ������ ������ �߰��մϴ�\n");
		printf("o)���� ����Ʈ�� ����մϴ�(���� ���õ� ���� : o)\n");
		printf("e)���α׷��� �����մϴ�.\n");
		printf("====================\n");
		printf("�޴��� �������ּ���.");
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
			printf("�߰��� ������ �̸��� �Է��ϼ���: ");
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
			printf("�������� �ʴ� �޴��Դϴ�. �ٽ� �Է����ּ���.\n\n");
		getchar();
	} while (ch != 'e');
}
	/*do
	{
		printf("\n��ɾ �Է��Ͻÿ�(<, >, q): ");
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

//rlink�� ������, llink�� ������ ����Ű�� �ִµ� �߰��� �ϳ��� ��带 �߰�
//���Ե� ����� 1���� ����, 2���� ������ ����Ű��
//���� rlink�� ���Ե� ��� ����Ű�� ���� llink�� ���Ե� ��� ����Ŵ
void dinsert(DListNode* before, element data) //before -> previous
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode)); //���ο� ��带
	//����ų �� �ִ� ������ ����� DListNode�� ������ �� �����Ͱ� �� ��带 ����Ų��.
	strcpy(newnode->data, data); //data���� ���� ������� ����� data���� ����
	//�켱 ���ο� ��尡 �յڸ� ����Ű�� ��������
	newnode->llink = before; //before���� ���ο� ����� ����link�� ����(1)
	newnode->rlink = before->rlink;//before�� ����Ű�� �ִ�
	//rlink��(����before������ �ִ� ���)�� ���ο� ����� ������link�� ����(2)
	//llink�� ���ο� ��带 �����Ѿ���
	before->rlink->llink = newnode;
	//newnode�� ����Ű�� �ִ� ��(������ ���)�� rlink�� ����Ű�� �ִ� llink��
	//����Ű�� �ִ� �Ϳ� ����
	before->rlink = newnode;
	//before����� rlink���� ������ ����� �ּ� ����

}


void ddelete(DListNode* head, DListNode* removed)
{
	//head�� �������� �ȵ�
	if (removed == head) return;
	//removed�� �i�ư�����
	removed->llink->rlink = removed->rlink;//before��尡 ������ ���
	//���� ������ ����Ŵ
	removed->rlink->llink = removed->llink;
	//removed�� ����Ű�� ���� llink���� ����(������ ����� ���� ��尡 before���
	//����Ŵ
	//������ ��带 ��������
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