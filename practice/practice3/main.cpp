#include <stdio.h>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main (int argc, char* argv[]) {

	int n, m;
	scanf("%d%d", &n, &m);
	priority_queue<long long int, vector<long long int>, greater<long long int>> pq;
	for (int i = 0; i < m; i++) {
		pq.push(0);
	}
	//cout << pq.size() << endl;
	for (int i = 0; i < n; i++) {
		long long int req, tmp;
		scanf("%lld", &req);
		//cout << req << endl;
		tmp = pq.top();
		pq.push(tmp + req);
	}
	while (pq.size() > 1) {
		pq.pop();
	}
	//cout << pq.size() << endl;
	printf("%lld", pq.top());

}
