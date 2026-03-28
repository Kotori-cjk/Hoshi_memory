#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 2000010;

LL n, a[N];
LL q[N], hh, tt = -1;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i + n] = a[i];
	}
	for (int i = 1; i <= 2 * n; i++) a[i] += a[i - 1];

	LL ans = 0;
	for (int i = 1; i < 2 * n; i++) {
		while (hh <= tt && q[hh] < i - n + 1) hh++;
		while (hh <= tt && a[q[tt]] >= a[i]) tt--;
		q[++tt] = i;
		if (i >= n) {
			if (a[q[hh]] - a[i - n] >= 0) {
				ans++;
			}
		}
	}

	cout << ans << endl;

	return 0;
}