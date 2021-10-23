#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int score = 0;
bool blue_space[6][6] = { 0, };
bool green_space[6][6] = { 0, };

void insert_block(int x, int y, int type) {
	int insert_point;
	// blue
	if (type == 1 || type == 2) {
		for (insert_point = 2; insert_point < 6; insert_point++) {
			if (blue_space[x][insert_point]) {
				break;
			}
		}
		insert_point--;
		blue_space[x][insert_point] = true;
		if (type == 2) {
			blue_space[x][insert_point - 1] = true;
		}
	}
	else if (type == 3) {
		for (insert_point = 2; insert_point < 6; insert_point++) {
			if (blue_space[x][insert_point] || blue_space[x + 1][insert_point]) {
				break;
			}
		}
		insert_point--;
		blue_space[x][insert_point] = true;
		blue_space[x + 1][insert_point] = true;
	}
	// green
	if (type == 1 || type == 3) {
		for (insert_point = 2; insert_point < 6; insert_point++) {
			if (green_space[y][insert_point]) {
				break;
			}
		}
		insert_point--;
		green_space[y][insert_point] = true;
		if (type == 3) {
			green_space[y][insert_point - 1] = true;
		}
	}
	else if (type == 2) {
		for (insert_point = 2; insert_point < 6; insert_point++) {
			if (green_space[y][insert_point] || green_space[y + 1][insert_point]) {
				break;
			}
		}
		insert_point--;
		green_space[y][insert_point] = true;
		green_space[y + 1][insert_point] = true;
	}
}

void block_state_check() {
	// score
	// blue
	for (int y = 5; y >= 0; y--) {
		if (blue_space[0][y] && blue_space[1][y] && blue_space[2][y] && blue_space[3][y]) {
			score++;
			for (int line = y; line > 0; line--) {
				for (int x = 0; x < 4; x++) {
					blue_space[x][line] = blue_space[x][line - 1];
				}
			}
			for (int x = 0; x < 4; x++) {
				blue_space[x][0] = false;
			}
			y++;
		}
	}
	// green
	for (int y = 5; y >= 0; y--) {
		if (green_space[0][y] && green_space[1][y] && green_space[2][y] && green_space[3][y]) {
			score++;
			for (int line = y; line > 0; line--) {
				for (int x = 0; x < 4; x++) {
					green_space[x][line] = green_space[x][line - 1];
				}
			}
			for (int x = 0; x < 4; x++) {
				green_space[x][0] = false;
			}
			y++;
		}
	}
	// line_push
	// blue
	for (int t = 0; t < 2; t++) {
		bool line_empty = true;
		for (int x = 0; x < 4; x++) {
			if (blue_space[x][1]) {
				line_empty = false;
			}
		}
		if (line_empty) {
			break;
		}
		for (int line = 5; line > 0; line--) {
			for (int x = 0; x < 4; x++) {
				blue_space[x][line] = blue_space[x][line - 1];
			}
		}
		for (int x = 0; x < 4; x++) {
			blue_space[x][0] = false;
		}
	}
	// green
	for (int t = 0; t < 2; t++) {
		bool line_empty = true;
		for (int x = 0; x < 4; x++) {
			if (green_space[x][1]) {
				line_empty = false;
			}
		}
		if (line_empty) {
			break;
		}
		for (int line = 5; line > 0; line--) {
			for (int x = 0; x < 4; x++) {
				green_space[x][line] = green_space[x][line - 1];
			}
		}
		for (int x = 0; x < 4; x++) {
			green_space[x][0] = false;
		}
	}
}

void block_game() {
	int x, y, type;

	for (int n = 0; n < N; n++) {
		cin >> type >> x >> y;
		insert_block(x, y, type);
		block_state_check();
	}
}

int main() {
	int answer = 0;

	cin >> N;

	block_game();

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 6; y++) {
			if (blue_space[x][y]) {
				answer++;
			}
			if (green_space[x][y]) {
				answer++;
			}
		}
	}

	cout << score << endl;
	cout << answer << endl;
	return 0;
}

