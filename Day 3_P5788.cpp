#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10000010;

int stk[N], tt;
int n, a[N], f[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];

	for (int i = n; i >= 1; i--) {
		while (a[stk[tt]] <= a[i] && tt > 0) tt--;
		if (tt <= 0) f[i] = 0;
		else f[i] = stk[tt];
		stk[++tt] = i;
	}

	for (int i = 1; i <= n; i++) cout << f[i] << " ";

	return 0;
}