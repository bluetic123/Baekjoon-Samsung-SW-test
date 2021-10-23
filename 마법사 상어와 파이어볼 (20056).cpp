#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int N, M, K;
vector<vector<int>> fire_ball_info; // [index], [r, c, m, s, d]

vector<vector<int>> map_info[52][52];

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int nx, ny, nm, ns, nd;

long long cycle() {
	int x, y, m, s, d;
	vector<int> info;
	for (int k = 0; k < K; k++) {
		for (x = 0; x < N; x++) {
			for (y = 0; y < N; y++) {
				map_info[x][y].clear();
			}
		}
		// move
		for (int idx = 0; idx < fire_ball_info.size(); idx++) {
			x = fire_ball_info[idx][0]; y = fire_ball_info[idx][1];
			m = fire_ball_info[idx][2]; s = fire_ball_info[idx][3];
			d = fire_ball_info[idx][4];

			ns = s; s %= N;
			nx = x + dx[d] * s; ny = y + dy[d] * s;
			if (nx < 0) {
				nx = N + nx;
			}
			else if (nx >= N) {
				nx = nx - N;
			}
			if (ny < 0) {
				ny = N + ny;
			}
			else if (ny >= N) {
				ny = ny - N;
			}

			info.clear();
			info.push_back(nx); info.push_back(ny);
			info.push_back(m); info.push_back(ns);
			info.push_back(d);

			map_info[nx][ny].push_back(info);
		}

		//merge
		fire_ball_info.clear();
		for (x = 0; x < N; x++) {
			for (y = 0; y < N; y++) {
				if (map_info[x][y].size() <= 1) {
					if (map_info[x][y].size() > 0) {
						info = map_info[x][y][0];
						fire_ball_info.push_back(info);
					}
					continue;
				}
				int total_m = 0, total_s = 0;
				bool d_check = true;
				for (int i = 0; i < map_info[x][y].size(); i++) {
					if (i > 0 && map_info[x][y][i][4] % 2 != map_info[x][y][i - 1][4] % 2) {
						d_check = false;
					}
					total_m += map_info[x][y][i][2];
					total_s += map_info[x][y][i][3];
				}
				nm = total_m / 5;
				if (nm == 0) {
					continue;
				}
				ns = total_s / map_info[x][y].size();
				info.clear();
				info.push_back(x); info.push_back(y);
				info.push_back(nm); info.push_back(ns);
				info.push_back(0);
				if (d_check) {
					info[4] = 0; fire_ball_info.push_back(info);
					info[4] = 2; fire_ball_info.push_back(info);
					info[4] = 4; fire_ball_info.push_back(info);
					info[4] = 6; fire_ball_info.push_back(info);
				}
				else {
					info[4] = 1; fire_ball_info.push_back(info);
					info[4] = 3; fire_ball_info.push_back(info);
					info[4] = 5; fire_ball_info.push_back(info);
					info[4] = 7; fire_ball_info.push_back(info);
				}
			}
		}
	}
	long long total_m = 0;
	for (int idx = 0; idx < fire_ball_info.size(); idx++) {
		total_m += (long long)fire_ball_info[idx][2];
	}
	return total_m;
}
int main() {
	long long answer = 0;
	int r, c, m, s, d;
	vector<int> info;

	cin >> N >> M >> K;

	for (int idx = 0; idx < M; idx++) {
		cin >> r >> c >> m >> s >> d;
		r--; c--;

		info.clear();
		info.push_back(r); info.push_back(c);
		info.push_back(m); info.push_back(s);
		info.push_back(d);

		fire_ball_info.push_back(info);
	}

	answer = cycle();

	cout << answer << endl;
	return 0;
}
