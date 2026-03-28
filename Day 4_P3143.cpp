#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000010;

int n, c;
int a[N], lenv[N], best[N];

int main() {
	cin >> n >> c;
	for (int i = 1; i <= n; i++) cin >> a[i];

	sort(a + 1, a + 1 + n);

	for (int i = 1, j = 1; i <= n; i++) {
		while (j + 1 <= n && a[j + 1] - a[i] <= c) j++;
		lenv[i] = j - i + 1;
	}

	best[n + 1] = 0;
	for (int i = n; i >= 1; i--) {
		best[i] = max(best[i + 1], lenv[i]);
	}

	int res = 0;
	for (int i = 1; i <= n; i++) {
		int end = i + lenv[i] - 1;
		res = max(res, lenv[i] + best[end + 1]);
	}

	cout << res << endl;

	return 0;
}