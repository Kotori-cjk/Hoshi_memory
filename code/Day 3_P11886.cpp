#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;

const int N = 1000010;

int n, k, a[N];
int q[N], hh, tt = -1;

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];

	for (int i = 1; i <= n; i++) {
		while (hh <= tt && q[hh] < i - k + 1) hh++;
		while (hh <= tt && a[q[tt]] >= a[i]) tt--;
		q[++tt] = i;
		if (i >= k) cout << a[q[hh]] << " ";
		//q[++tt] = i;
	}
	cout << endl;
	hh = 0, tt = -1;
	for (int i = 1; i <= n; i++) {
		while (hh <= tt && q[hh] < i - k + 1) hh++;
		while (hh <= tt && a[q[tt]] <= a[i]) tt--;
		q[++tt] = i;
		if (i >= k) cout << a[q[hh]] << " ";
	}

	return 0;
}