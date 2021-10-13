#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
using namespace std;

int board[102][102] = { 0, };
int head_x = 1;
int head_y = 1;
int tail_x = 1;
int tail_y = 1;
int c_direct = 1;//오른쪽 : 1, 아래쪽 : 2, 왼쪽 : 3, 위쪽 : 4
int c_time = 0;
int N;

queue<int> q_t;
queue<char> q_d;

void snake() {
	if ((!q_t.empty()) && c_time == q_t.front()) {
		q_t.pop();
		if (q_d.front() == 'D') {
			c_direct++;
			if (c_direct > 4) {
				c_direct = 1;
			}
		}
		else {
			c_direct--;
			if (c_direct < 1) {
				c_direct = 4;
			}
		}
		q_d.pop();
	}
	c_time++;
	if (c_direct == 2) {
		head_x++;
		if (head_x > N) {
			return;
		}
	}
	else if (c_direct == 1) {
		head_y++;
		if (head_y > N) {
			return;
		}
	}
	else if (c_direct == 4) {
		head_x--;
		if (head_x < 1) {
			return;
		}
	}
	else {
		head_y--;
		if (head_y < 1) {
			return;
		}
	}

	if (board[head_x][head_y] > 0) {
		return;
	}
	if (board[head_x][head_y] == -1) {
		board[head_x][head_y] = c_time;
	}
	else {
		board[head_x][head_y] = c_time;
		if (board[tail_x][tail_y] + 1 == board[tail_x + 1][tail_y]) {
			board[tail_x][tail_y] = 0;
			tail_x += 1;
		}
		else if (board[tail_x][tail_y] + 1 == board[tail_x - 1][tail_y]) {
			board[tail_x][tail_y] = 0;
			tail_x -= 1;
		}
		else if (board[tail_x][tail_y] + 1 == board[tail_x][tail_y + 1]) {
			board[tail_x][tail_y] = 0;
			tail_y += 1;
		}
		else {
			board[tail_x][tail_y] = 0;
			tail_y -= 1;
		}
	}
	snake();
}

int main() {
	int K, L;
	int x, y;
	int sum = 0;
	int num;
	int check = 0;
	int count = 0;
	int result;
	int time;
	char direct;

	scanf("%d", &N);

	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &x, &y);
		board[x][y] = -1;
	}

	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		scanf("%d %c", &time, &direct);
		q_t.push(time);
		q_d.push(direct);
	}

	snake();

	printf("%d\n", c_time);

	return 0;
}