#include <stdio.h>
#include <stdlib.h>

// 節點結構定義
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 堆疊結構，top 指向鏈結串列的頭節點
typedef struct {
    Node *top;
} Stack;

// 建立新節點
Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("記憶體配置失敗！\n");
        exit(1);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

// 初始化堆疊
void initStack(Stack *s) {
    s->top = NULL;
}

// 判斷是否為空
int isEmpty(Stack *s) {
    return s->top == NULL;
}

// push 新節點到串列頭
void push(Stack *s, int value) {
    Node *node = createNode(value);
    node->next = s->top;
    s->top = node;
    printf("push %d\n", value);
}

// pop 並回傳頂端元素
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("堆疊為空，無法 pop\n");
        return -1;
    }
    Node *node = s->top;
    int value = node->data;
    s->top = node->next;
    free(node);
    printf("pop %d\n", value);
    return value;
}

// 取得頂端元素但不移除
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("堆疊為空，無法 peek\n");
        return -1;
    }
    return s->top->data;
}

// 印出堆疊內容
void printStack(Stack *s) {
    printf("堆疊內容（頂端在左邊）：[ ");
    Node *cur = s->top;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("]\n");
}

// 釋放整個堆疊
void freeStack(Stack *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

int main() {
    Stack stack;
    initStack(&stack);

    printf("=== Linked List 版堆疊 ===\n\n");

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    printStack(&stack);

    printf("peek = %d\n", peek(&stack));

    pop(&stack);
    printStack(&stack);

    push(&stack, 40);
    printStack(&stack);

    freeStack(&stack);
    return 0;
}
