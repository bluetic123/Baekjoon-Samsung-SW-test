#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N;
int A[20];
int op_num[5]; // 덧셈, 뺄셈, 곱셈, 나누셈
int max_result = -1000000000, min_result = 1000000000;

void dfs(int pre, int idx) {
	int cur;
	if (idx >= N) {
		if (max_result < pre) {
			max_result = pre;
		}
		if (min_result > pre) {
			min_result = pre;
		}
		return;
	}
	for (int op = 0; op < 4; op++) {
		if (op_num[op] > 0) {
			op_num[op]--;
			if (op == 0) {
				cur = pre + A[idx];
			}
			else if (op == 1) {
				cur = pre - A[idx];
			}
			else if (op == 2) {
				cur = pre * A[idx];
			}
			else {
				cur = pre / A[idx];
			}
			dfs(cur, idx + 1);
			op_num[op]++;
		}
	}
}

int main() {
	cin >> N;
	for (int n = 0; n < N; n++) {
		cin >> A[n];
	}
	for (int op = 0; op < 4; op++) {
		cin >> op_num[op];
	}
	dfs(A[0], 1);

	cout << max_result << endl;
	cout << min_result << endl;

	return 0;
}
