#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
int map[10][10];
vector<vector<int>> cctv_pos;

int zero_space() {
	int count = 0;
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			if (map[n][m] == 0) {
				count++;
			}
		}
	}
	return count;
}
void direction_setting(int xpos, int ypos, int d, bool is_plus) {
	if (d == 1) {
		if (is_plus) {
			for (int i = 1; xpos + i < N; i++) {
				if (map[xpos + i][ypos] == 6) {
					break;
				}
				if (map[xpos + i][ypos] == 0 || map[xpos + i][ypos] >= 10) {
					map[xpos + i][ypos] += 10;
				}
			}
		}
		else {
			for (int i = 1; xpos + i < N; i++) {
				if (map[xpos + i][ypos] == 6) {
					break;
				}
				if (map[xpos + i][ypos] >= 10) {
					map[xpos + i][ypos] -= 10;
				}
			}
		}
	}
	else if (d == 2) {
		if (is_plus) {
			for (int i = 1; xpos - i >= 0; i++) {
				if (map[xpos - i][ypos] == 6) {
					break;
				}
				if (map[xpos - i][ypos] == 0 || map[xpos - i][ypos] >= 10) {
					map[xpos - i][ypos] += 10;
				}
			}
		}
		else {
			for (int i = 1; xpos - i >= 0; i++) {
				if (map[xpos - i][ypos] == 6) {
					break;
				}
				if (map[xpos - i][ypos] >= 10) {
					map[xpos - i][ypos] -= 10;
				}
			}
		}
	}
	else if (d == 3) {
		if (is_plus) {
			for (int i = 1; ypos + i < M; i++) {
				if (map[xpos][ypos + i] == 6) {
					break;
				}
				if (map[xpos][ypos + i] == 0 || map[xpos][ypos + i] >= 10) {
					map[xpos][ypos + i] += 10;
				}
			}
		}
		else {
			for (int i = 1; ypos + i < M; i++) {
				if (map[xpos][ypos + i] == 6) {
					break;
				}
				if (map[xpos][ypos + i] >= 10) {
					map[xpos][ypos + i] -= 10;
				}
			}
		}
	}
	else {
		if (is_plus) {
			for (int i = 1; ypos - i >= 0; i++) {
				if (map[xpos][ypos - i] == 6) {
					break;
				}
				if (map[xpos][ypos - i] == 0 || map[xpos][ypos - i] >= 10) {
					map[xpos][ypos - i] += 10;
				}
			}
		}
		else {
			for (int i = 1; ypos - i >= 0; i++) {
				if (map[xpos][ypos - i] == 6) {
					break;
				}
				if (map[xpos][ypos - i] >= 10) {
					map[xpos][ypos - i] -= 10;
				}
			}
		}
	}
}

int cctv_test(int cctv_num) {
	if (cctv_num >= cctv_pos.size()) {
		return zero_space();
	}
	int xpos = cctv_pos[cctv_num][0], ypos = cctv_pos[cctv_num][1];
	int ret, min_zero = 100;
	int type = map[xpos][ypos];

	if (type == 1) {
		direction_setting(xpos, ypos, 1, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 1, false);

		direction_setting(xpos, ypos, 2, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 2, false);

		direction_setting(xpos, ypos, 3, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 3, false);

		direction_setting(xpos, ypos, 4, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 4, false);
	}
	else if (type == 2) {
		direction_setting(xpos, ypos, 1, true);
		direction_setting(xpos, ypos, 2, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 1, false);
		direction_setting(xpos, ypos, 2, false);

		direction_setting(xpos, ypos, 3, true);
		direction_setting(xpos, ypos, 4, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 3, false);
		direction_setting(xpos, ypos, 4, false);
	}
	else if (type == 3) {
		direction_setting(xpos, ypos, 1, true);
		direction_setting(xpos, ypos, 3, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 3, false);
		direction_setting(xpos, ypos, 4, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 1, false);
		direction_setting(xpos, ypos, 2, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 4, false);
		direction_setting(xpos, ypos, 3, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 2, false);
		direction_setting(xpos, ypos, 3, false);
	}
	else if (type == 4) {
		direction_setting(xpos, ypos, 1, true);
		direction_setting(xpos, ypos, 3, true);
		direction_setting(xpos, ypos, 4, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 3, false);
		direction_setting(xpos, ypos, 2, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 1, false);
		direction_setting(xpos, ypos, 3, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 4, false);
		direction_setting(xpos, ypos, 1, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 1, false);
		direction_setting(xpos, ypos, 2, false);
		direction_setting(xpos, ypos, 3, false);
	}
	else {
		direction_setting(xpos, ypos, 1, true);
		direction_setting(xpos, ypos, 2, true);
		direction_setting(xpos, ypos, 3, true);
		direction_setting(xpos, ypos, 4, true);
		ret = cctv_test(cctv_num + 1);
		if (ret < min_zero) {
			min_zero = ret;
		}
		direction_setting(xpos, ypos, 1, false);
		direction_setting(xpos, ypos, 2, false);
		direction_setting(xpos, ypos, 3, false);
		direction_setting(xpos, ypos, 4, false);
	}

	return min_zero;
}

int main() {
	int answer = 0;
	vector<int> pos;

	cin >> N >> M;

	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			cin >> map[n][m];
			if (map[n][m] > 0 && map[n][m] < 6) {
				pos.clear(); pos.push_back(n); pos.push_back(m);
				cctv_pos.push_back(pos);
			}
		}
	}
	answer = cctv_test(0);

	cout << answer << endl;
	return 0;
}
