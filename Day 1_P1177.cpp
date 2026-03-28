<<<<<<< HEAD
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;
int a[N];

// 快排
//void my_quicksort(int a[], int l, int r) {
//	if (l >= r) return;
//
//	int i = l - 1, j = r + 1;
//	int x = a[l + r >> 1];
//	while (i < j) {
//		do i++; while (a[i] < x);
//		do j--; while (a[j] > x);
//		if (i < j) swap(a[i], a[j]);
//	}
//
//	my_quicksort(a, l, j);
//	my_quicksort(a, j + 1, r);
//}
//
//int main() {
//	cin >> n;
//	for (int i = 0; i < n; i++) cin >> a[i];
//
//	my_quicksort(a, 0, n - 1);
//
//	for (int i = 0; i < n; i++) cout << a[i] << " ";
//	cout << endl;
//
//	return 0;
//}

// 归并
int tmp[N];
void merge_sort(int a[], int l, int r) {
	if (l >= r) return;

	int mid = l + r >> 1;
	merge_sort(a, l, mid), merge_sort(a, mid + 1, r);

	int i = l, j = mid + 1, cnt = 0;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) tmp[cnt++] = a[i++];
		else tmp[cnt++] = a[j++];
	}

	while (i <= mid) tmp[cnt++] = a[i++];
	while (j <= r) tmp[cnt++] = a[j++];

	for (int i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];

	merge_sort(a, 0, n - 1);

	for (int i = 0; i < n; i++) cout << a[i] << " ";
	cout << endl;

	return 0;
=======
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;

int n;
int a[N];

// 快排
//void my_quicksort(int a[], int l, int r) {
//	if (l >= r) return;
//
//	int i = l - 1, j = r + 1;
//	int x = a[l + r >> 1];
//	while (i < j) {
//		do i++; while (a[i] < x);
//		do j--; while (a[j] > x);
//		if (i < j) swap(a[i], a[j]);
//	}
//
//	my_quicksort(a, l, j);
//	my_quicksort(a, j + 1, r);
//}
//
//int main() {
//	cin >> n;
//	for (int i = 0; i < n; i++) cin >> a[i];
//
//	my_quicksort(a, 0, n - 1);
//
//	for (int i = 0; i < n; i++) cout << a[i] << " ";
//	cout << endl;
//
//	return 0;
//}

// 归并
int tmp[N];
void merge_sort(int a[], int l, int r) {
	if (l >= r) return;

	int mid = l + r >> 1;
	merge_sort(a, l, mid), merge_sort(a, mid + 1, r);

	int i = l, j = mid + 1, cnt = 0;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) tmp[cnt++] = a[i++];
		else tmp[cnt++] = a[j++];
	}

	while (i <= mid) tmp[cnt++] = a[i++];
	while (j <= r) tmp[cnt++] = a[j++];

	for (int i = l, j = 0; i <= r; i++, j++) a[i] = tmp[j];
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];

	merge_sort(a, 0, n - 1);

	for (int i = 0; i < n; i++) cout << a[i] << " ";
	cout << endl;

	return 0;
>>>>>>> 65bc4143f58b0cfba1a3fb5fdbf2aed72cbdb8f2
}