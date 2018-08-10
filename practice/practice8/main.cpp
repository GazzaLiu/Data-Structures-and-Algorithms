#include <stdio.h>
#include <iostream>

using namespace std;

long long int ans;
int* tmp;
int* seq;

void mergesort (int left, int right) {
	if (right - left <= 1) return;
	int middle = (left + right) / 2;
	mergesort(left, middle);
	mergesort(middle, right);
	copy(tmp + left, tmp + right, seq + left);
	int i = left, j = middle, k = left;
	for (; i < middle && j < right; k++) {
		if (seq[j] < seq[i]) {
			tmp[k] = seq[j];
			ans += middle - i;
			j++;
		}
		else {
			tmp[k] = seq[i];
			i++;
		}
	}
	copy(seq + i, seq + middle, tmp + k);
	copy(seq + j, seq + right, tmp + k);
}

int main (int argc, char* argv[]) {

	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		int n;
		scanf("%d", &n);
		ans = 0;
		tmp = new int[n];
		seq = new int[n];
		for (int j = 0; j < n; j++) {
			int a;
			scanf("%d", &a);
			tmp[j] = a;
			//cout << a << " ";
		}
		//cout << endl;
		mergesort(0, n);
		printf("%lld\n", ans);
	}

}
