#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct home { // 단순 연결 리스트의 노드 구조를 구조체로 정의
	int index;
	char city[10];
	int post;
	struct home *link;
}home_t;

typedef struct Stack {
	home_t* top;
}Stack;

void InitStack(Stack *stack) { //스택 초기화
	stack->top = NULL;

}
int IsEmpty(Stack *stack) { //스택이 비었는지 확인
	return stack->top == NULL;
}
void Push(Stack *stack, home_t* p) {//스택에 보관
	home_t *now = (home_t *)malloc(sizeof(home_t)); //노드 생성
	now->index = p->index;//데이터 설정
	strcpy(now->city, p->city);
	now->post = p->post;
	now->link = stack->top;//now의 link링크를 현재 top으로 설정   
	stack->top = now;   //스택의 맨 앞은 now로 설정
}
int Pop(Stack *stack) {//스택에서 꺼냄
	home_t *now;
	int re;

	if (IsEmpty(stack)){
		return 0;
	}
	now = stack->top;//now를 top으로 설정
	re = now->index;//꺼낼 값은 now의 index로 설정

	stack->top = now->link;//top을 now의 link로 설정
	free(now);//필요없으니 메모리 해제
	return re;
}

typedef struct Queue {//Queue 구조체 정의
	home_t *front; //맨 앞
	home_t *rear; //맨 뒤
	int count;//보관 개수
}Queue;

void InitQueue(Queue *queue){
	queue->front = queue->rear = NULL; //front와 rear를 NULL로 설정
	queue->count = 0;//보관 개수를 0
}

int IsEmpty(Queue *queue){
	return queue->count == 0;    // 빈 상태
}

void Enqueue(Queue *queue, home_t* p){
	home_t *now = (home_t *)malloc(sizeof(home_t)); //노드 생성
	now->index = p->index;//데이터 설정
	strcpy(now->city, p->city);
	now->post = p->post;
	now->link = NULL;

	if (IsEmpty(queue)) {//큐가 비어있을 때
		queue->front = now;//맨 앞을 now로 설정       
	}
	else {//비어있지 않을 때
		queue->rear->link = now;//맨 뒤의 다음을 now로 설정
	}
	queue->rear = now;//맨 뒤를 now로 설정   
	queue->count++;//보관 개수를 1 증가
}

int Dequeue(Queue *queue){
	int re = 0;
	home_t *now;
	if (IsEmpty(queue)){//큐가 비었을 때
		return re;
	}
	now = queue->front;//맨 앞의 노드를 now에 기억
	re = now->index;//반환할 값은 now의 인덱스로 설정
	queue->front = now->link;//맨 앞은 now의 다음 노드로 설정
	free(now);//now 소멸
	queue->count--;//보관 개수를 1 감소
	return re;
}

typedef struct { // 리스트의 시작을 나타내는 head 노드를 구조체로 정의
	home_t* head;
} linkedList_h;

linkedList_h* createLinkedList_h(void) {// 공백 연결 리스트를 생성하는 연산
	linkedList_h* L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h));
	L->head = NULL;// 공백 리스트이므로 NULL로 설정
	return L;
}

void freeLinkedList_h(linkedList_h* L) {// 연결 리스트의 전체 메모리를 해제하는 연산
	home_t* p;
	while (L->head != NULL) {
		p = L->head;
		L->head = L->head->link;
		free(p);
		p = NULL;
	}
}

void printList(linkedList_h* L) {// 연결 리스트를 순서대로 출력하는 연산
	home_t* p;
	printf("L = (");
	p = L->head; 
	while (p != NULL) { //출력 모든 원소 다하도록 바꿈
		printf("인덱스 : %d, 도시 : %s, 우편번호 : %d", p->index,p->city,p->post);
		p = p->link;
		if (p != NULL) printf(" -> ");
	}
	printf(") \n");
}

void insertFirstNode(linkedList_h *L, home_t *src) {// 첫 번째 노드로 삽입하는 연산
	home_t* newNode;
	newNode = (home_t*)malloc(sizeof(home_t));// 삽입할 새 노드 할당
	strcpy(newNode->city, src->city);           // 값지정
	newNode->index = src->index;
	newNode->post = src->post;

	newNode->link = L->head; // 링크 연결
	L->head = newNode;
}

void insertMiddleNode(linkedList_h* L, home_t *pre, home_t *src) {// 노드를 pre 뒤에 삽입하는 연산
	home_t* newNode;
	newNode = (home_t*)malloc(sizeof(home_t));// 삽입할 새 노드 할당
	strcpy(newNode->city, src->city);           // 값지정
	newNode->index = src->index;
	newNode->post = src->post;

	if (L == NULL) {// 공백 리스트인 경우
		newNode->link = NULL;// 새 노드를 첫 번째이자 마지막 노드로 연결
		L->head = newNode;
	}
	else if (pre == NULL) {// 삽입 위치를 지정하는 포인터 pre가 NULL인 경우
		L->head = newNode;// 새 노드를 첫 번째 노드로 삽입
	}
	else {
		newNode->link = pre->link;// 포인터 pre의 노드 뒤에 새 노드 연결
		pre->link = newNode;
	}
}
 
void insertLastNode(linkedList_h* L, home_t *src) {// 마지막 노드로 삽입하는 연산
	home_t* newNode, *temp;
	newNode = (home_t*)malloc(sizeof(home_t));// 삽입할 새 노드 할당
	strcpy(newNode->city, src->city);           // 값지정
	newNode->index = src->index;
	newNode->post = src->post;

	newNode->link = NULL;
	if (L->head == NULL) {// 현재 리스트가 공백인 경우
		L->head = newNode;// 새 노드를 리스트의 시작 노드로 연결
		return;
	}
	// 현재 리스트가 공백이 아닌 경우
	temp = L->head;
	while (temp->link != NULL) temp = temp->link;// 현재 리스트의 마지막 노드를 찾음
	temp->link = newNode;// 새 노드를 마지막 노드(temp)의 다음 노드로 연결 
}

void deleteNode(linkedList_h* L, home_t* p) {// 리스트에서 노드 p를 삭제하는 연산
	home_t* pre;// 삭제할 노드의 선행자 노드를 나타낼 포인터
	if (L->head == NULL) return;// 공백 리스트라면 삭제 연산 중단
	if (L->head->link == NULL) {    // 리스트에 노드가 한 개만 있는 경우
		free(L->head);// 첫 번째 노드를 메모리에서 해제하고
		L->head = NULL;// 리스트 시작 포인터를 NULL로 설정
		return;
	}
	else if (p == NULL)
		return;// 삭제할 노드가 없다면 삭제 연산 중단
	else if (L->head == p) { // 맨 앞 노드를 삭제하는 경우.
		L->head = p->link;
		free(p);
	}
	else {// 삭제할 노드 p의 선행자 노드를 포인터 pre를 이용해 찾음
		pre = L->head;
		while (pre->link != p) {
			pre = pre->link;
		}
		pre->link = p->link;// 삭제할 노드 p의 선행자 노드와 다음 노드를 연결
		free(p);// 삭제 노드의 메모리 해제
	}
}

home_t* searchNode(linkedList_h* L, int index) {// 리스트에서 x 노드를 탐색하는 연산
	home_t *temp;
	temp = L->head;
	while (temp != NULL) {
		if (temp->index == index) return temp;
		else temp = temp->link;
	}
	return temp;
}

int searchNodeIdx(linkedList_h* L, int index) {
	home_t *temp;
	int idx = 0;
	temp = L->head;
	while (temp != NULL) {
		idx++;
		if (temp->index == index) return idx;
		else temp = temp->link;
	}
	return -1;
}

int main() {
	linkedList_h* L;
	home_t *p;
	int choice;
	L = createLinkedList_h();// 공백 리스트 생성
	Stack stack;
	InitStack(&stack); //스택 초기화
	Queue queue;
	InitQueue(&queue); //큐 초기화

	while (1) {
		printf("다음 중 어떤 Operation을 수행하겠습니까? \n");
		printf("1. home 추가    2. home 삭제     3. home 검색     4. 스택     5.큐     6.프로그램 종료 >> ");
		scanf("%d", &choice);

		if (choice == 1) {
			int choice2;

			p = (home_t*)malloc(sizeof(home_t));// 삽입할 새 노드 할당
			printf("home 정보를 인덱스, 도시, 우편번호(숫자만)으로 입력하세요.(각 정보는 빈칸으로 구분) \n>> ");
			scanf("%d %s %d", &p->index, &p->city, &p->post);
			printf("home 정보를 어디에 추가 하시겠습니까? \n");
			printf("1. 맨앞    2. 맨뒤    3 특정 인덱스 뒤에 >> ");
			scanf("%d", &choice2);
			if (choice2 == 1)
				insertFirstNode(L, p);
			else if (choice2 == 2)
				insertLastNode(L, p);
			else if (choice2 == 3) {
				int index = 0;
				home_t *pre;

				printf("다음 home 정보에서 찾아서 입력하세요 \n");
				printList(L);
				printf(">> ");
				scanf("%d", &index);

				pre = searchNode(L, index);

				if (pre != NULL)
					insertMiddleNode(L, pre, p);
				else
					insertFirstNode(L, p);
			}printf("\n");
		}
		else if (choice == 2) {
			int index = 0;

			printf("다음 home 정보에서 삭제할 인덱스를 찾아서 입력하세요 \n");
			printList(L);
			printf(">> ");
			scanf("%d", &index);

			p = searchNode(L, index);

			if (p != NULL)
				deleteNode(L, p);
			else
				printf("요청하신 인덱스를 찾을 수 없습니다. \n");
			printf("\n");
		}
		else if (choice == 3) {
			int index = 0;

			printf("다음 home 정보에서 검색할 인덱스를 찾아서 입력하세요 \n");
			printList(L);
			printf(">> ");
			scanf("%d", &index);

			int idx = searchNodeIdx(L, index);

			if (idx == -1)
				printf("검색요청하신 인덱스를 찾을 수 없습니다. \n");
			else
				printf("검색요청하신 인덱스는 전체 리스트의 %d번째 있습니다.  \n", idx);
			printf("\n");
		}
		else if (choice == 4) {
			int choice2;
			printf("1. push()    2. pop() >> ");
			scanf("%d", &choice2);
			if (choice2 == 1) {
				p = (home_t*)malloc(sizeof(home_t));
				printf("Push : home 정보를 인덱스, 도시, 우편번호(숫자만)으로 입력하세요.(각 정보는 빈칸으로 구분) \n>> ");
				scanf("%d %s %d", &p->index, &p->city, &p->post);
				Push(&stack, p);
			}
			else if (choice2 == 2) {
				if(!IsEmpty(&stack))
					printf("인덱스 %d : pop() 완료\n", Pop(&stack));//스택에서 꺼내온 값 출력
			}printf("\n");
		}
		else if (choice == 5) {
			int choice2;
			printf("1. Enqueue()    2. Dequeue >> ");
			scanf("%d", &choice2);
			if (choice2 == 1) {
				p = (home_t*)malloc(sizeof(home_t));
				printf("Enqueue : home 정보를 인덱스, 도시, 우편번호(숫자만)으로 입력하세요.(각 정보는 빈칸으로 구분) \n>> ");
				scanf("%d %s %d", &p->index, &p->city, &p->post);
				Enqueue(&queue, p);
			}
			else if (choice2 == 2) {
				if (!IsEmpty(&queue))
					printf("인덱스 %d : Dequeue() 완료\n", Dequeue(&queue));//스택에서 꺼내온 값 출력
			}printf("\n");
		}
		else if (choice == 6)
			break;
	}
	getchar();

	return 0;
}
