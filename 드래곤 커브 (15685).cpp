#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N;
bool map[102][102];

int sub_dragon() {
	int count = 0;
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			if (map[x][y] && map[x + 1][y] && map[x][y + 1] && map[x + 1][y + 1]) {
				count++;
			}
		}
	}
	return count;
}

void dragon_curve(int remain_k, vector<vector<int>> pos, vector<int> pivot) {
	if (remain_k <= 0) {
		return;
	}
	vector<int> temp;
	int x, y, x_dif, y_dif, rx, ry, len = pos.size();
	for (int idx = 0; idx < len; idx++) {
		x = pos[idx][0]; y = pos[idx][1];
		x_dif = pivot[0] - x; y_dif = pivot[1] - y;
		rx = pivot[0] + y_dif; ry = pivot[1] - x_dif;
		if (rx == x && ry == y) {
			continue;
		}
		temp.clear(); temp.push_back(rx); temp.push_back(ry);
		pos.push_back(temp);
		map[temp[0]][temp[1]] = true;
	}
	pivot = pos[len];
	dragon_curve(remain_k - 1, pos, pivot);
}

int main() {
	int answer = 0;
	int x, y, d, k;
	vector<vector<int>> pos;
	vector<int> temp, pivot;
	cin >> N;
	for (int n = 0; n < N; n++) {
		cin >> x >> y >> d >> k;
		temp.clear(); pivot.clear(); pos.clear();
		temp.push_back(x); temp.push_back(y);
		pos.push_back(temp);
		map[temp[0]][temp[1]] = true;
		if (d == 0) {
			pivot.push_back(x + 1); pivot.push_back(y);
		}
		else if (d == 1) {
			pivot.push_back(x); pivot.push_back(y - 1);
		}
		else if (d == 2) {
			pivot.push_back(x - 1); pivot.push_back(y);
		}
		else {
			pivot.push_back(x); pivot.push_back(y + 1);
		}
		pos.push_back(pivot);
		map[pivot[0]][pivot[1]] = true;
		dragon_curve(k, pos, pivot);
	}
	answer = sub_dragon();
	cout << answer << endl;
	return 0;
}
