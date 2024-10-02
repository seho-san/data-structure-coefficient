#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <crtdbg.h>

// 다항식 노드 구조체 정의
typedef struct _POLYNODE_ {
	int coef; // 계수
	int exp; // 지수
	struct _POLYNODE_* next; // 다음 항을 가리키는 포인터
} POLYNODE;

// 주어진 계수와 지수로 새 노드를 생성하는 함수
POLYNODE* createNode(int coef, int exp) {
	POLYNODE* newNode = (POLYNODE*)malloc(sizeof(POLYNODE)); // 새 노드를 위한 메모리 할당
	newNode->coef = coef; // 계수
	newNode->exp = exp; // 지수 
	newNode->next = NULL; // 다음 노드를 NULL로 설정
	return newNode; // 새 노드의 포인터 반환
}

// 다항식에 새 노드를 삽입하는 함수
void insertNode(POLYNODE** head, int coef, int exp) {
	POLYNODE* newNode = createNode(coef, exp); // 새 노드 생성
	if (*head == NULL || (*head)->exp < exp) { // 다항식이 비어 있거나 새 노드의 지수가 더 큰 경우
		newNode->next = *head; // 새 노드를 다항식의 맨 앞에 삽입
		*head = newNode; // 헤드를 새 노드로 업데이트
	}
	else { // 새 노드의 지수가 더 작은 경우
		POLYNODE* temp = *head; // 임시 포인터 생성
		while (temp->next != NULL && temp->next->exp >= exp) //템프가 가리키는 노드가 널이 아니고 지수가 일치할 때까지
			temp = temp->next; 
		newNode->next = temp->next; // 새 노드를 다항식에 삽입
		temp->next = newNode;
	}
}

// 두 다항식을 더하는 함수
POLYNODE* addPolynomials(POLYNODE* poly1, POLYNODE* poly2) {
	POLYNODE* result = NULL; // 결과 다항식 초기화
	while (poly1 && poly2) { // 두 다항식 모두 노드가 남아 있는 동안
		if (poly1->exp > poly2->exp) { // 첫 번째 다항식의 현재 항의 지수가 더 큰 경우
			insertNode(&result, poly1->coef, poly1->exp); // 첫 번째 다항식의 현재 항을 결과에 추가
			poly1 = poly1->next; // 첫 번째 다항식의 다음 항으로 이동
		}
		else if (poly1->exp < poly2->exp) { // 두 번째 다항식의 현재 항의 지수가 더 큰 경우
			insertNode(&result, poly2->coef, poly2->exp); // 두 번째 다항식의 현재 항을 결과에 추가
			poly2 = poly2->next; // 두 번째 다항식의 다음 항으로 이동
		}
		else { // 두 다항식의 현재 항의 지수가 같은 경우
			insertNode(&result, poly1->coef + poly2->coef, poly1->exp); // 두 항의 계수를 더한 항을 결과에 추가
			poly1 = poly1->next; // 첫 번째 다항식의 다음 항으로 이동
			poly2 = poly2->next; // 두 번째 다항식의 다음 항으로 이동
		}
	}
	while (poly1 || poly2) { // 한 다항식의 모든 항을 처리한 후 다른 다항식의 남은 항을 결과에 추가
		if (poly1) { //poly1이 null이 아니면
			insertNode(&result, poly1->coef, poly1->exp); // 첫 번째 다항식의 남은 항을 결과에 추가
			poly1 = poly1->next; // 첫 번째 다항식의 다음 항으로 이동
		}
		if (poly2) {
			insertNode(&result, poly2->coef, poly2->exp); // 두 번째 다항식의 남은 항을 결과에 추가
			poly2 = poly2->next; // 두 번째 다항식의 다음 항으로 이동
		}
	}
	return result; // 결과 다항식 반환
}

// 다항식을 출력하는 함수
void printPolynomial(POLYNODE* head) {
	while (head) { // 다항식의 모든 항을 순회
		printf("%dx^%d", head->coef, head->exp); // 현재 항 출력
		head = head->next; // 다음 항으로 이동
		if (head != NULL) // 다음 항이 있는 경우
			printf(" + "); // 덧셈 기호 출력
	}
	printf("\n"); // 줄 바꿈
}

// 다항식 리스트를 해제하는 함수
void freePolynomial(POLYNODE* head) {
	POLYNODE* temp;
	while (head) { // 리스트의 모든 노드를 순회
		temp = head; // 현재 노드를 임시 변수에 저장
		head = head->next; // 다음 노드로 이동
		free(temp); // 현재 노드 해제
	}
}

// 메인 함수
int main() {
	POLYNODE* poly1 = NULL; // 첫 번째 다항식 초기화
	POLYNODE* poly2 = NULL; // 두 번째 다항식 초기화
	POLYNODE* result = NULL; // 결과 다항식 초기화

	// 첫 번째 다항식에 항 추가
	insertNode(&poly1, 5, 2);
	insertNode(&poly1, 4, 1);
	insertNode(&poly1, 2, 0);

	// 두 번째 다항식에 항 추가
	insertNode(&poly2, 5, 1);
	insertNode(&poly2, 5, 0);

	// 첫 번째 다항식 출력
	printf("첫 번째 다항식: ");
	printPolynomial(poly1);

	// 두 번째 다항식 출력
	printf("두 번째 다항식: ");
	printPolynomial(poly2);

	// 두 다항식을 더하고 결과를 저장
	result = addPolynomials(poly1, poly2);

	
	//더 많은 다항식을 계산하고자 할 경우 result와 새로운 다항식을 더하면 된다.
	POLYNODE* poly3 = NULL; // 세 번째 다항식 초기화
	insertNode(&poly3, 4, 2);
	insertNode(&poly3, 2, 1);
	insertNode(&poly3, 9, 0);

	// 세 번째 다항식 출력
	printf("세 번째 다항식: ");
	printPolynomial(poly3);

	result = addPolynomials(result, poly3);
	

	// 결과 다항식 출력
	printf("결과: ");
	printPolynomial(result);

	// 다항식 리스트 해제
	freePolynomial(poly1);
	freePolynomial(poly2);
	freePolynomial(result);

	return 0; // 프로그램 종료
}
