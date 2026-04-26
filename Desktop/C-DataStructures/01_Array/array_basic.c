#include <stdio.h>

// =============================
//  陣列 (Array) 基礎操作範例
// =============================
// 陣列是一組相同型別的資料，儲存在連續的記憶體位置
// 優點：可用索引直接存取，速度快 O(1)
// 缺點：大小固定，插入/刪除需要搬移元素 O(n)

#define SIZE 5  // 定義陣列大小

// 函式宣告
void printArray(int arr[], int size);
void insertElement(int arr[], int *size, int maxSize, int index, int value);
void deleteElement(int arr[], int *size, int index);
int searchElement(int arr[], int size, int target);

int main() {
    int arr[10] = {10, 20, 30, 40, 50};  // 初始化陣列 (預留空間供插入用)
    int size = SIZE;                       // 目前有效元素數量

    printf("=== 陣列基礎操作 ===\n\n");

    // 1. 印出陣列
    printf("【初始陣列】\n");
    printArray(arr, size);

    // 2. 存取元素（用索引）
    printf("\n【存取元素】\n");
    printf("arr[0] = %d\n", arr[0]);  // 第一個元素
    printf("arr[2] = %d\n", arr[2]);  // 第三個元素
    printf("arr[4] = %d\n", arr[4]);  // 最後一個元素

    // 3. 修改元素
    printf("\n【修改元素】arr[2] 改成 99\n");
    arr[2] = 99;
    printArray(arr, size);

    // 4. 插入元素（在 index=1 的位置插入 55）
    printf("\n【插入元素】在 index=1 插入 55\n");
    insertElement(arr, &size, 10, 1, 55);
    printArray(arr, size);

    // 5. 刪除元素（刪除 index=3 的元素）
    printf("\n【刪除元素】刪除 index=3 的元素\n");
    deleteElement(arr, &size, 3);
    printArray(arr, size);

    // 6. 搜尋元素
    printf("\n【搜尋元素】尋找 40\n");
    int pos = searchElement(arr, size, 40);
    if (pos != -1)
        printf("找到了！40 在 index = %d\n", pos);
    else
        printf("找不到 40\n");

    return 0;
}

// 印出整個陣列
void printArray(int arr[], int size) {
    printf("陣列內容：[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]  (共 %d 個元素)\n", size);
}

// 在指定位置插入元素
// 原理：把 index 之後的元素往後搬，再把新值放進去
void insertElement(int arr[], int *size, int maxSize, int index, int value) {
    if (*size >= maxSize) {
        printf("陣列已滿，無法插入！\n");
        return;
    }
    if (index < 0 || index > *size) {
        printf("索引超出範圍！\n");
        return;
    }
    // 從最後一個元素開始往後移
    for (int i = *size; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    (*size)++;
}

// 刪除指定位置的元素
// 原理：把 index 之後的元素往前搬，覆蓋掉被刪的元素
void deleteElement(int arr[], int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("索引超出範圍！\n");
        return;
    }
    for (int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
}

// 線性搜尋（從頭到尾找）
// 時間複雜度：O(n)
int searchElement(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target)
            return i;  // 回傳找到的索引
    }
    return -1;  // 找不到回傳 -1
}
