#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N;
int T[20];
int P[20];
int DP[20];

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> T[i] >> P[i];
	}
	for (int i = 0; i < 20; i++) {
		DP[i] = 0;
	}
	for (int cur_day = 0; cur_day < N; cur_day++) {
		int end_time = cur_day + T[cur_day];
		if (cur_day > 0 && DP[cur_day] < DP[cur_day - 1]) {
			DP[cur_day] = DP[cur_day - 1];
		}
		if (DP[end_time] < DP[cur_day] + P[cur_day]) {
			DP[end_time] = DP[cur_day] + P[cur_day];
		}
	}
	if (DP[N] < DP[N - 1]) {
		DP[N] = DP[N - 1];
	}
	cout << DP[N] << endl;

	return 0;
}
