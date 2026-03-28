<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int g[N][N];

void insert(int x1, int y1, int x2, int y2) {
	g[x1][y1]++, g[x1][y2 + 1]--, g[x2 + 1][y1]--, g[x2 + 1][y2 + 1]++;
}

int main() {
	cin >> n >> m;

	while (m--) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		insert(x1, y1, x2, y2);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << g[i][j] << " ";
		cout << "\n";
	}

	return 0;
=======
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int g[N][N];

void insert(int x1, int y1, int x2, int y2) {
	g[x1][y1]++, g[x1][y2 + 1]--, g[x2 + 1][y1]--, g[x2 + 1][y2 + 1]++;
}

int main() {
	cin >> n >> m;

	while (m--) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		insert(x1, y1, x2, y2);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << g[i][j] << " ";
		cout << "\n";
	}

	return 0;
>>>>>>> 65bc4143f58b0cfba1a3fb5fdbf2aed72cbdb8f2
}