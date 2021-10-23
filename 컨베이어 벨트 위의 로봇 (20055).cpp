#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, K;
int A[202];
bool is_exist[102];

int cycle() {
	int zero_count = 0;
	for (int i = 0; i < N; i++) {
		is_exist[i] = false;
	}
	int level = 0;
	while (++level) {
		// rotate
		for (int i = N - 1; i > 0; i--) {
			is_exist[i] = is_exist[i - 1];
		}
		is_exist[N - 1] = false; is_exist[0] = false;
		int temp = A[N * 2 - 1];
		for (int i = 2 * N - 1; i > 0; i--) {
			A[i] = A[i - 1];
		}
		A[0] = temp;

		// move
		for (int i = N - 2; i >= 0; i--) {
			if (is_exist[i] && !is_exist[i + 1] && A[i + 1] > 0) {
				is_exist[i] = false;
				is_exist[i + 1] = true;
				if (--A[i + 1] <= 0) {
					zero_count++;
				}
			}
		}
		if (A[0] > 0) {
			is_exist[0] = true;
			if (--A[0] <= 0) {
				zero_count++;
			}
		}

		if (zero_count >= K) {
			return level;
		}
	}
	return level;
}

int main() {
	int answer = 0;
	int x, y;

	cin >> N >> K;

	for (int i = 0; i < 2 * N; i++) {
		cin >> A[i];
	}

	answer = cycle();

	cout << answer << endl;
	return 0;
}

