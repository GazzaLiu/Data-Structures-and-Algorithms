#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

int binarySearch (vector<int>::iterator low, vector<int>::iterator high, int key) {
	if (low > high) return -1;
	vector<int>::iterator mid = low + floor(distance(low, high) / 2);
	//cout << mid << endl;
	int e = *mid;
	if (key == e) return e;
	else if (key < e) {
		return binarySearch(low, mid - 1, key);
	}
	else {
		return binarySearch(mid + 1, high, key);
	}
}

int main (int argc, char* argv[]) {

	int n, m, w, t, v;
	long long int sum = 0;
	vector<int> database;

	scanf("%d", &n);
	scanf("%d", &m);

	for (int i = 0; i < n; i++) {
		scanf("%d", &w);
		database.push_back(w);
	}
	cout << binarySearch(database.begin(), database.end(), 30000) << endl;

	for (int i = 0; i < m; i++) {
		if (scanf("%d%d", &t, &v) == EOF) break;
		if (t == 1) {
			insert(v);
		}
		else {
			remove(v);
		}
		for (int i = u - 1; i < v; i++) {
			sum += database[i];
		}
	}
	printf("%lld\n", sum);

}