//
// Created by shea on 8/1/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_ARRAY_LENGTH        13

/**
 * 希尔排序
 */
int shell_sort(int *data, int length) {

    int gap = 0;
    int i = 0, j = 0;
    int temp;

    for (gap = length / 2; gap >= 1; gap /= 2) {    //跨度不断缩小

        for (i = gap; i < length; i++) {

            temp = data[i];
            for (j = i - gap; j >= 0 && temp < data[j]; j = j - gap) {  //依次比较

                data[j + gap] = data[j];

            }
            data[j + gap] = temp;
        }

    }

    return 0;
}


void merge(int *data, int *temp, int start, int middle, int end) {

    int i = start, j = middle + 1, k = start;

    while (i <= middle && j <= end) {
        if (data[i] > data[j]) {    //temp存小的
            temp[k++] = data[j++];
        } else {
            temp[k++] = data[i++];
        }
    }

    //接着存没遍历完的一方(i或j)
    while (i <= middle) {
        temp[k++] = data[i++];
    }
    while (j <= end) {
        temp[k++] = data[j++];
    }

    for (i = start; i <= end; i++) {
        data[i] = temp[i];
    }
}

/**
 * 归并排序
 */
int merge_sort(int *data, int *temp, int start, int end) {

    int middle = 0;

    if (start < end) {
        middle = start + (end - start) / 2; //middle >= start

        //左边调用自己独立排序
        merge_sort(data, temp, start, middle);
        //右边调用自己独立排序
        merge_sort(data, temp, middle + 1, end);
        //递归最深层是 middle - start = 0; end - middle = 1
        merge(data, temp, start, middle, end);
    }

    return 0;
}


void sort(int *data, int left, int right) {

    if (left >= right) return;  //限制递归最深返回条件

    int i = left;
    int j = right;
    int key = data[left];

    while (i < j) {

        while (i < j && key <= data[j]) {
            j--;
        }
        data[i] = data[j];

        while (i < j && key >= data[i]) {
            i++;
        }
        data[j] = data[i];
    }

    data[i] = key;
    //最左侧数字放入i 排好序

    sort(data, left, i - 1);
    sort(data, i + 1, right);

}

/**
 * 快速排序
 */
int quick_sort(int *data, int length) {

    sort(data, 0, length - 1);
    return 0;
}

void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}
void max_heapify(int arr[], int start, int end) {
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) {    //若子节点指标在范围内才做比较
        if (son + 1 <= end && arr[son] < arr[son + 1])  //先比较两个子节点大小，选择最大的
            son++;
        if (arr[dad] > arr[son])    //如果父节点大于子节点代表调整完毕，直接跳出函数
            return;
        else {  //否则交换父子内容再继续子节点和孙节点比较
            swap(&arr[dad], &arr[son]);
            //向下一分支找
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

/**
 * 堆排序
 */
void heap_sort(int arr[], int len) {
    int i;
    //初始化，i从最后一个父节点开始调整
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    //先将第一个元素和已排好元素前一位做交换，再重新调整，直到排序完毕
    for (i = len - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}

int main() {

    int data[DATA_ARRAY_LENGTH] = {23, 64, 24, 12, 9, 16, 53, 57, 71, 79, 87, 97, 1};
    int i = 0;

#if 0
    shell_sort(data, DATA_ARRAY_LENGTH);

#elif 0

    int temp[DATA_ARRAY_LENGTH] = {0};

    merge_sort(data, temp, 0, DATA_ARRAY_LENGTH-1);

#elif 1
    heap_sort(data, DATA_ARRAY_LENGTH);

#else

    quick_sort(data, DATA_ARRAY_LENGTH);

#endif

    for (i = 0; i < DATA_ARRAY_LENGTH; i++) {
        printf("%4d", data[i]);
    }
    printf("\n");

}


