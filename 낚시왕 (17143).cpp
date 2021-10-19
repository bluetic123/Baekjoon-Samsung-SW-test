#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int R, C, M;
vector<int> shark_info[10002]; // speed, direction, size
int index_map[102][102];
int next_index_map[102][102];

int catch_shark(int cur_c) {
	int size = 0;
	for (int target_r = 0; target_r < R; target_r++) {
		if (index_map[target_r][cur_c] != 0) {
			int idx = index_map[target_r][cur_c];
			index_map[target_r][cur_c] = 0;
			size = shark_info[idx][2];
			break;
		}
	}
	return size;
}

void move_shark() {
	int s, d, z, idx;
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			next_index_map[x][y] = 0;
		}
	}
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			if (index_map[x][y] != 0) {
				idx = index_map[x][y];
				s = shark_info[idx][0];
				d = shark_info[idx][1];
				z = shark_info[idx][2];

				int dx[] = { 0, -1, 1, 0, 0 };
				int dy[] = { 0, 0, 0, 1, -1 };
				int nx = x + dx[d] * s;
				int ny = y + dy[d] * s;

				for (int r = 0; r < 3; r++) {
					if (nx < 0) {
						shark_info[idx][1] = 2;
						nx *= -1;
					}
					else if (nx >= R) {
						shark_info[idx][1] = 1;
						nx = R - (nx - R) - 2;
					}
					else if (ny < 0) {
						shark_info[idx][1] = 3;
						ny *= -1;
					}
					else if (ny >= C) {
						shark_info[idx][1] = 4;
						ny = C - (ny - C) - 2;
					}
				}

				if (next_index_map[nx][ny] == 0 || z > shark_info[next_index_map[nx][ny]][2]) {
					next_index_map[nx][ny] = idx;
				}
			}
		}
	}
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			index_map[x][y] = next_index_map[x][y];
		}
	}
}

int cycle() {
	int total_size = 0;
	for (int cur_c = 0; cur_c < C; cur_c++) {
		total_size += catch_shark(cur_c);
		move_shark();
	}
	return total_size;
}

int main() {
	int answer = 0;
	int r, c, s, d, z;
	cin >> R >> C >> M;

	for (int m = 1; m <= M; m++) {
		cin >> r >> c >> s >> d >> z;
		if (d <= 2) {
			s %= R * 2 - 2;
		}
		else {
			s %= C * 2 - 2;
		}
		shark_info[m].push_back(s);
		shark_info[m].push_back(d);
		shark_info[m].push_back(z);
		index_map[r - 1][c - 1] = m;
	}


	answer = cycle();

	cout << answer << endl;
	return 0;
}
