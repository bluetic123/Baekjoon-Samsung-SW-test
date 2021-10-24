#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int N, Q;
int L[1002];

int map[100][100];
int temp_map[100][100];
int len;
bool visited[100][100];

void fire_storm(int level) {
	int b_len = 1;
	for (int l = 0; l < level; l++) {
		b_len *= 2;
	}
	for (int x = 0; x < len; x += b_len) {
		for (int y = 0; y < len; y += b_len) {
			for (int i = 0; i < b_len; i++) {
				for (int j = 0; j < b_len; j++) {
					temp_map[x + j][y + b_len - 1 - i] = map[x + i][y + j];
				}
			}
			for (int i = 0; i < b_len; i++) {
				for (int j = 0; j < b_len; j++) {
					map[x + i][y + j] = temp_map[x + i][y + j];
				}
			}
		}
	}
}

void ice_check() {
	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int adj_x, adj_y, adj_ice;
	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			adj_ice = 0;
			for (int d = 0; d < 4; d++) {
				adj_x = x + dx[d];
				adj_y = y + dy[d];
				if (adj_x >= 0 && adj_x < len && adj_y >= 0 && adj_y < len && map[adj_x][adj_y] > 0) {
					adj_ice++;
				}
			}
			if (adj_ice < 3 && map[x][y] > 0) {
				temp_map[x][y] = map[x][y] - 1;
			}
			else {
				temp_map[x][y] = map[x][y];
			}
		}
	}

	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			map[x][y] = temp_map[x][y];
		}
	}
}

int dfs(int x, int y) {
	visited[x][y] = true;

	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int nx, ny, sum = 1;
	for (int d = 0; d < 4; d++) {
		nx = x + dx[d];
		ny = y + dy[d];
		if (nx >= 0 && nx < len && ny >= 0 && ny < len && map[nx][ny] > 0 && !visited[nx][ny]) {
			sum += dfs(nx, ny);
		}
	}
	return sum;
}

int max_ice_block_check() {
	int max_block = 0, ret;

	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			visited[x][y] = false;
		}
	}
	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			if (map[x][y] > 0 && !visited[x][y]) {
				ret = dfs(x, y);
				if (ret > max_block) {
					max_block = ret;
				}
			}
		}
	}
	return max_block;
}

int total_ice_check() {
	int sum = 0;
	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			if (map[x][y] > 0) {
				sum += map[x][y];
			}
		}
	}
	return sum;
}

void cycle() {
	int total_ice = 0, max_ice_block = 0;;
	for (int q = 0; q < Q; q++) {
		fire_storm(L[q]);
		ice_check();
	}
	total_ice = total_ice_check();
	max_ice_block = max_ice_block_check();

	cout << total_ice << endl;
	cout << max_ice_block << endl;
}

int main() {

	cin >> N >> Q;

	len = 1;
	for (int l = 0; l < N; l++) {
		len *= 2;
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < Q; i++) {
		cin >> L[i];
	}

	cycle();

	return 0;
}
