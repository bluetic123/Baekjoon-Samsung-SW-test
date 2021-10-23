#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, K;
int cur_m;
int smell_map[22][22];
int smell_shark[22][22];
int map[22][22];
int shark_current_direction[402];
int direction_priority[402][5][5]; // shark index, current direction, priority

int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, -1, 1 };
int nx, ny, nd;

int cycle() {
	int next_map[22][22];
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			smell_map[x][y] = 0;
		}
	}
	for (int cur_time = 1; cur_time <= 1000; cur_time++) {
		// smell
		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {
				smell_map[x][y]--;
				next_map[x][y] = 0;
				if (map[x][y] > 0) {
					smell_shark[x][y] = map[x][y];
					smell_map[x][y] = K;
				}
			}
		}

		//move
		int shark_idx, shark_d;
		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {
				if (map[x][y] == 0) {
					continue;
				}
				shark_idx = map[x][y];
				shark_d = shark_current_direction[shark_idx];

				bool finded = false;
				// find empty space
				for (int p = 1; p <= 4; p++) {
					nd = direction_priority[shark_idx][shark_d][p];
					nx = x + dx[nd];
					ny = y + dy[nd];
					if (nx >= 0 && nx < N && ny >= 0 && ny < N && smell_map[nx][ny] <= 0) {
						if (next_map[nx][ny] <= 0 || next_map[nx][ny] > shark_idx) {
							next_map[nx][ny] = shark_idx;
						}
						finded = true;
						shark_current_direction[shark_idx] = nd;
						break;
					}
				}

				// fine my smell space
				if (!finded) {
					for (int p = 1; p <= 4; p++) {
						nd = direction_priority[shark_idx][shark_d][p];
						nx = x + dx[nd];
						ny = y + dy[nd];

						if (nx >= 0 && nx < N && ny >= 0 && ny < N && smell_shark[nx][ny] == shark_idx) {
							if (next_map[nx][ny] <= 0 || next_map[nx][ny] > shark_idx) {
								next_map[nx][ny] = shark_idx;
							}
							finded = true;
							shark_current_direction[shark_idx] = nd;
							break;
						}
					}
				}

			}
		}


		// check the number of sharks
		cur_m = 0;
		for (int x = 0; x < N; x++) {
			for (int y = 0; y < N; y++) {
				map[x][y] = next_map[x][y];
				if (map[x][y] > 0) {
					cur_m++;
				}
			}
		}

		if (cur_m <= 1) {
			return cur_time;
		}
	}
	return -1;
}

int main() {
	int answer = 0;

	cin >> N >> M >> K;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cin >> map[x][y];
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> shark_current_direction[i];
	}
	for (int i = 1; i <= M; i++) {
		for (int cur_d = 1; cur_d <= 4; cur_d++) {
			for (int p = 1; p <= 4; p++) {
				cin >> direction_priority[i][cur_d][p];
			}
		}
	}

	answer = cycle();

	cout << answer << endl;
	return 0;
}

