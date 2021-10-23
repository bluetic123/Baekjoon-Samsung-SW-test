#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, K;

bool wall[22][22];
int client_xpos[402], client_ypos[402];
int destination_xpos[402], destination_ypos[402];
int taxi_xpos, taxi_ypos;
int min_idx, min_cost, go_cost;

int cost_map[22][22];
int index_map[22][22];

int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
int nx, ny;

void select_dfs(int x, int y, int cur_cost) {
	cost_map[x][y] = cur_cost;
	if (index_map[x][y] != 0) {
		if (min_cost > cur_cost ||
			(min_cost == cur_cost && client_xpos[min_idx] > x) ||
			(min_cost == cur_cost && client_xpos[min_idx] == x && client_ypos[min_idx] > y)) {
			min_idx = index_map[x][y];
			min_cost = cur_cost;
		}
		return;
	}

	for (int d = 0; d < 4; d++) {
		nx = x + dx[d];
		ny = y + dy[d];
		if (nx >= 0 && nx < N && ny >= 0 && ny < N && !wall[nx][ny] && cost_map[nx][ny] > cur_cost + 1) {
			select_dfs(nx, ny, cur_cost + 1);
		}
	}
}

void go_dfs(int x, int y, int cur_cost, int obj_idx) {
	cost_map[x][y] = cur_cost;
	if (x == destination_xpos[obj_idx] && y == destination_ypos[obj_idx]) {
		if (go_cost > cur_cost) {
			go_cost = cur_cost;
		}
		return;
	}

	for (int d = 0; d < 4; d++) {
		nx = x + dx[d];
		ny = y + dy[d];
		if (nx >= 0 && nx < N && ny >= 0 && ny < N && !wall[nx][ny] && cost_map[nx][ny] > cur_cost + 1) {
			go_dfs(nx, ny, cur_cost + 1, obj_idx);
		}
	}
}

void select_client() {

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cost_map[x][y] = 1000000000;
		}
	}
	min_cost = 1000000000;
	select_dfs(taxi_xpos, taxi_ypos, 0);

	index_map[client_xpos[min_idx]][client_ypos[min_idx]] = 0;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cost_map[x][y] = 1000000000;
		}
	}
	go_cost = 1000000000;
	go_dfs(client_xpos[min_idx], client_ypos[min_idx], 0, min_idx);
}

int cycle() {
	int cur_energy = K;
	for (int m = 0; m < M; m++) {
		select_client();
		//		printf("%d %d\n", min_cost, go_cost);
		if (cur_energy < min_cost + go_cost) {
			return -1;
		}
		cur_energy -= min_cost;
		cur_energy += go_cost;

		taxi_xpos = destination_xpos[min_idx];
		taxi_ypos = destination_ypos[min_idx];
	}
	return cur_energy;
}

int main() {
	int answer = 0;
	int x, y;

	cin >> N >> M >> K;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cin >> wall[x][y];
		}
	}
	cin >> x >> y;
	taxi_xpos = x - 1; taxi_ypos = y - 1;
	for (int idx = 1; idx <= M; idx++) {
		cin >> x >> y;
		client_xpos[idx] = x - 1; client_ypos[idx] = y - 1;
		cin >> x >> y;
		destination_xpos[idx] = x - 1; destination_ypos[idx] = y - 1;
		index_map[client_xpos[idx]][client_ypos[idx]] = idx;
	}

	answer = cycle();

	cout << answer << endl;
	return 0;
}

