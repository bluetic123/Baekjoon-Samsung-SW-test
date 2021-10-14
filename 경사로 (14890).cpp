#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, L;
int map[102][102];
int line[102];

bool check_line() {
	int pre, cur;
	bool is_empty[102];
	for (int i = 0; i < N; i++) {
		is_empty[i] = true;
	}
	pre = line[0];
	for (int i = 1; i < N; i++) {
		if (pre > line[i]) {
			cur = line[i];
			if (pre - line[i] != 1) {
				return false;
			}
			for (int l = 0; l < L; l++) {
				if (i + l >= N || !is_empty[i + l] || cur != line[i + l]) {
					return false;
				}
				is_empty[i + l] = false;
			}
		}
		if (pre < line[i]) {
			cur = pre;
			if (line[i] - pre != 1) {
				return false;
			}
			for (int l = 1; l <= L; l++) {
				if (i - l < 0 || !is_empty[i - l] || cur != line[i - l]) {
					return false;
				}
				is_empty[i - l] = false;
			}
		}
		pre = line[i];
	}
	return true;
}

int main() {
	int answer = 0;
	cin >> N >> L;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			line[j] = map[i][j];
		}
		if (check_line()) {
			answer++;
		}
		for (int j = 0; j < N; j++) {
			line[j] = map[j][i];
		}
		if (check_line()) {
			answer++;
		}
	}
	cout << answer << endl;
	return 0;
}
