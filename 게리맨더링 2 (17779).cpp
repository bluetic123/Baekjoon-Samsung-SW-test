#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int map[22][22];

int brute_force() {
	int min_dif = 1000000000;
	int local_min, local_max, cur_sum;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			for (int d1 = 1; x + d1 < N && y - d1 >= 0; d1++) {
				for (int d2 = 1; x + d1 + d2 < N && y + d2 < N; d2++) {
					local_min = 100000000; local_max = 0;
					bool checked[22][22] = { 0, };
					/// 1
					cur_sum = 0;
					for (int r = 0; r < x + d1; r++) {
						for (int c = 0; c <= y; c++) {
							if (r + c >= x + y) {
								break;
							}
							cur_sum += map[r][c];
							checked[r][c] = true;
						}
					}
					if (cur_sum < local_min) {
						local_min = cur_sum;
					}
					if (cur_sum > local_max) {
						local_max = cur_sum;
					}
					/// 2
					cur_sum = 0;
					for (int r = 0; r <= x + d2; r++) {
						for (int c = y + 1; c < N; c++) {
							if (c == y + 1 && r > x) {
								c += r - x;
							}
							cur_sum += map[r][c];
							checked[r][c] = true;
						}
					}
					if (cur_sum < local_min) {
						local_min = cur_sum;
					}
					if (cur_sum > local_max) {
						local_max = cur_sum;
					}
					/// 3
					cur_sum = 0;
					int temp_d1 = d1;
					int temp_d2 = d2;
					for (int r = x + d1; r < N; r++) {
						for (int c = 0; c < y - temp_d1; c++) {
							cur_sum += map[r][c];
							checked[r][c] = true;
						}
						if (temp_d2 > 0) {
							temp_d1--; temp_d2--;
						}
					}
					if (cur_sum < local_min) {
						local_min = cur_sum;
					}
					if (cur_sum > local_max) {
						local_max = cur_sum;
					}
					/// 4
					cur_sum = 0;
					temp_d1 = d1;
					temp_d2 = d2;
					for (int r = x + d2 + 1; r < N; r++) {
						for (int c = y + temp_d2; c < N; c++) {
							cur_sum += map[r][c];
							checked[r][c] = true;
						}
						if (temp_d1 > 0) {
							temp_d1--; temp_d2--;
						}
					}
					if (cur_sum < local_min) {
						local_min = cur_sum;
					}
					if (cur_sum > local_max) {
						local_max = cur_sum;
					}
					// 5
					cur_sum = 0;
					for (int r = 0; r < N; r++) {
						for (int c = 0; c < N; c++) {
							if (!checked[r][c]) {
								cur_sum += map[r][c];
							}
						}
					}
					if (cur_sum < local_min) {
						local_min = cur_sum;
					}
					if (cur_sum > local_max) {
						local_max = cur_sum;
					}

					if (min_dif > local_max - local_min) {
						min_dif = local_max - local_min;
					}
				}
			}
		}
	}
	return min_dif;
}


int main() {
	int answer = 0;

	cin >> N;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cin >> map[x][y];
		}
	}

	answer = brute_force();

	cout << answer << endl;
	return 0;
}

