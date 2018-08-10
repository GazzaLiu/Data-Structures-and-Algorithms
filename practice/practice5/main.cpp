#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

unordered_map<set<int>, int> dis;
queue<set<int> > queue;

void visit (set<int> state, int len) {
	if (n + m - sum(now) == k) {
		printf(len + 1);
		return;
	}
	if (dis.insert({state, len + 1}).second) queue.push(state);
}

void insertVisit (set<int> state, int num, int len) {
	state.insert(num);
	visit(state, len);
	state.erase(state.find(num));
}

int main (int argc, char* argv[]) {

	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		while (true) {
			set<int> now = queue.front();
			next = now;
			queue.pop();
			int hold = n + m - sum(now);
			int len = dis[now];
			if (hold > 0) {
				insertVisit(next, hold, len);
				insertVisit(next, 1, len);
			}
			for () {
				next.erase();
				if (hold > 0) {
					insertVisit(next, i + 1, len)
				}
				next.insert(i);
			}
		}
	}

}
