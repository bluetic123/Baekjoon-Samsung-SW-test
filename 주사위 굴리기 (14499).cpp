#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M, K;
int place_num[22][22];

int main() {
	int cur_x, cur_y, d, temp;
	int next_x, next_y;
	int cube[] = { 0, 0, 0, 0, 0, 0 };

	cin >> N >> M >> cur_x >> cur_y >> K;

	for (int x = N - 1; x >= 0; x--) {
		for (int y = 0; y < M; y++) {
			cin >> place_num[x][y];
		}
	}
	cur_x = N - 1 - cur_x;
	int dx[] = { 0, 0, 1, -1 };
	int dy[] = { 1, -1, 0, 0 };
	for (int k = 0; k < K; k++) {
		cin >> d; d--;
		next_x = cur_x + dx[d];
		next_y = cur_y + dy[d];
		if (!(next_x >= 0 && next_x < N && next_y >= 0 && next_y < M)) {
			continue;
		}
		cur_x = next_x;
		cur_y = next_y;
		if (d == 0) {
			temp = cube[1];
			cube[1] = cube[4];
			cube[4] = cube[3];
			cube[3] = cube[5];
			cube[5] = temp;
		}
		else if (d == 1) {
			temp = cube[1];
			cube[1] = cube[5];
			cube[5] = cube[3];
			cube[3] = cube[4];
			cube[4] = temp;
		}
		else if (d == 2) {
			temp = cube[1];
			cube[1] = cube[2];
			cube[2] = cube[3];
			cube[3] = cube[0];
			cube[0] = temp;
		}
		else {
			temp = cube[1];
			cube[1] = cube[0];
			cube[0] = cube[3];
			cube[3] = cube[2];
			cube[2] = temp;
		}
		if (place_num[cur_x][cur_y] == 0) {
			place_num[cur_x][cur_y] = cube[3];
		}
		else {
			cube[3] = place_num[cur_x][cur_y];
			place_num[cur_x][cur_y] = 0;
		}
		cout << cube[1] << endl;
	}


	return 0;
}
