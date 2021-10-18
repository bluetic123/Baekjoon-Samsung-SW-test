#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M, H;
bool is_line[12][32];

bool is_i_to_i() {
	int cur_n, cur_h;
	for (int i = 1; i <= N; i++) {
		cur_n = i; cur_h = 1;
		while (cur_h <= H) {
			if (is_line[cur_n][cur_h]) {
				cur_n++;
			}
			else if (is_line[cur_n - 1][cur_h]) {
				cur_n--;
			}
			cur_h++;
		}
		if (cur_n != i) {
			return false;
		}
	}
	return true;
}

int brute_force(int cur, int pre_n, int pre_h) {
	int ret, min_answer = 4;
	if (cur > 3) {
		return -1;
	}
	if (is_i_to_i()) {
		return cur;
	}
	for (int h = pre_h + 1; h <= H; h++) {
		if (!is_line[pre_n][h] && !is_line[pre_n + 1][h] && !is_line[pre_n - 1][h]) {
			is_line[pre_n][h] = true;
			ret = brute_force(cur + 1, pre_n, h);
			is_line[pre_n][h] = false;
			if (ret != -1 && min_answer > ret) {
				min_answer = ret;
			}
		}
	}
	for (int n = pre_n + 1; n <= N; n++) {
		for (int h = 1; h <= H; h++) {
			if (!is_line[n][h] && !is_line[n + 1][h] && !is_line[n - 1][h]) {
				is_line[n][h] = true;
				ret = brute_force(cur + 1, n, h);
				is_line[n][h] = false;
				if (ret != -1 && min_answer > ret) {
					min_answer = ret;
				}
			}
		}
	}
	if (min_answer == 4) {
		return -1;
	}
	return min_answer;
}

int main() {
	int answer = 0;
	int a, b;

	cin >> N >> M >> H;

	for (int n = 0; n <= N; n++) {
		for (int h = 1; h <= H; h++) {
			is_line[n][h] = false;
		}
	}
	for (int m = 0; m < M; m++) {
		cin >> a >> b;
		is_line[b][a] = true;
	}
	answer = brute_force(0, 1, 0);

	cout << answer << endl;
	return 0;
}
