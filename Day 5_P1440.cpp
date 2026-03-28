#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2000010;

int n, m;
int a[N];
int q[N], hh, tt = -1;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];

	printf("0\n");
	for (int i = 2; i <= n; i++) {
		while (hh <= tt && q[hh] < i - m) hh++;
		while (hh <= tt && a[q[tt]] >= a[i - 1]) tt--;
		q[++tt] = i - 1;
		printf("%d\n", a[q[hh]]);
	}

	return 0;
}