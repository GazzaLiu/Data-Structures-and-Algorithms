#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Edge {
	int point;
	long long int weight;
	bool operator<(const Edge& i) const {
		return weight > i.weight;
	}
};

bool* isInTree;

void Dijkstra (int source, long long int* distance, vector<Edge>* edges) {
	priority_queue<Edge> edgePQ;
	fill(isInTree, isInTree + sizeof(isInTree), false);
	fill(distance, distance + sizeof(distance), numeric_limits<long long int>::max());
	distance[source] = 0;
	struct Edge temp({source, 0});
	edgePQ.push(temp);
	/*while (true) {
		while (!edgePQ.empty() && isInTree[edgePQ.top().point]) {
			edgePQ.pop();
		}
		if (edgePQ.empty()) return;
		int current = edgePQ.top().point;
		isInTree[current] = true;
		for (auto it = edges[current].begin(); it != edges[current].end(); it++) {
			if (!isInTree[it->point] && distance[it->point] > distance[current] + it->weight) {
				edgePQ.push((Edge){it->point, distance[it->point] = distance[current] + it->weight});
			}
		}
	}*/
}

int main (int argc, char* argv[]) {

	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		int n, m, source, target;
		scanf("%d%d", &n, &m);
		scanf("%d%d", &source, &target);
		//cout << n << m << source << target << endl;
		isInTree = new bool[n];
		long long int* distance1 = new long long int[n];
		long long int* distance2 = new long long int[n];
		vector<Edge> graph[n];
		vector<Edge> reversed[n];
		for (int j = 0; j < m; j++) {
			int a, b;
			long long int k;
			scanf("%d%d%lld", &a, &b, &k);
			//cout << a << b << k << endl;
			graph[a].push_back((Edge){b, k});
			reversed[b].push_back((Edge){a, k});
		}
		Dijkstra(source, distance1, graph);
		Dijkstra(target, distance2, reversed);
		long long int ans = numeric_limits<long long int>::max();
		//for ()
	}

}
