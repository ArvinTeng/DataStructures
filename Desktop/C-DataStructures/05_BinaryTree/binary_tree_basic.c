#include <stdio.h>
#include <stdlib.h>

// 節點結構定義
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// 建立新節點
Node *createNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("記憶體配置失敗！\n");
        exit(1);
    }
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 插入節點（回傳更新後的根節點）
Node *insert(Node *root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("%d 已存在，不重複插入\n", value);
    }
    return root;
}

// 搜尋節點
Node *search(Node *root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }
    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// 中序遍歷：左 → 根 → 右（結果為升序排列）
void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// 前序遍歷：根 → 左 → 右
void preorder(Node *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// 後序遍歷：左 → 右 → 根
void postorder(Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// 釋放整棵樹（用後序，先釋放子節點再釋放自己）
void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node *root = NULL;

    printf("=== 二元搜尋樹 (BST) 範例 ===\n\n");

    // 1. 插入節點
    //        30
    //       /  \
    //     20    40
    //    /  \     \
    //  10   25    50
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 50);
    root = insert(root, 30);  // 重複測試

    // 2. 三種遍歷
    printf("\n中序遍歷（升序）：");
    inorder(root);
    printf("\n");

    printf("前序遍歷：");
    preorder(root);
    printf("\n");

    printf("後序遍歷：");
    postorder(root);
    printf("\n");

    // 3. 搜尋
    int target = 25;
    Node *found = search(root, target);
    printf("\n搜尋 %d：%s\n", target, found ? "找到了！" : "找不到。");

    target = 99;
    found = search(root, target);
    printf("搜尋 %d：%s\n", target, found ? "找到了！" : "找不到。");

    // 4. 釋放記憶體
    freeTree(root);
    return 0;
}
