#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 10000010;

int n, m, a[N];
int q[N], hh, tt = -1;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d",&a[i]);

	printf("0\n");
	for (int i = 2; i <= n; i++) {
		while (hh <= tt && q[hh] < i - m) hh++;
		while (hh <= tt && a[q[tt]] >= a[i - 1]) tt--;
		q[++tt] = i - 1;
		printf("%d\n", a[q[hh]]);
	}
	printf("\n");
	return 0;
}