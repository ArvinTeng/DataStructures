#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7  // bucket 數量，選質數可以讓分佈更均勻

// 鏈結串列節點
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 雜湊表結構
typedef struct {
    Node *buckets[TABLE_SIZE];  // 每個 bucket 是一條 Linked List 的頭
} HashTable;

// 雜湊函式：把 key 對應到 bucket 索引
int hash(int key) {
    return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;  // +TABLE_SIZE 處理負數 key
}

// 初始化雜湊表
void initTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
}

// 插入元素
void insert(HashTable *ht, int value) {
    int index = hash(value);

    // 檢查是否已存在
    Node *cur = ht->buckets[index];
    while (cur != NULL) {
        if (cur->data == value) {
            printf("%d 已存在，不重複插入\n", value);
            return;
        }
        cur = cur->next;
    }

    // 插入到 bucket 的鏈結串列開頭（最快）
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("記憶體配置失敗！\n");
        exit(1);
    }
    node->data = value;
    node->next = ht->buckets[index];
    ht->buckets[index] = node;
    printf("insert %d → bucket[%d]\n", value, index);
}

// 搜尋元素
int search(HashTable *ht, int value) {
    int index = hash(value);
    Node *cur = ht->buckets[index];
    while (cur != NULL) {
        if (cur->data == value) return 1;
        cur = cur->next;
    }
    return 0;
}

// 刪除元素
void delete(HashTable *ht, int value) {
    int index = hash(value);
    Node *cur = ht->buckets[index];
    Node *prev = NULL;

    while (cur != NULL) {
        if (cur->data == value) {
            if (prev == NULL) {
                ht->buckets[index] = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            printf("delete %d（從 bucket[%d] 移除）\n", value, index);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("找不到 %d，無法刪除\n", value);
}

// 印出整個雜湊表
void printTable(HashTable *ht) {
    printf("\n雜湊表內容：\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("  bucket[%d] → ", i);
        Node *cur = ht->buckets[i];
        if (cur == NULL) {
            printf("(空)");
        }
        while (cur != NULL) {
            printf("[%d] → ", cur->data);
            cur = cur->next;
        }
        printf("NULL\n");
    }
}

// 釋放整個雜湊表
void freeTable(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *cur = ht->buckets[i];
        while (cur != NULL) {
            Node *next = cur->next;
            free(cur);
            cur = next;
        }
        ht->buckets[i] = NULL;
    }
}

int main() {
    HashTable ht;
    initTable(&ht);

    printf("=== 雜湊表 (Hash Table) 範例 ===\n");
    printf("TABLE_SIZE = %d，hash(key) = key %% %d\n\n", TABLE_SIZE, TABLE_SIZE);

    // 1. 插入元素
    insert(&ht, 10);
    insert(&ht, 20);
    insert(&ht, 42);
    insert(&ht, 15);
    insert(&ht, 49);  // 49 % 7 = 0，與 42 碰撞
    insert(&ht, 7);   //  7 % 7 = 0，與 42、49 碰撞
    insert(&ht, 3);
    insert(&ht, 42);  // 重複測試
    printTable(&ht);

    // 2. 搜尋
    printf("\n搜尋 15：%s\n", search(&ht, 15) ? "找到了！" : "找不到。");
    printf("搜尋 99：%s\n", search(&ht, 99) ? "找到了！" : "找不到。");

    // 3. 刪除
    printf("\n");
    delete(&ht, 49);
    delete(&ht, 99);  // 不存在的值
    printTable(&ht);

    // 4. 釋放記憶體
    freeTable(&ht);
    return 0;
}
