#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N, M;
int block[504][504];

int type1(int x, int y) {
	int local_max = 0, sum;
	sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += block[x + i][y];
	}
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += block[x][y + i];
	}
	if (sum > local_max) {
		local_max = sum;
	}
	return local_max;
}

int type2(int x, int y) {
	int local_max = 0, sum;
	sum = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			sum += block[x + i][y + j];
		}
	}
	if (sum > local_max) {
		local_max = sum;
	}
	return local_max;
}

int type3(int x, int y) {
	int local_max = 0, sum;
	sum = 0;
	sum = block[x][y] + block[x + 1][y] + block[x + 2][y] + block[x + 2][y + 1];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y + 1] + block[x + 1][y + 1] + block[x + 2][y + 1] + block[x + 2][y];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y] + block[x + 1][y] + block[x + 2][y] + block[x][y + 1];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y + 1] + block[x + 1][y + 1] + block[x + 2][y + 1] + block[x][y];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y] + block[x][y + 1] + block[x][y + 2] + block[x + 1][y];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y] + block[x + 1][y] + block[x + 1][y + 1] + block[x + 1][y + 2];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y] + block[x][y + 1] + block[x][y + 2] + block[x + 1][y + 2];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x + 1][y] + block[x + 1][y + 1] + block[x + 1][y + 2] + block[x][y + 2];
	if (sum > local_max) {
		local_max = sum;
	}
	return local_max;
}
int type4(int x, int y) {
	int local_max = 0, sum;
	sum = 0;
	sum = block[x][y] + block[x + 1][y] + block[x + 1][y + 1] + block[x + 2][y + 1];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y + 1] + block[x + 1][y + 1] + block[x + 1][y] + block[x + 2][y];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y + 1] + block[x][y + 2] + block[x + 1][y] + block[x + 1][y + 1];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y] + block[x][y + 1] + block[x + 1][y + 1] + block[x + 1][y + 2];
	if (sum > local_max) {
		local_max = sum;
	}
	return local_max;
}
int type5(int x, int y) {
	int local_max = 0, sum;
	sum = 0;
	sum = block[x][y] + block[x][y + 1] + block[x + 1][y + 1] + block[x][y + 2];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y] + block[x + 1][y + 1] + block[x + 1][y] + block[x + 2][y];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x][y + 1] + block[x + 1][y + 1] + block[x + 1][y] + block[x + 2][y + 1];
	if (sum > local_max) {
		local_max = sum;
	}
	sum = 0;
	sum = block[x + 1][y] + block[x + 1][y + 1] + block[x][y + 1] + block[x + 1][y + 2];
	if (sum > local_max) {
		local_max = sum;
	}
	return local_max;
}
int main() {
	cin >> N >> M;
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			cin >> block[n][m];
		}
	}
	for (int n = N; n < N + 3; n++) {
		for (int m = M; m < M + 3; m++) {
			block[n][m] = 0;
		}
	}

	int global_max = 0;
	for (int n = 0; n < N; n++) {
		for (int m = 0; m < M; m++) {
			int local_max = 0, ret;
			ret = type1(n, m);
			if (ret > local_max) {
				local_max = ret;
			}
			ret = type2(n, m);
			if (ret > local_max) {
				local_max = ret;
			}
			ret = type3(n, m);
			if (ret > local_max) {
				local_max = ret;
			}
			ret = type4(n, m);
			if (ret > local_max) {
				local_max = ret;
			}
			ret = type5(n, m);
			if (ret > local_max) {
				local_max = ret;
			}
			if (local_max > global_max) {
				global_max = local_max;
			}
		}
	}
	cout << global_max << endl;
	return 0;
}
