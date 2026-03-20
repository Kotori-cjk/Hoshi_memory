#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>                         // 在本题中并不是必须的

extern "C" int Seniorious(int);           // 在这里需要声明一次交互库给出的函数。

extern "C" int Chtholly(int n, int OvO) { // 在这里实现交互库要求你实现的函数。
    int l = 1, r = n;
    while (l < r) {
        int mid = l + r >> 1;
        int tmp = Seniorious(mid);
        if (tmp == 1) r = mid - 1;
        else if (tmp == -1) l = mid + 1;
        else return mid;
    }
    return r;
}