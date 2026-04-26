#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// 堆疊結構
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 初始化堆疊
void initStack(Stack *s) {
    s->top = -1;
}

// 判斷是否為空
int isEmpty(Stack *s) {
    return s->top == -1;
}

// 判斷是否已滿
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// 推入元素
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("堆疊已滿，無法 push %d\n", value);
        return;
    }
    s->data[++s->top] = value;
    printf("push %d\n", value);
}

// 彈出元素
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("堆疊為空，無法 pop\n");
        return -1;
    }
    int value = s->data[s->top--];
    printf("pop %d\n", value);
    return value;
}

// 取得堆疊頂端元素
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("堆疊為空，無法 peek\n");
        return -1;
    }
    return s->data[s->top];
}

// 印出堆疊內容
void printStack(Stack *s) {
    printf("堆疊內容（頂端在右邊）：[ ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->data[i]);
    }
    printf("]\n");
}

int main() {
    Stack stack;
    initStack(&stack);

    printf("=== 堆疊 (Stack) 範例 ===\n\n");

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    printStack(&stack);

    printf("peek = %d\n", peek(&stack));

    pop(&stack);
    printStack(&stack);

    push(&stack, 40);
    push(&stack, 50);
    push(&stack, 60); // 這次會超過容量
    printStack(&stack);

    while (!isEmpty(&stack)) {
        pop(&stack);
    }

    pop(&stack); // 空堆疊
    return 0;
}
