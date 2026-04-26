#include <stdio.h>
#include <stdlib.h>

// 節點結構定義
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 佇列結構，front 指向頭節點，rear 指向尾節點
typedef struct {
    Node *front;
    Node *rear;
} Queue;

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

// 初始化佇列
void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

// 判斷是否為空
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// 從尾端加入元素（入隊）
void enqueue(Queue *q, int value) {
    Node *node = createNode(value);
    if (isEmpty(q)) {
        q->front = node;
        q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
    printf("enqueue %d\n", value);
}

// 從前端取出元素（出隊）
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("佇列為空，無法 dequeue\n");
        return -1;
    }
    Node *node = q->front;
    int value = node->data;
    q->front = node->next;
    if (q->front == NULL) {
        q->rear = NULL;  // 取出最後一個元素時，rear 也要清空
    }
    free(node);
    printf("dequeue %d\n", value);
    return value;
}

// 查看前端元素，不取出
int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("佇列為空，無法 peek\n");
        return -1;
    }
    return q->front->data;
}

// 印出佇列內容
void printQueue(Queue *q) {
    printf("佇列內容（前端在左邊）：[ ");
    Node *cur = q->front;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("]\n");
}

// 釋放整個佇列
void freeQueue(Queue *q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}

int main() {
    Queue q;
    initQueue(&q);

    printf("=== Linked List 版佇列 ===\n\n");

    // 1. 入隊
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printQueue(&q);

    // 2. 查看前端
    printf("peek = %d\n", peek(&q));

    // 3. 出隊
    dequeue(&q);
    printQueue(&q);

    // 4. 繼續入隊（Linked List 沒有大小限制）
    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);
    printQueue(&q);

    // 5. 清空佇列
    printf("\n清空佇列：\n");
    freeQueue(&q);

    dequeue(&q);  // 空佇列測試
    return 0;
}
