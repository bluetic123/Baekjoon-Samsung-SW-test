#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int R, C, T;
int map[52][52];
int up_pos, down_pos;

void diffusion() {
	int diffuse_map[52][52] = { 0, };
	int dif_value;
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			if (map[x][y] > 0) {
				int dx[] = { 1, -1, 0, 0 };
				int dy[] = { 0, 0, 1, -1 };
				int nx, ny;
				dif_value = map[x][y] / 5;
				for (int d = 0; d < 4; d++) {
					nx = x + dx[d]; ny = y + dy[d];
					if (nx >= 0 && nx < R && ny >= 0 && ny < C && map[nx][ny] != -1) {
						diffuse_map[nx][ny] += dif_value;
						map[x][y] -= dif_value;
					}
				}
			}
		}
	}
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			map[x][y] += diffuse_map[x][y];
		}
	}
}

void purifier() {
	for (int x = up_pos - 1; x > 0; x--) {
		map[x][0] = map[x - 1][0];
	}
	for (int x = down_pos + 1; x < R - 1; x++) {
		map[x][0] = map[x + 1][0];
	}

	for (int y = 1; y < C; y++) {
		map[0][y - 1] = map[0][y];
		map[R - 1][y - 1] = map[R - 1][y];
	}

	for (int x = 1; x <= up_pos; x++) {
		map[x - 1][C - 1] = map[x][C - 1];
	}
	for (int x = R - 1; x > down_pos; x--) {
		map[x][C - 1] = map[x - 1][C - 1];
	}

	for (int y = C - 1; y > 1; y--) {
		map[up_pos][y] = map[up_pos][y - 1];
		map[down_pos][y] = map[down_pos][y - 1];
	}
	map[up_pos][1] = 0;
	map[down_pos][1] = 0;
}

int remain_mimun() {
	int sum = 0;
	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			if (map[x][y] > 0) {
				sum += map[x][y];
			}
		}
	}
	return sum;
}

int mimun_cycle(int time) {
	for (int t = 0; t < time; t++) {
		diffusion();
		purifier();
	}
	return remain_mimun();
}

int main() {
	int answer = 0;
	cin >> R >> C >> T;

	for (int x = 0; x < R; x++) {
		for (int y = 0; y < C; y++) {
			cin >> map[x][y];
		}
	}
	for (int x = 0; x < R; x++) {
		if (map[x][0] == -1) {
			up_pos = x;
			down_pos = x + 1;
			break;
		}
	}

	answer = mimun_cycle(T);

	cout << answer << endl;
	return 0;
}
