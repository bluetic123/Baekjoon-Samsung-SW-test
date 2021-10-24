#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int N;
int map[22][22];

vector<int> prefer[402];

void placement(int idx) {
	int max_prefer = 0, max_empty = -1;
	int max_x = 0, max_y = 0;
	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int adj_x, adj_y;

	int cur_prefer, cur_empty;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			if (map[x][y] > 0) {
				continue;
			}
			cur_prefer = 0; cur_empty = 0;
			for (int d = 0; d < 4; d++) {
				adj_x = x + dx[d];
				adj_y = y + dy[d];
				if (adj_x >= 0 && adj_x < N && adj_y >= 0 && adj_y < N &&
					(map[adj_x][adj_y] == prefer[idx][0] || map[adj_x][adj_y] == prefer[idx][1]
						|| map[adj_x][adj_y] == prefer[idx][2] || map[adj_x][adj_y] == prefer[idx][3])) {
					cur_prefer++;
				}
				else if (adj_x >= 0 && adj_x < N && adj_y >= 0 && adj_y < N &&
					map[adj_x][adj_y] == 0) {
					cur_empty++;
				}
			}
			if (cur_prefer > max_prefer) {
				max_prefer = cur_prefer;
				max_empty = cur_empty;
				max_x = x; max_y = y;
			}
			else if (cur_prefer == max_prefer && cur_empty > max_empty) {
				max_empty = cur_empty;
				max_x = x; max_y = y;
			}
		}
	}
	map[max_x][max_y] = idx;
}

int prefer_score() {
	int total_prefer = 0, cur_prefer, score;
	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int adj_x, adj_y, idx;
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			idx = map[x][y];
			cur_prefer = 0;
			for (int d = 0; d < 4; d++) {
				adj_x = x + dx[d];
				adj_y = y + dy[d];
				if (adj_x >= 0 && adj_x < N && adj_y >= 0 && adj_y < N &&
					(map[adj_x][adj_y] == prefer[idx][0] || map[adj_x][adj_y] == prefer[idx][1]
						|| map[adj_x][adj_y] == prefer[idx][2] || map[adj_x][adj_y] == prefer[idx][3])) {
					cur_prefer++;
				}
			}
			if (cur_prefer >= 1) {
				score = 1;
				for (int i = 1; i < cur_prefer; i++) {
					score *= 10;
				}
				total_prefer += score;
			}
		}
	}
	return total_prefer;
}

int main() {
	int answer = 0;
	int temp, idx;

	cin >> N;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			map[x][y] = 0;
		}
	}

	for (int i = 0; i < N * N; i++) {
		cin >> idx;
		for (int j = 0; j < 4; j++) {
			cin >> temp;
			prefer[idx].push_back(temp);
		}
		placement(idx);
	}

	answer = prefer_score();

	cout << answer << endl;

	return 0;
}
