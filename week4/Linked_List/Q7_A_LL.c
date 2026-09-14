//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 7 */

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
void RecursiveReverse(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Reversed the linked list:\n");
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
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			RecursiveReverse(&(ll.head)); // You need to code this function
			printf("The resulting linked list after reversed the given linked list is: ");
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

void RecursiveReverse(ListNode **ptrHead)
{
	/* add your code here */
	/*
	설계)
		- 어느 부분을 재귀로 구현? 뒤에서 시작해서 뒤에 바로 앞에 있는 원소를 맨뒤로 보낸다는 생각
		- 종료지점은 언제로?
			-> 연결 리스트가 NULL이거나 리스트가 한 개일 때? tail과 head가 같을때
	*/
	/*
	Q7 재귀 뒤집기 TODO)

	[ ] 1. 코드 작성 전에 작은 리스트를 손으로 추적하기
		1 -> 2 -> 3 -> 4 -> NULL

		호출이 내려갈 때:
		Reverse(1) -> Reverse(2) -> Reverse(3) -> Reverse(4)

		호출이 돌아올 때:
		4 뒤에 3 연결 -> 3 뒤에 2 연결 -> 2 뒤에 1 연결

		주의: 4가 모든 노드와 직접 자리를 바꾸는 것이 아니다.
		각 호출은 현재 노드와 바로 다음 노드의 연결 하나만 뒤집는다.

	[ ] 2. 종료 조건 정하기
		다음 경우에는 뒤집을 연결이 없다.
		- ptrHead 자체가 NULL인 경우
		- 현재 노드가 NULL인 경우
		- 현재 노드의 next가 NULL인 경우(노드가 하나 또는 마지막 노드)

		질문: 위 조건에서 바로 return 해야 하는 이유를 말로 설명할 수 있는가?

	[ ] 3. 재귀에 맡길 범위 정하기
		현재 노드까지 한꺼번에 뒤집으려 하지 않는다.
		현재 노드의 "다음 노드부터 시작하는 리스트"를 재귀에 맡긴다.

		질문: 현재 노드가 1이라면 재귀 호출은 1과 2 중 어디서 시작해야 하는가?
		질문: ListNode **를 받는 현재 함수에서 다음 노드의 주소를 어떻게 전달할 것인가?

	[ ] 4. 재귀 호출 전 현재 노드 기억하기
		재귀 호출이 끝난 뒤에도 현재 노드를 다시 사용해야 한다.

		질문: 현재 노드를 가리킬 지역 포인터 하나가 필요한가?
		질문: 재귀가 돌아온 뒤에도 그 포인터는 같은 노드를 가리키는가?

	[ ] 5. 돌아오는 과정에서 역방향 연결 만들기
		현재 노드가 3이고 다음 노드가 4라면 원하는 결과는 다음과 같다.
		3 -> 4  에서  4 -> 3

		질문: 현재 노드의 next는 4를 가리킨다.
		      그렇다면 4의 next가 3을 가리키게 하려면
		      어떤 포인터의 next를 변경해야 하는가?

	[ ] 6. 기존 정방향 연결 끊기
		4 -> 3을 만든 뒤에도 3 -> 4를 그대로 두면 순환 구조가 생긴다.

		3 -> 4
		^    |
		|____|

		질문: 현재 노드가 기존 다음 노드를 더 이상 가리키지 않게 하려면
		      현재 노드의 next에 무엇을 넣어야 하는가?

	[ ] 7. 새로운 head가 언제 결정되는지 확인하기
		마지막 노드에 도착했을 때 그 노드가 뒤집힌 리스트의 새 head가 된다.
		재귀가 돌아오는 동안 새 head는 계속 유지되어야 한다.

		질문: void 함수이므로 새 head를 return할 수 없다.
		      그렇다면 최종적으로 *ptrHead를 언제, 어떤 노드로 바꿔야 하는가?

	[ ] 8. 아래 입력을 순서대로 테스트하기
		- 빈 리스트
		- 1 -> NULL
		- 1 -> 2 -> NULL
		- 1 -> 2 -> 3 -> 4 -> NULL

	[ ] 9. 실행 후 확인하기
		- 새로운 head가 원래 마지막 노드인가?
		- 모든 노드가 한 번씩만 출력되는가?
		- 마지막 노드의 next가 NULL인가?
		- 같은 숫자가 무한히 출력되는 순환 구조가 생기지 않았는가?

	한 줄 설계)
		현재 노드 뒤의 리스트를 재귀로 먼저 뒤집고,
		호출이 돌아올 때 현재 노드를 그 뒤에 연결한 뒤 기존 연결을 끊는다.
	*/	
	ListNode *first;
	ListNode *next;
	
	// ptrHead가 NULL
	if(ptrHead == NULL || *ptrHead == NULL || (*ptrHead)->next == NULL){
		return;
	}
	first = *ptrHead; // 현재 노드 기억
	next = first->next; // 다음 리스트의 시작 기억

	// 현재 노드의 바로 다음 노드를 재귀에 맡길 리스트의 시작점으로 저장
	// cur를 재귀함수로 넘겨준다
	RecursiveReverse(&next);

	// 원래 다음 노드가 현재 노드를 가리키게 하기
	first->next->next = first;
	// 기존 정방향 연결 끊기
	first->next = NULL;
	// 새로운 첫 노드 반영
	*ptrHead = next;
	
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
