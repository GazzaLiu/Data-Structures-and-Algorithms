#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

int main (int argc, char* argv[]) {

	int n, m, u, v;
	long long int p;
	vector<long long int> database;

	scanf("%d", &n);
	scanf("%d", &m);

	for (int i = 0; i < n; i++) {
		scanf("%lld", &p);
		database.push_back(p);
	}

	for (int i = 0; i < m; i++) {
		if (scanf("%d%d", &u, &v) == EOF) break;
		long long int sum = 0;
		for (int i = u - 1; i < v; i++) {
			sum += database[i];
		}
		printf("%lld\n", sum);
	}

}