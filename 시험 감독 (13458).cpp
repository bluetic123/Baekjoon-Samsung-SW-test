#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long N, M;
long long A[1000002];
long long B, C;

int main() {
	long long answer = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	cin >> B >> C;
	for (int i = 0; i < N; i++) {
		A[i] -= B;
		answer++;
		if (A[i] <= 0) {
			continue;
		}
		answer += A[i] / C;
		if (A[i] % C != 0) {
			answer++;
		}
	}
	cout << answer << endl;

	return 0;
}
