#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

void connect (int* nxt, int* prv, int a, int b) {
	nxt[a] = b;
	prv[b] = a;
}

int main (int argc, char* argv[]) {

	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		int n, m, init;
		long long int rest = 0;
		vector<int> result;
		scanf("%d%d%d", &n, &m, &init);
		int* nxt = new int[n + 3];
		int* prv = new int[n + 3];
		connect(nxt, prv, n + 1, init);
		connect(nxt, prv, init, n + 2);
		for (int j = 0; j < m; j++) {
			int k, a, b, c;
			scanf("%d%d%d%d", &k, &a, &b, &c);
			//cout << k << a << b << c << endl;
			if (k == 1) {
				if (c == 1) {
					connect(nxt, prv, prv[b], a);
					connect(nxt, prv, a, b);
				}
				else {
					connect(nxt, prv, a, nxt[b]);
					connect(nxt, prv, b, a);
				}
			}
			else if (k == 2) {
				connect(nxt, prv, prv[a], nxt[b]);
				connect(nxt, prv, prv[c], a);
				connect(nxt, prv, b, c);
			}
			else {
				int x, y;
				if (c == 1) {
					for (x = a, y = nxt[a]; x <= n && b; x = prv[x], b--) {
						result.push_back(x);
					}
				}
				else {
					for (y = a, x = prv[a]; y <= n && b; y = nxt[y], b--) {
						result.push_back(y);
					}
				}
				rest += b;
				connect(nxt, prv, x, y);
			}
			/*for (int o = 0; o < n + 3; o++) {
				cout << nxt[o] << " ";
			}
			cout << endl;
			for (int o = 0; o < n + 3; o++) {
				cout << prv[o] << " ";
			}
			cout << endl;*/
		}
		printf("%lld\n", rest);
		for (vector<int>::iterator it = result.begin(); it != result.end(); it++) {
			printf("%d\n", *it);
		}
	}

}
