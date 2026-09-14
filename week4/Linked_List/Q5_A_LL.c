//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
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
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	/* add your code here */
	/*
	설계)
		- int ll_size, ll_f_size, ll_b_size; 각 ll의 사이즈
		- ListNode *cur; (기존 리스트를 옮겨 다닐 포인터 cur)
		- int mid = (ll_size)/2; size를 반으로 나눈 값
		- mid가 반으로 나누어떨어지지 않는 경우 resultFrontList 사이즈 +1
		- ll_f_size 순회하면서 insertNode를 사용하여 추가 (메모리는 어떻게?)
		- ll_b_size 순회하면서 insertNode를 사용하여 추가 (메모리는 어떻게?)
	*/
	int ll_size, ll_f_size, ll_b_size, mid;
	ListNode *ll_cur; // 기존 리스트의 포인터

	// 기존 리스트 ll가 비어있을 경우 종료
	if(ll_size == 0){
		return;
	}
	ll_size = ll->size;
	mid = (ll_size)/2;

	// mid가 반으로 딱 나누어지지 않을 때, ll_f_size 사이즈 1을 더 준다
	if((ll_size)%2 == 0){
		ll_f_size = mid;
		ll_b_size = mid;
	}else{
		ll_f_size = mid+1;
		ll_b_size = mid;
	}

	// ll_cur ll->head로 초기화
	ll_cur = ll->head;

	// ll_f_size만큼 ll의 리스트를 resultFrontList에 할당
	for(int i=0; i<ll_f_size; i++){
	
		insertNode(resultFrontList, i, ll_cur->item);
		ll_cur = ll_cur->next;
	}	

	// ll_b_size만큼 ll의 리스트를 resultBackList에 할당
	for(int i=0; i<ll_b_size; i++){
		insertNode(resultBackList, i, ll_cur->item);
		ll_cur = ll_cur->next;
	}
}

///////////////////////////////////////////////////////////////////////////////////

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
