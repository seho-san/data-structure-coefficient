#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <crtdbg.h>

// ���׽� ��� ����ü ����
typedef struct _POLYNODE_ {
	int coef; // ���
	int exp; // ����
	struct _POLYNODE_* next; // ���� ���� ����Ű�� ������
} POLYNODE;

// �־��� ����� ������ �� ��带 �����ϴ� �Լ�
POLYNODE* createNode(int coef, int exp) {
	POLYNODE* newNode = (POLYNODE*)malloc(sizeof(POLYNODE)); // �� ��带 ���� �޸� �Ҵ�
	newNode->coef = coef; // ���
	newNode->exp = exp; // ���� 
	newNode->next = NULL; // ���� ��带 NULL�� ����
	return newNode; // �� ����� ������ ��ȯ
}

// ���׽Ŀ� �� ��带 �����ϴ� �Լ�
void insertNode(POLYNODE** head, int coef, int exp) {
	POLYNODE* newNode = createNode(coef, exp); // �� ��� ����
	if (*head == NULL || (*head)->exp < exp) { // ���׽��� ��� �ְų� �� ����� ������ �� ū ���
		newNode->next = *head; // �� ��带 ���׽��� �� �տ� ����
		*head = newNode; // ��带 �� ���� ������Ʈ
	}
	else { // �� ����� ������ �� ���� ���
		POLYNODE* temp = *head; // �ӽ� ������ ����
		while (temp->next != NULL && temp->next->exp >= exp) //������ ����Ű�� ��尡 ���� �ƴϰ� ������ ��ġ�� ������
			temp = temp->next; 
		newNode->next = temp->next; // �� ��带 ���׽Ŀ� ����
		temp->next = newNode;
	}
}

// �� ���׽��� ���ϴ� �Լ�
POLYNODE* addPolynomials(POLYNODE* poly1, POLYNODE* poly2) {
	POLYNODE* result = NULL; // ��� ���׽� �ʱ�ȭ
	while (poly1 && poly2) { // �� ���׽� ��� ��尡 ���� �ִ� ����
		if (poly1->exp > poly2->exp) { // ù ��° ���׽��� ���� ���� ������ �� ū ���
			insertNode(&result, poly1->coef, poly1->exp); // ù ��° ���׽��� ���� ���� ����� �߰�
			poly1 = poly1->next; // ù ��° ���׽��� ���� ������ �̵�
		}
		else if (poly1->exp < poly2->exp) { // �� ��° ���׽��� ���� ���� ������ �� ū ���
			insertNode(&result, poly2->coef, poly2->exp); // �� ��° ���׽��� ���� ���� ����� �߰�
			poly2 = poly2->next; // �� ��° ���׽��� ���� ������ �̵�
		}
		else { // �� ���׽��� ���� ���� ������ ���� ���
			insertNode(&result, poly1->coef + poly2->coef, poly1->exp); // �� ���� ����� ���� ���� ����� �߰�
			poly1 = poly1->next; // ù ��° ���׽��� ���� ������ �̵�
			poly2 = poly2->next; // �� ��° ���׽��� ���� ������ �̵�
		}
	}
	while (poly1 || poly2) { // �� ���׽��� ��� ���� ó���� �� �ٸ� ���׽��� ���� ���� ����� �߰�
		if (poly1) { //poly1�� null�� �ƴϸ�
			insertNode(&result, poly1->coef, poly1->exp); // ù ��° ���׽��� ���� ���� ����� �߰�
			poly1 = poly1->next; // ù ��° ���׽��� ���� ������ �̵�
		}
		if (poly2) {
			insertNode(&result, poly2->coef, poly2->exp); // �� ��° ���׽��� ���� ���� ����� �߰�
			poly2 = poly2->next; // �� ��° ���׽��� ���� ������ �̵�
		}
	}
	return result; // ��� ���׽� ��ȯ
}

// ���׽��� ����ϴ� �Լ�
void printPolynomial(POLYNODE* head) {
	while (head) { // ���׽��� ��� ���� ��ȸ
		printf("%dx^%d", head->coef, head->exp); // ���� �� ���
		head = head->next; // ���� ������ �̵�
		if (head != NULL) // ���� ���� �ִ� ���
			printf(" + "); // ���� ��ȣ ���
	}
	printf("\n"); // �� �ٲ�
}

// ���׽� ����Ʈ�� �����ϴ� �Լ�
void freePolynomial(POLYNODE* head) {
	POLYNODE* temp;
	while (head) { // ����Ʈ�� ��� ��带 ��ȸ
		temp = head; // ���� ��带 �ӽ� ������ ����
		head = head->next; // ���� ���� �̵�
		free(temp); // ���� ��� ����
	}
}

// ���� �Լ�
int main() {
	POLYNODE* poly1 = NULL; // ù ��° ���׽� �ʱ�ȭ
	POLYNODE* poly2 = NULL; // �� ��° ���׽� �ʱ�ȭ
	POLYNODE* result = NULL; // ��� ���׽� �ʱ�ȭ

	// ù ��° ���׽Ŀ� �� �߰�
	insertNode(&poly1, 5, 2);
	insertNode(&poly1, 4, 1);
	insertNode(&poly1, 2, 0);

	// �� ��° ���׽Ŀ� �� �߰�
	insertNode(&poly2, 5, 1);
	insertNode(&poly2, 5, 0);

	// ù ��° ���׽� ���
	printf("ù ��° ���׽�: ");
	printPolynomial(poly1);

	// �� ��° ���׽� ���
	printf("�� ��° ���׽�: ");
	printPolynomial(poly2);

	// �� ���׽��� ���ϰ� ����� ����
	result = addPolynomials(poly1, poly2);

	
	//�� ���� ���׽��� ����ϰ��� �� ��� result�� ���ο� ���׽��� ���ϸ� �ȴ�.
	POLYNODE* poly3 = NULL; // �� ��° ���׽� �ʱ�ȭ
	insertNode(&poly3, 4, 2);
	insertNode(&poly3, 2, 1);
	insertNode(&poly3, 9, 0);

	// �� ��° ���׽� ���
	printf("�� ��° ���׽�: ");
	printPolynomial(poly3);

	result = addPolynomials(result, poly3);
	

	// ��� ���׽� ���
	printf("���: ");
	printPolynomial(result);

	// ���׽� ����Ʈ ����
	freePolynomial(poly1);
	freePolynomial(poly2);
	freePolynomial(result);

	return 0; // ���α׷� ����
}
