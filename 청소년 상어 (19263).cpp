#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> next_bs;
vector<vector<int>> next_info;

int dfs(int shark_x, int shark_y, int shark_d, vector<vector<int>> block_state, vector<vector<int>> index_to_info) {
	int dx[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
	int dy[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
	int nx, ny, nd;
	int eaten_idx;
	int ret, local_max = 0;

	bool moved = false;
	for (int m = 1; m <= 3; m++) {
		nx = shark_x + dx[shark_d] * m;
		ny = shark_y + dy[shark_d] * m;
		if (nx >= 0 && nx < 4 && ny >= 0 && ny < 4 && block_state[nx][ny] != -1) {
			moved = true;

			next_bs = block_state;
			next_info = index_to_info;

			eaten_idx = block_state[nx][ny];
			nd = index_to_info[eaten_idx][2];
			next_bs[nx][ny] = -1;
			next_info[eaten_idx][0] = -1;
			next_info[eaten_idx][1] = -1;


			int fish_x, fish_y, fish_d;
			int target_x, target_y, target_idx;
			for (int idx = 1; idx <= 16; idx++) {
				if (next_info[idx][0] != -1) {
					fish_x = next_info[idx][0];
					fish_y = next_info[idx][1];
					fish_d = next_info[idx][2];
					for (int i = 0; i < 8; i++) {
						target_x = fish_x + dx[fish_d];
						target_y = fish_y + dy[fish_d];
						if (target_x >= 0 && target_x < 4 && target_y >= 0 && target_y < 4 && (target_x != nx || target_y != ny)) {
							int temp;
							target_idx = next_bs[target_x][target_y];

							next_info[idx][0] = target_x;
							next_info[idx][1] = target_y;
							next_info[idx][2] = fish_d;
							next_bs[target_x][target_y] = idx;
							next_bs[fish_x][fish_y] = target_idx;

							if (target_idx != -1) {
								next_info[target_idx][0] = fish_x;
								next_info[target_idx][1] = fish_y;
							}

							break;
						}
						if (++fish_d > 8) {
							fish_d = 1;
						}
					}
				}
			}

			ret = dfs(nx, ny, nd, next_bs, next_info);

			if (ret > local_max) {
				local_max = ret;
			}
		}
	}
	if (moved) {
		return local_max;
	}

	int sum = 0;
	for (int idx = 1; idx <= 16; idx++) {
		if (index_to_info[idx][0] == -1) {
			sum += idx;
		}
	}
	return sum;
}

int main() {
	int answer = 0;
	int a, b;
	vector<vector<int>> block_state; // fish index
	vector<vector<int>> index_to_pos;
	for (int i = 0; i < 4; i++) {
		vector<int> temp(4);
		block_state.push_back(temp);
	}
	for (int i = 0; i <= 16; i++) {
		vector<int> temp(3);
		index_to_pos.push_back(temp);
	}
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			cin >> a >> b;
			block_state[x][y] = a;
			index_to_pos[a][0] = x;
			index_to_pos[a][1] = y;
			index_to_pos[a][2] = b;
		}
	}
	int eaten_idx = block_state[0][0];
	block_state[0][0] = -1;
	index_to_pos[eaten_idx][0] = -1;
	index_to_pos[eaten_idx][1] = -1;

	int dx[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
	int dy[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
	int fish_x, fish_y, fish_d;
	int target_x, target_y, target_idx;
	for (int idx = 1; idx <= 16; idx++) {
		if (index_to_pos[idx][0] != -1) {
			fish_x = index_to_pos[idx][0];
			fish_y = index_to_pos[idx][1];
			fish_d = index_to_pos[idx][2];
			for (int i = 0; i < 8; i++) {
				target_x = fish_x + dx[fish_d];
				target_y = fish_y + dy[fish_d];
				if (target_x >= 0 && target_x < 4 && target_y >= 0 && target_y < 4 && (target_x != 0 || target_y != 0)) {
					int temp;
					target_idx = block_state[target_x][target_y];

					index_to_pos[idx][0] = target_x;
					index_to_pos[idx][1] = target_y;
					index_to_pos[idx][2] = fish_d;
					block_state[target_x][target_y] = idx;
					block_state[fish_x][fish_y] = target_idx;

					if (target_idx != -1) {
						index_to_pos[target_idx][0] = fish_x;
						index_to_pos[target_idx][1] = fish_y;
					}

					break;
				}
				if (++fish_d > 8) {
					fish_d = 1;
				}
			}
		}
	}

	answer = dfs(0, 0, index_to_pos[eaten_idx][2], block_state, index_to_pos);

	cout << answer << endl;
	return 0;
}

