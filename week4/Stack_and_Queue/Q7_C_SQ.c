//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_INT -1000

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList


typedef struct stack
{
	LinkedList ll;
} Stack; // You should not change the definition of stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int balanced(char *expression);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	char ch, str[256];
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Enter a string:\n");
	printf("2: Check whether expressions comprised of the characters ()[]{} is balanced:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Enter expressions without spaces to check whether it is balanced or not: ");
			scanf("%s", str);
			break;
        case 2:
            if(balanced(str))
                printf("not balanced!\n");
            else
                printf("balanced!\n");
			break;
		case 0:
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////
int balanced(char *expression)
{
	/* add your code here */
	/*
		설계)
			- 필요한 변수는? Stack s, int length(expression의 길이를 담을)
			- 초기화는? Stack s, int length = strlen(expression)
				-> strlen() 함수를 사용하기 위해서는 헤더에 string.h 추가
			- 예외 처리는? expression이 빈 값일 때 0 반환
			- expression char 배열 순회
				- {, [, ( 을 만났을 때 s에 push
				- }, ], ) 을 만났을 때 s에서 pop
			- s에 값이 남아있다면 return 0, 비어 있다면 return 1
		TroubleShooting)
			1) 올바르지 않은 짝임에도 1 반환이 된다.
				-> 1을 반환하지 않았음에도 1을 반환한다는 것은 1이 고정값인가 본데
			2) 예외 케이스를 생각하지 못함
				-> {}[]}일 경우 1 반환
				-> isEmptyStack 분기를 타지 않는다. -> 아니다! 탄다.
				-> {]) 일 경우에는 잘못된 코드이다. 짝이 맞지 않는데 여는 괄호가 있다는 이유로만 pop한다.
				-> 예외 케이스를 세 개로 짝지어 분기 처리
	*/
	Stack s = {0}; // s 초기화
	int length = strlen(expression);

	// expression이 비어 있다면
	if(length == 0){
		return 0;
	}

	// for(int i=0; i<length; i++){
	// 	// {, [, ( 을 포함한다면 push1
	// 	if(expression[i] == '{' || expression[i] == '[' || expression[i] == '('){
	// 		push(&s, expression[i]);
	// 	}
	// 	// {, [, ( 을 포함한다면 pop
	// 	if(expression[i] == '}' || expression[i] == ']' || expression[i] == ')'){
	// 		// pop하기 전에 s가 비어 있다면 종료
	// 		if(isEmptyStack(&s)){
	// 			return 0;
	// 		}
	// 		if(s.ll.head->item == '{' || s.ll.head->item == '[' || s.ll.head->item == '('){
	// 			pop(&s);
	// 		}
	// 	}
		
	// }
	
	for(int i=0; i<length; i++){
		if(expression[i] == '{' || expression[i] == '(' || expression[i] == '['){
			push(&s, expression[i]);
		}
		if(expression[i] == '}' || expression[i] == ')' || expression[i] == ']'){
			if(isEmptyStack(&s)){
				return 1;
			}
			if(s.ll.head->item == '{' && expression[i] == '}'){
				pop(&s);
			}else if(s.ll.head->item == '(' && expression[i] == ')'){
				pop(&s);
			}else if(s.ll.head->item == '[' && expression[i] == ']'){
				pop(&s);
			}else{
				return 0;
			}
		}
	}

	if(isEmptyStack(&s)){
		return 0;
	}
	return 1;
	
}

////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
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

/////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int peek(Stack *s){
    if(isEmptyStack(s))
        return MIN_INT;
    else
        return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


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
		if (ll->head == NULL)
		{
			exit(0);
		}
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
		if (pre->next == NULL)
		{
			exit(0);
		}
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
