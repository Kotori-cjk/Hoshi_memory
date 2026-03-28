#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long LL;

vector<LL> divide(vector<LL> A, LL B, LL& r) {
	vector<LL> C;
	r = 0;
	for (int i = A.size() - 1; i >= 0; i--) {
		r = r * 10 + A[i];
		C.push_back(r / B);
		r = r % B;
	}
	reverse(C.begin(), C.end());
	while (C.size() > 1 && C.back() == 0) C.pop_back();
	return C;
}

int main() {
	string a;
	LL B, r;
	vector<LL> A;
	cin >> a >> B;
	for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');

	vector<LL> C = divide(A, B, r);
	for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
	cout << endl;

	return 0;
}