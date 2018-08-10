#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main (int argc, char* argv[]) {

	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		int n;
		scanf("%d", &n);
		int* sequence = new int[n];
		vector<int> D;
		for (int j = 0; j < n;) {
			int a;
			scanf("%d", &a);
			sequence[j++] = a;
			//cout << a;
		}
		for (int i = 0; i < n; i++) {
			auto it = upper_bound(D.begin(), D.end(), -sequence[i]);
			if (it == D.end()) D.push_back(-sequence[i]);
			else *it = -sequence[i];
		}
		printf("%d\n", (int)D.size());
	}

}
