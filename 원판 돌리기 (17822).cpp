#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N, M, T;
int board[52][52];
bool erased;

void rotate(int x, int d, int k) {
	int temp[52] = { 0, };
	for (int i = x; i <= N; i += x) {
		if (d == 0) {
			int idx = 0;
			for (int j = M - k; j < M; j++, idx++) {
				temp[idx] = board[i][j];
			}
			for (int j = M - 1; j >= k; j--) {
				board[i][j] = board[i][j - k];
			}
			for (int j = 0; j < k; j++) {
				board[i][j] = temp[j];
			}
		}
		else {
			for (int j = 0; j < k; j++) {
				temp[j] = board[i][j];
			}
			for (int j = k; j < M; j++) {
				board[i][j - k] = board[i][j];
			}
			int idx = 0;
			for (int j = M - k; j < M; j++, idx++) {
				board[i][j] = temp[idx];
			}
		}
	}
}

void dfs_erase(int x, int y, int value) {
	board[x][y] = 0;
	erased = true;

	int dx[] = { 1, -1, 0, 0 };
	int dy[] = { 0, 0, 1, -1 };
	int nx, ny;
	for (int d = 0; d < 4; d++) {
		nx = x + dx[d];
		ny = y + dy[d];
		if (ny < 0) {
			ny = M - 1;
		}
		else if (ny >= M) {
			ny = 0;
		}
		if (nx > 0 && nx <= N && board[nx][ny] == value) {
			dfs_erase(nx, ny, value);
		}
	}
}
void same_erase() {
	erased = false;
	for (int x = 1; x <= N; x++) {
		for (int y = 0; y < M; y++) {
			if (board[x][y] != 0) {
				if ((x < N && board[x][y] == board[x + 1][y]) || (x > 1 && board[x][y] == board[x - 1][y])
					|| (y < M - 1 && board[x][y] == board[x][y + 1]) || (y > 0 && board[x][y] == board[x][y - 1]
						|| (y == 0 && board[x][y] == board[x][M - 1]) || (y == M - 1 && board[x][y] == board[x][0]))) {
					dfs_erase(x, y, board[x][y]);
				}
			}
		}
	}
}

void avr_plus_minus() {
	float count = 0, sum = 0, avr;
	for (int x = 1; x <= N; x++) {
		for (int y = 0; y < M; y++) {
			if (board[x][y] > 0) {
				count++;
				sum += board[x][y];
			}
		}
	}
	if (count == 0) {
		return;
	}
	avr = sum / count;
	for (int x = 1; x <= N; x++) {
		for (int y = 0; y < M; y++) {
			if (board[x][y] > 0) {
				if (board[x][y] > avr) {
					board[x][y]--;
				}
				else if (board[x][y] < avr) {
					board[x][y]++;
				}
			}
		}
	}
}


int main() {
	int answer = 0;
	int x, d, k;

	cin >> N >> M >> T;

	for (int x = 1; x <= N; x++) {
		for (int y = 0; y < M; y++) {
			cin >> board[x][y];
		}
	}

	for (int t = 0; t < T; t++) {
		cin >> x >> d >> k;

		rotate(x, d, k);
		same_erase();
		if (!erased) {
			avr_plus_minus();
		}
	}
	for (int x = 1; x <= N; x++) {
		for (int y = 0; y < M; y++) {
			answer += board[x][y];
		}
	}

	cout << answer << endl;
	return 0;
}

