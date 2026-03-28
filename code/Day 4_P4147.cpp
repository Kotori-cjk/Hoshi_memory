#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
char g[N][N];
int stk[N], tt;
int h[N];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> g[i][j];
		}
	}

	int res = 0;
	for (int r = 1; r <= n; r++) {
		tt = 0;
		for (int c = 1; c <= m; c++) {
			if (g[r][c] == 'F') h[c]++;
			else h[c] = 0;
		}

		for (int i = 1; i <= m + 1; i++) {
			while (tt > 0 && h[stk[tt]] > h[i]) {
				int mid = stk[tt--];
				res = max(res, h[mid] * (i - stk[tt] - 1));
			}
			stk[++tt] = i;
		}
	}

	cout << res * 3 << endl;

	return 0;
}