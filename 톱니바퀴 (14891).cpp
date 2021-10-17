#include <iostream>
#include <string>
#include <vector>

using namespace std;

int K;
int ns_state[5][10];

void rotate(int num, int d) {
	if (d == 1) {
		for (int i = 7; i >= 0; i--) {
			ns_state[num][i + 1] = ns_state[num][i];
		}
		ns_state[num][0] = ns_state[num][8];
	}
	else {
		ns_state[num][8] = ns_state[num][0];
		for (int i = 0; i < 8; i++) {
			ns_state[num][i] = ns_state[num][i + 1];
		}
	}
}

int main() {
	int answer = 0;
	int target, d, pre_state, pre_d;
	char buf[10];
	for (int i = 1; i <= 4; i++) {
		cin >> buf;
		for (int j = 0; j < 8; j++) {
			ns_state[i][j] = buf[j] - '0';
		}
	}
	cin >> K;
	for (int k = 0; k < K; k++) {
		cin >> target >> d;
		// 6 - 2
		pre_state = ns_state[target][6];
		pre_d = d;
		for (int adj = target - 1; adj > 0; adj--) {
			if (ns_state[adj][2] == pre_state) {
				break;
			}
			pre_state = ns_state[adj][6];
			pre_d *= -1;
			rotate(adj, pre_d);
		}
		pre_state = ns_state[target][2];
		pre_d = d;
		for (int adj = target + 1; adj <= 4; adj++) {
			if (ns_state[adj][6] == pre_state) {
				break;
			}
			pre_state = ns_state[adj][2];
			pre_d *= -1;
			rotate(adj, pre_d);
		}
		rotate(target, d);
	}
	answer = ns_state[1][0] * 1 + ns_state[2][0] * 2 + ns_state[3][0] * 4 + ns_state[4][0] * 8;

	cout << answer << endl;
	return 0;
}
