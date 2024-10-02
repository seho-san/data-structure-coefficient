#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<crtdbg.h>

// 다항식의 각 항을 표현하는 구조체
typedef struct _POLYNODE_ {
	int coef;  // 계수
	int exp;   // 지수
	struct _POLYNODE_* next;  // 다음 항을 가리키는 포인터
} POLYNODE;

// 다항식을 표현하는 구조체
typedef struct _POLYLIST_ {
	POLYNODE* head;  // 다항식의 첫 항을 가리키는 포인터
	int numOfData;  // 다항식의 항 개수
} POLYLIST;

// 다항식 리스트를 초기화하는 함수
void InitPolyList(POLYLIST* pList) {
	pList->head = (POLYNODE*)calloc(1, sizeof(POLYNODE));  // 더미 노드 생성
	pList->head->next = NULL;  // 더미 노드의 next를 NULL로 설정
	pList->numOfData = 0;  // 데이터 개수를 0으로 초기화
}

// 다항식에 항을 추가하는 함수
void InsertPolyNode(POLYLIST* pList, int coef, int exp) {
	POLYNODE* newNode = (POLYNODE*)calloc(1, sizeof(POLYNODE));  // 새 노드 생성
	newNode->coef = coef;  // 새 노드의 계수 설정
	newNode->exp = exp;  // 새 노드의 지수 설정
	newNode->next = NULL;  // 새 노드의 next를 NULL로 설정

	POLYNODE* cur = pList->head;  // 현재 노드를 더미 노드로 설정
	while (cur->next != NULL && cur->next->exp > exp) {  //차수가 맞는 항이 나올 때까지
		cur = cur->next;
	}
	newNode->next = cur->next;  // 새 노드를 리스트에 연결
	cur->next = newNode;
	pList->numOfData += 1;  // 데이터 개수 증가
}

// 두 다항식을 더하는 함수
POLYLIST* AddPoly(POLYLIST* pList1, POLYLIST* pList2) {
	POLYLIST* result = (POLYLIST*)malloc(sizeof(POLYLIST));  // 결과 다항식 생성
	InitPolyList(result);  // 결과 다항식 초기화

	POLYNODE* cur1 = pList1->head->next;  // 첫 번째 다항식의 첫 항
	POLYNODE* cur2 = pList2->head->next;  // 두 번째 다항식의 첫 항

	while (cur1 != NULL && cur2 != NULL) {  // 두 다항식의 모든 항을 순회
		if (cur1->exp > cur2->exp) {  // 첫 번째 다항식의 항이 더 큰 경우
			InsertPolyNode(result, cur1->coef, cur1->exp);  // 결과 다항식에 첫 번째 다항식의 항 추가
			cur1 = cur1->next;  // 다음 항으로 이동
		}
		else if (cur1->exp < cur2->exp) {  // 두 번째 다항식의 항이 더 큰 경우
			InsertPolyNode(result, cur2->coef, cur2->exp);  // 결과 다항식에 두 번째 다항식의 항 추가
			cur2 = cur2->next;  // 다음 항으로 이동
		}
		else {  // 두 항의 지수가 같은 경우
			InsertPolyNode(result, cur1->coef + cur2->coef, cur1->exp);  // 두 항의 계수를 더한 항을 결과 다항식에 추가
			cur1 = cur1->next;  // 다음 항으로 이동
			cur2 = cur2->next;  // 다음 항으로 이동
		}
	}

	while (cur1 != NULL) {  // 첫 번째 다항식의 남은 항을 결과 다항식에 추가
		InsertPolyNode(result, cur1->coef, cur1->exp);
		cur1 = cur1->next;
	}

	while (cur2 != NULL) {  // 두 번째 다항식의 남은 항을 결과 다항식에 추가
		InsertPolyNode(result, cur2->coef, cur2->exp);
		cur2 = cur2->next;
	}

	return result;  // 결과 다항식 반환
}

// 다항식을 출력하는 함수
void PrintPoly(POLYLIST* pList) {
	POLYNODE* cur = pList->head->next;  // 첫 항부터 시작
	while (cur != NULL) {  // 모든 항을 순회
		printf("%dx^%d", cur->coef, cur->exp);  // 각 항 출력
		if (cur->next != NULL) {
			printf(" + ");  // 다음 항이 있으면 '+' 출력
		}
		cur = cur->next;  // 다음 항으로 이동
	}
	printf("\n");  // 줄 바꿈
}

// 다항식 리스트를 해제하는 함수
void FreePolyList(POLYLIST* pList) {
	POLYNODE* cur = pList->head;  // 첫 항부터 시작
	while (cur != NULL) {  // 모든 항을 순회
		POLYNODE* next = cur->next;  // 다음 항을 임시 변수에 저장
		free(cur);  // 현재 항 해제
		cur = next;  // 다음 항으로 이동
	}
}

int main() {
	POLYLIST list1, list2;
	InitPolyList(&list1);  // 첫 번째 다항식 초기화
	InitPolyList(&list2);  // 두 번째 다항식 초기화

	InsertPolyNode(&list1, 3, 4);  // 첫 번째 다항식에 항 추가
	InsertPolyNode(&list1, 2, 2);
	InsertPolyNode(&list1, 1, 0);

	InsertPolyNode(&list2, 5, 1);  // 두 번째 다항식에 항 추가
	InsertPolyNode(&list2, 6, 0);

	printf("1번 다항식: ");
	PrintPoly(&list1);  // 첫 번째 다항식 출력

	printf("2번 다항식: ");
	PrintPoly(&list2);  // 두 번째 다항식 출력

	POLYLIST* result = AddPoly(&list1, &list2);  // 두 다항식을 더함

	printf("Result: ");
	PrintPoly(result);  // 결과 다항식 출력

	// 메모리 해제
	FreePolyList(&list1);
	FreePolyList(&list2);
	FreePolyList(result);

	return 0;
}
