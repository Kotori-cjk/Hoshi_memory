<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> A, vector<int> B) {
	if (A.size() != B.size()) return A.size() > B.size();
	for (int i = A.size() - 1; i >= 0; i--) {
		if (A[i] != B[i]) return A[i] > B[i];
	}
	return true;
}

vector<int> sub(vector<int> A, vector<int> B) {
	vector<int> res;
	int t = 0;
	for (int i = 0; i < A.size() || t; i++) {
		t = A[i] - t;
		if (i < B.size()) t -= B[i];
		res.push_back((t + 10) % 10);
		if (t < 0) t = 1;
		else t = 0;
	}

	while (res.size() > 1 && res.back() == 0) res.pop_back();
	return res;
}

int main() {
	string a, b;
	cin >> a >> b;

	vector<int> A, B;
	A.clear(), B.clear();
	for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
	for (int j = b.size() - 1; j >= 0; j--) B.push_back(b[j] - '0');

	vector<int> res;
	res.clear();
	if (cmp(A, B)) res = sub(A, B);
	else {
		cout << '-';
		res = sub(B, A);
	}

	for (int i = res.size() - 1; i >= 0; i--) cout << res[i];
	cout << endl;

	return 0;
=======
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> A, vector<int> B) {
	if (A.size() != B.size()) return A.size() > B.size();
	for (int i = A.size() - 1; i >= 0; i--) {
		if (A[i] != B[i]) return A[i] > B[i];
	}
	return true;
}

vector<int> sub(vector<int> A, vector<int> B) {
	vector<int> res;
	int t = 0;
	for (int i = 0; i < A.size() || t; i++) {
		t = A[i] - t;
		if (i < B.size()) t -= B[i];
		res.push_back((t + 10) % 10);
		if (t < 0) t = 1;
		else t = 0;
	}

	while (res.size() > 1 && res.back() == 0) res.pop_back();
	return res;
}

int main() {
	string a, b;
	cin >> a >> b;

	vector<int> A, B;
	A.clear(), B.clear();
	for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
	for (int j = b.size() - 1; j >= 0; j--) B.push_back(b[j] - '0');

	vector<int> res;
	res.clear();
	if (cmp(A, B)) res = sub(A, B);
	else {
		cout << '-';
		res = sub(B, A);
	}

	for (int i = res.size() - 1; i >= 0; i--) cout << res[i];
	cout << endl;

	return 0;
>>>>>>> 65bc4143f58b0cfba1a3fb5fdbf2aed72cbdb8f2
}