<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 125;

int n;
int g[N][N], sum[N], f[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> g[i][j];

	int max_val = -1e9;
	for (int top = 1; top <= n; top++) {
		memset(sum, 0, sizeof sum);
		for (int bottom = top; bottom <= n; bottom++) {
			int cur = 0;
			for (int i = 1; i <= n; i++) {
				sum[i] += g[bottom][i];
			}
			for (int i = 1; i <= n; i++) {
				cur = max(cur + sum[i], sum[i]);
				max_val = max(max_val, cur);
			}
		}
	}

	cout << max_val << endl;

	return 0;
=======
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 125;

int n;
int g[N][N], sum[N], f[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> g[i][j];

	int max_val = -1e9;
	for (int top = 1; top <= n; top++) {
		memset(sum, 0, sizeof sum);
		for (int bottom = top; bottom <= n; bottom++) {
			int cur = 0;
			for (int i = 1; i <= n; i++) {
				sum[i] += g[bottom][i];
			}
			for (int i = 1; i <= n; i++) {
				cur = max(cur + sum[i], sum[i]);
				max_val = max(max_val, cur);
			}
		}
	}

	cout << max_val << endl;

	return 0;
>>>>>>> 65bc4143f58b0cfba1a3fb5fdbf2aed72cbdb8f2
}