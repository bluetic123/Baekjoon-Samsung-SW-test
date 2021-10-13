#include <stdio.h>
#include <queue>
#include <stack>
#include <string.h>
#include <utility>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>
#define INF -1
using namespace std;

int board[21][21] = { 0, };
int max_block = 0;
int N;

void game(int move) {
	int pre, cur, count = 0;
	queue<int> q[4][20];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (max_block < board[i][j]) {
				max_block = board[i][j];
			}
		}
	}
	if (move < 1) {
		return;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 0) {
				q[0][i].push(board[i][j]);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = N - 1; j >= 0; j--) {
			if (board[i][j] != 0) {
				q[1][i].push(board[i][j]);
			}
		}
	}
	for (int i = N - 1; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 0) {
				q[2][j].push(board[i][j]);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] != 0) {
				q[3][j].push(board[i][j]);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		pre = 0;
		count = 0;
		while (!q[0][i].empty()) {
			cur = q[0][i].front(); q[0][i].pop();
			if (pre == cur) {
				pre *= 2;
				board[i][count++] = pre;
				pre = 0;
			}
			else {
				if (pre != 0) {
					board[i][count++] = pre;
				}
				pre = cur;
			}
		}
		if (pre != 0) {
			board[i][count++] = pre;
		}
		while (count < N) {
			board[i][count++] = 0;
		}
	}
	game(move - 1);
	for (int i = 0; i < N; i++) {
		pre = 0;
		count = N - 1;
		while (!q[1][i].empty()) {
			cur = q[1][i].front(); q[1][i].pop();
			if (pre == cur) {
				pre *= 2;
				board[i][count--] = pre;
				pre = 0;
			}
			else {
				if (pre != 0) {
					board[i][count--] = pre;
				}
				pre = cur;
			}
		}
		if (pre != 0) {
			board[i][count--] = pre;
		}
		while (count >= 0) {
			board[i][count--] = 0;
		}
	}
	game(move - 1);
	for (int i = 0; i < N; i++) {
		pre = 0;
		count = N - 1;
		while (!q[2][i].empty()) {
			cur = q[2][i].front(); q[2][i].pop();
			if (pre == cur) {
				pre *= 2;
				board[count--][i] = pre;
				pre = 0;
			}
			else {
				if (pre != 0) {
					board[count--][i] = pre;
				}
				pre = cur;
			}
		}
		if (pre != 0) {
			board[count--][i] = pre;
		}
		while (count >= 0) {
			board[count--][i] = 0;
		}
	}
	game(move - 1);
	for (int i = 0; i < N; i++) {
		pre = 0;
		count = 0;
		while (!q[3][i].empty()) {
			cur = q[3][i].front(); q[3][i].pop();
			if (pre == cur) {
				pre *= 2;
				board[count++][i] = pre;
				pre = 0;
			}
			else {
				if (pre != 0) {
					board[count++][i] = pre;
				}
				pre = cur;
			}
		}
		if (pre != 0) {
			board[count++][i] = pre;
		}
		while (count < N) {
			board[count++][i] = 0;
		}
	}
	game(move - 1);
}

int main() {
	int temp;
	int left = 0, right = 0;
	int len1, len2;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	game(5);

	printf("%d\n", max_block);

	return 0;
}


