//
// Created by shea on 8/11/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * KMP 算法永不回退 text 的指针 i，不走回头路（不会重复扫描 text），而是借助 dp 数组中储存的信息把 pattern
 * 移到正确的位置继续匹配，时间复杂度只需 O(N)，用空间换时间，所以我认为它是一种动态规划算法
 * ---------------------
 * 每次匹配失败后pattern移动的距离不一定是 1，某些情况下一次可移动多个位置
 */

void make_next(const char *pattern, int *next) {

    int q, k;
    size_t m = strlen(pattern);

    next[0] = 0;
    for (q = 1, k = 0; q < m; q++) {

        while (k > 0 && pattern[q] != pattern[k])
            k = next[k - 1];

        if (pattern[q] == pattern[k]) {
            k++;
        }

        next[q] = k;

    }

    /**
     * text = ababxbababababcdababcabddcadfdsss
     * pattern = abcabd
     * next      000120
     */

}


int kmp(const char *text, const char *pattern, int *next) {

    size_t n = strlen(text);
    size_t m = strlen(pattern);

    make_next(pattern, next);

    int i, q;
    for (i = 0, q = 0; i < n; i++) {

        while (q > 0 && pattern[q] != text[i]) {
            q = next[q - 1];
        }

        if (pattern[q] == text[i]) {
            q++;
        }

        if (q == m) {
            printf("Pattern occurs with shift: %lu\n", (i-m+1));
            break;
        }
    }

    return i - q + 1;
}

int main() {

    int i;
    int next[20] = {0};

    char *text = "ababxbabcabbfabcdababcabddcadfdsss";
    char *pattern = "abcabdd";

    int idx = kmp(text, pattern, next);
    printf("match pattern : %d\n", idx);

    for (i = 0; i < strlen(pattern); i++) {
        printf("%4d", next[i]);
    }
    printf("\n");

    return 0;

}



