#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<crtdbg.h>

// ���׽��� �� ���� ǥ���ϴ� ����ü
typedef struct _POLYNODE_ {
	int coef;  // ���
	int exp;   // ����
	struct _POLYNODE_* next;  // ���� ���� ����Ű�� ������
} POLYNODE;

// ���׽��� ǥ���ϴ� ����ü
typedef struct _POLYLIST_ {
	POLYNODE* head;  // ���׽��� ù ���� ����Ű�� ������
	int numOfData;  // ���׽��� �� ����
} POLYLIST;

// ���׽� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
void InitPolyList(POLYLIST* pList) {
	pList->head = (POLYNODE*)calloc(1, sizeof(POLYNODE));  // ���� ��� ����
	pList->head->next = NULL;  // ���� ����� next�� NULL�� ����
	pList->numOfData = 0;  // ������ ������ 0���� �ʱ�ȭ
}

// ���׽Ŀ� ���� �߰��ϴ� �Լ�
void InsertPolyNode(POLYLIST* pList, int coef, int exp) {
	POLYNODE* newNode = (POLYNODE*)calloc(1, sizeof(POLYNODE));  // �� ��� ����
	newNode->coef = coef;  // �� ����� ��� ����
	newNode->exp = exp;  // �� ����� ���� ����
	newNode->next = NULL;  // �� ����� next�� NULL�� ����

	POLYNODE* cur = pList->head;  // ���� ��带 ���� ���� ����
	while (cur->next != NULL && cur->next->exp > exp) {  //������ �´� ���� ���� ������
		cur = cur->next;
	}
	newNode->next = cur->next;  // �� ��带 ����Ʈ�� ����
	cur->next = newNode;
	pList->numOfData += 1;  // ������ ���� ����
}

// �� ���׽��� ���ϴ� �Լ�
POLYLIST* AddPoly(POLYLIST* pList1, POLYLIST* pList2) {
	POLYLIST* result = (POLYLIST*)malloc(sizeof(POLYLIST));  // ��� ���׽� ����
	InitPolyList(result);  // ��� ���׽� �ʱ�ȭ

	POLYNODE* cur1 = pList1->head->next;  // ù ��° ���׽��� ù ��
	POLYNODE* cur2 = pList2->head->next;  // �� ��° ���׽��� ù ��

	while (cur1 != NULL && cur2 != NULL) {  // �� ���׽��� ��� ���� ��ȸ
		if (cur1->exp > cur2->exp) {  // ù ��° ���׽��� ���� �� ū ���
			InsertPolyNode(result, cur1->coef, cur1->exp);  // ��� ���׽Ŀ� ù ��° ���׽��� �� �߰�
			cur1 = cur1->next;  // ���� ������ �̵�
		}
		else if (cur1->exp < cur2->exp) {  // �� ��° ���׽��� ���� �� ū ���
			InsertPolyNode(result, cur2->coef, cur2->exp);  // ��� ���׽Ŀ� �� ��° ���׽��� �� �߰�
			cur2 = cur2->next;  // ���� ������ �̵�
		}
		else {  // �� ���� ������ ���� ���
			InsertPolyNode(result, cur1->coef + cur2->coef, cur1->exp);  // �� ���� ����� ���� ���� ��� ���׽Ŀ� �߰�
			cur1 = cur1->next;  // ���� ������ �̵�
			cur2 = cur2->next;  // ���� ������ �̵�
		}
	}

	while (cur1 != NULL) {  // ù ��° ���׽��� ���� ���� ��� ���׽Ŀ� �߰�
		InsertPolyNode(result, cur1->coef, cur1->exp);
		cur1 = cur1->next;
	}

	while (cur2 != NULL) {  // �� ��° ���׽��� ���� ���� ��� ���׽Ŀ� �߰�
		InsertPolyNode(result, cur2->coef, cur2->exp);
		cur2 = cur2->next;
	}

	return result;  // ��� ���׽� ��ȯ
}

// ���׽��� ����ϴ� �Լ�
void PrintPoly(POLYLIST* pList) {
	POLYNODE* cur = pList->head->next;  // ù �׺��� ����
	while (cur != NULL) {  // ��� ���� ��ȸ
		printf("%dx^%d", cur->coef, cur->exp);  // �� �� ���
		if (cur->next != NULL) {
			printf(" + ");  // ���� ���� ������ '+' ���
		}
		cur = cur->next;  // ���� ������ �̵�
	}
	printf("\n");  // �� �ٲ�
}

// ���׽� ����Ʈ�� �����ϴ� �Լ�
void FreePolyList(POLYLIST* pList) {
	POLYNODE* cur = pList->head;  // ù �׺��� ����
	while (cur != NULL) {  // ��� ���� ��ȸ
		POLYNODE* next = cur->next;  // ���� ���� �ӽ� ������ ����
		free(cur);  // ���� �� ����
		cur = next;  // ���� ������ �̵�
	}
}

int main() {
	POLYLIST list1, list2;
	InitPolyList(&list1);  // ù ��° ���׽� �ʱ�ȭ
	InitPolyList(&list2);  // �� ��° ���׽� �ʱ�ȭ

	InsertPolyNode(&list1, 3, 4);  // ù ��° ���׽Ŀ� �� �߰�
	InsertPolyNode(&list1, 2, 2);
	InsertPolyNode(&list1, 1, 0);

	InsertPolyNode(&list2, 5, 1);  // �� ��° ���׽Ŀ� �� �߰�
	InsertPolyNode(&list2, 6, 0);

	printf("1�� ���׽�: ");
	PrintPoly(&list1);  // ù ��° ���׽� ���

	printf("2�� ���׽�: ");
	PrintPoly(&list2);  // �� ��° ���׽� ���

	POLYLIST* result = AddPoly(&list1, &list2);  // �� ���׽��� ����

	printf("Result: ");
	PrintPoly(result);  // ��� ���׽� ���

	// �޸� ����
	FreePolyList(&list1);
	FreePolyList(&list2);
	FreePolyList(result);

	return 0;
}
