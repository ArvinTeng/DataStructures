#include <stdio.h>
#include <stdlib.h>

// 節點結構定義
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 建立新節點
Node *createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("記憶體配置失敗！\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// 印出鏈結串列
void printList(Node *head) {
    printf("鏈結串列內容：");
    Node *cur = head;
    while (cur != NULL) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// 在串列開頭插入節點
void insertAtHead(Node **head, int value) {
    Node *newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

// 在串列尾端插入節點
void insertAtTail(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newNode;
}

// 刪除第一次出現的指定值節點
void deleteValue(Node **head, int value) {
    if (*head == NULL) {
        printf("串列為空，無法刪除。\n");
        return;
    }
    Node *cur = *head;
    Node *prev = NULL;

    while (cur != NULL && cur->data != value) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("找不到 %d，無法刪除。\n", value);
        return;
    }
    if (prev == NULL) {
        *head = cur->next;
    } else {
        prev->next = cur->next;
    }
    free(cur);
}

// 搜尋節點，回傳指標或 NULL
Node *search(Node *head, int target) {
    Node *cur = head;
    while (cur != NULL) {
        if (cur->data == target) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// 釋放整個串列
void freeList(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
}

int main() {
    Node *head = NULL;

    printf("=== 鏈結串列基本操作 ===\n\n");

    // 1. 插入節點
    insertAtHead(&head, 30);
    insertAtHead(&head, 20);
    insertAtHead(&head, 10);
    printList(head);

    // 2. 在尾端插入節點
    insertAtTail(&head, 40);
    insertAtTail(&head, 50);
    printList(head);

    // 3. 搜尋節點
    int target = 40;
    Node *found = search(head, target);
    if (found != NULL) {
        printf("找到 %d！\n", target);
    } else {
        printf("找不到 %d。\n", target);
    }

    // 4. 刪除節點
    deleteValue(&head, 20);
    printList(head);

    // 5. 釋放記憶體
    freeList(head);
    return 0;
}
