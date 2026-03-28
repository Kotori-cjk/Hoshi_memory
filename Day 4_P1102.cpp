#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef long long LL;

LL n, c;
vector<LL> a;
map<LL, LL> cnt;

int main() {
	cin >> n >> c;
	for (int i = 1; i <= n; i++) {
		LL x;
		cin >> x;
		if (cnt[x] == 0) {
			a.push_back(x);
			cnt[x]++;
		}
		else cnt[x]++;
	}
	sort(a.begin(), a.end());
	n = a.size();

	LL ans = 0;
	for (int i = 0, j = 0; i < n; i++) {
		while (j < i && a[i] - a[j] > c) j++;
		if (a[i] - a[j] == c) {
			ans += cnt[a[i]] * cnt[a[j]];
		}
	}

	cout << ans << endl;

	return 0;
}