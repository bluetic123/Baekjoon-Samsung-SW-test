#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;
int A[12][12];
int energy[12][12];
vector<int> tree_year[12][12];

void spring_and_summer() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sort(tree_year[i][j].begin(), tree_year[i][j].end());
			int dead_point = 0;
			for (int t = 0; t < tree_year[i][j].size(); t++) {
				if (energy[i][j] < tree_year[i][j][t]) {
					for (int dt = t; dt < tree_year[i][j].size(); dt++) {
						dead_point += tree_year[i][j][dt] / 2;
					}
					tree_year[i][j].erase(tree_year[i][j].begin() + t, tree_year[i][j].end());
					break;
				}
				else {
					energy[i][j] -= tree_year[i][j][t];
					tree_year[i][j][t]++;
				}
			}
			energy[i][j] += dead_point;
		}
	}
}
void fall() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int t = 0; t < tree_year[i][j].size(); t++) {
				if (tree_year[i][j][t] % 5 == 0) {
					int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
					int dy[] = { 0, 1, -1, 1, -1, 0, 1, -1 };
					int nx, ny;
					for (int d = 0; d < 8; d++) {
						nx = i + dx[d]; ny = j + dy[d];
						if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
							tree_year[nx][ny].push_back(1);
						}
					}
				}
			}
		}
	}
}
void winter() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			energy[i][j] += A[i][j];
		}
	}
}

int remain_tree(int cur_k) {
	if (cur_k >= K) {
		int num = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				num += tree_year[i][j].size();
			}
		}
		return num;
	}
	spring_and_summer();
	fall();
	winter();
	return remain_tree(cur_k + 1);
}

int main() {
	int answer = 0;
	int x, y, z;
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
			energy[i][j] = 5;
		}
	}
	for (int m = 0; m < M; m++) {
		cin >> x >> y >> z;
		tree_year[x - 1][y - 1].push_back(z);
	}
	answer = remain_tree(0);
	cout << answer << endl;
	return 0;
}
