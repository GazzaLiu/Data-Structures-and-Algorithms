#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare (const pair<int, int> &a, const pair<int, int> &b) {
	if (a.first < b.first) {
		return true;
	}
	else if (a.first == b.first) {
		return a.second < b.second;
	}
	else {
		return false;
	}
}

int main (int argc, char* argv[]) {

	int n, m, q;
	scanf("%u%u%u", &n, &m, &q);
	vector<pair<int, int> > record;
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (a > b) swap(a, b);
		record.push_back(make_pair(a, b));
	}
	sort(record.begin(), record.end(), compare);
	for (int i = 0; i < q; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (a > b) swap(a, b);
		if (binary_search(record.begin(), record.end(), make_pair(a, b), compare)) puts("yes");
		else puts("no");
	}

}
