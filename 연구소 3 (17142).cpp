#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M;
int max_count;
int map[52][52];
int temp_map[52][52];
vector<int> virus_xpos, virus_ypos;
bool selected[12];

int diffuse_time() {
	queue<int> xpos, ypos;
	int used_time = 0;
	int x, y;

	if (max_count <= 0) {
		return 0;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp_map[i][j] = map[i][j];
		}
	}

	for (int idx = 0; idx < virus_xpos.size(); idx++) {
		if (selected[idx]) {
			xpos.push(virus_xpos[idx]);
			ypos.push(virus_ypos[idx]);
			temp_map[virus_xpos[idx]][virus_ypos[idx]] = 1;
		}
	}

	xpos.push(-1);
	ypos.push(-1);

	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int nx, ny;
	int cur_count = 0;

	while (!xpos.empty()) {
		x = xpos.front(); xpos.pop();
		y = ypos.front(); ypos.pop();
		if (x == -1 && y == -1) {
			if (xpos.empty()) {
				break;
			}
			used_time++;

			if (cur_count >= max_count) {
				break;
			}
			xpos.push(-1);
			ypos.push(-1);
			continue;
		}
		for (int d = 0; d < 4; d++) {
			nx = x + dx[d];
			ny = y + dy[d];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N && temp_map[nx][ny] != 1) {
				if (temp_map[nx][ny] == 0) {
					cur_count++;
				}
				temp_map[nx][ny] = 1;
				xpos.push(nx);
				ypos.push(ny);
			}
		}
	}
	if (cur_count < max_count) {
		return -1;
	}
	return used_time;
}

int select_virus(int select_num, int pre_idx) {
	int ret, min = 1000000;
	if (select_num >= M) {
		return diffuse_time();
	}
	for (int idx = pre_idx + 1; idx < virus_xpos.size(); idx++) {
		selected[idx] = true;
		ret = select_virus(select_num + 1, idx);
		selected[idx] = false;
		if (ret != -1 && ret < min) {
			min = ret;
		}
	}
	if (min > 100000) {
		min = -1;
	}
	return min;
}

int main() {
	int answer = 0;
	int x, y;

	cin >> N >> M;

	max_count = 0;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cin >> map[x][y];
			if (map[x][y] == 2) {
				virus_xpos.push_back(x);
				virus_ypos.push_back(y);
			}
			if (map[x][y] == 0) {
				max_count++;
			}
		}
	}

	answer = select_virus(0, -1);


	cout << answer << endl;
	return 0;
}

