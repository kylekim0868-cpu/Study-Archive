//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

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
void moveOddItemsToBack(LinkedList *ll);

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
	printf("2: Move all odd integers to the back of the linked list:\n");
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
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
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

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	/* add your code here */
	/*
		설계
		- ListNode *node; 변수 생성
		- 리스트의 size 만큼 순회
		 	- 홀수를 만나면 리스트의 맨 뒤로 보내준다 (-> cur->next = NULL)
			- cur = head; (cur 포인터를 head, 즉 첫 번째 노드를 바라보도록 초기화)
			- 짝수라면 다음 노드로 이동
			- cur = cur->next;
			- size는 변동X	
	*/ 
	/*
		TroubleShooting
		1) 홀수 count를 잘못 계산
			->해결방법: 홀수인 node의 item을 count하고 node의 위치를 변경해주지 않았다. 즉, 초기화를 하지 못했다
			1-1) 왜 자꾸 count가 size+1값이 나올까?
			->해결방법: clang -o 명령어는 수정한 소스파일이 바로 적용되지 않는 명령어. 소스를 수정한 뒤 다시 컴파일하지 않아 이전 실행 파일이 실행됐다
		2) 홀수 한 개만 맨 뒤로 이동시키고 종료함
			해결→ node->next = NULL은 현재 노드의 다음 연결을 끊는 동작이다.
			→ 현재 자리에서 노드를 빼고, 마지막 노드 뒤에 연결하는 과정이 빠져 있었다.
			→ prev 또는 head로 기존 연결을 수정하고, tail 뒤에 현재 노드를 붙이도록 수정했다.
			2-1) 여전히 한 개만 맨뒤로 이동시키고 초기화
			->해결:
			2-2) 다른 문제가 생겼다. segmentation fault. -> 잘못된 메모리 접근
			->해결: ! size만큼 순회한 후에 node를 다시 head를 초기화하지 않음. 이건 정말 중요한 실수다.
				예를 들어, 1,5,3,2, NULL<--|
						       node ----|
				전체 순회를 하고 나면 노드 2 바로 뒤인 node에 위치헀고 NULL을 바라보기 때문이다.
			3) 다음 주소를 저장햇다고 생각햇지만 연결 변경 후 길을 잃었다.
			-> temp = node는 현재 노드의 주소만 복사한다. 노드 자체나 기존 next를 복사하지 않는다.
			-> temp = node->next로 원래 다음 노드의 주소를 보관한 뒤 연결을 변경하도록 수정했다.
			4) prev가 이전 노드를 가리키지 않았다.
			→ 매 반복 시작에서 prev = node를 하면 현재 노드의 주소로 덮어쓰게 된다.
			→ 짝수를 현재 자리에 남기고 지나갈 때만 prev를 갱신했다.
			→ 홀수를 빼낼 때는 이전 노드가 그대로이므로 prev도 유지했다.
	*/
	ListNode *node = ll->head; // ll주소를 바라보는 ListNode형의 node 할당
	ListNode *temp; //
	ListNode *prev = NULL;
	ListNode *tail = ll->head;
	int count = 0;

	//ll의 size만큼 순회하며 홀수 개수 체크 + 마지막 노드 체크
	for(int i=0; i<ll->size; i++){
		// 노드의 item이 홀수라면 count++
		if((node->item)%2 != 0){
			count++;
		}

		tail = node;
		node = node->next;
	}
	int temp_cnt = 0;
	node = ll->head; // !! size만큼 순회한 후에 node를 다시 head를 초기화하지 않음. 이건 정말 중요한 실수다.
	for(int i=0; temp_cnt<count; i++){		
		// 홀수를 만났다면 맨 뒤로 노드를 이동
		// 뒤로 이동시키기 전에 temp에 주소를 저장
		// 이미 미자막 노드라면 옮길 필요 없음
		if (node == tail){
			break;
		}

		temp = node->next;

		if((node->item)%2 != 0){
			//현재 자리에서 노드 옮기기
			if (prev == NULL){
				ll->head = temp;
			} else{
				prev->next = temp;
			}

			tail->next =node;
			node->next = NULL;
			tail = node; // 홀수인 노드를 맨 뒤로 이동시켰을 때만 head로 초기화
			temp_cnt++;
		} else{
			prev = node;
		}
		node = temp;
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


ListNode *findNode(LinkedList *ll, int index){

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
