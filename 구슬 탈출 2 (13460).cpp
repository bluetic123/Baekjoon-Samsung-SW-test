#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
int goal_x, goal_y;
bool is_wall[11][11];

int dfs(int r_pos[2], int b_pos[2], int count) {
	if (count > 10) {
		return -1;
	}
	int min_count = 11;
	int nr_pos[2], nb_pos[2];
	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int nx, ny;
	int ret;

	for (int i = 0; i < 4; i++) {
		nr_pos[0] = r_pos[0]; nr_pos[1] = r_pos[1]; nb_pos[0] = b_pos[0]; nb_pos[1] = b_pos[1];
		ret = 0;
		for (int d = 0; d < 10; d++) {
			nx = nr_pos[0] + dx[i]; ny = nr_pos[1] + dy[i];
			if (nx >= 1 && nx < N && ny >= 1 && ny < M && !is_wall[nx][ny] && !(nx == nb_pos[0] && ny == nb_pos[1])) {
				if (nx == goal_x && ny == goal_y) {
					ret = count;
					nr_pos[0] = -1;
					nr_pos[1] = -1;
				}
				nr_pos[0] += dx[i];
				nr_pos[1] += dy[i];
			}
			nx = nb_pos[0] + dx[i]; ny = nb_pos[1] + dy[i];
			if (nx >= 1 && nx < N && ny >= 1 && ny < M && !is_wall[nx][ny] && !(nx == nr_pos[0] && ny == nr_pos[1])) {
				if (nx == goal_x && ny == goal_y) {
					ret = -1;
					break;
				}
				nb_pos[0] += dx[i];
				nb_pos[1] += dy[i];
			}
		}
		if (ret == 0) {
			ret = dfs(nr_pos, nb_pos, count + 1);
		}
		if (ret != -1 && ret < min_count) {
			min_count = ret;
		}
	}
	if (min_count == 11) {
		return -1;
	}
	else {
		return min_count;
	}
}

int main() {
	cin >> N >> M;
	char temp;
	int r_pos[2], b_pos[2];
	int ret;
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			cin >> temp;
			if (temp == '#') {
				is_wall[n][m] = true;
			}
			else {
				is_wall[n][m] = false;
				if (temp == 'R') {
					r_pos[0] = n; r_pos[1] = m;
				}
				else if (temp == 'B') {
					b_pos[0] = n; b_pos[1] = m;
				}
				else if (temp == 'O') {
					goal_x = n; goal_y = m;
				}
			}
		}
	}
	ret = dfs(r_pos, b_pos, 1);
	cout << ret << endl;

	return 0;
}
