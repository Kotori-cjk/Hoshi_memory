#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1000010;

int n, m;
int a[N];

int find(int x) {
	int l = 0, r = n - 1;
	while (l < r) {
		int mid = l + r >> 1;
		if (a[mid] >= x) r = mid;
		else l = mid + 1;
	}
	if (a[r] == x) return r + 1;
	else return -1;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);

	while (m--) {
		int x;
		scanf("%d", &x);
		printf("%d ", find(x));
	}
	printf("\n");

	return 0;
}