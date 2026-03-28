#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct BigInt
{
	vector<int> nums;
	bool positive;

	BigInt() { nums.clear(); positive = true; }
	BigInt(string s) {
		for (int i = s.size() - 1; i >= 0; i--) nums.push_back(s[i] - '0');
	}
	BigInt(int n) {
		while (n)
		{
			nums.push_back(n % 10);
			n /= 10;
		}
	}

	friend bool operator>=(const BigInt& A, const BigInt& B) {
		if (A.nums.size() != B.nums.size()) return A.nums.size() > B.nums.size();
		for (int i = A.nums.size() - 1; i >= 0; i--) {
			if (A.nums[i] != B.nums[i]) return A.nums[i] > B.nums[i];
		}
		return true;
	}

	friend BigInt operator+ (const BigInt& A, const BigInt& B) {
		BigInt C;
		int ml = max(A.nums.size(), B.nums.size());
		for (int i = 0, t = 0; i < ml || t; i++) {
			if (i < A.nums.size()) t += A.nums[i];
			if (i < B.nums.size()) t += B.nums[i];
			C.nums.push_back(t % 10);
			t /= 10;
		}
		return C;
	}

	friend BigInt operator- (const BigInt& A, const BigInt& B) {
		BigInt C;
		int t = 0;
		for (int i = 0; i < A.nums.size(); i++) {
			t = A.nums[i] - t;
			if (i < B.nums.size()) t -= B.nums[i];
			C.nums.push_back((t + 10) % 10);
			if (t < 0) t = 1;
			else t = 0;
		}
		while (C.nums.size() > 1 && C.nums.back() == 0) C.nums.pop_back();
		return C;
	}

	friend BigInt operator*(const BigInt& A, const BigInt& B) {
		BigInt C;
		C.nums.resize(A.nums.size() + B.nums.size(), 0);
		for (int i = 0; i < A.nums.size(); i++) {
			for (int j = 0; j < B.nums.size(); j++) {
				// 易错点1：这里是+=而不是=
				C.nums[i + j] += A.nums[i] * B.nums[j];
			}
		}

		for (int i = 0; i < C.nums.size() - 1; i++) {
			C.nums[i + 1] += C.nums[i] / 10;
			C.nums[i] %= 10;
		}

		while (C.nums.size() > 1 && C.nums.back() == 0) C.nums.pop_back();
		return C;
	}

	friend BigInt divide(const BigInt& A, const BigInt& B, BigInt& r) {
		int n = A.nums.size(), m = B.nums.size();
		BigInt C;
		// 易错点2：这里是resize(1,0) 而不是 resize(0),否则不便后续计算
		r.nums.resize(1, 0);
		for (int i = A.nums.size() - 1; i >= 0; i--) {
			r = r * BigInt(10) + BigInt(A.nums[i]);
			// 易错点3：q每轮都要重设为0，防止影响之后的计算
			int q = 0;
			// 关键：这里采用“每次能减就减，然后商的该位+1”的方式处理除数也是大整数的情况
			while (r >= B) {
				r = r - B;
				q++;
			}
			C.nums.push_back(q);
		}

		// 易错点4：由于商是从高位开始存的，所以需要reverse
		reverse(C.nums.begin(), C.nums.end());
		while (C.nums.size() > 1 && C.nums.back() == 0) C.nums.pop_back();
		return C;
	}

	friend ostream& operator<<(ostream& os,const BigInt& num) {
		for (int i = num.nums.size() - 1; i >= 0; i--) os << num.nums[i];
		return os;
	}
};

int main() {
	string a, b;
	cin >> a >> b;
	BigInt A(a), B(b), r;

	cout << A + B << endl;
	if (A >= B) {
		cout << A - B << endl;
	}
	else {
		cout << "-";
		cout << B - A << endl;
	}
	cout << A * B << endl;
	cout << divide(A, B, r) << endl;
	cout << r << endl;

	return 0;
}