#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int shark_size, s_xpos, s_ypos, eat_count;
int map[22][22];
int visited_dist[22][22];
int min_x, min_y, min_dist;


bool dfs(int cur_x, int cur_y, int cur_dist) {
	visited_dist[cur_x][cur_y] = cur_dist;
	if (map[cur_x][cur_y] != 0 && map[cur_x][cur_y] < shark_size) {
		if (min_dist > cur_dist || (min_dist == cur_dist && ((min_x > cur_x) || (min_x == cur_x && min_y > cur_y)))) {
			min_dist = cur_dist;
			min_x = cur_x; min_y = cur_y;
		}
		return true;
	}
	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int nx, ny;
	int ret = 0;
	for (int d = 0; d < 4; d++) {
		nx = cur_x + dx[d];
		ny = cur_y + dy[d];
		if (nx >= 0 && nx < N && ny >= 0 && ny < N && map[nx][ny] <= shark_size && visited_dist[nx][ny] > cur_dist + 1) {
			ret += dfs(nx, ny, cur_dist + 1);
		}
	}
	return ret;
}

bool pos_eat() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited_dist[i][j] = 1000;
		}
	}
	min_dist = 1000;
	return dfs(s_xpos, s_ypos, 0);
}

int help_time(int cur_time) {
	bool searched = false;
	//search
	if (!pos_eat()) {
		return cur_time;
	}
	//move
	s_xpos = min_x; s_ypos = min_y;
	cur_time += min_dist;
	//eat
	map[min_x][min_y] = 0;
	eat_count++;
	if (eat_count >= shark_size) {
		eat_count = 0;
		shark_size++;
	}
	return help_time(cur_time);
}

int main() {
	int answer = 0;
	int x, y, z;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				map[i][j] = 0;
				shark_size = 2; s_xpos = i; s_ypos = j;
				eat_count = 0;
			}
		}
	}
	answer = help_time(0);

	cout << answer << endl;
	return 0;
}
