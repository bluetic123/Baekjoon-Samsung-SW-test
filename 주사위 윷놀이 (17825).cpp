#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int marker_info[5][2];
int line[4][22] = { { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 },
	{ 0, 13, 16, 19, 25, 30, 35, 40 },
	{ 0, 22, 24, 25, 30, 35, 40 },
	{ 0, 28, 27, 26, 25, 30, 35, 40 } };
int cube_num[11];
int marker_order[11];
int line_max_idx[] = { 20, 7, 6, 7 };

int game_result() {
	int score = 0;
	int m_idx, line_num, line_idx;
	for (int idx = 0; idx < 4; idx++) {
		marker_info[idx][0] = 0;
		marker_info[idx][1] = 0;
	}
	for (int t = 0; t < 10; t++) {
		m_idx = marker_order[t];
		marker_info[m_idx][1] += cube_num[t];
		// overlap check
		for (int other_idx = 0; other_idx < 4; other_idx++) {
			if (other_idx == m_idx) {
				continue;
			}
			if (marker_info[m_idx][1] <= line_max_idx[marker_info[m_idx][0]] &&
				marker_info[m_idx][0] == marker_info[other_idx][0] &&
				marker_info[m_idx][1] == marker_info[other_idx][1]) {
				return 0;
			}
			else if (marker_info[m_idx][0] == 0 && marker_info[m_idx][1] == 5 &&
				marker_info[other_idx][0] == 1 && marker_info[other_idx][1] == 0) {
				return 0;
			}
			else if (marker_info[m_idx][0] == 0 && marker_info[m_idx][1] == 10 &&
				marker_info[other_idx][0] == 2 && marker_info[other_idx][1] == 0) {
				return 0;
			}
			else if (marker_info[m_idx][0] == 0 && marker_info[m_idx][1] == 15 &&
				marker_info[other_idx][0] == 3 && marker_info[other_idx][1] == 0) {
				return 0;
			}
			else if (marker_info[m_idx][1] <= 20 && marker_info[other_idx][1] <= 20 &&
				line[marker_info[m_idx][0]][marker_info[m_idx][1]] == 25 &&
				line[marker_info[other_idx][0]][marker_info[other_idx][1]] == 25) {
				return 0;
			}
			else if (marker_info[m_idx][1] <= 20 && marker_info[other_idx][1] <= 20 &&
				line[marker_info[m_idx][0]][marker_info[m_idx][1]] == 30 &&
				line[marker_info[other_idx][0]][marker_info[other_idx][1]] == 30 &&
				marker_info[m_idx][0] != 0 && marker_info[other_idx][0] != 0) {
				return 0;
			}
			else if (marker_info[m_idx][1] <= 20 && marker_info[other_idx][1] <= 20 &&
				line[marker_info[m_idx][0]][marker_info[m_idx][1]] == 35 &&
				line[marker_info[other_idx][0]][marker_info[other_idx][1]] == 35) {
				return 0;
			}
			else if (marker_info[m_idx][1] <= 20 && marker_info[other_idx][1] <= 20 &&
				line[marker_info[m_idx][0]][marker_info[m_idx][1]] == 40 &&
				line[marker_info[other_idx][0]][marker_info[other_idx][1]] == 40) {
				return 0;
			}
		}
		line_num = marker_info[m_idx][0];
		line_idx = marker_info[m_idx][1];
		if (line_idx <= line_max_idx[line_num]) {
			score += line[line_num][line_idx];
			if (line_num == 0) {
				if (line_idx == 5) {
					marker_info[m_idx][0] = 1;
					marker_info[m_idx][1] = 0;
				}
				else if (line_idx == 10) {
					marker_info[m_idx][0] = 2;
					marker_info[m_idx][1] = 0;
				}
				else if (line_idx == 15) {
					marker_info[m_idx][0] = 3;
					marker_info[m_idx][1] = 0;
				}
			}
		}
	}

	return score;
}

int dfs_select(int order) {
	int local_max = 0, ret;
	if (order >= 10) {
		ret = game_result();
		return ret;
	}
	for (int idx = 0; idx < 4; idx++) {
		marker_order[order] = idx;
		ret = dfs_select(order + 1);
		if (ret > local_max) {
			local_max = ret;
		}
	}
	return local_max;
}

int main() {
	int answer = 0;

	for (int i = 0; i < 10; i++) {
		cin >> cube_num[i];
	}
	answer = dfs_select(0);

	cout << answer << endl;
	return 0;
}

