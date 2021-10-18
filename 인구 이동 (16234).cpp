#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, L, R;
int map[52][52];
bool checked[52][52];
vector<vector<int>> cur_mem_pos;

bool pos_move() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i > 0 && abs(map[i][j] - map[i - 1][j]) >= L && abs(map[i][j] - map[i - 1][j]) <= R) {
				return true;
			}
			if (j > 0 && abs(map[i][j] - map[i][j - 1]) >= L && abs(map[i][j] - map[i][j - 1]) <= R) {
				return true;
			}
			if (i + 1 < N && abs(map[i][j] - map[i + 1][j]) >= L && abs(map[i][j] - map[i + 1][j]) <= R) {
				return true;
			}
			if (j + 1 < N && abs(map[i][j] - map[i][j + 1]) >= L && abs(map[i][j] - map[i][j + 1]) <= R) {
				return true;
			}
		}
	}
	return false;
}

int dfs(int x, int y) {
	vector<int> pos;
	pos.push_back(x); pos.push_back(y);
	cur_mem_pos.push_back(pos);
	checked[x][y] = true;

	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int nx, ny;
	int sum = map[x][y];
	for (int i = 0; i < 4; i++) {
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx >= 0 && nx < N && ny >= 0 && ny < N && !checked[nx][ny]
			&& abs(map[x][y] - map[nx][ny]) >= L && abs(map[x][y] - map[nx][ny]) <= R) {
			sum += dfs(nx, ny);
		}
	}
	return sum;
}

int move(int day) {
	if (!pos_move()) {
		return day;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			checked[i][j] = false;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (checked[i][j]) {
				continue;
			}
			cur_mem_pos.clear();
			int total = dfs(i, j);
			int mem_num = cur_mem_pos.size();
			for (int m = 0; m < mem_num; m++) {
				int x = cur_mem_pos[m][0], y = cur_mem_pos[m][1];
				map[x][y] = total / mem_num;
			}
		}
	}
	return move(day + 1);
}

int main() {
	int answer = 0;
	cin >> N >> L >> R;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	answer = move(0);
	cout << answer << endl;
	return 0;
}
