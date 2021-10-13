#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
int dx[] = { -1, 0, 1 ,0 };
int dy[] = { 0, 1, 0, -1 };
bool is_wall[52][52];
bool cleaned[52][52];

int robot(int x, int y, int d, int count) {
	int ret, start_d = d;

	count++;
	cleaned[x][y] = true;
	while (true) {
		int left_d = d - 1;
		if (left_d < 0) {
			left_d += 4;
		}
		int left_x = x + dx[left_d];
		int left_y = y + dy[left_d];
		if (left_x >= 0 && left_x < N && left_y >= 0 && left_y < M && !is_wall[left_x][left_y] && !cleaned[left_x][left_y]) {
			count = robot(left_x, left_y, left_d, count);
			break;
		}
		else {
			d = left_d;
		}
		if (d == start_d) {
			int back_d = d - 2;
			if (back_d < 0) {
				back_d += 4;
			}
			int back_x = x + dx[back_d];
			int back_y = y + dy[back_d];
			if (!(back_x >= 0 && back_x < N && back_y >= 0 && back_y < M && !is_wall[back_x][back_y])) {
				break;
			}
			x = back_x;
			y = back_y;
		}
	}
	return count;
}

int main() {
	int ret;
	int r, c, d;
	cin >> N >> M;
	cin >> r >> c >> d;
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			cin >> is_wall[n][m];
			cleaned[n][m] = false;
		}
	}
	cout << robot(r, c, d, 0) << endl;
	return 0;
}
