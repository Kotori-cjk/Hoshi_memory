#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10000010;

int n, a[N], f[N];
int stk[N], tt;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];

	for (int i = n; i >= 1; i--) {
		while (tt > 0 && a[stk[tt]] <= a[i]) tt--;
		if (tt > 0) f[i] = stk[tt];
		stk[++tt] = i;
	}

	for (int i = 1; i <= n; i++) cout << f[i] << " ";
	cout << endl;

	return 0;
}