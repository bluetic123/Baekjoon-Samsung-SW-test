#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
int block[10][10];
int c_block[10][10];

void virus_test(int x, int y) {
	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx >= 0 && nx < N && ny >= 0 && ny < M && c_block[nx][ny] == 0) {
			c_block[nx][ny] = 2;
			virus_test(nx, ny);
		}
	}
}
int safe_space() {
	int count = 0;
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			c_block[n][m] = block[n][m];
		}
	}
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			if (c_block[n][m] == 2) {
				virus_test(n, m);
			}
		}
	}
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			if (c_block[n][m] == 0) {
				count++;
			}
		}
	}
	return count;
}

int b_force(int r_wall) {
	int local_max = 0, ret;
	if (r_wall <= 0) {
		return safe_space();
	}
	for (int n1 = 0; n1 < N; n1++) {
		for (int m1 = 0; m1 < M; m1++) {
			if (block[n1][m1] != 0) {
				continue;
			}
			block[n1][m1] = 1;
			ret = b_force(r_wall - 1);
			if (ret > local_max) {
				local_max = ret;
			}
			block[n1][m1] = 0;
		}
	}
	return local_max;
}

int main() {
	cin >> N >> M;
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			cin >> block[n][m];
		}
	}
	cout << b_force(3) << endl;
	return 0;
}
