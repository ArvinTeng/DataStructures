#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// 佇列結構（使用環狀陣列）
typedef struct {
    int data[MAX_SIZE];
    int front;  // 指向第一個元素
    int rear;   // 指向最後一個元素的下一個位置
    int count;  // 目前元素數量
} Queue;

// 初始化佇列
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// 判斷是否為空
int isEmpty(Queue *q) {
    return q->count == 0;
}

// 判斷是否已滿
int isFull(Queue *q) {
    return q->count == MAX_SIZE;
}

// 從尾端加入元素（入隊）
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("佇列已滿，無法 enqueue %d\n", value);
        return;
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_SIZE;  // 環狀移動
    q->count++;
    printf("enqueue %d\n", value);
}

// 從前端取出元素（出隊）
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("佇列為空，無法 dequeue\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;  // 環狀移動
    q->count--;
    printf("dequeue %d\n", value);
    return value;
}

// 查看前端元素，不取出
int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("佇列為空，無法 peek\n");
        return -1;
    }
    return q->data[q->front];
}

// 印出佇列內容
void printQueue(Queue *q) {
    printf("佇列內容（前端在左邊）：[ ");
    for (int i = 0; i < q->count; i++) {
        printf("%d ", q->data[(q->front + i) % MAX_SIZE]);
    }
    printf("]\n");
}

int main() {
    Queue q;
    initQueue(&q);

    printf("=== 佇列 (Queue) 範例 ===\n\n");

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

    // 4. 繼續入隊（測試環狀陣列效果）
    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);
    enqueue(&q, 70);  // 這次會超過容量
    printQueue(&q);

    // 5. 清空佇列
    printf("\n清空佇列：\n");
    while (!isEmpty(&q)) {
        dequeue(&q);
    }

    dequeue(&q);  // 空佇列測試
    return 0;
}
