//Stack 코드
#include "../header/main.h"
// 스택을 초기화하는 함수
void InitializeStack(Stack *s) {
    s->topNode = NULL;
    s->cnt = 0;
}

// 스택이 비어있는지 확인하는 함수
int IsEmpty(Stack *s) {
    return s->topNode == NULL;
}

// 스택에 요소를 추가하는 함수
void Push(Stack *s, char *name) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(newNode->name, name);
    newNode->nextNode = s->topNode;
    s->topNode = newNode;
    s->cnt++;
}

// 스택에서 요소를 제거하고 그 값을 반환하는 함수
char* Pop(Stack *s) {
    if (IsEmpty(s)) {
        printf("Stack is empty\n");
        return NULL;
    }
    StackNode *tempNode = s->topNode;
    char *name = (char *)malloc(MAX_NAME * sizeof(char));
    strcpy(name, tempNode->name);

    s->topNode = tempNode->nextNode;
    free(tempNode);
    s->cnt--;
    return name;
}