<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int N = 1000010;

int n, m, bx, by, min_len = 1e9;
int a[N];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];

	map<int, int> cnt;
	int total_num = 0;
	for (int i = 1, j = 1; i <= n; i++) {
		cnt[a[i]]++;
		if (cnt[a[i]] == 1) total_num++;

		if (total_num == m) {
			while (j <= i && cnt[a[j]] > 1) {
				cnt[a[j]]--;
				j++;
			}
			if (i - j + 1 < min_len) {
				min_len = i - j + 1;
				bx = j, by = i;
			}
		}
	}

	cout << bx << " " << by << endl;

	return 0;
=======
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int N = 1000010;

int n, m, bx, by, min_len = 1e9;
int a[N];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];

	map<int, int> cnt;
	int total_num = 0;
	for (int i = 1, j = 1; i <= n; i++) {
		cnt[a[i]]++;
		if (cnt[a[i]] == 1) total_num++;

		if (total_num == m) {
			while (j <= i && cnt[a[j]] > 1) {
				cnt[a[j]]--;
				j++;
			}
			if (i - j + 1 < min_len) {
				min_len = i - j + 1;
				bx = j, by = i;
			}
		}
	}

	cout << bx << " " << by << endl;

	return 0;
>>>>>>> 65bc4143f58b0cfba1a3fb5fdbf2aed72cbdb8f2
}