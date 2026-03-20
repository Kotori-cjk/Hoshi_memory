#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1000010;

int n;
int a[N], tmp[N];

LL merge_count(int a[], int l, int r) {
	if (l >= r) return 0;

	int mid = l + r >> 1;
	LL res = merge_count(a, l, mid) + merge_count(a, mid + 1, r);

	int i = l, j = mid + 1, cnt = 0;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) tmp[cnt++] = a[i++];
		else {
			res += mid - i + 1;
			tmp[cnt++] = a[j++];
		}
	}
	while (i <= mid) tmp[cnt++] = a[i++];
	while (j <= r) tmp[cnt++] = a[j++];

	for (int i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];

	return res;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];

	cout << merge_count(a, 0, n - 1) << endl;
	return 0;
}