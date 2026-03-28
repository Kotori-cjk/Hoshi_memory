<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> mul(vector<int> A, vector<int> B) {
	vector<int> C;
	C.resize(A.size() + B.size(), 0);
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			C[i + j] += A[i] * B[j];
		}
	}

	for (int i = 0; i < C.size() - 1; i++) {
		C[i + 1] += C[i] / 10;
		C[i] %= 10;
	}

	while (C.size() > 1 && C.back() == 0) C.pop_back();

	return C;
}

int main() {
	string a, b;
	cin >> a >> b;
	vector<int> A, B, C;
	for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
	for (int j = b.size() - 1; j >= 0; j--) B.push_back(b[j] - '0');

	C = mul(A, B);
	for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
	cout << endl;

	return 0;
=======
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> mul(vector<int> A, vector<int> B) {
	vector<int> C;
	C.resize(A.size() + B.size(), 0);
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			C[i + j] += A[i] * B[j];
		}
	}

	for (int i = 0; i < C.size() - 1; i++) {
		C[i + 1] += C[i] / 10;
		C[i] %= 10;
	}

	while (C.size() > 1 && C.back() == 0) C.pop_back();

	return C;
}

int main() {
	string a, b;
	cin >> a >> b;
	vector<int> A, B, C;
	for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
	for (int j = b.size() - 1; j >= 0; j--) B.push_back(b[j] - '0');

	C = mul(A, B);
	for (int i = C.size() - 1; i >= 0; i--) cout << C[i];
	cout << endl;

	return 0;
>>>>>>> 65bc4143f58b0cfba1a3fb5fdbf2aed72cbdb8f2
}