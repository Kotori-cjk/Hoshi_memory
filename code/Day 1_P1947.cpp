#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>                         // �ڱ����в����Ǳ����

extern "C" int Seniorious(int);           // ��������Ҫ����һ�ν���������ĺ�����

extern "C" int Chtholly(int n, int OvO) { // ������ʵ�ֽ�����Ҫ����ʵ�ֵĺ�����
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