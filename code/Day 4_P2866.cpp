#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1000010;

LL n, a[N];
LL stk[N], tt;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];

	LL res = 0;
	for (int i = n; i >= 1; i--) {
		while (tt > 0 && a[stk[tt]] < a[i]) tt--;
		if (tt > 0) {
			res += stk[tt] - i - 1;
		}
		else res += n - i;
		stk[++tt] = i;
	}

	cout << res << endl;

	return 0;
}