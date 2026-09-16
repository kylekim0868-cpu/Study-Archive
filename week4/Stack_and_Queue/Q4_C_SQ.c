//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////   linked list /////////////////////////////////

typedef struct _listnode{
   int item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
   ListNode *tail;
} LinkedList;

////////////////////////////////// stack    ///////////////////////////////////////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////////////////

typedef struct _queue{
	LinkedList ll;
} Queue;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void reverse(Queue *q);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *s);

///////////////////////////////////////////////////////////////////////////////////////////////////
void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

///////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    int c, value;

    Queue q;

    //initialize the queue
	q.ll.head =NULL;
	q.ll.size =0;
	q.ll.tail=NULL;

    c =1;

    printf("1: Insert an integer into the queue;\n");
    printf("2: Reverse the queue;\n");
    printf("0: Quit;\n");

    while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the queue: ");
			scanf("%d", &value);
			enqueue(&q, value);
			printf("The queue is: ");
			printList(&(q.ll));
			break;
		case 2:
			reverse(&q); // You need to code this function
			printf("The resulting queue after reversing its elements is: ");
			printList(&(q.ll));
			removeAllItems(&(q.ll));
			break;
		case 0:
			removeAllItems(&(q.ll));
			break; 
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void reverse(Queue *q)
{
	/* add your code here */
	/*
		설계)
			- Stack 초기화
			- Q에서 모든 원소를 꺼낸다
			- s에 담는다
			- s에서 pop사용해 q에 다시 담는다
				=> Queue는 FIFO Stack은 LIFO구조기 때문에 위의 방식대로 설계하면 역순으로 데이터를 넣게 된다
		TroubleShooting)
			1) segmentation fault
				-> 정확한 원인 파악을 위해 printf("여기까지 왔나?")를 사용해 step별로 파악해본다.
					-> ! printf()도 줄바꿈 없이 출력하면 버퍼에 남을 수 있어서, 출력이 안 보인다는 사실만으로 실행 위치를 단정하기는 어렵다.
				-> Stack *s; 이 부분이 문제가 있다.
				-> 초기화를 해주지 않고 메모리 할당만 시켜놨다.
				-> Stack *s = NULL;
				-> s->ll.size, s->ll.head 이 코드에서 bus error가 발생
			2) while(!isEmptyStack(&s)){
					pop(&s);
				}
				-> 이 코드가 문제가 발생하는 부분이다. 초기화를 한다면 반복해서 pop를 할 필요도 없고 이 분기를 거치지 않는다.
				해결) 
					방법은 구조체 변수, 포인터 변수를 활용하는 2가지 방법이 존재한다.
					Stack *s;는 메모리가 할당되지 않은 포인터
					Stack *s = NULL;도 역참조하면 오류
					Stack s = {0};처럼 실제 구조체 변수를 선언하는 것이 가장 간단한 해결책
					포인터 변수로 유지하려면 malloc() 후 사용하고 마지막에 free()해야 함
					현재 코드의 첫 번째 while (!isEmptyStack(s))는 초기화되지 않은 s를 사용하므로 제거해야 함

	*/
	// s 초기화 (2가지 방법)
	// 1) 포인터 변수 활용
	// 2) 구조체 변수 활용
	// * 포인터 변수 *
	// Stack *s = (Stack *)malloc(sizeof(*s));

	// if(s == NULL){
	// 	return;
	// }

	// * 구조체 변수 *
	// Stack s;
	// s.ll.head = NULL;
	// s.ll.size = 0;
	// s.ll.tail = NULL;
	
	Stack s = {0};
	int v = 0;

	while(!isEmptyStack(&s)){

	}
	// q 비워질 때까지 dequeue()를 사용하여 s(스택)에 담아준다
	while(!isEmptyQueue(q)){
		v = dequeue(q);
		push(&s, v);
	}
	// s 비워질 때까지 enqueue()를 사용하여 s(스택)에서 꺼내서 담는다
	while(!isEmptyStack(&s)){
		v = pop(&s);
		enqueue(q, v);
	}
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   int item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

void enqueue(Queue *q, int item){
   insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
   int item;
   item = ((q->ll).head)->item;
   removeNode(&(q->ll), 0);
   return item;
}

int isEmptyQueue(Queue *q){
   if ((q->ll).size == 0)
      return 1;
   return 0;
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
