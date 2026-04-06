#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*CompareFunc)(const void *, const void *);

int compareInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compareFloat(const void *a, const void *b) {
    float diff = (*(float*)a - *(float*)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

int compareString(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);
}

void sort(void *array, size_t n, size_t size, CompareFunc compare) {
    qsort(array, n, size, compare);
}

void processFile(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (!fin) {
        printf("错误: 无法打开文件 %s\n", filename);
        return;
    }

    int choice, n;
    if (fscanf(fin, "%d", &choice) != 1 || fscanf(fin, "%d", &n) != 1) {
        printf("错误: 文件 %s 格式不正确\n", filename);
        fclose(fin);
        return;
    }

    if (n > 20) n = 20;  // 最多支持20个元素

    printf("=== 处理数据来自: %s ===\n", filename);

    switch (choice) {
        // TODO: 在这里添加你的代码
        case 1:
        int *arr1 = (int *)malloc(n * sizeof(int));
        for(int i=0;i<n;i++) fscanf(fin, "%d", arr1+i);
        sort((void *)arr1, n, sizeof(int), compareInt);
        for(int i=0;i<n;i++) {
            if(i<n-1) printf("%d ", arr1[i]);
            else printf("%d\n", arr1[i]);
        }
        break;
    case 2:
        float *arr2 = (float *)malloc(n * sizeof(float));
        for(int i=0;i<n;i++) fscanf(fin, "%f", arr2+i);
        sort((void *)arr2, n, sizeof(float), compareFloat);
        for(int i=0;i<n;i++) {
            if(i<n-1) printf("%f ", arr2[i]);
            else printf("%f\n", arr2[i]);
        }
        break;
    }

    fclose(fin);
}

int main() {
    processFile("int_sort.txt");
    processFile("float_sort.txt");

    return 0;
}