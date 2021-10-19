#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int R, C, K;
int max_R, max_C;
int A[102][102];
int count_num[102];
vector<int> count_idx_list[102];

void R_sort() {
	int local_max_C, global_max_C = 0;
	for (int r = 0; r < max_R; r++) {
		for (int c = 0; c <= 100; c++) {
			count_num[c] = 0;
			count_idx_list[c].clear();
		}
		for (int c = 0; c < max_C; c++) {
			count_num[A[r][c]]++;
			A[r][c] = 0;
		}
		for (int c = 1; c <= 100; c++) {
			count_idx_list[count_num[c]].push_back(c);
		}
		local_max_C = 0;
		for (int c = 1; c <= max_C; c++) {
			if (count_idx_list[c].size() > 0) {
				sort(count_idx_list[c].begin(), count_idx_list[c].end());
				for (int idx = 0; idx < count_idx_list[c].size(); idx++) {
					A[r][local_max_C++] = count_idx_list[c][idx];
					A[r][local_max_C++] = c;
					if (local_max_C >= 100) {
						local_max_C = 100;
						break;
					}
				}
				if (local_max_C >= 100) {
					local_max_C = 100;
					break;
				}
			}
		}
		if (global_max_C < local_max_C) {
			global_max_C = local_max_C;
		}
	}
	max_C = global_max_C;
}
void C_sort() {
	int local_max_R, global_max_R = 0;
	for (int c = 0; c < max_C; c++) {
		for (int r = 0; r <= 100; r++) {
			count_num[r] = 0;
			count_idx_list[r].clear();
		}
		for (int r = 0; r < max_R; r++) {
			count_num[A[r][c]]++;
			A[r][c] = 0;
		}
		for (int r = 1; r <= 100; r++) {
			count_idx_list[count_num[r]].push_back(r);
		}
		local_max_R = 0;
		for (int r = 1; r <= max_R; r++) {
			if (count_idx_list[r].size() > 0) {
				sort(count_idx_list[r].begin(), count_idx_list[r].end());
				for (int idx = 0; idx < count_idx_list[r].size(); idx++) {
					A[local_max_R++][c] = count_idx_list[r][idx];
					A[local_max_R++][c] = r;
					if (local_max_R >= 100) {
						local_max_R = 100;
						break;
					}
				}
				if (local_max_R >= 100) {
					local_max_R = 100;
					break;
				}
			}
		}
		if (global_max_R < local_max_R) {
			global_max_R = local_max_R;
		}
	}
	max_R = global_max_R;
}

int cycle() {
	for (int cur_time = 0; cur_time <= 100; cur_time++) {
		if (A[R - 1][C - 1] == K) {
			return cur_time;
		}
		if (max_R >= max_C) {
			R_sort();
		}
		else {
			C_sort();
		}
	}
	return -1;
}

int main() {
	int answer = 0;

	cin >> R >> C >> K;

	max_R = 3; max_C = 3;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			cin >> A[x][y];
		}
	}

	answer = cycle();


	cout << answer << endl;
	return 0;
}
