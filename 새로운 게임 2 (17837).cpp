#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, K;
vector<int> K_info[12]; // xpos, ypos, direction
int map_color[15][15];
vector<int> map_index[15][15];

int board_game() {
	int dx[] = { 0, 0, 0, -1, 1 };
	int dy[] = { 0, 1, -1, 0, 0 };
	int nx, ny;

	for (int cur_time = 1; cur_time <= 1000; cur_time++) {
		for (int k_idx = 0; k_idx < K; k_idx++) {

			int x = K_info[k_idx][0], y = K_info[k_idx][1], d = K_info[k_idx][2];
			nx = x + dx[d]; ny = y + dy[d];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N && map_color[nx][ny] != 2) {
				vector<int> move_set;
				int check_point = 0;
				for (int m_idx = 0; m_idx < map_index[x][y].size(); m_idx++) {
					if (map_index[x][y][m_idx] == k_idx) {
						check_point = m_idx;
						break;
					}
				}
				for (int m_idx = check_point; m_idx < map_index[x][y].size(); m_idx++) {
					move_set.push_back(map_index[x][y][m_idx]);
				}
				map_index[x][y].erase(map_index[x][y].begin() + check_point, map_index[x][y].end());
				if (map_color[nx][ny] == 1) {
					vector<int> reverse_ms;
					for (int ms_idx = move_set.size() - 1; ms_idx >= 0; ms_idx--) {
						reverse_ms.push_back(move_set[ms_idx]);
					}
					move_set = reverse_ms;
				}
				for (int ms_idx = 0; ms_idx < move_set.size(); ms_idx++) {
					map_index[nx][ny].push_back(move_set[ms_idx]);
					K_info[move_set[ms_idx]][0] = nx; K_info[move_set[ms_idx]][1] = ny;
				}
				if (map_index[nx][ny].size() >= 4) {
					return cur_time;
				}
			}
			else {
				if (d % 2 == 1) {
					d++;
				}
				else {
					d--;
				}
				K_info[k_idx][2] = d;
				nx = x + dx[d]; ny = y + dy[d];
				if (nx >= 0 && nx < N && ny >= 0 && ny < N && map_color[nx][ny] != 2) {
					k_idx--;
				}
			}
		}
	}
	return -1;
}

int main() {
	int answer = 0;
	int x, y, d;

	cin >> N >> K;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cin >> map_color[x][y];
		}
	}
	for (int k = 0; k < K; k++) {
		cin >> x >> y >> d; x--; y--;
		K_info[k].push_back(x); K_info[k].push_back(y); K_info[k].push_back(d);
		map_index[x][y].push_back(k);
	}

	answer = board_game();

	cout << answer << endl;
	return 0;
}

