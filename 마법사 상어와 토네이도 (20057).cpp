#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int N;

int cur_sand[502][502];

int move_sand(int x, int y, int d) {
	// 7, 2, 7, 2, 1, 1, 10, 10, 5, remainder
	int dx[4][10] = { {0, 0, 0, 0, -1, -1, 1, 1, 2, 1}, {0, 0, 0, 0, 1, 1, -1, -1, -2, -1}, {-1, -2, 1, 2, -1, 1, -1, 1, 0, 0}, {-1, -2, 1, 2, -1, 1, -1, 1, 0, 0} };
	int dy[4][10] = { {-1, -2, 1, 2, -1, 1, -1, 1, 0, 0}, { -1, -2, 1, 2, -1, 1, -1, 1, 0, 0 }, { 0, 0, 0, 0, -1, -1, 1, 1, 2, 1 }, { 0, 0, 0, 0, 1, 1, -1, -1, -2, -1 } };
	int percent[] = { 7, 2, 7, 2, 1, 1, 10, 10, 5, -1 };
	int nx, ny;

	int total_sand = cur_sand[x][y];
	int remain_sand = cur_sand[x][y];
	int out_of_sand = 0;
	int part_sand;
	cur_sand[x][y] = 0;
	for (int i = 0; i < 9; i++) {
		part_sand = total_sand * percent[i] / 100;
		remain_sand -= part_sand;

		nx = x + dx[d][i];
		ny = y + dy[d][i];

		if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
			cur_sand[nx][ny] += part_sand;
		}
		else {
			out_of_sand += part_sand;
		}
	}
	nx = x + dx[d][9];
	ny = y + dy[d][9];
	if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
		cur_sand[nx][ny] += remain_sand;
	}
	else {
		out_of_sand += remain_sand;
	}

	return out_of_sand;
}

int tornado() {
	int out_of_sand = 0;
	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int nx, ny;
	int x, y, d;
	int cur_n = 1;

	x = N / 2; y = N / 2;
	d = 3;

	while (true) {
		for (int i = 0; i < cur_n; i++) {
			x += dx[d]; y += dy[d];
			out_of_sand += move_sand(x, y, d);
		}
		if (cur_n >= N) {
			break;
		}

		if (d == 3) { d = 0; }
		else if (d == 0) { d = 2; }
		else if (d == 2) { d = 1; }
		else if (d == 1) { d = 3; }

		for (int i = 0; i < cur_n; i++) {
			x += dx[d]; y += dy[d];
			out_of_sand += move_sand(x, y, d);
		}

		if (d == 3) { d = 0; }
		else if (d == 0) { d = 2; }
		else if (d == 2) { d = 1; }
		else if (d == 1) { d = 3; }

		cur_n++;
	}

	return out_of_sand;
}

int main() {
	int answer = 0;

	cin >> N;

	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			cin >> cur_sand[x][y];
		}
	}

	answer = tornado();

	cout << answer << endl;
	return 0;
}
