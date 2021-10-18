#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> house_pos;
vector<vector<int>> chicken_pos;
int min_dist[102];

int dfs(int cur_chicken, vector<int> chicken_idx) {
	if (cur_chicken >= M) {
		int h_len = house_pos.size();
		for (int h = 0; h < h_len; h++) {
			min_dist[h] = 1000000;
		}
		int cx, cy, hx, hy, idx, dist;
		for (int c = 0; c < chicken_idx.size(); c++) {
			idx = chicken_idx[c];
			cx = chicken_pos[idx][0]; cy = chicken_pos[idx][1];
			for (int h = 0; h < h_len; h++) {
				hx = house_pos[h][0]; hy = house_pos[h][1];
				dist = abs(hx - cx) + abs(hy - cy);
				if (dist < min_dist[h]) {
					min_dist[h] = dist;
				}
			}
		}
		int sum = 0;
		for (int h = 0; h < h_len; h++) {
			sum += min_dist[h];
		}
		return sum;
	}
	int pre = 0, ret, local_min = 1000000;
	if (chicken_idx.size() != 0) {
		pre = chicken_idx[chicken_idx.size() - 1] + 1;
	}
	chicken_idx.push_back(0);
	for (int c = pre; c < chicken_pos.size(); c++) {
		chicken_idx[chicken_idx.size() - 1] = c;
		ret = dfs(cur_chicken + 1, chicken_idx);
		if (ret < local_min) {
			local_min = ret;
		}
	}
	return local_min;
}

int main() {
	int answer = 0;
	int type;
	vector<int> pos, empty_v;
	cin >> N >> M;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cin >> type;
			if (type == 1) {
				pos.clear();
				pos.push_back(x); pos.push_back(y);
				house_pos.push_back(pos);
			}
			else if (type == 2) {
				pos.clear();
				pos.push_back(x); pos.push_back(y);
				chicken_pos.push_back(pos);
			}
		}
	}
	answer = dfs(0, empty_v);
	cout << answer << endl;
	return 0;
}
