#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
vector<int> add(vector<int> A, vector<int> B) {
	vector<int> C;
	int len = max(A.size(), B.size());
	for (int i = 0, t = 0; i < len || t; i++) {
		if (i < A.size()) t += A[i];
		if (i < B.size()) t += B[i];
		C.push_back(t % 10);
		t /= 10;
	}
	return C;
}

int main() {
	string a, b;
	cin >> a >> b;
	vector<int> A, B;
	for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
	for (int j = b.size() - 1; j >= 0; j--) B.push_back(b[j] - '0');

	vector<int> res = add(A, B);
	for (int i = res.size() - 1; i >= 0; i--) cout << res[i];
	cout << endl;

	return 0;
}