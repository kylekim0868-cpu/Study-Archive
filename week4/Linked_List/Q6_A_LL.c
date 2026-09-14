//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
    /* add your code here */
	/*
	설계)
		- int size;
		- ListNode *cur = *prtHead; 
		- ListNode *temp;
		- while문으로 size를 구한다
		- size만큼 순회
			- 앞 뒤 item을 비교하여 앞의 item이 작다면 맨 뒤로 보내고
			- 아니라면 그대로 유지 
	*/
	/*
		1) 위의 설계대로 답을 구한다 하더라도 O(N2)이 되어 문제 조건 위배
			-> size개수를 구하는 것이 아닌 다른 방법으로 접근
			-> while문으로 해결?
	*/
	/* 접근 방법1) 실패*/
	// LinkedList *ll;
	// ListNode *cur = *ptrHead;

	// int size = 0; // 입력받은 ll의 사이즈 0 초기화
	// while(cur->next != NULL){
	// 	size++;
	// 	cur = cur->next;
	// }

	// printf("size: %d", size);
	// return 0;
	/*
	설계2)
		- while을 사용하여 cur가 NULL일 때까지
			- 최대값이 담겨져 있는 node를 저장
		- 최대값이 저장되어 있는 node 앞으로 이동시키기
	*/
	/* 접근 방법2) */
	/*
	TroubleShootind
		1) max가 첫 번째일 경우 예외처리가 없다
		2) ListNode *temp를 선언하고 초기화하지 않았기 때문에 segmentation fault 오류가 발생한다. 알 수 없는 메모리를 가리키기 때문에. 
	*/
	// 연결 리스트가 비어있다면 -1 반환
	if(ptrHead == NULL){
		return -1;
	}
	ListNode *cur = *ptrHead; // 움직일 노드 포인터
	ListNode *prev = NULL;
	ListNode *max = *ptrHead; // 일단 시작값이 최댓값이라고 가정! (-> 이게 중요)
	ListNode *maxPrev = NULL; 

	// 맨 뒤까지 순회하면서 max의 포인터 추출
	while(cur != NULL){
		// 현재 노드가 최대값보다 크다면
		// max = cur, maxPrev = prev; 할당
		if(cur->item > max->item){
			max = cur;
			maxPrev = prev;
		}

		prev = cur;
		cur = cur->next;
	}

	cur = *ptrHead;
	
	// max 노드 첫 번째 노드라서 옮길 필요가 없다면
	if(maxPrev == NULL){
		return 0;
	}else{
		maxPrev->next = max->next;
		max->next = cur;
		*ptrHead = max;
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
