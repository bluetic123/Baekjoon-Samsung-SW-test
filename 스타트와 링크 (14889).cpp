#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N;
int score[22][22];
int min_dif = -1;
bool is_Ateam[22];

int current_dif() {
	int A_score = 0, B_score = 0;
	for (int i = 0; i < N; i++) {
		if (is_Ateam[i]) {
			for (int j = 0; j < N; j++) {
				if (is_Ateam[j]) {
					A_score += score[i][j];
				}
			}
		}
		else {
			for (int j = 0; j < N; j++) {
				if (!is_Ateam[j]) {
					B_score += score[i][j];
				}
			}
		}
	}
	return abs(A_score - B_score);
}

void brute_force(int idx, int A_count) {
	if (A_count >= N / 2) {
		int ret = current_dif();
		if (min_dif == -1 || min_dif > ret) {
			min_dif = ret;
		}
		return;
	}
	for (int i = idx; i < N; i++) {
		is_Ateam[i] = true;
		brute_force(i + 1, A_count + 1);
		is_Ateam[i] = false;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> score[i][j];
		}
		is_Ateam[i] = false;
	}
	brute_force(0, 0);
	cout << min_dif << endl;
	return 0;
}
